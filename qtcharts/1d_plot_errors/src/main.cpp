#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QBoxPlotSeries>

#include "WorkspaceFactory.h"

#include <cmath>

QT_CHARTS_USE_NAMESPACE

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  const double xmin(0.0), xmax(10);
  const size_t npts(50);
  auto wksp = WorkspaceFactory().create1D(
      xmin, xmax, npts, std::ptr_fun<double, double>(std::cos),
      [](double x) { return sqrt(fabs(0.1 * x)); });

  auto *series0 = new QBoxPlotSeries();
  series0->setName("Cos(x) with errors & NaNs");
  series0->setBoxOutlineVisible(false);
  auto &curve0 = (*wksp)[0];
  // Introduce some NaNs
  for(size_t i = 25; i < 35; ++i ) {
    curve0.y[i] = 0.0/0.0;
  }

  for (size_t i = 0; i < npts; ++i) {
    const auto &x = curve0.x[i];
    const auto &y = curve0.y[i];
    const auto &dy = curve0.dy[i];
    QBoxSet *box = new QBoxSet(QString::number(x));
    box->setValue(QBoxSet::LowerExtreme, y - 0.5 * dy);
    box->setValue(QBoxSet::UpperExtreme, y + 0.5 * dy);
    box->setValue(QBoxSet::Median, y);
    box->setValue(QBoxSet::LowerQuartile, y);
    box->setValue(QBoxSet::UpperQuartile, y);
    series0->append(box);
  }

  QChart *chart = new QChart();
  chart->legend()->hide();
  chart->addSeries(series0);
  chart->createDefaultAxes();
  chart->setTitle("Cos(x) with errors & NaNs");
  chart->axisX()->setGridLineVisible(false);
  chart->axisY()->setGridLineVisible(false);
  chart->axisX()->setLineVisible(true);

  QChartView *chartView = new QChartView(chart);
  chartView->setRenderHint(QPainter::Antialiasing);

  QMainWindow window;
  window.setCentralWidget(chartView);
  window.resize(640, 480);
  window.show();

  return app.exec();
}
