#include "graphview.h"

#include <QVector>

#include "../ui/ui_graphview.h"

namespace s21 {

GraphView::GraphView(QWidget *parent) : QWidget(parent), ui(new Ui::GraphView) {
  ui->setupUi(this);

  ui->widget->xAxis->setLabel("X");
  ui->widget->yAxis->setLabel("Y");

  graph_model_ = new GraphModel();
  graph_controller_ = new GraphController(graph_model_);

  // qDebug() << this->parent()->objectName();
  connect(ui->ButtonCreateGraph, &QPushButton::clicked, this,
          &GraphView::CreateGraph);
}

GraphView::~GraphView() {
  delete graph_model_;
  delete graph_controller_;

  delete ui;
}

void s21::GraphView::SetValue(const std::string &other) {
  graph_controller_->SetValue(other);
}

void GraphView::CreateGraph() {
  bool error = true;
  double xMin = ui->lineXmin->text().toDouble(&error);
  if (!error) {
    QMessageBox::critical(nullptr, "Error",
                          "Incorrectly entered field \"xMin\"");
    return;
  }
  double xMax = ui->lineXmax->text().toDouble(&error);
  if (!error) {
    QMessageBox::critical(nullptr, "Error",
                          "Incorrectly entered field \"xMax\"");
    return;
  }
  double yMin = ui->lineYmin->text().toDouble(&error);
  if (!error) {
    QMessageBox::critical(nullptr, "Error",
                          "Incorrectly entered field \"yMin\"");
    return;
  }
  double yMax = ui->lineYmax->text().toDouble(&error);
  if (!error) {
    QMessageBox::critical(nullptr, "Error",
                          "Incorrectly entered field \"yMax\"");
    return;
  }
  graph_controller_->SetXMax(xMax);
  graph_controller_->SetXMin(xMin);
  graph_controller_->SetYMax(yMax);
  graph_controller_->SetYMin(yMin);

  ui->widget->xAxis->setRange(xMin, xMax);
  ui->widget->yAxis->setRange(yMin, yMax);

  try {
    graph_controller_->CalculateResult();
  } catch (const std::string &ex) {
    QMessageBox::critical(nullptr, "Error", QString::fromStdString(ex));
    return;
  }

  std::vector<double> x_results = graph_controller_->GetValuesX();
  std::vector<double> y_results = graph_controller_->GetValuesY();

  ui->widget->addGraph();
  ui->widget->graph(0)->setData(
      QVector<double>(x_results.begin(), x_results.end()),
      QVector<double>(y_results.begin(), y_results.end()));
  ui->widget->replot();
}

}  // namespace s21
