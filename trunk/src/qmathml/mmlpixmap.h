#ifndef MMLPIXMAP_H
#define MMLPIXMAP_H

#include "qmmlpainter.h"
#include <QPainter>
#include <QPixmap>
#include <QFont>

class MMLDocument;

/** 
 * Draws a mml document to a pixmap.
 **/
class MMLPixmap {
private:
    bool m_mustLayout;
    bool m_mustPaint;
    bool m_outline;
    int m_border;
    int m_w;
    int m_h;
    float m_ascent;
    const MMLDocument *m_doc;
    QPixmap m_buffer;
    QMMLPainter m_painter;
    QPainter m_qpainter;
    QFont m_font;
    QColor m_background;

    void layout();
public:
    MMLPixmap();
    ~MMLPixmap() {}
    void setDocument(const MMLDocument *);
    void setFont(const QFont &font) {
        if (m_font != font) {
            m_mustLayout = true;
            m_font = font;
        }
    }
    void setPalette(const QPalette &p) {
        if (p != m_painter.getPalette()) {
            m_mustPaint = true;
            m_background = p.background().color();
            m_painter.setPalette(p);
        }
    }
    void setOutline(bool outline) {
        if (m_outline != outline) {
            m_mustPaint = true;
            m_painter.setOutline(outline);
            m_outline = outline;
        }
    }
    QPointF getCoords(float x, float y) {
        return QPointF(x-m_border, y-m_ascent-m_border);
    }
    void repaint();
    const QPixmap &getPixmap();
};


#endif
