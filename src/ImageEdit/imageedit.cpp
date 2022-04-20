#include "imageedit.h"



#include <QApplication>
#include <QClipboard>
#include <QColorSpace>
#include <QDir>
#include <QFileDialog>
#include <QImageReader>
#include <QImageWriter>
#include <QLabel>
#include <QMenuBar>
#include <QMessageBox>
#include <QMimeData>
#include <QPainter>
#include <QScreen>
#include <QScrollArea>
#include <QScrollBar>
#include <QStandardPaths>
#include <QStatusBar>
#include <QtWidgets>



#include <QBoxLayout>
#include <QRadioButton>
#include <QTimer>
#include <QDateTime>
#include <QSlider>
#include <QMouseEvent>
#include <qmath.h>


ImageEdit::ImageEdit(QWidget *parent)
   : QMainWindow(parent), imageLabel(new QLabel)
   , scrollArea(new QScrollArea)
{
    imageLabel->setBackgroundRole(QPalette::Base);
    imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel->setScaledContents(true);

    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setWidget(imageLabel);
    scrollArea->setVisible(false);
    setCentralWidget(scrollArea);
    createDockWindows();
    createActions();

    resize(QGuiApplication::primaryScreen()->availableSize() * 3 / 5);

}


bool ImageEdit::loadFile(const QString &fileName)
{
    QImageReader reader(fileName);
    reader.setAutoTransform(true);
    const QImage newImage = reader.read();
    if (newImage.isNull()) {
        QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                                 tr("Cannot load %1: %2")
                                 .arg(QDir::toNativeSeparators(fileName), reader.errorString()));
        return false;
    }


    setImage(newImage);

    setWindowFilePath(fileName);

    const QString description = image.colorSpace().isValid()
        ? image.colorSpace().description() : tr("unknown");
    const QString message = tr("Opened \"%1\", %2x%3, Depth: %4 (%5)")
        .arg(QDir::toNativeSeparators(fileName)).arg(image.width()).arg(image.height())
        .arg(image.depth()).arg(description);
    statusBar()->showMessage(message);

    return true;
}

void ImageEdit::setImage(const QImage &newImage)
{
    image = newImage;
    if (image.colorSpace().isValid())
        image.convertToColorSpace(QColorSpace::SRgb);
    imageLabel->setPixmap(QPixmap::fromImage(image));

    scaleFactor = 1.0;

    scrollArea->setVisible(true);
    fitToWindowAct->setEnabled(true);
    updateActions();

    if (!fitToWindowAct->isChecked())
        imageLabel->adjustSize();

}


void ImageEdit::ImageBlue(const QImage &newImage)
{
    image = newImage;
    if (image.colorSpace().isValid())
        image.convertToColorSpace(QColorSpace::SRgb);


    QImage new_image = image;
    QPainter painter(&new_image);
    painter.setCompositionMode(QPainter::CompositionMode_Multiply);
    painter.fillRect(new_image.rect(), Qt::blue);
    painter.end();


    imageLabel->setPixmap(QPixmap::fromImage(new_image));

    scrollArea->setVisible(true);
    fitToWindowAct->setEnabled(true);
    updateActions();

    if (!fitToWindowAct->isChecked())
        imageLabel->adjustSize();

}

void ImageEdit::ImageRed(const QImage &newImage)
{
    image = newImage;
    if (image.colorSpace().isValid())
        image.convertToColorSpace(QColorSpace::SRgb);


    QImage new_image = image;
    QPainter painter(&new_image);
    painter.setCompositionMode(QPainter::CompositionMode_Multiply);
    painter.fillRect(new_image.rect(), Qt::red);
    painter.end();

    imageLabel->setPixmap(QPixmap::fromImage(new_image));

    scrollArea->setVisible(true);
    fitToWindowAct->setEnabled(true);
    updateActions();

    if (!fitToWindowAct->isChecked())
        imageLabel->adjustSize();

}

