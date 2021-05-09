#include "sudokugenerationwindow.h"
#include "ui_sudokugenerationwindow.h"

SudokuGenerationWindow::SudokuGenerationWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SudokuGenerationWindow)
{
    ui->setupUi(this);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimeout()));
    timer->start(1000);
    time = 0;

    list = {ui->lineEdit, ui->lineEdit_2, ui->lineEdit_3, ui->lineEdit_4, ui->lineEdit_5, ui->lineEdit_6, ui->lineEdit_7, ui->lineEdit_8, ui->lineEdit_9,
            ui->lineEdit_10, ui->lineEdit_11, ui->lineEdit_12, ui->lineEdit_13, ui->lineEdit_14, ui->lineEdit_15, ui->lineEdit_16, ui->lineEdit_17, ui->lineEdit_18,
            ui->lineEdit_19, ui->lineEdit_20, ui->lineEdit_21, ui->lineEdit_22, ui->lineEdit_23, ui->lineEdit_24, ui->lineEdit_25, ui->lineEdit_26, ui->lineEdit_27,
            ui->lineEdit_28, ui->lineEdit_29, ui->lineEdit_30, ui->lineEdit_31, ui->lineEdit_32, ui->lineEdit_33, ui->lineEdit_34, ui->lineEdit_35, ui->lineEdit_36,
            ui->lineEdit_37, ui->lineEdit_38, ui->lineEdit_39, ui->lineEdit_40, ui->lineEdit_41, ui->lineEdit_42, ui->lineEdit_43, ui->lineEdit_44, ui->lineEdit_45,
            ui->lineEdit_46, ui->lineEdit_47, ui->lineEdit_48, ui->lineEdit_49, ui->lineEdit_50, ui->lineEdit_51, ui->lineEdit_52, ui->lineEdit_53, ui->lineEdit_54,
            ui->lineEdit_55, ui->lineEdit_56, ui->lineEdit_57, ui->lineEdit_58, ui->lineEdit_59, ui->lineEdit_60, ui->lineEdit_61, ui->lineEdit_62, ui->lineEdit_63,
            ui->lineEdit_64, ui->lineEdit_65, ui->lineEdit_66, ui->lineEdit_67, ui->lineEdit_68, ui->lineEdit_69, ui->lineEdit_70, ui->lineEdit_71, ui->lineEdit_72,
            ui->lineEdit_73, ui->lineEdit_74, ui->lineEdit_75, ui->lineEdit_76, ui->lineEdit_77, ui->lineEdit_78, ui->lineEdit_79, ui->lineEdit_80, ui->lineEdit_81};
    for (int i = 0; i < 81; i++)
        list.at(i)->setValidator(new QIntValidator);
}

SudokuGenerationWindow::~SudokuGenerationWindow()
{
    delete ui;
}

void SudokuGenerationWindow::onTimeout()
{
    time++;
    ui->lcdNumber->display(time);
}
