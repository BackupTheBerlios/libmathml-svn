#include "mathmledit.h"
#include "mathmlview.h"
#undef ATTRIBUTE_PRINTF
#include "mmlreader.h"
#include <mathml/mmldocument.h>
#ifndef TRUE
	#define TRUE  ((bool)1)
	#define FALSE ((bool)0)
#endif
#include <wx/sizer.h>
#include <wx/textctrl.h>
#include <wx/combobox.h>
#include <wx/stattext.h>
#include <wx/statbmp.h>
#include <wx/checkbox.h>
#include <wx/dir.h>
#include <wx/filename.h>
#include <wx/button.h>
#include <wx/fontdlg.h>
#include <wx/frame.h>
#include <wx/listctrl.h>
#include <wx/wfstream.h>
#include <wx/txtstrm.h>
#include <wx/fontenum.h>
#include <wx/spinctrl.h>

IMPLEMENT_APP(MyApp);

bool
MyApp::OnInit() {
	wxInitAllImageHandlers();
	MathMLEdit *me = new MathMLEdit(_T("MathML Application"));//,
//		wxPoint(-1, -1), wxSize(-1, -1));
	SetTopWindow(me);
	me->Show(true);
	return true;
}

BEGIN_EVENT_TABLE(MathMLEdit, wxFrame)
	EVT_TEXT(TEXT_ID, MathMLEdit::setMML)
	EVT_COMBOBOX(DIRLST_ID, MathMLEdit::OnDirCombo)
	EVT_COMBOBOX(SUBDIRLST_ID, MathMLEdit::OnDirCombo)
	EVT_COMBOBOX(SUBSUBDIRLST_ID, MathMLEdit::OnDirCombo)
	EVT_COMBOBOX(FONT_ID, MathMLEdit::OnFontCmd)
	EVT_LIST_ITEM_FOCUSED(ICONS_ID, MathMLEdit::showFile)
	EVT_CHECKBOX(CHECK_ID, MathMLEdit::setOutline)
	EVT_SPINCTRL(SIZE_ID, MathMLEdit::OnFontSpin)
END_EVENT_TABLE()

const char *
appDir() {
	static char appprefix[512];
	int i, n;

	n = readlink("/proc/self/exe", appprefix, sizeof(appprefix)-1);
	readlink("/proc/self/exe", appprefix, sizeof(appprefix) -1);
	for (i = n; i > 0; i--) {
		if (appprefix[i]=='/') {
			appprefix[i]='\0';
			break;
		}
	}
	for (i = n; i > 0; i--) {
		if (appprefix[i]=='/') {
			appprefix[i]='\0';
			break;
		}
	}
	return appprefix;
}


