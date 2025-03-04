#include "mainwindow.h"
#include "figure.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    figure.points.data = (point_t*)malloc(sizeof(point_t) * MAX_VERTICES);
    figure.edges.data  = (edge_t*)malloc(sizeof(edge_t) * MAX_EDGES);

    if (!figure.points.data || !figure.edges.data) {
        free(figure.points.data);
        free(figure.edges.data);
        throw std::runtime_error("Ошибка выделения памяти!");
    }

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
    free(figure.points.data);
    free(figure.edges.data);
    delete ui;
}

void MainWindow::draw()
{
    if (check_figure(figure))
    {
        QMessageBox::warning(this, "Ошибка", "Фигура не задана!");
        return;
    }
    
    QRect rcontent = ui->graph->contentsRect();
    ui->graph->scene()->setSceneRect(0, 0, rcontent.width(), rcontent.height());
    
    draw_figure(ui->graph->scene(), figure);
}

void MainWindow::import()
{
    QString filename = ui->file_inpt->text();
    std::string std_filename = filename.toStdString();
    const char *c_filename = std_filename.c_str();
    if (read_figure(c_filename, figure))
    {
        QMessageBox::warning(this, "Ошибка", "Ошибка в чтении файла!");
        return;
    }
    printf("v:%d e:%d\n", figure.edges.len, figure.points.len);
}

void MainWindow::export_gui()
{
    QString filename = ui->file_inpt->text();
    std::string std_filename = filename.toStdString();
    const char *c_filename = std_filename.c_str();
    if (export_figure(c_filename, figure))
    {
        QMessageBox::warning(this, "Ошибка", "Ошибка в записи файла!");
        return;
    }
    printf("v:%d e:%d\n", figure.edges.len, figure.points.len);
}

void MainWindow::openFileDialog()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Выберите файл");
    if (!fileName.isEmpty())
    {
        ui->file_inpt->setText(fileName);
    }
}

void MainWindow::translateModel()
{
    if (check_figure(figure))
    {
        QMessageBox::warning(this, "Ошибка", "Фигура не задана!");
        return;
    }
    bool ok1, ok2, ok3;
    double dx = ui->dx_inpt->text().toDouble(&ok1);
    double dy = ui->dy_inpt->text().toDouble(&ok2);
    double dz = ui->dz_inpt->text().toDouble(&ok3);
    
    if (!ok1 || !ok2 || !ok3) {
        QMessageBox::warning(this, "Ошибка", "Введите корректные числа для переноса");
        return;
    }
    
    translate_points(dx, dy, dz, figure.points);
    draw();
}

void MainWindow::scaleModel()
{
    if (check_figure(figure))
    {
        QMessageBox::warning(this, "Ошибка", "Фигура не задана!");
        return;
    }
    bool ok1, ok2, ok3;
    double sx = ui->x_scale->text().toDouble(&ok1);
    double sy = ui->y_scale->text().toDouble(&ok2);
    double sz = ui->z_scale->text().toDouble(&ok3);
    
    if (!ok1 || !ok2 || !ok3) {
        QMessageBox::warning(this, "Ошибка", "Введите корректные числа для масштабирования");
        return;
    }
    
    scale_points(sx, sy, sz, figure.points);
    draw();
}

void MainWindow::rotateModel()
{
    if (check_figure(figure))
    {
        QMessageBox::warning(this, "Ошибка", "Фигура не задана!");
        return;
    }
    bool ok1, ok2, ok3;
    double ax = ui->x_angle->text().toDouble(&ok1);
    double ay = ui->y_angle->text().toDouble(&ok2);
    double az = ui->z_angle->text().toDouble(&ok3);
    
    if (!ok1 || !ok2 || !ok3) {
        QMessageBox::warning(this, "Ошибка", "Введите корректные числовые значения для поворота");
        return;
    }
    
    rotate_points(ax, ay, az, figure.points);
    draw();
}