void ImageEdit::ImageGreen(const QImage &newImage)
{
    image = newImage;
    if (image.colorSpace().isValid())
        image.convertToColorSpace(QColorSpace::SRgb);

    QImage new_image = image;
    QPainter painter(&new_image);
    painter.setCompositionMode(QPainter::CompositionMode_Multiply);
    painter.fillRect(new_image.rect(), Qt::green);
    painter.end();


    imageLabel->setPixmap(QPixmap::fromImage(new_image));

    scrollArea->setVisible(true);
    fitToWindowAct->setEnabled(true);
    updateActions();

    if (!fitToWindowAct->isChecked())
        imageLabel->adjustSize();

}

void ImageEdit::ImageCyan(const QImage &newImage)
{
    image = newImage;
    if (image.colorSpace().isValid())
        image.convertToColorSpace(QColorSpace::SRgb);

    QImage new_image = image;
    QPainter painter(&new_image);
    painter.setCompositionMode(QPainter::CompositionMode_Multiply);
    painter.fillRect(new_image.rect(), Qt::cyan);
    painter.end();


    imageLabel->setPixmap(QPixmap::fromImage(new_image));

    scrollArea->setVisible(true);
    fitToWindowAct->setEnabled(true);
    updateActions();

    if (!fitToWindowAct->isChecked())
        imageLabel->adjustSize();

}

void ImageEdit::ImageMagenta(const QImage &newImage)
{
    image = newImage;
    if (image.colorSpace().isValid())
        image.convertToColorSpace(QColorSpace::SRgb);

    QImage new_image = image;
    QPainter painter(&new_image);
    painter.setCompositionMode(QPainter::CompositionMode_Multiply);
    painter.fillRect(new_image.rect(), Qt::magenta);
    painter.end();


    imageLabel->setPixmap(QPixmap::fromImage(new_image));
//    scaleFactor = 1.0;

    scrollArea->setVisible(true);
    fitToWindowAct->setEnabled(true);
    updateActions();

    if (!fitToWindowAct->isChecked())
        imageLabel->adjustSize();
//    normalSize();

}





bool ImageEdit::saveFile(const QString &fileName)
{
    image = imageLabel->pixmap().toImage();
    QImageWriter writer(fileName);

    if (!writer.write(image)) {
        QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                                 tr("Cannot write %1: %2")
                                 .arg(QDir::toNativeSeparators(fileName), writer.errorString()));
        return false;
    }
    const QString message = tr("Wrote \"%1\"").arg(QDir::toNativeSeparators(fileName));
    statusBar()->showMessage(message);
    return true;
}


static void initializeImageFileDialog(QFileDialog &dialog, QFileDialog::AcceptMode acceptMode)
{
    static bool firstDialog = true;

    if (firstDialog) {
        firstDialog = false;
        const QStringList picturesLocations = QStandardPaths::standardLocations(QStandardPaths::PicturesLocation);
        dialog.setDirectory(picturesLocations.isEmpty() ? QDir::currentPath() : picturesLocations.last());
    }

    QStringList mimeTypeFilters;
    const QByteArrayList supportedMimeTypes = acceptMode == QFileDialog::AcceptOpen
        ? QImageReader::supportedMimeTypes() : QImageWriter::supportedMimeTypes();
    for (const QByteArray &mimeTypeName : supportedMimeTypes)
        mimeTypeFilters.append(mimeTypeName);
    mimeTypeFilters.sort();
    dialog.setMimeTypeFilters(mimeTypeFilters);
    dialog.selectMimeTypeFilter("image/jpeg");
    dialog.setAcceptMode(acceptMode);
    if (acceptMode == QFileDialog::AcceptSave)
        dialog.setDefaultSuffix("jpg");
}

void ImageEdit::open()
{
    QFileDialog dialog(this, tr("Open File"));
    initializeImageFileDialog(dialog, QFileDialog::AcceptOpen);

    while (dialog.exec() == QDialog::Accepted && !loadFile(dialog.selectedFiles().constFirst())) {}
}


