#ifndef MATHMLEDIT_H
#define MATHMLEDIT_H

#include <wx/app.h>
#include <wx/imaglist.h>
class MyApp : public wxApp {
public:
    virtual bool OnInit();
};

DECLARE_APP(MyApp);

class wxTextCtrl;
class wxStaticText;
class MathMLView;
class wxComboBox;
class wxCheckBox;
class wxStaticBitmap;
class wxButton;
class wxSpinCtrl;
class wxListCtrl;
class wxSpinEvent;
class wxListEvent;

class MathMLEdit : public wxFrame {
public:
    MathMLEdit(const wxString &title);
    void OnDirCombo(wxCommandEvent &event );
    void OnFontSpin(wxSpinEvent &event );
    void OnFontCmd(wxCommandEvent &event );
    void showFile(wxListEvent &event);
    void setOutline(wxCommandEvent &event);
    void setMML(wxCommandEvent&);
private:
    wxTextCtrl *qte;
    wxStaticText *ql;
    MathMLView *mv;
    wxComboBox *fontlist, *zoomlist;
    wxSpinCtrl *fontsize;
    wxCheckBox *debug;
    wxListCtrl *testicons;
    wxComboBox *dirlist, *subdirlist, *subsubdirlist;
    wxStaticBitmap *testimage;
    wxString examplesdir;
    wxString subdir, subsubdir, dir;
    wxImageList il;

    void setExamplesDir(const wxString &dir);
    void setExamplesSubDir(const wxString &dir);
    void setExamplesSubSubDir(const wxString &dir);
    void loadExampleDir(const wxString &dir);

    enum {
        DIRLST_ID = wxID_HIGHEST + 1,
        SUBDIRLST_ID,
        SUBSUBDIRLST_ID,
        FONT_ID,
        ICONS_ID,
        TEXT_ID,
        CHECK_ID,
        SIZE_ID
    };
    DECLARE_EVENT_TABLE()
};

#endif
