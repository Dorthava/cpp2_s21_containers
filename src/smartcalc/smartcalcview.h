#ifndef CPP3_S21_SMARTCALC_V20_SMARTCALC_SMARTCALC_VIEW_H
#define CPP3_S21_SMARTCALC_V20_SMARTCALC_SMARTCALC_VIEW_H

#include <QDoubleValidator>
#include <QWidget>

#include "../graph/graphview.h"
#include "smartcalc_controller.h"
#include "smartcalc_model.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class SmartcalcView;
}
QT_END_NAMESPACE

namespace s21 {

class SmartcalcView : public QWidget {
  Q_OBJECT

 public:
  explicit SmartcalcView(QWidget* parent = nullptr);
  SmartcalcView(const SmartcalcView& other) = delete;
  SmartcalcView(SmartcalcView&& other) = delete;
  SmartcalcView& operator=(const SmartcalcView& other) = delete;
  SmartcalcView& operator=(SmartcalcView&& other) = delete;
  ~SmartcalcView();

  void СonversionNumber(QString& number);

 private:
  Ui::SmartcalcView* ui;
  GraphView* graph_;
  s21::Controller* controller_;
  s21::Model* model_;
  QDoubleValidator* doubleValidator;

 private slots:
  void SendSignal();
  void on_Button_eq_clicked();
  void on_Button_C_clicked();
  void on_pushBuildGraph_clicked();
};

}  // namespace s21

#endif  // CPP3_S21_SMARTCALC_V20_SMARTCALC_SMARTCALC_VIEW_H
