#include "Figure.h"
#include <QtCharts/QLineSeries>
#include <QtCharts/QScatterSeries>
#include <QtWidgets/QHBoxLayout>

QT_CHARTS_USE_NAMESPACE

Figure::Figure(const Workspace &workspace, QWidget *parent)
    : QWidget(parent), m_chartView(new QChartView(this)),
      m_typeBox(new QComboBox), m_curveType(1) {
  // Chart
  QChart *chart(new QChart);
  m_chartView->setChart(chart);
  chart->legend()->hide();
  chart->setTitle("Cos(x) with errors & NaNs");

  // Start with a scatter series
  auto *series0 = new QScatterSeries();
  series0->setName("Cos(x) with NaNs");
  const auto &curve0 = workspace[0];
  for (size_t i = 0; i < curve0.y.size(); ++i) {
    const auto &x = curve0.x[i];
    const auto &y = curve0.y[i];
    series0->append(x, y);
  }
  m_chartView->chart()->addSeries(series0);
  m_chartView->chart()->createDefaultAxes();
  m_chartView->chart()->axisX()->setGridLineVisible(false);
  m_chartView->chart()->axisY()->setGridLineVisible(false);
  m_chartView->chart()->axisX()->setLineVisible(true);

  // Curve type selection
  m_typeBox->addItem("Points");
  m_typeBox->addItem("Line");
  m_typeBox->addItem("Line + Points");

  auto layout = new QHBoxLayout;
  layout->addWidget(m_chartView);
  layout->addWidget(m_typeBox);
  this->setLayout(layout);

  // signals
  connect(m_typeBox, SIGNAL(currentIndexChanged(int)), this,
          SLOT(onCurveTypeChanged(int)));
}

void Figure::onCurveTypeChanged(int newIndex) {
  switchToSeriesType(newIndex + 1);
}

void Figure::switchToSeriesType(int type) {
  if (type == m_curveType)
    return;

  auto chart = m_chartView->chart();
  QXYSeries *oldSeries(static_cast<QXYSeries *>(chart->series().front()));
  QXYSeries *newSeries(nullptr);
  if (type == 1 || (type == 3 && m_curveType == 2)) {
    newSeries = new QScatterSeries;
  } else if (type == 2 || (type == 3 && m_curveType == 1)) {
    newSeries = new QLineSeries;
  }

  // Pull over the data - this is not great!
  auto oldPoints = oldSeries->points();
  for (int i = 0; i < oldPoints.size(); ++i) {
    newSeries->append(oldPoints[i].x(), oldPoints[i].y());
  }
  if (type < 3) {
    chart->removeAllSeries();
  }
  chart->addSeries(newSeries);
  m_curveType = type;
}
