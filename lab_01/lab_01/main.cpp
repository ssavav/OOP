#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    try
    {
        MainWindow w;
        w.show();
        return a.exec();
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        QMessageBox::critical(nullptr, "Uzhas! ERROR!", e.what());
        return MEMORY_ERROR;
    }
    
}
