#include "iniciosesion.h"

#include <QApplication>
#include <QSplashScreen>
#include <QTimer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle("fusion");

    QSplashScreen * splash = new QSplashScreen;
       splash->setPixmap(QPixmap("://img/Iconos/logo.jpeg"));
       splash->show();

       InicioSesion w;

       QTimer::singleShot(3000, splash, SLOT(close()));
       QTimer::singleShot(3000, &w, SLOT(show()));

       //w.show();

       return a.exec();
    return a.exec();
}
