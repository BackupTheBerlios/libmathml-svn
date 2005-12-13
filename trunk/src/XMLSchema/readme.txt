Qmathml

A large part of qmathml's code is generated from the MathML schema.
Two files are generated from the MathML schema: mathml.h and mathml.cpp.
These files define the elements and attributes that are allowed in mathml.

The enumeration Element lists all possible elements.
The enumeration AttributeType lists all allowed types for the attributes.
The enumeration Attribute lists all allowed attributes.
The class MMLAttribute is the base class for all MathML attributes.
For each existing attribute type, a subclass from MMLAtribute is created.

For each existing element, an enumeration is created that enumerates the attributes in the element.

The class MathML

The array elementTag contains the tags of all elements. E.g.
MathML::elementTag[POWER] = "power"

The same is true for the array attList:
MathML::attributeTag[BACKGROUND] = "background"

The array attList contains an array for each element. This array lists
the attributes in this element. You can print all attributes of the element mn as follows:
for (short i=0; i<MathML::mnNumAtts; ++i) {
	cout << MathML::attributeTag[attList[MN][i]] << endl;
}

instead of using MathML::mnNumAtts, you can use the more general
MathML::attListLen[MN]

Now you generally print the attributes of the arbitrary element e:
for (short i=0; i<MathML::attListLen[e]; ++i) {
	cout << MathML::attributeTag[attList[e][i]] << endl;
}

The function MathML::createAttribute(const char *attributeName,
	const DOMString &value, Element e, MMLAttribute **att) is a
general function for creating a new attribute with name attributeName.
New memory for an attribute is allocated and the attribute is pointed to
by a new pointer in the array att.
The attribute is initialized with the value 'value'. For e.g. an attribute of type bool, the function MMLAttribute *createBOOL(Attribute a, const DOMString &v) is called.


The class Attributes

This class defines the current environment. It contains an array with pointers to objects of class AttributeType. If the pointer is 0, the attribute is not set and if it is not 0, then it is set or its default value is defined.

When laying out or painting an equation, the Attributes object is passed
to the element to be layed out. If it requires a value of on of its
attributes, it checks if this attribute is defined in this element.
If it is, this value is used. If it is not defined, the element checks
the Attributes object for a value of the attribute.

When the element passes the Attributes element to its children, it
replaces the pointers to the attributes for which it has a value with
those of its own. Each attribute must have a default value, either set by
the element or the environment.
When the childeren are done with the Attributes object,
the element restores the pointers in the Attributes object.
The setting and unsetting of these values is done by calling the function
Attributes::setAttributes.
Each element has an array with set values:
defatt[MathML::attListLen[e]]
an array that stores the incomming values fromthe Attributes object:
envatt[MathML::attListLen[e]]



Special attributes

Some attributes have more than one definitions. These attributes require special attention and are listed here. (The list is not yet guaranteed to be complete.)

width
occurs in:
mtable as "auto | number h-unit"
mspace as "number h-unit | namedspace"
mpadded as "[ + | - ] unsigned-number ( % [ pseudo-unit ] | pseudo-unit | h-unit | namedspace )"
