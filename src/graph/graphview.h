#ifndef CPP3_S21_SMARTCALC_V20_GRAPH_GRAPH_VIEW_H
#define CPP3_S21_SMARTCALC_V20_GRAPH_GRAPH_VIEW_H

#include <QWidget>

#include "graph_controller.h"
#include "graph_model.h"
#include "qcustomplot.h"

namespace Ui {
class GraphView;
}

namespace s21 {
class GraphView : public QWidget {
  Q_OBJECT

 public:
  GraphView() = delete;
  explicit GraphView(QWidget* parent = nullptr);
  GraphView(const GraphView& other) = delete;
  GraphView(GraphView&& other) = delete;
  GraphView& operator=(const GraphView& other) = delete;
  GraphView& operator=(GraphView&& other) = delete;
  ~GraphView();

  void SetValue(const std::string& other);

 private:
  GraphController* graph_controller_;
  GraphModel* graph_model_;

  Ui::GraphView* ui;

 private slots:
  void CreateGraph();
};

}  // namespace s21

#endif  // CPP3_S21_SMARTCALC_V20_GRAPH_GRAPH_VIEW_H
