#ifndef IMAGEEDIT_H
#define IMAGEEDIT_H


#include <QMainWindow>
#include <QListWidget>
#include <QImage>
#include <QTextEdit>
#include <QDockWidget>
#include <QDialog>
#include <QGraphicsEffect>
#include <QGraphicsBlurEffect>
#include <QGraphicsColorizeEffect>
#include <QPainter>



QT_BEGIN_NAMESPACE
class QAction;
class QLabel;
class QMenu;
class QScrollArea;
class QScrollBar;
class QDialogButtonBox;
class QGroupBox;
class QLineEdit;
class QMenuBar;
class QPushButton;
QT_END_NAMESPACE


class ImageEdit : public QMainWindow
{
    Q_OBJECT
    enum ObjectType { NoObject, Circle, Rectangle, Image };

    Q_PROPERTY(int circleColor READ circleColor WRITE setCircleColor)

public:
    ImageEdit(QWidget *parent = nullptr);
    bool loadFile(const QString &);

    int circleColor() const { return m_circle_hue; }

public slots:

    void setCircleColor(int hue) { m_circle_hue = hue; update(); }


private slots:
    void open();
    void saveAs();
    void copy();
    void paste();
    void zoomIn();
    void zoomOut();
    void normalSize();
    void fitToWindow();



private:
    void createActions();
    void createMenus();
    void updateActions();
    bool saveFile(const QString &fileName);
    void setImage(const QImage &newImage);
    void scaleImage(double factor);
    void adjustScrollBar(QScrollBar *scrollBar, double factor);

    QImage image;
    QLabel *imageLabel;
    QScrollArea *scrollArea;
    double scaleFactor = 1;
    QAction *saveAsAct;
    QAction *copyAct;
    QAction *zoomInAct;
    QAction *zoomOutAct;
    QAction *normalSizeAct;
    QAction *fitToWindowAct;


    void createDockWindows();
    void createHorizontalGroupBox();
    void createGridGroupBox();
    void createFormGroupBox();

    enum { NumGridRows = 2, NumButtons =  5};


    QGroupBox *horizontalGroupBox;
    QGroupBox *HBox;
    QGroupBox *gridGroupBox;
    QGroupBox *formGroupBox;

    QLabel *labels[NumGridRows];
    QLineEdit *lineEdits[NumGridRows];
    QPushButton *buttons[NumButtons];
    QPushButton *moreButtons[NumButtons];
    QDialogButtonBox *buttonBox;
    void blurButton();
    void colorizeButton();
    void opacityButton();
    void maskButton();

    QImage m_image;
    int m_circle_hue;
    void drawSource(QPainter &p);
    QPainter::CompositionMode m_composition_mode;

    QPointF m_circle_pos;

    int m_circle_alpha;



};



#endif // IMAGEEDIT_H
