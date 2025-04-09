#include "mainscreen.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QResource>
#include "config.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "StarWar_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    QResource::registerResource("./plane.rcc");//注册的资源需要在Debug文件夹下

    MainScreen w;
    w.show();
    return a.exec();
}
