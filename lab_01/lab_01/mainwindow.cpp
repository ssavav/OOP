#include "mainwindow.h"
#include "figure.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // figure.points.data = (point_t*)malloc(sizeof(point_t) * MAX_VERTICES);
    // figure.edges.data  = (edge_t*)malloc(sizeof(edge_t) * MAX_EDGES);

    // if (!figure.points.data || !figure.edges.data) {
    //     free(figure.points.data);
    //     free(figure.edges.data);
    //     throw std::runtime_error("Ошибка выделения памяти!");
    // }

    QGraphicsScene *scene = new QGraphicsScene(this);

    ui->graph->setScene(scene);
    ui->graph->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graph->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    
    ui->graph->setRenderHint(QPainter::Antialiasing);
    ui->graph->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

    ui->graph->setStyleSheet("QGraphicsView {background-color: white}");
    connect(ui->draw_btn, &QPushButton::clicked, this, &MainWindow::draw);
    connect(ui->file_btn, &QPushButton::clicked, this, &MainWindow::import);
    connect(ui->choose_btn, &QPushButton::clicked, this, &MainWindow::openFileDialog);
    connect(ui->translate_btn, &QPushButton::clicked, this, &MainWindow::translateModel);
    connect(ui->scale_btn, &QPushButton::clicked, this, &MainWindow::scaleModel);
    connect(ui->rotate_btn, &QPushButton::clicked, this, &MainWindow::rotateModel);
    connect(ui->export_btn, &QPushButton::clicked, this, &MainWindow::export_gui);
}

MainWindow::~MainWindow()
{
    request_t request;
    request.action = QUIT;
    manager(request);
    // free(figure.points.data);
    // free(figure.edges.data);
    delete ui;
}

void MainWindow::show_error(int error)
{
    char *str = "Ошибка!";
    switch (error)
    {
    case DATA_ERROR:
        str = "Фигура не задана!";
        break;
    case FILE_ERROR:
        str = "Ошибка при работе с файлом!";
        break;
    
    default:
        break;
    }
    QMessageBox::warning(this, "Ошибка", str);
}

void MainWindow::draw()
{   
    request_t request;
    request.action = CHECK;
    
    int error = manager(request);
    if (error) 
    {
        show_error(error);
        return;
    }
    QRect rcontent = ui->graph->contentsRect();
    ui->graph->scene()->setSceneRect(0, 0, rcontent.width(), rcontent.height());

    request.action = DRAW;
    request.draw.scene = ui->graph->scene();
    request.draw.width = rcontent.width();
    request.draw.height = rcontent.height();


    error = manager(request);
    if (error) show_error(error);
    
}

void MainWindow::import()
{
    QString filename = ui->file_inpt->text();
    std::string std_filename = filename.toStdString();
    const char *c_filename = std_filename.c_str();
    
    request_t request;
    request.action = IMPORT;
    request.filename = c_filename;
    std::cout << request.filename <<std::endl;

    int error = manager(request);
    if (error) show_error(error);
}

void MainWindow::export_gui()
{
    QString filename = ui->file_inpt->text();
    std::string std_filename = filename.toStdString();
    const char *c_filename = std_filename.c_str();

    request_t request;
    request.action = CHECK;
    
    int error = manager(request);
    if (error) 
    {
        show_error(error);
        return;
    }

    request.action = EXPORT;
    request.filename = c_filename;

    error = manager(request);
    if (error) show_error(error);
}

void MainWindow::openFileDialog()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Выберите файл", "../../../../OOP/lab_01/lab_01/data");
    if (!fileName.isEmpty())
    {
        ui->file_inpt->setText(fileName);
    }
}

void MainWindow::translateModel()
{   
    request_t request;
    request.action = CHECK;
    
    int error = manager(request);
    if (error) 
    {
        show_error(error);
        return;
    }
    bool ok1, ok2, ok3;
    request.move.dx = ui->dx_inpt->text().toDouble(&ok1);
    request.move.dy = ui->dy_inpt->text().toDouble(&ok2);
    request.move.dz = ui->dz_inpt->text().toDouble(&ok3);
    
    if (!ok1 || !ok2 || !ok3) {
        QMessageBox::warning(this, "Ошибка", "Введите корректные числа для переноса");
        return;
    }
    request.action = MOVE;
    manager(request);
    draw();
}

void MainWindow::scaleModel()
{
    request_t request;
    request.action = CHECK;
    
    int error = manager(request);
    if (error) 
    {
        show_error(error);
        return;
    }
    bool ok1, ok2, ok3;
    request.scale.sx = ui->x_scale->text().toDouble(&ok1);
    request.scale.sy = ui->y_scale->text().toDouble(&ok2);
    request.scale.sz = ui->z_scale->text().toDouble(&ok3);
    
    if (!ok1 || !ok2 || !ok3) {
        QMessageBox::warning(this, "Ошибка", "Введите корректные числа для масштабирования");
        return;
    }
    
    request.action = SCALE;
    manager(request);
    draw();
}

void MainWindow::rotateModel()
{
    request_t request;
    request.action = CHECK;
    
    int error = manager(request);
    if (error) 
    {
        show_error(error);
        return;
    }
    bool ok1, ok2, ok3;
    request.rotate.ax = ui->x_angle->text().toDouble(&ok1);
    request.rotate.ay = ui->y_angle->text().toDouble(&ok2);
    request.rotate.az = ui->z_angle->text().toDouble(&ok3);
    
    if (!ok1 || !ok2 || !ok3) {
        QMessageBox::warning(this, "Ошибка", "Введите корректные числовые значения для поворота");
        return;
    }
    
    request.action = ROTATE;
    manager(request);
    draw();
}
