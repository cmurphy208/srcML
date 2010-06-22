/*
  srcMLTranslator.cpp

  Copyright (C) 2004-2006  SDML (www.sdml.info)

  This file is part of the srcML translator.

  The srcML translator is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  The srcML translator is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with the srcML translator; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

  Class for straightforward translation from source code to srcML
*/

#include "srcMLTranslator.h"
#include "KeywordCPPLexer.hpp"
#include "srcMLParser.hpp"
#include "StreamMLParser.h"
#include "srcMLOutput.h"
#include "srcmlns.h"

// constructor
srcMLTranslator::srcMLTranslator(int language,                // programming language of source code
				 const char* src_encoding,    // text encoding of source code
				 const char* xml_encoding,    // xml encoding of result srcML file
				 const char* srcml_filename,  // filename of result srcML file
				 int op,
				 const char* directory,       // 
				 const char* filename,        // 
				 const char* version,         //
				 const char* uri[]
				 )
  : Language(language), encoding(src_encoding), options(op),
    out(0, srcml_filename, getLanguageString(), xml_encoding, options, uri), ifilename(0) {

  // root unit for compound srcML documents
  if ((options & OPTION_NESTED) > 0)
    out.startUnit(getLanguageString(), directory, filename, version, true);
}

// setup the input source based on the filename
void srcMLTranslator::setupInput(const char* src_filename) {

  // cache filename for later
  ifilename = strdup(src_filename);
}

// translate from input stream to output stream
void srcMLTranslator::translate(const char* unit_directory,
				const char* unit_filename, const char* unit_version,
				int language) {

  try {

      // master lexer with multiple streams
      antlr::TokenStreamSelector selector;

      // srcML lexical analyzer from standard input
      KeywordCPPLexer lexer(ifilename, encoding, language);
      lexer.setSelector(&selector);

      // pure block comment lexer
      PureCommentLexer textlexer(lexer.getInputState());
      textlexer.setSelector(&selector);

      // switching between lexers
      selector.addInputStream(&lexer, "main");
      selector.addInputStream(&textlexer, "text");
      selector.select(&lexer);

      // base stream parser srcML connected to lexical analyzer
      StreamMLParser<srcMLParser> parser(selector, language, options);

      // connect local parser to attribute for output
      out.setTokenStream(parser);

      // parse and form srcML output with unit attributes
      out.consume(unit_directory, unit_filename, unit_version);

      // done with filename
      free(ifilename);

  } catch (const std::exception& e) {
    free(ifilename);
    fprintf(stderr, "SRCML Exception: %s\n", e.what());
  }
  catch (UTF8FileError) {
    free(ifilename);
    throw FileError();
  }
  catch (...) {
    fprintf(stderr, "ERROR\n");
  }
}

// destructor
srcMLTranslator::~srcMLTranslator() {}
