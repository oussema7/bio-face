#include <QtWidgets/QApplication>
#include "include/interface.h"

/** Main **/
int main(int argc, char *argv[])
{
    //Interface
    QApplication app(argc, argv);

    Interface fenetre;

    fenetre.show();

    return app.exec();
}
