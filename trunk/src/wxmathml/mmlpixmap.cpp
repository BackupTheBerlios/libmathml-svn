#include "mmlpixmap.h"
#include <mathml/mmldocument.h>
#include <wx/settings.h>
#include <cmath>

MMLPixmap::MMLPixmap() : m_painter(&m_wxpainter) {
    m_border = 4;
    m_outline = false;
    m_mustLayout = true;
    m_mustPaint = true;
    m_doc = 0;
    m_buffer = wxBitmap(1, 1);
    m_wxpainter.SelectObject(m_buffer);
}
void
MMLPixmap::setDocument(const MMLDocument *doc) {
    m_doc = doc;
    m_mustLayout = true;
}
void
MMLPixmap::layout() {
    m_doc->setPainter(&m_painter);
    m_doc->layout();

    // obtain the dimensions of the document
    float ascent = 0;
    float height = 0;
    float maxwidth = 0;
    bool more = true;
    int view = 0;
    do {
        m_doc->setCurrentView(view++);
        m_doc->setX(0);
        m_doc->setY(height);
        more = m_doc->setMaxViewWidth(1000);
        ascent += m_doc->getAscent();
        height += m_doc->getHeight();
        float w = m_doc->getWidth();
        if (w > maxwidth) maxwidth = w;
    } while (more);
    m_ascent = (int)ceil(ascent);
    m_w = int(ceil(maxwidth + 2*m_border));
    m_h = int(ceil(height + 2*m_border));

    if (m_w > 1000) m_w = 1000;
    if (m_h > 1000) m_h = 1000;
    m_mustLayout = false;
    m_mustPaint = true;

    m_doc->setX(m_border);
    m_doc->setY(m_ascent + m_border);
}
void
MMLPixmap::repaint() {
    if (m_mustLayout) layout();

    if (m_buffer.GetWidth() != m_w || m_buffer.GetHeight() != m_h) {
        m_buffer = wxBitmap(m_w, m_h);
        m_wxpainter.SelectObject(m_buffer);
    }
    // initialize the buffer and painter
    wxColor c = wxSystemSettings::GetColour(wxSYS_COLOUR_BACKGROUND);
    wxBrush b(c);
    m_wxpainter.SetBackground(b);
    m_wxpainter.Clear();

    // paint a border
    if (m_outline) {
        m_wxpainter.DrawRectangle(m_border-1, m_border-1, m_w-2*m_border+1,
            m_h-2*m_border+1);
    }

    // paint all the views below each other
    for (ushort i=0; i < m_doc->countViewPorts(); ++i) {
        m_doc->setCurrentView(i);
        m_doc->paint();
    }
    m_mustPaint = false;
}
wxMemoryDC &
MMLPixmap::getPixmap() {
    if (m_mustLayout || m_mustPaint) repaint();
    return m_wxpainter;
}
