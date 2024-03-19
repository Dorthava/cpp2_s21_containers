#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <locale.h>

#include <QMainWindow>

#include "credit/creditview.h"
#include "deposit/depositview.h"
#include "smartcalc/smartcalcview.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

namespace s21 {
class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget* parent = nullptr);
  ~MainWindow();

 private slots:
  void on_actionSmartCalc_triggered();

  void on_actionCreditCalc_triggered();

  void on_actionDepositCalc_triggered();

 private:
  SmartcalcView* smartcalc_view_;
  CreditView* credit_view_;
  DepositView* deposit_view_;
  Ui::MainWindow* ui;
};
}  // namespace s21
#endif  // MAINWINDOW_H
