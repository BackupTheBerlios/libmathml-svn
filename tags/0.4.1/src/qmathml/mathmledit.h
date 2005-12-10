#ifndef MATHMLEDIT_H
#define MATHMLEDIT_H

#include <QWidget>

class MathMLView;
class MathMLView2;
class CursorInfo;
class ConstMathCursor;
class LatexLoader;
class QTextEdit;
class QLabel;
class QComboBox;
class QCheckBox;
class QListWidget;
class QListWidgetItem;

class MathMLEdit : public QWidget {
Q_OBJECT
public:
    MathMLEdit(QWidget *parent=0, Qt::WFlags f=0);
    ~MathMLEdit();
private slots:
    void setMML();
    void showFile();
    void changeFont(const QString &);
    void changeStyle(const QString &);
    void changeSize(const QString &);
    void changeZoom(const QString &);
    void setOutline();
    void setExamplesDir(const QString &dir);
    void setExamplesSubDir(const QString &dir);
    void setExamplesSubSubDir(const QString &dir);
    void loadExampleDir(const QString &dir);
private:
    QTextEdit *qte;
    QLabel *ql;
    MathMLView *mv;
    MathMLView2 *mv2;
    CursorInfo *cursorinfo;
    QComboBox *familylist, *stylelist, *sizelist, *zoomlist;
    QLabel *sizelabel, *zoomlabel;
    QCheckBox *debug;
    QListWidget *testicons;
    QComboBox *dirlist, *subdirlist, *subsubdirlist;
    QLabel *testimage;
    LatexLoader *latex;
    QString examplesdir;
    QString subdir, subsubdir, dir;
    bool pointsize;
    int lastSelectedSize;
    bool donotupdate;

    void setActive(QComboBox *, const QString &);
    int updateSizeList(const QString family, const QString &style);

};

#endif
