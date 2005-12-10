#ifndef MMLPIXMAP_H
#define MMLPIXMAP_H

#include "wxmmlpainter.h"
#include <wx/dcmemory.h>

class MMLDocument;

/** 
 * Draws a mml document to a pixmap.
 **/
class MMLPixmap {
private:
    bool m_mustLayout;
    bool m_mustPaint;
    bool m_outline;
    int m_w;
    int m_h;
    int m_border;
    int m_ascent;
    const MMLDocument *m_doc;

    wxBitmap m_buffer;
    wxMemoryDC m_wxpainter;
    wxMMLPainter m_painter;

    void layout();
public:
    MMLPixmap();
    ~MMLPixmap() {}
    void setDocument(const MMLDocument *);
    void setFont(const wxFont &font) {
        if (font != m_wxpainter.GetFont()) {
            m_mustLayout = true;
            m_wxpainter.SetFont(font);
        }
    }
    void setOutline(bool outline) {
        if (m_outline != outline) {
            m_mustPaint = true;
            m_painter.setOutline(outline);
            m_outline = outline;
        }
    }
    wxPoint getCoords(int x, int y) {
        return wxPoint(x-m_border, y-m_ascent-m_border);
    }
    int getWidth() {
        if (m_mustLayout) {
            layout();
        }
        return m_w;
    }
    int getHeight() {
        if (m_mustLayout) {
            layout();
        }
        return m_h;
    }
    void repaint();
    wxMemoryDC &getPixmap();
};

#endif
