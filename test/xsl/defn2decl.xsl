<xsl:stylesheet
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns:src="http://www.sdml.info/srcML/src"
	xmlns:cpp="http://www.sdml.info/srcML/cpp"
	xmlns:str="http://exslt.org/strings"
	xmlns:func="http://exslt.org/functions"
	xmlns:exsl="http://exslt.org/common"
	extension-element-prefixes="str exsl func"
	exclude-result-prefixes="src"
	version="1.0">

<!--
	defn2decl.xsl

	Converts srcML function definitions to function declarations

	Michael L. Collard
	collard@cs.kent.edu
-->

<xsl:import href="str.replace.function.xsl"/>

<xsl:output method="xml" omit-xml-declaration="no" version="1.0" encoding="ISO-8859-1"/>

<!-- change the directory attribute on any unit from "if" to "while" -->
<xsl:template match="src:unit/@dir">
	<xsl:attribute name="dir">
		<xsl:value-of select="str:replace(., 'function', 'function_decl')"/>
	</xsl:attribute>
</xsl:template>

<!-- change the function element to a function declaration element -->
<xsl:template match="src:function">
	<src:function_decl>
		<xsl:apply-templates select="*|@*|text()"/>
	</src:function_decl>
</xsl:template>

<!-- change the if keyword to a while keyword -->
<xsl:template match="src:function/src:block">
	<xsl:text>;</xsl:text>
</xsl:template>

<!-- default identity copy -->
<xsl:template match="@*|node()">
	<xsl:copy>
	  <xsl:apply-templates select="@*|node()"/>
	</xsl:copy>
</xsl:template>

</xsl:stylesheet>
