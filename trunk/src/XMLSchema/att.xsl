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


<xsl:template match="xs:attribute">
<xsl:value-of select="@name"/>:<xsl:value-of select="@type"/><xsl:text>
</xsl:text>
<xsl:apply-templates/>&lt;
</xsl:template>

<xsl:template match="xs:attribute/xs:simpleType">
<xsl:apply-templates/>
</xsl:template>

<xsl:template match='xs:union'> union:<xsl:value-of select="@memberTypes"/><xsl:text>
</xsl:text>
</xsl:template>

<xsl:template match='xs:attribute//xs:pattern'> pattern:<xsl:value-of select="@value"/><xsl:text>
</xsl:text>
</xsl:template>

</xsl:stylesheet>

