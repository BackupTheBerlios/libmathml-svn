#include "mathmlview.h"
#include "wxmmlpainter.h"
#include <mathml/mmldocument.h>
#include <mathml/constmathcursor.h>
#include <wx/dcclient.h>
#include <cmath>

MathMLView::MathMLView(wxWindow *parent)
	: wxWindow(parent, -1) {
	m_owner = parent;
	doc = 0;
    m_scale = 1;
    mmlpix.setOutline(false);
}
MathMLView::~MathMLView() {
	if (doc) {
		delete doc;
	}
}
void
MathMLView::setOutline(bool o) {
    mmlpix.setOutline(o);
    Refresh();
}
void
MathMLView::changeFont(const wxFont &f) {
	mmlpix.setFont(f);
    updatePix();
    GetParent()->Layout();
}
void
MathMLView::setDocument(const MMLDocument *d) {
    if (doc != d) {
        delete doc;
    }
    doc = d;
    if (doc) {
        mmlpix.setDocument(doc);
        updatePix();
    }
	GetParent()->Layout();
}
void
MathMLView::updatePix() {
    int w = (int)ceil(m_scale*mmlpix.getWidth());
    int h = (int)ceil(m_scale*mmlpix.getHeight());
    SetSizeHints(w, h, w, h);
}
const MMLDocument *
MathMLView::document() const {
	return doc;
}
void
MathMLView::OnPaint(wxPaintEvent &) {
	if (doc) {
		wxPaintDC dc(this);
        dc.SetUserScale(m_scale, m_scale);
        dc.Blit(0, 0, mmlpix.getWidth(), mmlpix.getHeight(), &mmlpix.getPixmap(), 0, 0);
	}
}
void
MathMLView::OnMouseMove(wxMouseEvent &e) {
	if (!e.LeftIsDown()) return;
	SetFocus();
	if (doc) {
        float x = e.GetX()/m_scale;
        float y = e.GetY()/m_scale;
        wxPoint p = mmlpix.getCoords((int)x, (int)y);
		bool change = doc->constcursor()->selectTo(p.x, p.y);
        if (change) {
            mmlpix.repaint();
            Refresh();
        }
	}
}
void
MathMLView::OnMousePress(wxMouseEvent &e) {
    printf("press\n");
	SetFocus();
	if (doc) {
        float x = e.GetX()/m_scale;
        float y = e.GetY()/m_scale;
        wxPoint p = mmlpix.getCoords((int)x, (int)y);
		ConstMathCursor *c = doc->constcursor();
        bool change;
		if (e.ShiftDown()) {
			change = c->selectTo(x, y);
		} else {
            printf("moving\n");
			change = c->moveTo(x, y);
		}
        if (change) {
            printf("changed\n");
            mmlpix.repaint();
            Refresh();
        }
	}
}
// the event tables connect the wxWindows events with the functions (event
// handlers) which process them.
BEGIN_EVENT_TABLE(MathMLView, wxWindow)
	EVT_PAINT  (MathMLView::OnPaint)
	EVT_MOTION (MathMLView::OnMouseMove)
	EVT_LEFT_DOWN (MathMLView::OnMousePress)
END_EVENT_TABLE()
