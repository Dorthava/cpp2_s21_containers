#include "smartcalc_controller.h"

namespace s21 {
// Controller::Controller() : model_(nullptr) {}

Controller::Controller(Model *model) : model_(model) {}

double s21::Controller::GetResult(const std::string &received_string) {
  model_->SetReceived(received_string);
  return model_->CalculatingResult();
}

void s21::Controller::SetValueX(const double &valueX) {
  model_->SetValueX(valueX);
}

}  // namespace s21
