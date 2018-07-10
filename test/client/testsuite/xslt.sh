#!/bin/bash

# test framework
source $(dirname "$0")/framework_test.sh

# test xslt empty input
define srcml <<- 'STDOUT'
	<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
	<unit xmlns="http://www.srcML.org/srcML/src" xmlns:cpp="http://www.srcML.org/srcML/cpp" revision="REVISION" language="C++"/>
	STDOUT

define copyxslt <<- 'STDOUT'
	<xsl:stylesheet
	xmlns="http://www.srcML.org/srcML/src"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns:cpp="http://www.srcML.org/srcML/cpp"
	version="1.0">

	<!--
	copy.xsl

	Identity transformation.

	Michael L. Collard
	collard@uakron.edu
	-->

	<xsl:output method="xml" version="1.0" encoding="UTF-8" standalone="yes"/>

	<xsl:template match="@*|node()"><xsl:copy><xsl:apply-templates select="@*|node()"/></xsl:copy></xsl:template>

	</xsl:stylesheet>
	STDOUT

define setlanguage <<- 'STDOUT'
	<xsl:stylesheet
	xmlns="http://www.srcML.org/srcML/src"
	xmlns:src="http://www.srcML.org/srcML/src"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns:cpp="http://www.srcML.org/srcML/cpp"
	version="1.0">

	<!--
	setlanguage.xsl

	Identity transformation.

	Michael L. Collard
	collard@uakron.edu
	-->

	<xsl:output method="xml" version="1.0" encoding="UTF-8" standalone="yes"/>

	<xsl:param name="language"/>

	<xsl:template match="src:unit/@language"><xsl:attribute name="language"><xsl:value-of select="$language"/></xsl:attribute></xsl:template>

	<xsl:template match="@*|node()"><xsl:copy><xsl:apply-templates select="@*|node()"/></xsl:copy></xsl:template>

	</xsl:stylesheet>
	STDOUT

define srcml <<- 'STDOUT'
	<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
	<unit xmlns="http://www.srcML.org/srcML/src" xmlns:cpp="http://www.srcML.org/srcML/cpp" revision="REVISION" language="C++"/>
	STDOUT

define srcmljava <<- 'STDOUT'
	<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
	<unit xmlns="http://www.srcML.org/srcML/src" xmlns:cpp="http://www.srcML.org/srcML/cpp" revision="REVISION" language="Java"/>
	STDOUT

xmlcheck "$srcml"
createfile sub/a.cpp.xml "$srcml"
createfile copy.xsl "$copyxslt"
createfile setlanguage.xsl "$setlanguage"

# xslt copy xpathparam NAME=VALUE
srcml --xslt=copy.xsl --xpathparam 'NAME=VALUE' sub/a.cpp.xml
check "$srcml"

srcml --xslt=copy.xsl --xpathparam 'NAME=VALUE' < sub/a.cpp.xml
check "$srcml"

srcml --xslt=copy.xsl --xpathparam 'NAME=VALUE' sub/a.cpp.xml -o sub/b.cpp.xml
check sub/b.cpp.xml "$srcml"

srcml --xslt=copy.xsl --xpathparam 'NAME=VALUE' -o sub/b.cpp.xml sub/a.cpp.xml
check sub/b.cpp.xml "$srcml"

srcml --xslt=copy.xsl --xpathparam 'NAME=VALUE' -o sub/b.cpp.xml < sub/a.cpp.xml
check sub/b.cpp.xml "$srcml"


# xslt copy xpathparam name="a"
srcml --xslt=copy.xsl --xpathparam 'name="a"' sub/a.cpp.xml
check "$srcml"

srcml --xslt=copy.xsl --xpathparam 'name="a"' < sub/a.cpp.xml
check "$srcml"

srcml --xslt=copy.xsl --xpathparam 'name="a"' sub/a.cpp.xml -o sub/b.cpp.xml
check sub/b.cpp.xml "$srcml"

srcml --xslt=copy.xsl --xpathparam 'name="a"' -o sub/b.cpp.xml sub/a.cpp.xml
check sub/b.cpp.xml "$srcml"

srcml --xslt=copy.xsl --xpathparam 'name="a"' -o sub/b.cpp.xml < sub/a.cpp.xml
check sub/b.cpp.xml "$srcml"


srcml --xslt=setlanguage.xsl --xpathparam 'language="Java"' sub/a.cpp.xml
check "$srcmljava"

srcml --xslt=setlanguage.xsl --xpathparam 'language="Java"' < sub/a.cpp.xml
check "$srcmljava"

srcml --xslt=setlanguage.xsl --xpathparam 'language="Java"' sub/a.cpp.xml -o sub/b.java.xml
check sub/b.java.xml "$srcmljava"

srcml --xslt=setlanguage.xsl --xpathparam 'language="Java"' -o sub/b.java.xml sub/a.cpp.xml
check sub/b.java.xml "$srcmljava"

srcml --xslt=setlanguage.xsl --xpathparam 'language="Java"' -o sub/b.java.xml < sub/a.cpp.xml
check sub/b.java.xml "$srcmljava"


