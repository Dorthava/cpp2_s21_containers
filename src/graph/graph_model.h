#ifndef CPP3_S21_SMARTCALC_V20_GRAPH_GRAPH_MODEL_H
#define CPP3_S21_SMARTCALC_V20_GRAPH_GRAPH_MODEL_H
#include "../smartcalc/smartcalc_model.h"

namespace s21 {
class GraphModel {
 public:
  GraphModel();
  GraphModel(const GraphModel& other) = delete;
  GraphModel(GraphModel&& other) = delete;
  GraphModel& operator=(const GraphModel& other) = delete;
  GraphModel& operator=(GraphModel&& other) = delete;
  ~GraphModel();

  void CheckError();
  void CalculateResult();

  void SetValue(const std::string& other);
  void SetXMin(const double& other);
  void SetXMax(const double& other);
  void SetYMin(const double& other);
  void SetYMax(const double& other);
  void SetH(const double& other);

  std::vector<double> GetValuesX();
  std::vector<double> GetValuesY();

 private:
  Model* calc_model_;
  std::vector<double> x_values_;
  std::vector<double> y_values_;
  std::string received_;
  double xMin_;
  double xMax_;
  double yMin_;
  double yMax_;

  double h_;
};
}  // namespace s21

#endif  // CPP3_S21_SMARTCALC_V20_GRAPH_GRAPH_MODEL_H