MathMLEdit::MathMLEdit(const wxString& title)
	: wxFrame(0, -1, title) {

	qte = new wxTextCtrl(this, TEXT_ID, wxEmptyString, wxDefaultPosition,
		wxDefaultSize, wxTE_MULTILINE);
	mv = new MathMLView(this);
	ql = new wxStaticText(this, -1, wxEmptyString, wxDefaultPosition);

	// example file selection controls
	testimage = new wxStaticBitmap(this, -1, wxBitmap(), wxDefaultPosition);
	testicons = new wxListCtrl(this, ICONS_ID, wxDefaultPosition, wxDefaultSize,
			wxLC_ICON);
	dirlist = new wxComboBox(this, DIRLST_ID, wxEmptyString,
		wxDefaultPosition, wxDefaultSize, 0, 0,
		wxCB_READONLY | wxCB_SORT);
	subdirlist = new wxComboBox(this, SUBDIRLST_ID, wxEmptyString,
		wxDefaultPosition, wxDefaultSize, 0, 0,
		wxCB_READONLY | wxCB_SORT);
	subsubdirlist = new wxComboBox(this, SUBSUBDIRLST_ID, wxEmptyString,
		wxDefaultPosition, wxDefaultSize, 0, 0,
		wxCB_READONLY | wxCB_SORT);

	wxString dir;
#if wxUSE_UNICODE
        dir = wxConvLibc.cMB2WC(appDir());
#else
        dir = appDir();
#endif
	printf("dir: %s\n", appDir());
	setExamplesDir(dir + wxT("/share/libmathml/testsuite"));
	dirlist->SetSelection(dirlist->FindString(wxT("Presentation")));
	setExamplesSubDir(wxT("Presentation"));
	subdirlist->SetSelection(subdirlist->FindString(wxT("GeneralLayout")));
	setExamplesSubSubDir(wxT("GeneralLayout"));
	subsubdirlist->SetSelection(
		subsubdirlist->FindString(wxT("msqrt-mroot")));
	loadExampleDir(wxT("msqrt-mroot"));

//	setActive(subdirlist, "GeneralLayout");
//	setActive(subsubdirlist, "msqrt-mroot");

	// painter settings controls
	fontlist = new wxComboBox(this, FONT_ID, wxEmptyString, wxDefaultPosition,
		wxDefaultSize, 0, 0, wxCB_READONLY | wxCB_SORT);
	wxFontEnumerator fe;
	fe.EnumerateFacenames();
	wxArrayString *fonts = fe.GetFacenames();
	for (uint i=0; i<fonts->Count(); ++i) {
		fontlist->Append((*fonts)[i]);
	}
	int fp = fontlist->FindString(wxT("Nimbus Roman No9 L")	);
	fontlist->SetSelection(fp);

	fontsize = new wxSpinCtrl(this, SIZE_ID);
	fontsize->SetValue(GetFont().GetPointSize());
	fontsize->SetRange(6,100);

	wxStaticText *zoomlab = new wxStaticText(this, -1, wxT("zoom:"),
		wxDefaultPosition);
	zoomlist = new wxComboBox(this, -1, wxEmptyString, wxDefaultPosition,
		wxDefaultSize, 0, 0, wxCB_READONLY | wxCB_SORT);
	debug = new wxCheckBox(this, CHECK_ID, wxT("outline"));

	// layout
	wxBoxSizer *ptr_sizer = new wxBoxSizer(wxVERTICAL);
	ptr_sizer->Add(qte, 1, wxEXPAND);
	wxBoxSizer *hb = new wxBoxSizer(wxHORIZONTAL);
	hb->Add(mv, 1);
	hb->Add(testimage, 1, wxALIGN_CENTER_VERTICAL);
	ptr_sizer->Add(hb, 1, wxEXPAND);
	ptr_sizer->Add(ql, 0, wxEXPAND);
	ptr_sizer->Add(testicons, 1, wxEXPAND);
	hb = new wxBoxSizer(wxHORIZONTAL);
	hb->Add(dirlist, 1, wxEXPAND);
	hb->Add(subdirlist, 1, wxEXPAND);
	hb->Add(subsubdirlist, 1, wxEXPAND);
	ptr_sizer->Add(hb, 0, wxEXPAND);
	hb = new wxBoxSizer(wxHORIZONTAL);
	hb->Add(fontlist, 1, wxALIGN_CENTER_VERTICAL);
	hb->Add(fontsize, 0, wxALIGN_CENTER_VERTICAL);
	hb->Add(zoomlab, 0, wxALIGN_CENTER_VERTICAL);
	hb->Add(zoomlist, 1, wxALIGN_CENTER_VERTICAL);
	hb->Add(debug, 0, wxALIGN_CENTER_VERTICAL);
	ptr_sizer->Add(hb, 0, wxEXPAND);
	SetSizer(ptr_sizer);
	ptr_sizer->SetSizeHints(this);
	SetSize(600,400);
}
void
MathMLEdit::setMML(wxCommandEvent&) {
	MMLReader mr;
	printf("reading buffer of size %i\n", qte->GetValue().size());
	const wxCharBuffer cb = wxConvLibc.cWX2MB(qte->GetValue());
	DOMString xml = (const char*)cb;
	if (mr.parse(xml)) {
		ql->SetLabel(wxT("No errors"));
		mv->setDocument(mr.document());
	} else {
		const char *c = mr.error().utf8();
		ql->SetLabel(wxstring(c));
		mv->setDocument(NULL);
	}
}
void
MathMLEdit::OnDirCombo(wxCommandEvent &event ) {
	if (event.m_id == DIRLST_ID) {
		setExamplesSubDir(event.GetString());
	} else if (event.m_id == SUBDIRLST_ID) {
		setExamplesSubSubDir(event.GetString());
	} else if (event.m_id == SUBSUBDIRLST_ID) {
		loadExampleDir(event.GetString());
	}
}
void
MathMLEdit::setExamplesDir(const wxString &dir) {
	examplesdir = dir;
	wxDir d(dir);
	// find all subdirectories
	dirlist->Clear();
	wxString entry;
	bool cont = d.GetFirst(&entry, wxEmptyString, wxDIR_DIRS);
	while (cont) {
		dirlist->Append(entry);
		cont = d.GetNext(&entry);
	}
	if (d.HasFiles(wxT("*.mml"))) {
		dirlist->Append(wxT("."));
	}
	wxString sel;
	if (dirlist->GetCount() > 0) {
		sel = dirlist->GetStringSelection();
	}
	setExamplesSubDir(sel);
}
void
MathMLEdit::setExamplesSubDir(const wxString &dir) {
	subdir = examplesdir;
	subdir += wxT("/") + dir;
	wxDir d(subdir);
	// find all subdirectories
	subdirlist->Clear();
	wxString entry;
	bool cont = d.GetFirst(&entry, wxEmptyString, wxDIR_DIRS);
	while (cont) {
		subdirlist->Append(entry);
		cont = d.GetNext(&entry);
	}
	if (d.HasFiles(wxT("*.mml"))) {
		subdirlist->Append(wxT("."));
	}
	wxString sel;
	if (subdirlist->GetCount() > 0) {
		sel = subdirlist->GetStringSelection();
	}
	setExamplesSubSubDir(sel);
}
void
MathMLEdit::setExamplesSubSubDir(const wxString &dir) {
	subsubdir = subdir + wxT("/") + dir;
	wxDir d(subsubdir);
	// find all subdirectories
	subsubdirlist->Clear();
	wxString entry;
	bool cont = d.GetFirst(&entry, wxEmptyString, wxDIR_DIRS);
	while (cont) {
		subsubdirlist->Append(entry);
		cont = d.GetNext(&entry);
	}
	if (d.HasFiles(wxT("*.mml"))) {
		subsubdirlist->Append(wxT("."));
	}
	wxString sel;
	if (subsubdirlist->GetCount() > 0) {
		sel = subsubdirlist->GetStringSelection();
	}
	loadExampleDir(sel);
}
void
MathMLEdit::loadExampleDir(const wxString &sssdir) {
	dir = subsubdir + wxT("/") + sssdir;
	wxDir d(dir);
	testicons->ClearAll();
	wxString entry;
	bool cont = d.GetFirst(&entry, wxT("*.mml"), wxDIR_FILES);
	il.RemoveAll();
	testicons->SetImageList(&il, wxIMAGE_LIST_NORMAL);
	wxImage i;
	//i.AddHandler(wxPNGHandler);
	while (cont) {
		wxFileName fn(dir + wxT("/")
			+ entry.SubString(0, entry.size()-4) + wxT("png"));
		if (fn.FileExists()) {
			i.LoadFile(fn.GetFullPath());
			int w = i.GetWidth();
			int h = i.GetHeight();
			if (w > h) {
				w = 32;
				h = 32*h/w;
			} else {
				w = 32*w/h;
				h = 32;
			}
			i.Rescale(w, h);
			wxBitmap bm(i);
			int j = il.Add(bm);
			testicons->InsertItem(testicons->GetItemCount(),
				entry, j);
		} else {
			testicons->InsertItem(testicons->GetItemCount(), entry);
		}
		cont = d.GetNext(&entry);
	}
	testicons->Arrange(wxLIST_ALIGN_SNAP_TO_GRID);
	testicons->Show(testicons->GetItemCount() != 0);
}
#include <cstdio>
void
MathMLEdit::showFile(wxListEvent &event) {
	wxString f = dir + wxT("/") + event.GetText();
	wxFileName fn(f);
	if (!fn.FileExists() || fn.IsDir()) return;
	fn = f.SubString(0, f.size() - 4) + wxT("png");
	wxImage img(1, 1);
	if (fn.FileExists()) {
		img.LoadFile(fn.GetFullPath());
	}
	testimage->SetBitmap(img);
	testimage->GetParent()->Refresh();

	FILE *file = fopen(f.mb_str(), "r");
	wxString text;
	if (file) {
		fseek(file, 0, SEEK_END);
		long size = ftell(file);
		char *utf8 = new char[size+1];
		fseek(file, 0, SEEK_SET);
		long r = fread(utf8, 1, size, file);
		if (r == size) {
			utf8[size] = '\0';
			text = wxConvLibc.cMB2WX(utf8);
		}
		delete [] utf8;
	}
	qte->SetValue(text);
}
void
MathMLEdit::OnFontSpin(wxSpinEvent &e) {
	wxFont f(fontsize->GetValue(), wxDEFAULT , wxNORMAL, wxNORMAL, false,
		fontlist->GetStringSelection());
	mv->changeFont(f);
}
void
MathMLEdit::OnFontCmd(wxCommandEvent &) {
    wxFont f(fontsize->GetValue(), wxDEFAULT , wxNORMAL, wxNORMAL, false,
        fontlist->GetStringSelection());
    mv->changeFont(f);
}
void
MathMLEdit::setOutline(wxCommandEvent &event) {
	mv->setOutline(event.IsChecked());
}
