#ifndef MATHMLVIEW2_H
#define MATHMLVIEW2_H

#include "mmlimage.h"
#include <QWidget>
#include <QImage>
class MMLDocument;

class MathMLView2 : public QWidget {
Q_OBJECT
public:
    MathMLView2(QWidget *parent);
    ~MathMLView2();
    void setDocument(const MMLDocument *);
    void changeFont(const QFont &);
    void changeZoom(float);
    QSize sizeHint() const {
        return m_scale*m_img.size();
    }
signals:
    void cursorChanged();
public slots:
    void setOutline(bool);
protected:
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent ( QMouseEvent * e );
    void keyPressEvent(QKeyEvent *);
    void focusOutEvent ( QFocusEvent * event );
    void paintEvent(QPaintEvent *);
private:
    float m_scale;
    const MMLDocument *m_doc;
    QImage m_img;
    MMLImage m_mmlimg;

    void updatePix();
};

#endif
