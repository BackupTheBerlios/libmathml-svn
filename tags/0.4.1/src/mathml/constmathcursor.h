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

#ifndef CONSTMATHCURSOR_H
#define CONSTMATHCURSOR_H

class MathCursor;
class MMLNode;

class ConstMathCursor {
public:
    ConstMathCursor(MathCursor *mc);
    const MMLNode *movePrevious();
    const MMLNode *moveNext();
    const MMLNode *moveUp();
    const MMLNode *moveDown();
    const MMLNode *moveRight();
    const MMLNode *moveLeft();
    bool moveTo(float, float);
    void selectNext();
    void selectPrevious();
    bool selectTo(float, float);
    const MMLNode *container() const;
    long offset() const;
    const MMLNode *leftNode() const;
    const MMLNode *rightNode() const;
    void setBeforeNode(MMLNode *);
    void setAfterNode(MMLNode *);
    int nearness(const MMLNode *) const;
    bool isSelected(const MMLNode *) const;
    bool collapsed() const;
private:
    MathCursor * const mc;
};

#endif
