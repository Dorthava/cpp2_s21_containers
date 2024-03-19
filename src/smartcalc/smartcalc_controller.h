#ifndef CPP3_S21_SMARTCALC_V20_SMARTCALC_SMARTCALC_CONTROLLER_H
#define CPP3_S21_SMARTCALC_V20_SMARTCALC_SMARTCALC_CONTROLLER_H

#include "smartcalc_model.h"

namespace s21 {
class Controller {
 public:
  Controller() = delete;
  Controller(Model* model);
  Controller(const Controller& other) = delete;
  Controller(Controller&& other) = delete;
  Controller& operator=(const Controller& other) = delete;
  Controller& operator=(Controller&& other) = delete;
  ~Controller() = default;
  // Сеттеры
  void SetValueX(const double& valueX);

  // Геттеры
  double GetResult(const std::string& received_string);

 private:
  Model* model_;
};
}  // namespace s21

// #include "smartcalc_controller.cc"
#endif  // CPP3_S21_SMARTCALC_V20_SMARTCALC_SMARTCALC_CONTROLLER_H
