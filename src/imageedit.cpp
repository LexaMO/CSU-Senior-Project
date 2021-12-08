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


bool ImageEdit::saveFile(const QString &fileName)
{
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
    createFormGroupBox();

    QDockWidget *dock = new QDockWidget(tr("Editing Features"), this);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    dock->setWidget(horizontalGroupBox);
    addDockWidget(Qt::RightDockWidgetArea, dock);
    dock->setFixedWidth(300);


    QDockWidget *dock2 = new QDockWidget(tr("Crop Features"), this);
    dock2->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    dock2->setWidget(gridGroupBox);
    addDockWidget(Qt::RightDockWidgetArea, dock2);
    dock2->setFixedWidth(300);

    QDockWidget *dock3 = new QDockWidget(tr("Crop Features"), this);
    dock3->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    dock3->setWidget(formGroupBox);
    addDockWidget(Qt::RightDockWidgetArea, dock3);
    dock3->setFixedWidth(300);

}

void ImageEdit::createHorizontalGroupBox()
{
    horizontalGroupBox = new QGroupBox(tr("Effects"));
    QHBoxLayout *layout = new QHBoxLayout;
    buttons[0] = new QPushButton(tr("Blur").arg(1 + 1));
    connect(buttons[0], &QPushButton::released, this, &ImageEdit::blurButton);
    buttons[1] = new QPushButton(tr("Opacity").arg(2 + 1));
    connect(buttons[1], &QPushButton::released, this, &ImageEdit::opacityButton);
    buttons[2] = new QPushButton(tr("3:4").arg(3 + 1));
    buttons[3] = new QPushButton(tr("2:1").arg(4 + 1));
    buttons[4] = new QPushButton(tr("4:3").arg(5 + 1));
    for (int i = 0; i < NumButtons; ++i) {
        layout->addWidget(buttons[i]);
    }


    horizontalGroupBox->setLayout(layout);



}

void ImageEdit::createGridGroupBox()
{
    gridGroupBox = new QGroupBox(tr("Color Options"));

    QGridLayout *layout = new QGridLayout;

    QGroupBox *circleColorGroup = new QGroupBox(tr("Image color"));
    QSlider *circleColorSlider = new QSlider(Qt::Horizontal, circleColorGroup);
    circleColorSlider->setRange(0, 359);
    circleColorSlider->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    connect(circleColorSlider, &QAbstractSlider::valueChanged, this, &ImageEdit::setCircleColor);

    layout->addWidget(circleColorGroup);
    QVBoxLayout *circleColorLayout = new QVBoxLayout(circleColorGroup);
    circleColorLayout->addWidget(circleColorSlider);
    circleColorSlider->setValue(270);



    moreButtons[0] = new QPushButton(tr("Colorize").arg(1 + 1));
    connect(moreButtons[0], &QPushButton::released, this, &ImageEdit::colorizeButton);
    moreButtons[1] = new QPushButton(tr("color").arg(2 + 1));
    connect(moreButtons[1], &QPushButton::released, this, &ImageEdit::maskButton);
    moreButtons[2] = new QPushButton(tr("3:4").arg(3 + 1));
    moreButtons[3] = new QPushButton(tr("2:1").arg(4 + 1));
    moreButtons[4] = new QPushButton(tr("4:3").arg(5 + 1));
    for (int i = 0; i < NumButtons; ++i) {
        layout->addWidget(moreButtons[i]);
    }


    gridGroupBox->setLayout(layout);
}

void ImageEdit::createFormGroupBox()
{
    formGroupBox = new QGroupBox(tr("Form layout"));
    QFormLayout *layout = new QFormLayout;
    layout->addRow(new QLabel(tr("Line 1:")), new QLineEdit);
    layout->addRow(new QLabel(tr("Effect")), new QSpinBox);
    formGroupBox->setLayout(layout);

}

void ImageEdit::blurButton()
{

    imageLabel->setGraphicsEffect(new QGraphicsBlurEffect);
}

void ImageEdit::colorizeButton()
{
    imageLabel->setGraphicsEffect(new QGraphicsColorizeEffect);
}

void ImageEdit::opacityButton()
{
    imageLabel->setGraphicsEffect(new QGraphicsOpacityEffect);
}

void ImageEdit::maskButton()
{
}


QRectF rectangle_around(const QPointF &p, const QSizeF &size = QSize(250, 200))
{
    QRectF rect(p, size);
    rect.translate(-size.width()/2, -size.height()/2);
    return rect;
}

void ImageEdit::drawSource(QPainter &p)
{
    p.setPen(Qt::NoPen);
    p.setRenderHint(QPainter::Antialiasing);
    p.setCompositionMode(m_composition_mode);

    QRectF circle_rect = rectangle_around(m_circle_pos);
    QColor color = QColor::fromHsvF(m_circle_hue / 360.0, 1, 1, m_circle_alpha / 255.0);
    QLinearGradient circle_gradient(circle_rect.topLeft(), circle_rect.bottomRight());
    circle_gradient.setColorAt(0, color.lighter());
    circle_gradient.setColorAt(0.5, color);
    circle_gradient.setColorAt(1, color.darker());
    p.setBrush(circle_gradient);

    p.drawEllipse(circle_rect);
}














