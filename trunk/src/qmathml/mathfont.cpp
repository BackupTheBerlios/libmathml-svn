#include "mathfont.h"

const float MathFontCache::m_nan = nanf("");
const QFont MathFont::m_defaultfont;
MathFontCache::MathFontCache(QFont font, mathvariant::Mathvariant mv, float size) {
    m_font = font;
    m_mathvariant = mv;
    m_fontsize = size;
    m_fontmetrics = 0;

    m_ascent = m_nan;
    m_descent = m_nan;
    m_height = m_nan;
    m_ex = m_nan;
}

MathFont::MathFont() {
    m_current = 0;
    m_dpi = 72;
}

MathFont::~MathFont() {
    std::map<mathvariant::Mathvariant, std::map<int, MathFontCache*> >::const_iterator i, end;
    end = m_cache.end();
    for (i = m_cache.begin(); i != end; ++i) {
        clear(i->first);
    }
}

void
MathFont::setFontType(mathvariant::Mathvariant mv, const QFont &font) {
    clear(mv);
    m_defaults[mv] = font;
}
void
MathFont::clear(mathvariant::Mathvariant mv) {
    if (m_current && m_current->m_mathvariant == mv) {
        m_current = 0;
    }
    std::map<int, MathFontCache*>::const_iterator i, end;
    end = m_cache[mv].end();
    for (i = m_cache[mv].begin(); i != end; ++i) {
        delete i->second;
    }
    m_cache[mv].clear();
}
void
MathFont::setFont(mathvariant::Mathvariant mv, float size) {
    int intsize = (int)roundf(100*size);
    std::map<int, MathFontCache*> *m = &m_cache[mv];
    std::map<int, MathFontCache*>::const_iterator it;
    it = m->find(intsize);
    if (it == m->end()) {
        QFont f = m_defaults[mv];
        if (f.pointSize() == -1) {
            int newsize = (int)(size*m_dpi/72);
            f.setPixelSize(newsize);
        } else {
            f.setPointSizeF(size);
        }
        m_current = new MathFontCache(f, mv, size);
        m->insert(std::pair<int, MathFontCache*>(intsize, m_current));
    } else {
        m_current = it->second;
    }
}
