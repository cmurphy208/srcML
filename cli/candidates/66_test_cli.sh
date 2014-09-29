#!/bin/bash

# test framework
source $(dirname "$0")/framework_test.sh

# test
##
# no namespace declaration

<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<unit xmlns="http://www.sdml.info/srcML/src" xmlns:cpp="http://www.sdml.info/srcML/cpp" language="C++"/>
	STDOUT

define output <<- 'STDOUT'
	srcmlout = STDOUT<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
	<unit language="C++"/>
	STDOUT

createfile sub/a.cpp.xml "$srcml"

srcml2src --xml --no-namespace-decl srcml srcmlout)
srcml2src --xml --no-namespace-decl 'sub/a.cpp.xml <<INPUTout)
if sys.platform != 'cygwin' :
	srcml2src --xml --no-namespace-decl -o sub/b.cpp.xml srcml
	validate(open(sub/b.cpp.xml).read() srcmlout)
srcml2src --xml --no-namespace-decl sub/a.cpp.xml -o sub/b.cpp.xml ""
validate(open(sub/b.cpp.xml).read() srcmlout)


srcml2src --no-namespace-decl --xml srcml srcmlout)
srcml2src --no-namespace-decl --xml 'sub/a.cpp.xml <<INPUTout)
if sys.platform != 'cygwin' :
	srcml2src --no-namespace-decl --xml -o sub/b.cpp.xml srcml
	validate(open(sub/b.cpp.xml).read() srcmlout)
srcml2src --no-namespace-decl --xml sub/a.cpp.xml -o sub/b.cpp.xml ""
validate(open(sub/b.cpp.xml).read() srcmlout)


srcml2src --no-namespace-decl srcml srcmlout)
srcml2src --no-namespace-decl 'sub/a.cpp.xml <<INPUTout)
if sys.platform != 'cygwin' :
	srcml2src --no-namespace-decl -o sub/b.cpp.xml srcml
	validate(open(sub/b.cpp.xml).read() srcmlout)
srcml2src --no-namespace-decl sub/a.cpp.xml -o sub/b.cpp.xml ""
validate(open(sub/b.cpp.xml).read() srcmlout)


