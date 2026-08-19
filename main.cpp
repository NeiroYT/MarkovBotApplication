#include "NeirobotChatApplication.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    qRegisterMetaType<ExternalMsg>();
    QApplication app(argc, argv);
    NeirobotChatApplication window;
    window.show();
    return app.exec();
}
