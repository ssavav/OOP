/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QVBoxLayout *verticalLayout_6;
    QLabel *label;
    QLineEdit *file_inpt;
    QPushButton *choose_btn;
    QHBoxLayout *horizontalLayout;
    QPushButton *file_btn;
    QPushButton *export_btn;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_5;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_8;
    QLineEdit *dx_inpt;
    QLabel *label_6;
    QLineEdit *dy_inpt;
    QLabel *label_7;
    QLineEdit *dz_inpt;
    QPushButton *translate_btn;
    QSpacerItem *verticalSpacer_2;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_17;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_18;
    QLineEdit *x_angle;
    QLabel *label_19;
    QLineEdit *y_angle;
    QLabel *label_20;
    QLineEdit *z_angle;
    QPushButton *rotate_btn;
    QSpacerItem *verticalSpacer_3;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_9;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_10;
    QLineEdit *x_scale;
    QLabel *label_11;
    QLineEdit *y_scale;
    QLabel *label_12;
    QLineEdit *z_scale;
    QPushButton *scale_btn;
    QSpacerItem *verticalSpacer_4;
    QPushButton *draw_btn;
    QGraphicsView *graph;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(876, 663);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(9, 6, 271, 601));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName("verticalLayout_6");
        label = new QLabel(verticalLayoutWidget);
        label->setObjectName("label");

        verticalLayout_6->addWidget(label);

        file_inpt = new QLineEdit(verticalLayoutWidget);
        file_inpt->setObjectName("file_inpt");

        verticalLayout_6->addWidget(file_inpt);

        choose_btn = new QPushButton(verticalLayoutWidget);
        choose_btn->setObjectName("choose_btn");

        verticalLayout_6->addWidget(choose_btn);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        file_btn = new QPushButton(verticalLayoutWidget);
        file_btn->setObjectName("file_btn");

        horizontalLayout->addWidget(file_btn);

        export_btn = new QPushButton(verticalLayoutWidget);
        export_btn->setObjectName("export_btn");

        horizontalLayout->addWidget(export_btn);


        verticalLayout_6->addLayout(horizontalLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_6->addItem(verticalSpacer);


        verticalLayout->addLayout(verticalLayout_6);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        label_5 = new QLabel(verticalLayoutWidget);
        label_5->setObjectName("label_5");

        verticalLayout_2->addWidget(label_5);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label_8 = new QLabel(verticalLayoutWidget);
        label_8->setObjectName("label_8");

        horizontalLayout_3->addWidget(label_8);

        dx_inpt = new QLineEdit(verticalLayoutWidget);
        dx_inpt->setObjectName("dx_inpt");

        horizontalLayout_3->addWidget(dx_inpt);

        label_6 = new QLabel(verticalLayoutWidget);
        label_6->setObjectName("label_6");

        horizontalLayout_3->addWidget(label_6);

        dy_inpt = new QLineEdit(verticalLayoutWidget);
        dy_inpt->setObjectName("dy_inpt");

        horizontalLayout_3->addWidget(dy_inpt);

        label_7 = new QLabel(verticalLayoutWidget);
        label_7->setObjectName("label_7");

        horizontalLayout_3->addWidget(label_7);

        dz_inpt = new QLineEdit(verticalLayoutWidget);
        dz_inpt->setObjectName("dz_inpt");

        horizontalLayout_3->addWidget(dz_inpt);


        verticalLayout_2->addLayout(horizontalLayout_3);

        translate_btn = new QPushButton(verticalLayoutWidget);
        translate_btn->setObjectName("translate_btn");

        verticalLayout_2->addWidget(translate_btn);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);


        verticalLayout->addLayout(verticalLayout_2);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName("verticalLayout_5");
        label_17 = new QLabel(verticalLayoutWidget);
        label_17->setObjectName("label_17");

        verticalLayout_5->addWidget(label_17);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        label_18 = new QLabel(verticalLayoutWidget);
        label_18->setObjectName("label_18");

        horizontalLayout_6->addWidget(label_18);

        x_angle = new QLineEdit(verticalLayoutWidget);
        x_angle->setObjectName("x_angle");

        horizontalLayout_6->addWidget(x_angle);

        label_19 = new QLabel(verticalLayoutWidget);
        label_19->setObjectName("label_19");

        horizontalLayout_6->addWidget(label_19);

        y_angle = new QLineEdit(verticalLayoutWidget);
        y_angle->setObjectName("y_angle");

        horizontalLayout_6->addWidget(y_angle);

        label_20 = new QLabel(verticalLayoutWidget);
        label_20->setObjectName("label_20");

        horizontalLayout_6->addWidget(label_20);

        z_angle = new QLineEdit(verticalLayoutWidget);
        z_angle->setObjectName("z_angle");

        horizontalLayout_6->addWidget(z_angle);


        verticalLayout_5->addLayout(horizontalLayout_6);

        rotate_btn = new QPushButton(verticalLayoutWidget);
        rotate_btn->setObjectName("rotate_btn");

        verticalLayout_5->addWidget(rotate_btn);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_3);


        verticalLayout->addLayout(verticalLayout_5);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        label_9 = new QLabel(verticalLayoutWidget);
        label_9->setObjectName("label_9");

        verticalLayout_3->addWidget(label_9);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        label_10 = new QLabel(verticalLayoutWidget);
        label_10->setObjectName("label_10");

        horizontalLayout_4->addWidget(label_10);

        x_scale = new QLineEdit(verticalLayoutWidget);
        x_scale->setObjectName("x_scale");

        horizontalLayout_4->addWidget(x_scale);

        label_11 = new QLabel(verticalLayoutWidget);
        label_11->setObjectName("label_11");

        horizontalLayout_4->addWidget(label_11);

        y_scale = new QLineEdit(verticalLayoutWidget);
        y_scale->setObjectName("y_scale");

        horizontalLayout_4->addWidget(y_scale);

        label_12 = new QLabel(verticalLayoutWidget);
        label_12->setObjectName("label_12");

        horizontalLayout_4->addWidget(label_12);

        z_scale = new QLineEdit(verticalLayoutWidget);
        z_scale->setObjectName("z_scale");

        horizontalLayout_4->addWidget(z_scale);


        verticalLayout_3->addLayout(horizontalLayout_4);

        scale_btn = new QPushButton(verticalLayoutWidget);
        scale_btn->setObjectName("scale_btn");

        verticalLayout_3->addWidget(scale_btn);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_4);

        draw_btn = new QPushButton(verticalLayoutWidget);
        draw_btn->setObjectName("draw_btn");

        verticalLayout_3->addWidget(draw_btn);


        verticalLayout->addLayout(verticalLayout_3);

        graph = new QGraphicsView(centralwidget);
        graph->setObjectName("graph");
        graph->setGeometry(QRect(290, 0, 571, 621));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 876, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\320\237\321\203\321\202\321\214 \320\272 \321\204\320\260\320\271\320\273\321\203", nullptr));
        choose_btn->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\320\261\321\200\320\260\321\202\321\214 \321\204\320\260\320\271\320\273", nullptr));
        file_btn->setText(QCoreApplication::translate("MainWindow", "\320\230\320\274\320\277\320\276\321\200\321\202\320\270\321\200\320\276\320\262\320\260\321\202\321\214 \321\202\320\276\321\207\320\272\320\270", nullptr));
        export_btn->setText(QCoreApplication::translate("MainWindow", "\320\255\320\272\321\201\320\277\320\276\321\200\321\202\320\270\321\200\320\276\320\262\320\260\321\202\321\214 \321\202\320\276\321\207\320\272\320\270", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "\320\237\320\265\321\200\320\265\320\275\320\276\321\201", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "dx", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "dy", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "dz", nullptr));
        translate_btn->setText(QCoreApplication::translate("MainWindow", "\320\237\320\265\321\200\320\265\320\275\320\265\321\201\321\202\320\270 \320\274\320\276\320\264\320\265\320\273\321\214", nullptr));
        label_17->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\262\320\276\321\200\320\276\321\202 \320\275\320\260 \321\203\320\263\320\276\320\273", nullptr));
        label_18->setText(QCoreApplication::translate("MainWindow", "dx", nullptr));
        x_angle->setText(QString());
        label_19->setText(QCoreApplication::translate("MainWindow", "dy", nullptr));
        label_20->setText(QCoreApplication::translate("MainWindow", "dz", nullptr));
        rotate_btn->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\262\320\265\321\200\320\275\321\203\321\202\321\214 \320\274\320\276\320\264\320\265\320\273\321\214", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "\320\234\320\260\321\201\321\210\321\202\320\260\320\261\320\270\321\200\320\276\320\262\320\260\320\275\320\270\320\265", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "sx", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "sy", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "sz", nullptr));
        scale_btn->setText(QCoreApplication::translate("MainWindow", "\320\234\320\260\321\201\321\210\321\202\320\260\320\261\320\270\321\200\320\276\320\262\320\260\321\202\321\214 \320\274\320\276\320\264\320\265\320\273\321\214", nullptr));
        draw_btn->setText(QCoreApplication::translate("MainWindow", "\320\235\320\260\321\200\320\270\321\201\320\276\320\262\320\260\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
