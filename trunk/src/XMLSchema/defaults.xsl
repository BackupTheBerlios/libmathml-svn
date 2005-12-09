<?xml version="1.0"?>
<xsl:stylesheet version="1.0"
                xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                xmlns:xs="http://www.w3.org/2001/XMLSchema">
<xsl:strip-space elements="*"/>

<xsl:variable name="includes" select="/xs:schema/xs:include/@schemaLocation"/>
<xsl:variable name="elements" select="document($includes)//*"/>

<!-- match the root element of the schema elements -->
<xsl:template match="/xs:schema">
 <xsl:apply-templates select="$includes"/>
 <xsl:for-each select="$includes">
  <xsl:value-of select="self"/>
 </xsl:for-each>
 <xsl:for-each select="$elements">
  <xsl:value-of select="self/@name"/>
 </xsl:for-each>
 
</xsl:template>

<xsl:template match="xs:include">
 hello
 <xsl:variable name="include" select="document(@schemaLocation)"/>
</xsl:template>

<xsl:template match="xs:schema">
hi
</xsl:template>

<xsl:template match="xs:element">
  +<xsl:value-of select="@name"/>
  -<xsl:apply-templates select="//xs:attribute"/>
</xsl:template>

<xsl:template match="xs:attribute">
 <xsl:if test="@default">
  <xsl:value-of select="@name"/>
  =
  <xsl:value-of select="@default"/>
  --
  </xsl:if>
</xsl:template>


</xsl:stylesheet>

