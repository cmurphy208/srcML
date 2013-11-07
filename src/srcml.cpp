/*
  srcml.cpp

  Copyright (C) 2013  SDML (www.srcML.org)

  This file is part of the srcML Toolkit.

  The srcML Toolkit is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  The srcML Toolkit is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with the srcML Toolkit; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

/*
  The srcml program to transform to/from the srcML format, plus provides a variety of
  querying and transformation features.

  Replaces the src2srcml and srcml2src of the original srcML toolkit.
*/

#include "libsrcml/srcml.h"
#include <srcmlCLI.hpp>
#include <thread_queue.hpp>

#include <archive.h>
#include <archive_entry.h>
//#include <curl/curl.h>
#include <pthread.h>

#include <iostream>
#include <string>

struct ParseRequest {
    ParseRequest() : buffer(0) {}

    void swap(ParseRequest& other) {

        filename.swap(other.filename);
        buffer.swap(other.buffer);
    }

    // empty ParseRequests indicate termination
    bool empty() const {
        return filename.empty() && buffer.empty();
    }

    std::string filename;
    std::vector<char> buffer;
};

ParseRequest NullParseRequest;

bool checkLocalFile(const std::string& pos_arg) {
  FILE * local;
  if(pos_arg.find("http:") == std::string::npos){
    local = fopen(pos_arg.c_str(),"r");
    if (local == NULL) {
      std::cerr << "File " << pos_arg << " not found.\n";
      return false;
    }
    fclose(local);
  }
  return true;
}

int main(int argc, char * argv[]) {
  
  srcml_request_t srcml_request = srcmlCLI::parseCLI(argc, argv);

  // CHECK FOR INVALID GLOBAL FLAGS
  if (srcml_request.encoding != "" && srcml_check_encoding(srcml_request.encoding.c_str()) == 0) {
    std::cerr << "Invalid Encoding.\n";
    return 1; //ERROR CODE TBD
  }
  if (srcml_request.language != "" && srcml_check_language(srcml_request.language.c_str()) == 0) {
    //INVALID OPTION
    std::cerr << "Invalid Language.\n";
    return 1; //ERROR CODE TBD
  }
  if (srcml_request.tabs <= 0) {
    //INVALID OPTION
    std::cerr << "Invalid Tab Stop.\n";
    return 1; //ERROR CODE TBD
  }
  
  // SET GLOBAL OPTIONS
  srcml_set_encoding(srcml_request.encoding.c_str());
  srcml_set_filename(srcml_request.filename.c_str());
  srcml_set_directory(srcml_request.directory.c_str());
  srcml_set_version(srcml_request.src_versions.c_str());
  srcml_set_tabstop(srcml_request.tabs);
  srcml_set_all_options(srcml_request.markup_options);

  if (srcml_request.language != "") {
    srcml_set_language(srcml_request.language.c_str());  
  }
  else {
    srcml_set_language(SRCML_LANGUAGE_NONE);  
  }

  for(int i = 0; i < srcml_request.register_ext.size(); ++i) {
    int pos = srcml_request.register_ext[i].find('=');
    srcml_register_file_extension(srcml_request.register_ext[i].substr(0,pos).c_str(),
          srcml_request.register_ext[i].substr(pos+1).c_str());
  }

  for(int i = 0; i < srcml_request.xmlns_prefix.size(); ++i) {
    int pos = srcml_request.xmlns_prefix[i].find('=');
    srcml_register_namespace(srcml_request.xmlns_prefix[i].substr(0,pos).c_str(),
           srcml_request.xmlns_prefix[i].substr(pos+1).c_str());
  }

  /* 
    MIGHT USE THIS LATER:
    CHECK TO SEE WHAT VERSION OF LIBARCHIVE IS RUNNING
    SWITCH ON FEATURES (LIBARCHIVE FOR DIRECTORY, ETC.)
    #if ARCHIVE_VERSION_NUMBER < 3000000
      //YOU HAVE V2 OR LOWER
    #else
      //YOU HAVE V3 OR HIGHER
    #endif
  */

  ThreadQueue<ParseRequest, 10> queue;
  
  if (srcml_request.positional_args.empty()) {
    std::cerr << "No input files found.\n";
    return 0;
  }
  
  for (int i = 0; i < srcml_request.positional_args.size(); ++i) {
    if (!checkLocalFile(srcml_request.positional_args[i]))
      return 1;
  } 

  if (srcml_request.positional_args.size() == 1) {
    srcml(srcml_request.positional_args[0].c_str(), srcml_request.output.c_str());
    return 0;
  }

  /* create a new srcml archive structure */
  srcml_archive * archive = srcml_create_archive();

  /* open a srcML archive for output */
  srcml_write_open_filename(archive, srcml_request.output.c_str());

  /* add all the files to the archive */
  for(int i = 0; i < srcml_request.positional_args.size(); ++i) {
    srcml_unit * unit = srcml_create_unit(archive);
    srcml_unit_set_filename(unit, srcml_request.positional_args[i].c_str());

    /* Translate to srcml and append to the archive */
    srcml_parse_unit_filename(unit, srcml_request.positional_args[i].c_str());

    /* Translate to srcml and append to the archive */
    srcml_write_unit(archive, unit);
    srcml_free_unit(unit);
  }

  /* close the srcML archive */
  srcml_close_archive(archive);

  /* free the srcML archive data */
  srcml_free_archive(archive);

  return 0;
}
