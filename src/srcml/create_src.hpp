/**
 * @file create_src.hpp
 *
 * @copyright @copyright Copyright (C) 2014 SDML (www.srcML.org)
 *
 * This file is part of the srcML Toolkit.
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
 * along with the srcML Toolkit; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef CREATE_SRC_HPP
#define CREATE_SRC_HPP

#include <srcml_cli.hpp>
#include <srcml_input_src.hpp>
#include <string>
#include <boost/optional.hpp>

// create srcml from the current request
void create_src(srcml_input_t& input_sources,
                srcml_request_t& srcml_request,
                boost::optional<FILE*>,
                boost::optional<int>);

#endif
