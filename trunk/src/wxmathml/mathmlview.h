#ifndef MATHMLVIEW_H
#define MATHMLVIEW_H

#include "mmlpixmap.h"
#include <wx/window.h>

class MMLDocument;

class MathMLView : public wxWindow {
public:
    MathMLView(wxWindow *parent);
    ~MathMLView();
    void setOutline(bool outline);
    void setDocument(const MMLDocument *);
    const MMLDocument *document() const;
    void OnPaint(wxPaintEvent &event);
    void OnMouseMove(wxMouseEvent &event);
    void OnMousePress(wxMouseEvent &);
    void changeFont(const wxFont &f);
private:
    float m_scale;
    wxWindow *m_owner;
    const MMLDocument *doc;

    MMLPixmap mmlpix;

    void updatePix();

    DECLARE_EVENT_TABLE();
};

#endif
