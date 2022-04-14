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
    int opac;

public slots:

    void setCircleColor(int hue) { m_circle_hue = hue; update(); }
    void setText(const QString &newText) { text = newText; }



private slots:
    void open();
    void saveAs();
    void copy();
    void paste();
    void zoomIn();
    void zoomOut();
    void normalSize();
    void doubleSize();
    void quadrupleSize();

    void fitToWindow();



private:
    void createActions();
    void createMenus();
    void updateActions();
    bool saveFile(const QString &fileName);
    void setImage(const QImage &newImage);

    void ImageRed(const QImage &newImage);
    void ImageMagenta(const QImage &newImage);
    void ImageGreen(const QImage &newImage);
    void ImageBlue(const QImage &newImage);
    void ImageCyan(const QImage &newImage);



    void scaleImage(double factor);
    void adjustScrollBar(QScrollBar *scrollBar, double factor);

    QImage image;
    QPixmap result_image;


    QString text;




    QLabel *imageLabel;
    QScrollArea *scrollArea;
    double scaleFactor = 1;
    QAction *saveAsAct;
    QAction *saveFileAct;
    QAction *copyAct;
    QAction *zoomInAct;
    QAction *zoomOutAct;
    QAction *normalSizeAct;
    QAction *fitToWindowAct;
    int sliderPosition;



    void createDockWindows();
    void createHorizontalGroupBox();
    void createGridGroupBox();
    void createFormGroupBox();

    enum { NumGridRows = 2, NumButtons =  5, NumButts = 3};


    QGroupBox *horizontalGroupBox;
    QGroupBox *HBox;
    QGroupBox *gridGroupBox;
    //QGroupBox *horizontalGroupBox2;

    QGroupBox *formGroupBox;

    QLabel *labels[NumGridRows];
    QLineEdit *lineEdits[NumGridRows];
    QPushButton *buttons[NumButtons];
    QPushButton *butts[NumButts];
    QPushButton *moreButtons[NumButts];
    QDialogButtonBox *buttonBox;

    void blurButton();
    void colorizeButton();
    void flipButton();
    void redButton();
    void magentaButton();
    void greenButton();
    void blueButton();
    void cyanButton();


    void setOpacity(int value);

    //void setText();


    QImage m_image;
    int m_circle_hue;



};



#endif // IMAGEEDIT_H
