#!/bin/bash

# test framework
source $(dirname "$0")/framework_test.sh

# test
define srcml <<- 'STDOUT'
	<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
	<unit xmlns="http://www.sdml.info/srcML/src" xmlns:cpp="http://www.sdml.info/srcML/cpp" revision="REVISION" language="C++">
	</unit>
	STDOUT

define srcmlout <<- 'STDOUT'
	<unit xmlns="http://www.sdml.info/srcML/src" xmlns:cpp="http://www.sdml.info/srcML/cpp" revision="REVISION" language="C++">
	</unit>
	STDOUT

srcml2src -X --no-xml-declaration -o sub/a.cpp.xml <<< "$srcml"

check sub/a.cpp.xml 3<<< "$srcmlout"

srcml2src --no-xml-declaration <<< "$srcml"

check sub/a.cpp.xml 3<<< "$srcmlout"
