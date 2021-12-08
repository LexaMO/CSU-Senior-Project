#include <QApplication>
#include <QCommandLineParser>

#include "imageedit.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QGuiApplication::setApplicationDisplayName(ImageEdit::tr("Image Editor"));
    QCommandLineParser commandLineParser;
    commandLineParser.addHelpOption();
    commandLineParser.addPositionalArgument(ImageEdit::tr("[file]"), ImageEdit::tr("Image file to open."));
    commandLineParser.process(QCoreApplication::arguments());
    ImageEdit ImageEdit;
    if (!commandLineParser.positionalArguments().isEmpty()
        && !ImageEdit.loadFile(commandLineParser.positionalArguments().constFirst())) {
        return -1;
    }
    ImageEdit.show();

    return app.exec();
}

