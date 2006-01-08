#ifndef MATHFONT_H
#define MATHFONT_H

#include <mathml/attributes.h>
#include <QFontMetrics>
#include <map>
#include <cmath>

class QFontMetricsF;
class MathFont;
class MathFontCache {
friend class MathFont;
private:
    MathFontCache();
    MathFontCache(const MathFontCache &);
public:
    MathFontCache(QFont font, mathvariant::Mathvariant mv, float size);
    ~MathFontCache() {
        if (m_fontmetrics) { delete m_fontmetrics; }
    }
    const QFontMetricsF &fontMetrics() {
        if (!m_fontmetrics) {
            m_fontmetrics = new QFontMetricsF(m_font);
        }
        return *m_fontmetrics;
    }
    float ascent() {
        if (isnan(m_ascent)) {
            m_ascent = fontMetrics().ascent();
        }
        return m_ascent;
    }
    float descent() {
        if (isnan(m_descent)) {
            m_descent = fontMetrics().descent();
        }
        return m_descent;
    }
    float height() {
        if (isnan(m_height)) {
            m_height = fontMetrics().height();
        }
        return m_height;
    }
    float ex() {
        if (isnan(m_ex)) {
            m_ex = fontMetrics().boundingRect("x").height();
        }
        return m_ex;
    }
    QRectF boundingRect(const QString &s) {
        std::map<const QString, const QRectF>::const_iterator i;
        i = m_cache.find(s);
        if (i == m_cache.end()) {
            QRectF r = fontMetrics().boundingRect(s);
            m_cache.insert(std::pair<const QString, const QRectF>(s, r));
            return r;
        } else {
            return i->second;
        }
    }
private:
    const static float m_nan;
    mathvariant::Mathvariant m_mathvariant;
    float m_fontsize;

    float m_ascent;
    float m_descent;
    float m_height;
    float m_ex;
    QFont m_font;
    QFontMetricsF *m_fontmetrics;
    std::map<const QString, const QRectF> m_cache;
};

class MathFont {
private:
    MathFontCache *m_current;
    float m_dpi;
    static const QFont m_defaultfont;
    std::map<mathvariant::Mathvariant, QFont> m_defaults;
    std::map<mathvariant::Mathvariant, std::map<int, MathFontCache*> > m_cache;

    void clear(mathvariant::Mathvariant);
public:
    MathFont();
    ~MathFont();
    void setFontType(mathvariant::Mathvariant mv, const QFont &font);
    void setFont(mathvariant::Mathvariant mv, float size);
    const QFont &font() const {
        if (m_current) {
            return m_current->m_font;
        } else {
            return m_defaultfont;
        }
    }
    float ascent() const {
        if (m_current) {
            return m_current->ascent();
        } else {
            return MathFontCache::m_nan;
        }
    }
    float descent() const {
        if (m_current) {
            return m_current->descent();
        } else {
            return MathFontCache::m_nan;
        }
    }
    float em() const {
        if (m_current) {
            return m_current->height();
        } else {
            return MathFontCache::m_nan;
        }
    }
    float ex() const {
        if (m_current) {
            return m_current->ex();
        } else {
            return MathFontCache::m_nan;
        }
    }
    QRectF boundingRect(const QString &s) const {
        if (m_current) {
            return m_current->boundingRect(s);
        } else {
            return QRectF();
        }
    }
};

#endif
