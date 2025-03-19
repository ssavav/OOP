#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QMessageBox>
#include <QPen>
#include <QBrush>
#include "figure.h"
#include "request_manager.h"
#include "draw.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    figure_t figure;
    void draw();
    void import();
    void openFileDialog();
    void translateModel();
    void scaleModel();
    void rotateModel();
    void export_gui();
    void show_error(int error);

};
#endif // MAINWINDOW_H
