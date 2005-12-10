#! /bin/sh

# This document turns the provided xml file into a png image
# For this, the programs xsltproc, latex and dvipng are required

# test that there is one argument and that it ends with ".xml"
# ....

# set variables
EXEDIR=`dirname $0`
DOCDIR=`dirname $1`
cd $DOCDIR
XMLFILE=$1
TEXFILE=$1.tex
LOGFILE=$1.log
AUXFILE=$1.aux
DVIFILE=$1.dvi
PNGFILE=$1.png
MMLTEXXSL=$EXEDIR/mmltex.xsl
echo $MMLTEXXSL > /tmp/out

# process the xml file
echo '\documentclass{article}' > $TEXFILE
echo '\pagestyle{empty}' >> $TEXFILE
echo '\begin{document}' >> $TEXFILE
xsltproc $MMLTEXXSL $XMLFILE >> $TEXFILE
echo '\end{document}' >> $TEXFILE

# create dvi file
pdfetex -progname latex -interaction nonstopmode $TEXFILE 
dvipng -D 150 -o $PNGFILE $DVIFILE

# cleanup
rm $XMLFILE $TEXFILE $LOGFILE $AUXFILE $DVIFILE

cd -
