#include "smartcalcview.h"

#include "../ui/ui_smartcalcview.h"

namespace s21 {

SmartcalcView::SmartcalcView(QWidget* parent)
    : QWidget(parent), ui(new Ui::SmartcalcView) {
  ui->setupUi(this);
  SendSignal();
  model_ = new s21::Model();
  graph_ = new GraphView(this);
  graph_->setWindowFlags(Qt::Popup);
  controller_ = new s21::Controller(model_);
  doubleValidator = new QDoubleValidator(-100000000, 100000000, 7);
  doubleValidator->setLocale(QLocale::English);
}

SmartcalcView::~SmartcalcView() {
  delete ui;

  delete graph_;
  delete model_;
  delete controller_;
  delete doubleValidator;
}

void SmartcalcView::SendSignal() {
  ui->textEdit->moveCursor(QTextCursor::Start);
  connect(ui->Button_0, &QPushButton::clicked, ui->textEdit,
          [this]() { ui->textEdit->insertPlainText("0"); });
  connect(ui->Button_1, &QPushButton::clicked, ui->textEdit,
          [this]() { ui->textEdit->insertPlainText("1"); });
  connect(ui->Button_2, &QPushButton::clicked, ui->textEdit,
          [this]() { ui->textEdit->insertPlainText("2"); });
  connect(ui->Button_3, &QPushButton::clicked, ui->textEdit,
          [this]() { ui->textEdit->insertPlainText("3"); });
  connect(ui->Button_4, &QPushButton::clicked, ui->textEdit,
          [this]() { ui->textEdit->insertPlainText("4"); });
  connect(ui->Button_5, &QPushButton::clicked, ui->textEdit,
          [this]() { ui->textEdit->insertPlainText("5"); });
  connect(ui->Button_6, &QPushButton::clicked, ui->textEdit,
          [this]() { ui->textEdit->insertPlainText("6"); });
  connect(ui->Button_7, &QPushButton::clicked, ui->textEdit,
          [this]() { ui->textEdit->insertPlainText("7"); });
  connect(ui->Button_8, &QPushButton::clicked, ui->textEdit,
          [this]() { ui->textEdit->insertPlainText("8"); });
  connect(ui->Button_9, &QPushButton::clicked, ui->textEdit,
          [this]() { ui->textEdit->insertPlainText("9"); });
  connect(ui->Button_comma, &QPushButton::clicked, ui->textEdit,
          [this]() { ui->textEdit->insertPlainText("."); });

  connect(ui->Button_x, &QPushButton::clicked, ui->textEdit,
          [this]() { ui->textEdit->insertPlainText("x"); });

  connect(ui->Button_add, &QPushButton::clicked, ui->textEdit,
          [this]() { ui->textEdit->insertPlainText("+"); });
  connect(ui->Button_min, &QPushButton::clicked, ui->textEdit,
          [this]() { ui->textEdit->insertPlainText("-"); });
  connect(ui->Button_mul, &QPushButton::clicked, ui->textEdit,
          [this]() { ui->textEdit->insertPlainText("*"); });
  connect(ui->Button_div, &QPushButton::clicked, ui->textEdit,
          [this]() { ui->textEdit->insertPlainText("/"); });

  connect(ui->Button_mod, &QPushButton::clicked, ui->textEdit,
          [this]() { ui->textEdit->insertPlainText("mod"); });
  connect(ui->Button_pow, &QPushButton::clicked, ui->textEdit,
          [this]() { ui->textEdit->insertPlainText("^"); });
  connect(ui->Button_sqrt, &QPushButton::clicked, ui->textEdit,
          [this]() { ui->textEdit->insertPlainText("sqrt"); });

  connect(ui->Button_BracketLeft, &QPushButton::clicked, ui->textEdit,
          [this]() { ui->textEdit->insertPlainText("("); });
  connect(ui->Button_BracketRight, &QPushButton::clicked, ui->textEdit,
          [this]() { ui->textEdit->insertPlainText(")"); });

  connect(ui->Button_sin, &QPushButton::clicked, ui->textEdit,
          [this]() { ui->textEdit->insertPlainText("sin"); });
  connect(ui->Button_cos, &QPushButton::clicked, ui->textEdit,
          [this]() { ui->textEdit->insertPlainText("cos"); });
  connect(ui->Button_tan, &QPushButton::clicked, ui->textEdit,
          [this]() { ui->textEdit->insertPlainText("tan"); });
  connect(ui->Button_asin, &QPushButton::clicked, ui->textEdit,
          [this]() { ui->textEdit->insertPlainText("asin"); });
  connect(ui->Button_acos, &QPushButton::clicked, ui->textEdit,
          [this]() { ui->textEdit->insertPlainText("acos"); });
  connect(ui->Button_atan, &QPushButton::clicked, ui->textEdit,
          [this]() { ui->textEdit->insertPlainText("atan"); });
  connect(ui->Button_ln, &QPushButton::clicked, ui->textEdit,
          [this]() { ui->textEdit->insertPlainText("ln"); });
  connect(ui->Button_log, &QPushButton::clicked, ui->textEdit,
          [this]() { ui->textEdit->insertPlainText("log"); });

  connect(ui->Button_C, &QPushButton::clicked, ui->textEdit,
          [this]() { ui->textEdit->clear(); });
}

void SmartcalcView::СonversionNumber(QString& number) {
  while (number.back() == '0') {
    number.resize(number.length() - 1);
  }
  if (number.back() == '.') number.resize(number.length() - 1);
}

void SmartcalcView::on_Button_eq_clicked() {
  if (ui->textEdit->toPlainText().size() > 255) {
    QMessageBox::critical(
        this, "Error", "The number of characters in a line is more than 255.");
    return;
  }
  QString result{};
  double value{};
  try {
    controller_->SetValueX(ui->lineEdit_2->text().toDouble());
    value = controller_->GetResult(ui->textEdit->toPlainText().toStdString());
  } catch (const std::string& ex) {
    QMessageBox::critical(this, "Error", QString::fromStdString(ex));
    // result = QString::fromStdString(ex);
    return;
  }
  result = QString::number(value, 'f', 7);
  СonversionNumber(result);
  ui->textEdit->setText(result);
  QTextCursor cursor = ui->textEdit->textCursor();
  cursor.movePosition(cursor.EndOfBlock);
  ui->textEdit->setTextCursor(cursor);
}

void SmartcalcView::on_Button_C_clicked() {
  ui->textEdit->clear();
  ui->textEdit->insertPlainText("0");
  ui->lineEdit_2->clear();
  ui->lineEdit_2->setText("0");
}

void SmartcalcView::on_pushBuildGraph_clicked() {
  graph_->show();
  graph_->SetValue(ui->textEdit->toPlainText().toStdString());
}

}  // namespace s21
