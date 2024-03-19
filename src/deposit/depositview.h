#ifndef CPP3_S21_SMARTCALC_V20_DEPOSIT_DEPOSIT_VIEW_H
#define CPP3_S21_SMARTCALC_V20_DEPOSIT_DEPOSIT_VIEW_H

#include <QBoxLayout>
#include <QValidator>
#include <QWidget>

#include "deposit_controller.h"
#include "deposit_model.h"

namespace Ui {
class DepositView;
}

namespace s21 {

class DepositView : public QWidget {
  Q_OBJECT

 public:
  explicit DepositView(QWidget* parent = nullptr);
  DepositView(const DepositView& other) = delete;
  DepositView(DepositView&& other) = delete;
  DepositView& operator=(const DepositView& other) = delete;
  DepositView& operator=(DepositView&& other) = delete;
  ~DepositView();

 private slots:
  void on_pushButton_Reset_clicked();
  void on_pushButton_Calculate_clicked();
  void DeleteButton(const bool& index);
  void SetLine(QBoxLayout* layout);

  void on_AddReplenishment_clicked();
  void on_AddWithdrawal_clicked();

 private:
  bool CheckAndAddReplenishment(QBoxLayout* layout);
  void SetValidator();

  DepositController* controller_;
  DepositModel* model_;

  QDoubleValidator* validator_double_;
  QIntValidator* validator_int_;

  Ui::DepositView* ui;
};

}  // namespace s21
#endif  // CPP3_S21_SMARTCALC_V20_DEPOSIT_DEPOSIT_VIEW_H