void ImageEdit::saveAs()
{
    QFileDialog dialog(this, tr("Save File As"));
    initializeImageFileDialog(dialog, QFileDialog::AcceptSave);

    while (dialog.exec() == QDialog::Accepted && !saveFile(dialog.selectedFiles().constFirst())) {}
}


void ImageEdit::copy()
{
#ifndef QT_NO_CLIPBOARD
    QGuiApplication::clipboard()->setImage(image);
#endif
}

#ifndef QT_NO_CLIPBOARD
static QImage clipboardImage()
{
    if (const QMimeData *mimeData = QGuiApplication::clipboard()->mimeData()) {
        if (mimeData->hasImage()) {
            const QImage image = qvariant_cast<QImage>(mimeData->imageData());
            if (!image.isNull())
                return image;
        }
    }
    return QImage();
}
#endif

void ImageEdit::paste()
{
#ifndef QT_NO_CLIPBOARD
    const QImage newImage = clipboardImage();
    if (newImage.isNull()) {
        statusBar()->showMessage(tr("No image in clipboard"));
    } else {
        setImage(newImage);
        setWindowFilePath(QString());
        const QString message = tr("Obtained image from clipboard, %1x%2, Depth: %3")
            .arg(newImage.width()).arg(newImage.height()).arg(newImage.depth());
        statusBar()->showMessage(message);
    }
#endif
}

void ImageEdit::zoomIn()
{
    scaleImage(1.25);
}

void ImageEdit::zoomOut()
{
    scaleImage(0.8);
}


void ImageEdit::normalSize()

{
    imageLabel->adjustSize();
    scaleFactor = 1.0;
}

void ImageEdit::doubleSize()

{

    //imageLabel->adjustSize();
    imageLabel->setGeometry(500, 250, 500, 250);
}

void ImageEdit::quadrupleSize()

{

    //imageLabel->adjustSize();
    imageLabel->setGeometry(500, 400, 500, 400);
}


void ImageEdit::fitToWindow()
{
    bool fitToWindow = fitToWindowAct->isChecked();
    scrollArea->setWidgetResizable(fitToWindow);
    if (!fitToWindow)
        normalSize();
    updateActions();
}

void ImageEdit::createActions()

{
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));

    QAction *openAct = fileMenu->addAction(tr("&Open..."), this, &ImageEdit::open);
    openAct->setShortcut(QKeySequence::Open);

    saveAsAct = fileMenu->addAction(tr("&Save As..."), this, &ImageEdit::saveAs);
    saveAsAct->setEnabled(false);

    fileMenu->addSeparator();

    QAction *exitAct = fileMenu->addAction(tr("E&xit"), this, &QWidget::close);
    exitAct->setShortcut(tr("Ctrl+Q"));

    QMenu *editMenu = menuBar()->addMenu(tr("&Edit"));

    copyAct = editMenu->addAction(tr("&Copy"), this, &ImageEdit::copy);
    copyAct->setShortcut(QKeySequence::Copy);
    copyAct->setEnabled(false);

    QAction *pasteAct = editMenu->addAction(tr("&Paste"), this, &ImageEdit::paste);
    pasteAct->setShortcut(QKeySequence::Paste);

    QMenu *viewMenu = menuBar()->addMenu(tr("&View"));

    zoomInAct = viewMenu->addAction(tr("Zoom &In (25%)"), this, &ImageEdit::zoomIn);
    zoomInAct->setShortcut(QKeySequence::ZoomIn);
    zoomInAct->setEnabled(false);

    zoomOutAct = viewMenu->addAction(tr("Zoom &Out (25%)"), this, &ImageEdit::zoomOut);
    zoomOutAct->setShortcut(QKeySequence::ZoomOut);
    zoomOutAct->setEnabled(false);

    normalSizeAct = viewMenu->addAction(tr("&Normal Size"), this, &ImageEdit::normalSize);
    normalSizeAct->setShortcut(tr("Ctrl+S"));
    normalSizeAct->setEnabled(false);

    viewMenu->addSeparator();

    fitToWindowAct = viewMenu->addAction(tr("&Fit to Window"), this, &ImageEdit::fitToWindow);
    fitToWindowAct->setEnabled(false);
    fitToWindowAct->setCheckable(true);
    fitToWindowAct->setShortcut(tr("Ctrl+F"));


}

