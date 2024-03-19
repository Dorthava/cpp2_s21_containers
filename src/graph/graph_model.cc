#include "graph_model.h"

namespace s21 {
GraphModel::GraphModel() : calc_model_(new Model){};

GraphModel::~GraphModel() { delete calc_model_; }

void GraphModel::SetValue(const std::string& other) { received_ = other; }

void GraphModel::SetXMin(const double& other) { xMin_ = other; }

void GraphModel::SetXMax(const double& other) { xMax_ = other; }

void GraphModel::SetYMin(const double& other) { yMin_ = other; }

void GraphModel::SetYMax(const double& other) { yMax_ = other; }

void GraphModel::SetH(const double& other) { h_ = other; }

std::vector<double> s21::GraphModel::GetValuesX() { return x_values_; }

std::vector<double> s21::GraphModel::GetValuesY() { return y_values_; }

void GraphModel::CheckError() {
  if (xMin_ < -1000000 || xMin_ > 1000000) {
    throw std::string(
        "The \"xMin\" line contains a value that exceeds the permissible "
        "range");
  }

  if (xMax_ < -1000000 || xMax_ > 1000000) {
    throw std::string(
        "The \"xMax\" line contains a value that exceeds the permissible "
        "range");
  }

  if (yMin_ < -1000000 || yMin_ > 1000000) {
    throw std::string(
        "The \"yMin\" line contains a value that exceeds the permissible "
        "range");
  }

  if (yMax_ < -1000000 || yMax_ > 1000000) {
    throw std::string(
        "The \"yMax\" line contains a value that exceeds the permissible "
        "range");
  }
}

void GraphModel::CalculateResult() {
  CheckError();
  calc_model_->SetReceived(received_);

  x_values_.clear();
  y_values_.clear();

  h_ = 0.5;

  for (double x = xMin_; x < xMax_; x += h_) {
    calc_model_->SetValueX(x);
    x_values_.push_back(x);
    y_values_.push_back(calc_model_->CalculatingResult());
  }
}
}  // namespace s21
