#!/bin/bash

# test framework
source $(dirname "$0")/framework_test.sh


# test metadata options with xml and unit

define nestedfileextra <<- 'STDOUT'
	<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
	<unit xmlns="http://www.sdml.info/srcML/src" revision="REVISION">

	<unit xmlns:cpp="http://www.sdml.info/srcML/cpp" revision="REVISION" language="C++" directory="sub" filename="a.cpp">
	<expr_stmt><expr><name>a</name></expr>;</expr_stmt>
	</unit>

	<unit xmlns:cpp="http://www.sdml.info/srcML/cpp" revision="REVISION" language="Java" directory="emptysrc" filename="empty.java">
	<expr_stmt><expr><name>b</name></expr>;</expr_stmt>
	</unit>

	</unit>
	STDOUT

createfile sub/a.cpp.xml "$nestedfileextra"

srcml -X --unit "1" --show-language sub/a.cpp.xml
check 3<<< "C++"

srcml -X --unit "1" --show-directory sub/a.cpp.xml
check 3<<< "sub"

srcml -X --unit "1" --show-filename sub/a.cpp.xml
check 3<<< "a.cpp"

srcml -X --unit "2" --show-language sub/a.cpp.xml
check 3<<< "Java"

srcml -X --unit "2" --show-directory sub/a.cpp.xml
check 3<<< "emptysrc"

srcml -X --unit "2" --show-filename sub/a.cpp.xml
check 3<<< "empty.java"