void ImageEdit::updateActions()
{
    saveAsAct->setEnabled(!image.isNull());
    copyAct->setEnabled(!image.isNull());
    zoomInAct->setEnabled(!fitToWindowAct->isChecked());
    zoomOutAct->setEnabled(!fitToWindowAct->isChecked());
    normalSizeAct->setEnabled(!fitToWindowAct->isChecked());
}

void ImageEdit::scaleImage(double factor)
{
    scaleFactor *= factor;
    imageLabel->resize(scaleFactor * imageLabel->pixmap(Qt::ReturnByValue).size());

    adjustScrollBar(scrollArea->horizontalScrollBar(), factor);
    adjustScrollBar(scrollArea->verticalScrollBar(), factor);

    zoomInAct->setEnabled(scaleFactor < 3.0);
    zoomOutAct->setEnabled(scaleFactor > 0.333);
}

void ImageEdit::adjustScrollBar(QScrollBar *scrollBar, double factor)
{
    scrollBar->setValue(int(factor * scrollBar->value()
                            + ((factor - 1) * scrollBar->pageStep()/2)));
}

void ImageEdit::createDockWindows()
{
    createHorizontalGroupBox();
    createGridGroupBox();
   // createFormGroupBox();

    QDockWidget *dock = new QDockWidget(tr("Editing Features"), this);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    dock->setWidget(newGroupBox);
    addDockWidget(Qt::RightDockWidgetArea, dock);
    dock->setFixedWidth(300);


    QDockWidget *dock2 = new QDockWidget(tr("Image Properties and Edits"), this);
    dock2->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

    dock2->setWidget(gridGroupBox);

    addDockWidget(Qt::RightDockWidgetArea, dock2);
    dock2->setFixedWidth(300);

  /*  QDockWidget *dock3 = new QDockWidget(tr("Insert Text"), this);
    dock3->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    dock3->setWidget(formGroupBox);
    addDockWidget(Qt::RightDockWidgetArea, dock3);
    dock3->setFixedWidth(300);
*/
}

void ImageEdit::createHorizontalGroupBox()
{

    /*
    horizontalGroupBox = new QGroupBox(tr("Background color"));

    QHBoxLayout *layout = new QHBoxLayout;


    QGroupBox *normalcolor = new QGroupBox(tr("Set to Original Color"));
    button1[0] = new QPushButton(tr("Normal").arg(1 + 1));
    connect(button1[0], &QPushButton::released, this, &ImageEdit::normalButton);


    layout->addWidget(normalcolor);
    QHBoxLayout *layout2 = new QHBoxLayout(normalcolor);
    layout2->addWidget(button1[0]);


    buttons[0] = new QPushButton(tr("Red").arg(1 + 1));
    connect(buttons[0], &QPushButton::released, this, &ImageEdit::redButton);
    buttons[1] = new QPushButton(tr("Purple").arg(2 + 1));
    connect(buttons[1], &QPushButton::released, this, &ImageEdit::magentaButton);
    buttons[2] = new QPushButton(tr("Green").arg(3 + 1));
    connect(buttons[2], &QPushButton::released, this, &ImageEdit::greenButton);
    buttons[3] = new QPushButton(tr("Blue").arg(4 + 1));
    connect(buttons[3], &QPushButton::released, this, &ImageEdit::blueButton);
    buttons[4] = new QPushButton(tr("Cyan").arg(5 + 1));
    connect(buttons[4], &QPushButton::released, this, &ImageEdit::cyanButton);
    layout2->addWidget(button1[0]);

    for (int i = 0; i < NumButtons; ++i) {
        layout->addWidget(buttons[i]);
    }



    horizontalGroupBox->setLayout(layout);
    */





    newGroupBox = new QGroupBox(tr("Background Color"));
    QGridLayout *layout = new QGridLayout;


    //QGroupBox *horizontalGroupBox2 = new QGroupBox(tr("Set Image to Original Color"));
    button1[0] = new QPushButton(tr("Normal").arg(1 + 1));
    connect(button1[0], &QPushButton::released, this, &ImageEdit::normalButton);


//    layout->addWidget(horizontalGroupBox2);
   // QHBoxLayout *layout2 = new QHBoxLayout(horizontalGroupBox2);
    layout->addWidget(button1[0]);


    QGroupBox *horizontalGroupBox2 = new QGroupBox();
    buttons[0] = new QPushButton(tr("Red").arg(1 + 1));
    connect(buttons[0], &QPushButton::released, this, &ImageEdit::redButton);
    buttons[1] = new QPushButton(tr("Purple").arg(2 + 1));
    connect(buttons[1], &QPushButton::released, this, &ImageEdit::magentaButton);
    buttons[2] = new QPushButton(tr("Green").arg(3 + 1));
    connect(buttons[2], &QPushButton::released, this, &ImageEdit::greenButton);
    buttons[3] = new QPushButton(tr("Blue").arg(4 + 1));
    connect(buttons[3], &QPushButton::released, this, &ImageEdit::blueButton);
    buttons[4] = new QPushButton(tr("Cyan").arg(5 + 1));
    connect(buttons[4], &QPushButton::released, this, &ImageEdit::cyanButton);
    layout->addWidget(horizontalGroupBox2);
    QHBoxLayout *layout2 = new QHBoxLayout(horizontalGroupBox2);
    for (int i = 0; i < NumButtons; ++i) {
        layout2->addWidget(buttons[i]);
    }


    newGroupBox->setLayout(layout);

}

