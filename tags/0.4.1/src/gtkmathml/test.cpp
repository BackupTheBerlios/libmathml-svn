#include <gtkmm.h>
#include "mmlreader.h"
#include "mmlimage.h"
#include <mathml/mmldocument.h>

class MMLView : public Gtk::DrawingArea
{
protected:
    MMLDocument *m_doc;
    MMLImage m_img;

    virtual bool on_expose_event(GdkEventExpose* e)
    {
        Glib::RefPtr<Gdk::Window> window = get_window();
        GdkWindow* gdkWindow = window->gobj();
        GdkDrawable* gdkDrawable;
        gint xOffset;
        gint yOffset;
        gdk_window_get_internal_paint_info(gdkWindow,
            &gdkDrawable, &xOffset, &yOffset);
        cairo_t* cairo = gdk_cairo_create(gdkDrawable);
        if ((xOffset != 0) || (yOffset != 0))
        {
            cairo_save(cairo);
            cairo_translate(cairo, -xOffset, -yOffset);
        }
        Gtk::Allocation allocation = get_allocation();
        int width = allocation.get_width();
        int height = allocation.get_height();
        paint(cairo, width, height);
        if ((xOffset != 0) || (yOffset != 0))
            cairo_restore(cairo);
        cairo_destroy(cairo);
        return false;
    }

    virtual void paint(cairo_t* cairo, int width, int height)
    {
        if (m_doc == 0) return;
        printf("paint!\n");
        m_img.setDocument(m_doc);
        cairo_set_source_surface(cairo, m_img.getSurface(), 0, 0);

        //cairo_set_source_rgb(cairo, 0.0, 0.0, 1.0);
        cairo_rectangle(cairo, 0.0, 0.0, width, height);
        cairo_fill(cairo);
    }

public:
    MMLView() {
        m_doc = 0;
    }
    virtual ~MMLView() { }
    void setDocument(MMLDocument *d) {
        m_doc = d;
        queue_draw();
    }
};

class MMLEdit : public Gtk::Window {
protected:
    MMLView m_view;
    Gtk::VBox m_vbox;
    Gtk::TextView m_xmledit;
    Gtk::Label m_error;
    MMLReader reader;
    MMLDocument *m_doc;

    void on_xml_changed() {
        printf("on_xml_changed\n");
        DOMString buffer = m_xmledit.get_buffer()->get_text().c_str();
        if (reader.parse(buffer)) {
            MMLDocument *old = m_doc;
            m_doc = reader.document();
            m_view.setDocument(m_doc);
            m_error.set_text("No errors");
            if (old) delete old;
        } else {
            //DOMString error = reader.error();
            //printf("parsed wrong? %i\n", error.length());
            m_error.set_text(reader.error().utf8());
        }
    }
public:
    MMLEdit()
    {
        m_doc = 0;
        set_default_size(400, 400);
        set_title("Test");
        set_position(Gtk::WIN_POS_CENTER);
        add(m_vbox);
        m_vbox.add(m_view);
        m_vbox.add(m_xmledit);
        m_vbox.add(m_error);

        m_xmledit.get_buffer()->signal_changed().connect(
            sigc::mem_fun(*this, &MMLEdit::on_xml_changed));

        m_vbox.show();
        m_view.show();
        m_xmledit.show();
        m_error.show();

        m_xmledit.get_buffer()->set_text(
            "<msqrt><mo>-</mo><mn>1</mn></msqrt>");
    }

    virtual ~MMLEdit() {
        if (m_doc) delete m_doc;
    }
};

int
main(int argc, char* argv[])
{
    Gtk::Main gtkMain(argc, argv);
    MMLEdit mainWindow;
    gtkMain.run(mainWindow);
    return 0;
}
