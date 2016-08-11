#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QScatterSeries>

#include "WorkspaceFactory.h"

#include <cmath>

QT_CHARTS_USE_NAMESPACE

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  const double xmin(0.0), xmax(10);
  const size_t npts(50);
  auto wksp = WorkspaceFactory().create1D(
      xmin, xmax, npts, std::ptr_fun<double, double>(std::cos),
      [](double x) { return sqrt(fabs(x)); });

  QScatterSeries *series0 = new QScatterSeries();
  series0->setName("Sin(x)");
  series0->setMarkerShape(QScatterSeries::MarkerShapeCircle);
  series0->setMarkerSize(10.0);

  const auto &curve0 = (*wksp)[0];
  for (size_t i = 0; i < npts; ++i) {
    series0->append(curve0.x[i], curve0.y[i]);
  }

  QChart *chart = new QChart();
  chart->legend()->hide();
  chart->addSeries(series0);
  chart->createDefaultAxes();
  chart->setTitle("1D Plot With Errors");

  QChartView *chartView = new QChartView(chart);
  chartView->setRenderHint(QPainter::Antialiasing);

  QMainWindow window;
  window.setCentralWidget(chartView);
  window.resize(640, 480);
  window.show();

  return app.exec();
}