void ImageEdit::createGridGroupBox()
{


    //horizontalGroupBox2->setLayout(layout2);

    gridGroupBox = new QGroupBox(tr("Image Properties and Dimensions"));
    QGridLayout *layout = new QGridLayout;

    QGroupBox *horizontalGroupBox2 = new QGroupBox(tr("Image Dimensions"));
    butts[0] = new QPushButton(tr("1:1").arg(1 + 1));
    connect(butts[0], &QPushButton::released, this, &ImageEdit::normalSize);
    butts[1] = new QPushButton(tr("2:1").arg(2 + 1));
    connect(butts[1], &QPushButton::released, this, &ImageEdit::doubleSize);
    butts[2] = new QPushButton(tr("4:3").arg(3 + 1));
    connect(butts[2], &QPushButton::released, this, &ImageEdit::quadrupleSize);

    layout->addWidget(horizontalGroupBox2);
    QHBoxLayout *layout2 = new QHBoxLayout(horizontalGroupBox2);
    for (int i = 0; i < NumButts; ++i) {
        layout2->addWidget(butts[i]);
    }



    QGroupBox *circleOpacityGroup = new QGroupBox(tr("Image Opacity"));
    QSlider *circleOpacitySlider = new QSlider(Qt::Horizontal, circleOpacityGroup);
    circleOpacitySlider->setRange(1, 10);
    circleOpacitySlider->setValue(10);

    circleOpacitySlider->setFocusPolicy(Qt::StrongFocus);
    circleOpacitySlider->setTickPosition(QSlider::TicksBothSides);
    circleOpacitySlider->setTickInterval(1);
    circleOpacitySlider->setSingleStep(1);

    connect(circleOpacitySlider, &QSlider::valueChanged, this, &ImageEdit::setOpacity);


    layout->addWidget(circleOpacityGroup);
    QVBoxLayout *circleColorLayout = new QVBoxLayout(circleOpacityGroup);
    circleColorLayout->addWidget(circleOpacitySlider);

    moreButtons[0] = new QPushButton(tr("Colorize").arg(1 + 1));
    connect(moreButtons[0], &QPushButton::released, this, &ImageEdit::colorizeButton);
    moreButtons[1] = new QPushButton(tr("Blur").arg(2 + 1));
    connect(moreButtons[1], &QPushButton::released, this, &ImageEdit::blurButton);
    moreButtons[2] = new QPushButton(tr("Flip Image").arg(3 + 1));
    connect(moreButtons[2], &QPushButton::released, this, &ImageEdit::flipButton);
    for (int i = 0; i < NumButts; ++i) {
        layout->addWidget(moreButtons[i]);
    }


    gridGroupBox->setLayout(layout);





}

