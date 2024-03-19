#include "depositview.h"

#include <QMessageBox>

#include "../ui/ui_depositview.h"
namespace s21 {
DepositView::DepositView(QWidget *parent)
    : QWidget(parent), ui(new Ui::DepositView) {
  model_ = new DepositModel();
  controller_ = new DepositController(model_);
  ui->setupUi(this);

  SetValidator();
}

DepositView::~DepositView() {
  delete model_;
  delete controller_;

  delete validator_double_;
  delete validator_int_;

  delete ui;
}

void DepositView::SetValidator() {
  validator_double_ = new QDoubleValidator();
  validator_double_->setLocale(QLocale::English);
  validator_int_ = new QIntValidator(1, 999);

  ui->LineDepositAmount->setValidator(validator_double_);
  ui->LineDepositTerm->setValidator(validator_int_);
  ui->LineInterestRate->setValidator(validator_double_);
  ui->LineTaxRate->setValidator(validator_double_);
}

void DepositView::on_pushButton_Reset_clicked() {
  controller_->SetReset();
  ui->LineDepositAmount->clear();
  ui->LineDepositTerm->clear();
  ui->LineInterestRate->clear();
  ui->LineTaxRate->clear();
  ui->RadioButtonCapitalization->setChecked(false);
}

void DepositView::on_pushButton_Calculate_clicked() {
  bool error = false;
  double deposit_amount = ui->LineDepositAmount->text().toDouble(&error);
  if (!error) {
    QMessageBox::critical(nullptr, "Error",
                          "Incorrectly entered field \"Deposit amount\"");
    return;
  }

  double deposit_term = ui->LineDepositTerm->text().toInt(&error);
  if (!error) {
    QMessageBox::critical(nullptr, "Error",
                          "Incorrectly entered field \"Deposit term\"");
    return;
  }

  double interest_rate = ui->LineInterestRate->text().toDouble(&error);
  if (!error) {
    QMessageBox::critical(nullptr, "Error",
                          "Incorrectly entered field \"Interest rate\"");
    return;
  }

  double tax_rate = ui->LineTaxRate->text().toDouble(&error);
  if (!error) {
    QMessageBox::critical(nullptr, "Error",
                          "Incorrectly entered field \"Tax rate\"");
    return;
  }

  QDate date = ui->dateEdit->date();
  if (date.year() < 2000) {
    QMessageBox::critical(nullptr, "Error",
                          "Incorrectly entered field \"Start of term\"");
  }

  controller_->SetReset();

  controller_->SetDepositAmount(deposit_amount);
  controller_->SetDepositTerm(deposit_term);
  controller_->SetInterestRate(interest_rate);
  controller_->SetTaxRate(tax_rate);
  controller_->SetPeriodicity(ui->comboBox->currentIndex());
  controller_->SetCapitalization(ui->RadioButtonCapitalization->isChecked());
  controller_->SetDate(Date(date.day(), date.month(), date.year()));

  if (!ui->AddWD->isEmpty()) error = CheckAndAddReplenishment(ui->AddWD);
  if (!ui->AddRM->isEmpty()) error = CheckAndAddReplenishment(ui->AddRM);
  if (!error) return;
  try {
    controller_->CalculateResult();
  } catch (const std::string &ex) {
    QMessageBox::critical(nullptr, "Error", QString::fromStdString(ex));
    return;
  }

  ui->lineAccruedInterest->setText(
      QString::number(controller_->GetAccruedInterest(), 'f', 2));
  ui->lineTaxAmount->setText(
      QString::number(controller_->GetTaxAmount(), 'f', 2));
  ui->lineDepositEnd->setText(
      QString::number(controller_->GetDepositEnd(), 'f', 2));
}

bool DepositView::CheckAndAddReplenishment(QBoxLayout *layout) {
  for (int i = 0; i < layout->count(); i++) {
    bool error = true;
    double number = (qobject_cast<QLineEdit *>(
                         layout->itemAt(i)->layout()->itemAt(0)->widget()))
                        ->text()
                        .toDouble(&error);
    if (!error) {
      QMessageBox::critical(nullptr, "Error", "Incorrectly entered field ");
      return error;
    }
    if (layout->objectName() == "AddWD") number = -number;
    QDate date = (qobject_cast<QDateEdit *>(
                      layout->itemAt(i)->layout()->itemAt(1)->widget()))
                     ->date();
    if (date < ui->dateEdit->date() &&
        date > ui->dateEdit->date().addMonths(
                   ui->LineDepositTerm->text().toInt())) {
      QMessageBox::critical(nullptr, "Error", "Incorrectly entered field ");
      return error;
    }

    controller_->AddReplenishment(
        {Date(date.day(), date.month(), date.year()), number});
  }
  return true;
}

void DepositView::DeleteButton(const bool &index) {
  QPushButton *button = qobject_cast<QPushButton *>(sender());
  QLayout *layout;
  for (QObject *object : button->parentWidget()
                             ->layout()
                             ->children()[5]
                             ->children()[index]
                             ->children()) {
    layout = qobject_cast<QLayout *>(object);
    if (layout->indexOf(button) >= 0) {
      break;
    }
  }
  QLineEdit *lineEdit = qobject_cast<QLineEdit *>(layout->itemAt(0)->widget());
  QDateEdit *dateEdit = qobject_cast<QDateEdit *>(layout->itemAt(1)->widget());

  lineEdit->deleteLater();
  dateEdit->deleteLater();
  button->deleteLater();
  layout->deleteLater();

  // delete lineEdit;
  // delete dateEdit;
  // delete button;
  // delete layout;
}

void DepositView::SetLine(QBoxLayout *layout) {
  QHBoxLayout *innerLayout = new QHBoxLayout(this);
  layout->addLayout(innerLayout);
  QLineEdit *lineEdit = new QLineEdit(this);
  lineEdit->setValidator(validator_double_);
  innerLayout->addWidget(lineEdit);
  QDateEdit *dateEdit = new QDateEdit(this);
  innerLayout->addWidget(dateEdit);
  QPushButton *button = new QPushButton(this);
  button->setText("Delete");
  innerLayout->addWidget(button);
  bool index = layout->objectName() == ui->AddWD->objectName() ? true : false;
  connect(button, &QPushButton::clicked, this,
          [this, index] { DeleteButton(index); });
}

void DepositView::on_AddReplenishment_clicked() { SetLine(ui->AddRM); }

void DepositView::on_AddWithdrawal_clicked() { SetLine(ui->AddWD); }

}  // namespace s21
