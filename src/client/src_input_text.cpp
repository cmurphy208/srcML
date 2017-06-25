/**
 * @file src_input_text.cpp
 *
 * @copyright Copyright (C) 2015 srcML, LLC. (www.srcML.org)
 *
 * This file is part of the srcml command-line client.
 *
 * The srcML Toolkit is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * The srcML Toolkit is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with the srcml command-line client; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <src_input_text.hpp>
#include <srcml_options.hpp>
#include <src_input_libarchive.hpp>
#include <src_prefix.hpp>
#include <ctype.h>

static int hex2decimal(unsigned char c) {

    switch (c) {
        case 'a':
        case 'A': return 10;
        case 'b':
        case 'B': return 11;
        case 'c':
        case 'C': return 12;
        case 'd':
        case 'D': return 13;
        case 'e':
        case 'E': return 14;
        case 'f':
        case 'F': return 15;
        default: return c - '0';
    }
}

static bool isodigit(char c) {
    return c >= '0' && c <= '7';
}

// Convert input to a ParseRequest and assign request to the processing queue
 int src_input_text(ParseQueue& queue,
 	srcml_archive* srcml_arch,
 	const srcml_request_t& srcml_request,
 	const std::string& input_file) {

    // form the parsing request
 	ParseRequest* prequest = new ParseRequest;

 	if (srcml_request.command & SRCML_COMMAND_NOARCHIVE)
 		prequest->disk_dir = srcml_request.output_filename;

    prequest->filename = srcml_request.att_filename;
 	prequest->url = srcml_request.att_url;
 	prequest->version = srcml_request.att_version;
 	prequest->srcml_arch = srcml_arch;
 	prequest->language = srcml_request.att_language ? *srcml_request.att_language : "";
    prequest->total_num_inputs = srcml_request.input_sources.size();

    prequest->status = 0; //!language.empty() ? 0 : SRCML_STATUS_UNSET_LANGUAGE;

    std::string raw_text = src_prefix_resource(input_file);
    prequest->loc = 0;

    // fill up the parse request buffer
    if (!prequest->status) {
    	// copy from the text directly into a buffer
    	// perform newline and tab expansion
    	// TODO: Make test cases for each part
    	// TODO: Support \nnn, \xnnn, \unnn, \Unnnnnnnn

        const char* ptext = raw_text.c_str();
        while (ptext) {

            // find up to an escape
            const char* epos = strchr(ptext, '\\');
            if (!epos) {
                break;
            }
            // append up to the special char
            prequest->buffer.insert(prequest->buffer.end(), ptext, epos);

            // append the special character
            ++epos;
            switch (*epos) {
            case 'n':
                prequest->buffer.push_back('\n');
                ++prequest->loc;
                break;
            case 't':
                prequest->buffer.push_back('\t');
                break;
            case 'f':
                prequest->buffer.push_back('\f');
                break;
            case 'a':
                prequest->buffer.push_back('\a');
                break;
            case 'b':
                prequest->buffer.push_back('\b');
                break;
            /* \e not directly supported in C, but echo command does */
            case 'e':
                prequest->buffer.push_back('\x1B');
                break;
            case 'r':
                prequest->buffer.push_back('\r');
                break;
            case 'v':
                prequest->buffer.push_back('\v');
                break;
            // byte with hex value from 1 to 2 charcters
            case 'x':
            {
                int value = 0;
                int offset = 0;
                while (offset < 2 && isxdigit(*(epos + offset + 1))) {
                    value = hex2decimal(*(epos + offset + 1)) + 16 * value;
                    ++offset;
                }
                if (offset == 0) {
                    prequest->buffer.push_back('\\');
                    prequest->buffer.push_back('x');
                    break;
                }

                prequest->buffer.push_back(value);
                epos += offset;
                break;
            }
            // byte with octal value from 1 to 3 characters
            case '0':
            {
                int value = 0;
                int offset = 0;
                while (offset < 3 && isodigit(*(epos + offset + 1))) {
                    value = (*(epos + offset + 1) - '0') + 8 * value;
                    ++offset;
                }
                if (offset == 0) {
                    prequest->buffer.push_back('\\');
                    prequest->buffer.push_back('0');
                    break;
                }

                prequest->buffer.push_back(value);
                epos += offset;
                break;
            }
            default:
                prequest->buffer.push_back('\\');
            }
            ptext = epos + 1;
        }

        // finished with no '\\' remaining, so flush buffer
        prequest->buffer.insert(prequest->buffer.end(), ptext, ptext + strlen(ptext));
    }

    // schedule for parsing
    queue.schedule(prequest);

    return 1;
}
