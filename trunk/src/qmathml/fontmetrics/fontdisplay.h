#ifndef FONTDISPLAY
#define FONTDISPLAY

#include <QLabel>

class FontDisplay : public QLabel {
Q_OBJECT
private:
    bool m_bug;
    bool m_direct;
    float m_border;
    QString m_text;

    void drawText();
    void drawText(QPaintDevice *, const float border) const;
public:
    FontDisplay(bool bug, bool direct);
public slots:
    void setText(const QString &);
    void setBold(bool);
    void setItalic(bool);
    void setPointSize(int size);
};

#endif
