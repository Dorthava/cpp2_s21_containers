#include "graph_controller.h"

namespace s21 {

GraphController::GraphController(s21::GraphModel* model) : model_(model) {}

void GraphController::CalculateResult() { model_->CalculateResult(); }

void GraphController::SetValue(const std::string& other) {
  model_->SetValue(other);
}

void GraphController::SetXMin(const double& other) { model_->SetXMin(other); }

void GraphController::SetXMax(const double& other) { model_->SetXMax(other); }

void GraphController::SetYMin(const double& other) { model_->SetYMin(other); }

void GraphController::SetYMax(const double& other) { model_->SetYMax(other); }

void GraphController::SetH(const double& other) { model_->SetH(other); }

std::vector<double> GraphController::GetValuesX() {
  return model_->GetValuesX();
}

std::vector<double> GraphController::GetValuesY() {
  return model_->GetValuesY();
}
}  // namespace s21
