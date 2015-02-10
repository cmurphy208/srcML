#!/bin/bash

# test framework
source $(dirname "$0")/framework_test.sh

# test get src version
define input <<- 'STDOUT'
	<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
	<unit xmlns="http://www.sdml.info/srcML/src" xmlns:cpp="http://www.sdml.info/srcML/cpp" revision="REVISION" language="C++" directory="bar" filename="foo" version="1.2"/>
	STDOUT

createfile sub/a.cpp.xml "$input"
message "version provided"

srcml --show-src-version sub/a.cpp.xml
check 3<<< "1.2"

srcml --show-src-version < sub/a.cpp.xml
check 3<<< "1.2"

define empty <<- 'STDIN'
	<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
	<unit xmlns="http://www.sdml.info/srcML/src" xmlns:cpp="http://www.sdml.info/srcML/cpp" revision="REVISION" language="" directory="" filename="" version=""/>
	STDIN

createfile sub/a.cpp.xml "$empty"
message "version empty"

srcml --show-src-version sub/a.cpp.xml
check 3<<< ""

srcml --show-src-version < sub/a.cpp.xml
check 3<<< ""

define none <<- 'STDIN'
	<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
	<unit xmlns="http://www.sdml.info/srcML/src" xmlns:cpp="http://www.sdml.info/srcML/cpp"/>
	STDIN

createfile sub/a.cpp.xml "$none"
message "version not provided"

srcml --show-src-version sub/a.cpp.xml
check_null

srcml --show-src-version < sub/a.cpp.xml
check_null

