/**
 * @file srcml_consume.hpp
 *
 * @copyright Copyright (C) 2014-2019 srcML, LLC. (www.srcML.org)
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
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#ifndef SRCML_EXECUTE_HPP
#define SRCML_EXECUTE_HPP

#include <srcml_cli.hpp>
#include <srcml_input_src.hpp>
#include <list>

// has to be a typedef for older gcc compilers
typedef void (*process_srcml)(const srcml_request_t& srcml_request, const srcml_input_t& input_sources, const srcml_output_dest& destination);

typedef std::list<process_srcml> processing_steps_t;

void srcml_execute(const srcml_request_t& srcml_request,
                   processing_steps_t& processing_steps,
                   const srcml_input_t& input_sources,
                   const srcml_output_dest& output);

#endif
