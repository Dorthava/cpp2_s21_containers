#include "creditview.h"

#include <QMessageBox>

#include "../ui/ui_creditview.h"

namespace s21 {
CreditView::CreditView(QWidget* parent)
    : QWidget(parent), ui(new Ui::CreditView) {
  ui->setupUi(this);
  model_ = new CreditModel();
  controller_ = new CreditController(model_);
  SetValidators();
}

CreditView::~CreditView() {
  delete ui;

  delete validator_double_;
  delete validator_int_;

  delete model_;
  delete controller_;
}

void CreditView::SetValidators() {
  validator_double_ = new QDoubleValidator();
  validator_double_->setLocale(QLocale::English);
  validator_int_ = new QIntValidator(1, 600);  // От одного до 600 месяцев

  ui->lineEdit_Interest_rate->setValidator(validator_double_);
  ui->lineEdit_Term->setValidator(validator_int_);
  ui->lineEdit_TotalAmount->setValidator(validator_double_);
}

void CreditView::on_pushButton_clicked() {  // Надо бы вывести результат
                                            // проверки строки
  bool error = false;
  double total_amount = ui->lineEdit_TotalAmount->text().toDouble(&error);
  if (!error) {
    QMessageBox::critical(0, "Error",
                          "Incorrectly entered field \"Total Amount\"");
    return;
  }

  int term = ui->lineEdit_Term->text().toInt(&error);
  if (!error) {
    QMessageBox::critical(0, "Error", "Incorrectly entered field \"Term\"");
    return;
  }

  double interest_rate = ui->lineEdit_Interest_rate->text().toDouble(&error);
  if (!error) {
    QMessageBox::critical(0, "Error",
                          "Incorrectly entered field \"Interest rate\"");
    return;
  }

  controller_->SetInput(total_amount, term, interest_rate,
                        ui->radioButton_Annuity->isChecked());

  try {
    controller_->CalculateResult();
  } catch (const std::string& ex) {
    QMessageBox::critical(nullptr, "Error", QString::fromStdString(ex));
    return;
  }

  ui->lineEdit_TotalPayment->setText(
      QString::number(controller_->GetTotalPayment(), 'f', 2));
  ui->lineEdit_Overpayment->setText(
      QString::number(controller_->GetOverpaymentOnCredit(), 'f', 2));
  QString result;
  if (!ui->radioButton_Annuity->isChecked())
    result = QString::number(controller_->GetMonthlyPayment().first, 'f', 2) +
             "..." +
             QString::number(controller_->GetMonthlyPayment().second, 'f', 2);
  else
    result = QString::number(controller_->GetMonthlyPayment().first, 'f', 2);
  ui->lineEdit_Monthly->setText(result);
  controller_->GetMonthlyPayment();
}

void CreditView::on_pushButton_2_clicked() {
  controller_->SetInput(0., 0, 0., true);
  ui->radioButton_Annuity->setChecked(true);

  ui->lineEdit_Interest_rate->clear();
  ui->lineEdit_Monthly->clear();
  ui->lineEdit_Overpayment->clear();
  ui->lineEdit_TotalPayment->clear();
  ui->lineEdit_TotalAmount->clear();
  ui->lineEdit_Term->clear();
}
}  // namespace s21
