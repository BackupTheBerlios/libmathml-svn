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

#include "bpinfo.h"
#include <mathml/boundpoint.h>
#include <QLabel>
#include <QVBoxLayout>
#include <cassert>

BPInfo::BPInfo(QWidget *parent)
    : QGroupBox(parent) {
    QVBoxLayout *layout = new QVBoxLayout();
    setLayout(layout);
    setAlignment(Qt::Vertical);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    nodeName = new QLabel;
    layout->addWidget(nodeName);
}
void
BPInfo::setBoundPoint(const BoundPoint &bp) {
    assert(bp.container());
    nodeName->setText(bp.container()->nodeName());
}
