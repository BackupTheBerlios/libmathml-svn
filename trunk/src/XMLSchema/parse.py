#! /usr/bin/python
import sys
from xml.dom.ext.reader.Sax2 import FromXmlStream

def read(filename, donelist):
	# read file if it not in the donelist
	if (not donelist.contains(filename)):
		donelist.append(filename)
		print ("hi")
		fd = open()
		doc = FromXmlStream(fd)
		for node in doc.getElementsByTagName("xs:include"):
			if (node.nodeType == node.ELEMENT_NODE):
				print node.tagName

donelist = []
read("mathml2/mathml2.xsd", donelist)
read("mathml2/mathml2.xsd", donelist)
read("mathml2/mathml2.xsd", donelist)
