#include <QWidget>
#include <QImage>
#include <cairo/cairo.h>

class CairoTest : public QWidget {
Q_OBJECT
public:
    CairoTest();
protected:
    void paintEvent(QPaintEvent *);
    void resizeEvent(QResizeEvent* event);
private:
    QImage m_buffer;

    void drawPath(cairo_t *cr, int w, int h);
};
