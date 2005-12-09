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
#include "cursorinfo.h"
#include "bpinfo.h"
#include <mathml/mathcursor.h>
#include <mathml/mmldocument.h>
#include <QVBoxLayout>

CursorInfo::CursorInfo(QWidget *parent)
	: QWidget(parent) {
	start = new BPInfo();
	end = new BPInfo();
	setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

	QVBoxLayout *layout = new QVBoxLayout();
    setLayout(layout);
	layout->addWidget(start);
	layout->addWidget(end);
	layout->addStretch(1);
	mc = 0;
}
void
CursorInfo::setDocument(MMLDocument *doc) {
	if (doc) {
		mc = doc->cursor();
	} else {
		mc = 0;
	}	
	cursorChanged();
}
void
CursorInfo::cursorChanged() {
	if (!mc) {
		start->hide();
		end->hide();
	} else if (mc->collapsed()) {
		start->setTitle(tr("cursor"));
		start->setBoundPoint(mc->cursor());
		end->hide();
	} else {
		start->setTitle(tr("start selection"));
		start->setBoundPoint(mc->left());
		start->show();
		end->setTitle(tr("end selection"));
		end->setBoundPoint(mc->right());
		end->show();
	}
}
