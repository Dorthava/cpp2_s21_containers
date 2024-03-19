#include "mainwindow.h"

#include "ui/ui_mainwindow.h"

namespace s21 {
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  smartcalc_view_ = new SmartcalcView(this);
  credit_view_ = new CreditView(this);
  deposit_view_ = new DepositView(this);
  ui->horizontalLayout_1->addWidget(smartcalc_view_);
  ui->horizontalLayout_2->addWidget(credit_view_);
  ui->horizontalLayout_3->addWidget(deposit_view_);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_actionSmartCalc_triggered() {
  ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_actionCreditCalc_triggered() {
  ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_actionDepositCalc_triggered() {
  ui->stackedWidget->setCurrentIndex(2);
}

}  // namespace s21
