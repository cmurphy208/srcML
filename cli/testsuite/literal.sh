#!/bin/bash

# test framework
source $(dirname "$0")/framework_test.sh

# src2srcml Markup Extensions

createfile sub/a.cpp ""

define sfilelit <<- 'STDOUT'
	<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
	<unit xmlns="http://www.sdml.info/srcML/src" xmlns:cpp="http://www.sdml.info/srcML/cpp" revision="REVISION" language="C++" filename="sub/a.cpp"/>
	STDOUT

define output <<- 'STDOUT'
	<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
	<unit xmlns="http://www.sdml.info/srcML/src" xmlns:cpp="http://www.sdml.info/srcML/cpp" revision="REVISION" language="C++"/>
	STDOUT

echo -n "" | src2srcml -l C++ --literal

check 3<<< "$output"

src2srcml --literal sub/a.cpp  -o sub/a.cpp.xml

check sub/a.cpp.xml 3<<< "$sfilelit"

echo -n "" | src2srcml -l C++ --literal -o sub/a.cpp.xml

check sub/a.cpp.xml 3<<< "$output"

src2srcml --literal sub/a.cpp -o sub/a.cpp.xml

check sub/a.cpp.xml 3<<< "$sfilelit"
