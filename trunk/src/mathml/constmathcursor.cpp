/***************************************************************************
 *   Copyright (C) 2004 by Jos van den Oever                               *
 *   jos@vandenoever.info                                                  *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include "constmathcursor.h"
#include "mathcursor.h"

ConstMathCursor::ConstMathCursor(MathCursor *m)
	: mc(m) {
}
const MMLNode *
ConstMathCursor::movePrevious() {
	return mc->movePrevious();
}
const MMLNode *
ConstMathCursor::moveNext() {
	return mc->moveNext();
}
const MMLNode *
ConstMathCursor::moveUp() {
	return mc->moveUp();
}
const MMLNode *
ConstMathCursor::moveDown() {
	return mc->moveDown();
}
const MMLNode *
ConstMathCursor::moveRight() {
	return mc->moveRight();
}
const MMLNode *
ConstMathCursor::moveLeft() {
	return mc->moveLeft();
}
bool
ConstMathCursor::moveTo(float x, float y) {
	return mc->moveTo(x, y);
}
void
ConstMathCursor::selectNext() {
	mc->selectNext();
}
void
ConstMathCursor::selectPrevious() {
	mc->selectPrevious();
}
bool
ConstMathCursor::selectTo(float x, float y) {
	return mc->selectTo(x, y);
}
const MMLNode *
ConstMathCursor::container() const {
	return mc->container();
}
long
ConstMathCursor::offset() const {
	return mc->offset();
}
const MMLNode *
ConstMathCursor::leftNode() const {
	return mc->leftNode();
}
const MMLNode *
ConstMathCursor::rightNode() const {
	return mc->rightNode();
}
void
ConstMathCursor::setBeforeNode(MMLNode *n) {
	mc->setBeforeNode(n);
}
void
ConstMathCursor::setAfterNode(MMLNode *n) {
	mc->setAfterNode(n);
}
int
ConstMathCursor::nearness(const MMLNode *n) const {
	return mc->nearness(n);
}
bool
ConstMathCursor::isSelected(const MMLNode *n) const {
	return mc->isSelected(n);
}
bool
ConstMathCursor::collapsed() const {
	return mc->collapsed();
}
