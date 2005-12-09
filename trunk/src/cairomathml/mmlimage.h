#ifndef MMLIMAGE_H
#define MMLIMAGE_H

#include "cairopainter.h"

class MMLDocument;

/** 
 * Draws a mml document to a pixmap.
 **/
class MMLImage {
private:
    bool m_mustLayout;
    bool m_mustPaint;
    bool m_outline;
    int m_dataw;
    int m_datah;
    int m_w;
    int m_h;
    int m_border;
    float m_foreground[3];
    float m_background[3];
    std::string m_fontname;
    float m_fontsize;
    unsigned char *m_data;

    float m_ascent;
    const MMLDocument *m_doc;
    cairo_surface_t* m_buffer;
    cairo_t* m_cpainter;
    CairoPainter m_painter;

    void resize(int w, int h);
    void layout();
public:
    MMLImage();
    ~MMLImage();
    void setDocument(const MMLDocument *);
    void setFont(const std::string &name, float size);
    void setBackgroundColor(float, float, float);
    void setForeGroundColor(float, float, float);
    void setOutline(bool outline) {
        if (m_outline != outline) {
            m_mustPaint = true;
            m_painter.setOutline(outline);
            m_outline = outline;
        }
    }
    int getWidth() const {
        return m_dataw;
    }
    int getHeight() const {
        return m_datah;
    }
    void getCoords(float &x, float &y) {
        x = x-m_border;
        y = y-m_ascent-m_border;
    }
    void repaint();
    uchar *getPixmap();
    cairo_surface_t* getSurface();
};


#endif
