<?xml version="1.0"  encoding="UTF-8"?>
<xsl:stylesheet version = '1.0' 
     xmlns:xsl='http://www.w3.org/1999/XSL/Transform'
     xmlns:xs='http://www.w3.org/2001/XMLSchema'>
<xsl:output method="text"/>
<xsl:strip-space elements="*"/>

<xsl:template match="//xs:include">
 <xsl:apply-templates select="document(@schemaLocation)"/>
</xsl:template>

<!-- ignore annotation elements -->
<xsl:template match="//xs:annotation"/>

<!-- print all the enumeration values and the attribute
     they belong to -->
<xsl:template match="xs:enumeration">
<xsl:if test="../../../@name">
<xsl:value-of select="../../../@name"/><xsl:text>	</xsl:text><xsl:value-of select="@value"/><xsl:text>
</xsl:text>
</xsl:if>
</xsl:template>

</xsl:stylesheet>

