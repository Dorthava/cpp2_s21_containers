#ifndef CPP3_S21_SMARTCALC_V20_GRAPH_GRAPH_CONTROLLER_H
#define CPP3_S21_SMARTCALC_V20_GRAPH_GRAPH_CONTROLLER_H

#include "graph_model.h"

namespace s21 {
class GraphController {
 public:
  GraphController() = delete;
  GraphController(GraphModel* model);
  GraphController(const GraphController& other) = delete;
  GraphController(GraphController&& other) = delete;
  GraphController& operator=(const GraphController& other) = delete;
  GraphController& operator=(GraphController&& other) = delete;
  ~GraphController() = default;

  void CalculateResult();

  // Setters
  void SetValue(const std::string& other);
  void SetXMin(const double& other);
  void SetXMax(const double& other);
  void SetYMin(const double& other);
  void SetYMax(const double& other);
  void SetH(const double& other);

  // Getters
  std::vector<double> GetValuesX();
  std::vector<double> GetValuesY();

 private:
  GraphModel* model_;
};
}  // namespace s21

#endif  // CPP3_S21_SMARTCALC_V20_GRAPH_GRAPH_CONTROLLER_H