void ImageEdit::createFormGroupBox()
{
    //QLineEdit *lineEdit = new QLineEdit;
    formGroupBox = new QGroupBox();
    QFormLayout *layout = new QFormLayout;
    layout->addRow(new QLabel(tr("Text:")), new QLineEdit);
    layout->addRow(new QLabel(tr("Text Position")), new QSpinBox);
    formGroupBox->setLayout(layout);

    //connect(lineEdit, &QLineEdit::textChanged, layout, &ImageEdit::setText);
}

void ImageEdit::blurButton()
{

    imageLabel->setGraphicsEffect(new QGraphicsBlurEffect);
    scrollArea->setVisible(true);
    fitToWindowAct->setEnabled(true);
    updateActions();

    if (!fitToWindowAct->isChecked())
        imageLabel->adjustSize();
}

void ImageEdit::colorizeButton()
{
    imageLabel->setGraphicsEffect(new QGraphicsColorizeEffect);

    scrollArea->setVisible(true);
    fitToWindowAct->setEnabled(true);
    updateActions();

    if (!fitToWindowAct->isChecked())
        imageLabel->adjustSize();

}

void ImageEdit::flipButton()
{
   // imageLabel->setGraphicsEffect(new QGraphicsOpacityEffect);

    QImage target(image.size(), QImage::Format_ARGB32);

    QPainter painter(&target);
    QTransform transf = painter.transform();
    transf.scale(-1, 1);
    painter.setTransform(transf);
    painter.drawImage(-image.width(), 0, image);

    //painter.drawImage(QRect(0, 0, image.width(), image.height()), image);


    imageLabel->setPixmap(QPixmap::fromImage(target));
    scrollArea->setVisible(true);
    fitToWindowAct->setEnabled(true);
    updateActions();

    if (!fitToWindowAct->isChecked())
        imageLabel->adjustSize();


}

void ImageEdit::blueButton()
{
    ImageBlue(image);
}

void ImageEdit::redButton()
{
    ImageRed(image);
}

void ImageEdit::cyanButton()
{
    ImageCyan(image);
}

void ImageEdit::greenButton()
{
    ImageGreen(image);
}

void ImageEdit::magentaButton()
{
    ImageMagenta(image);
   // setImage(image);
}

void ImageEdit::normalButton()
{
   setImage(image);
}




void ImageEdit::setOpacity(int value)
{

    imageLabel->setAutoFillBackground(true);

    QImage newImg(image.size(), QImage::Format_ARGB32);
    newImg.fill(Qt::transparent);

    QPainter painter(&newImg);


    if(value == 1){
        painter.setOpacity(0.1);
    }
    else if(value == 2){
        painter.setOpacity(0.2);
    }
    else if(value == 3){
        painter.setOpacity(0.3);
    }
    else if(value == 4){
        painter.setOpacity(0.4);
    }
    else if(value == 5){
        painter.setOpacity(0.5);
    }
    else if(value == 6){
        painter.setOpacity(0.6);
    }
    else if(value == 7){
        painter.setOpacity(0.7);
    }
    else if(value == 8){
        painter.setOpacity(0.8);
    }
    else if(value == 9){
        painter.setOpacity(0.9);
    }
    else if(value == 10){
        painter.setOpacity(1);
    }

    painter.drawImage(QRect(0, 0, image.width(), image.height()), image);
    imageLabel->setPixmap(QPixmap::fromImage(newImg));
    scrollArea->setVisible(true);
    fitToWindowAct->setEnabled(true);
    updateActions();

    if (!fitToWindowAct->isChecked())
        imageLabel->adjustSize();

}


//void ImageEdit::setText()







