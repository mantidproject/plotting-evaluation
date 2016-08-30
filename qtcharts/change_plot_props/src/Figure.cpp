#include "Figure.h"
#include <QtCharts/QLineSeries>
#include <QtCharts/QScatterSeries>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>

QT_CHARTS_USE_NAMESPACE

Figure::Figure(const Workspace &workspace, QWidget *parent)
    : QWidget(parent), m_chartView(new QChartView(this)),
      m_propsLayout(nullptr), m_typeBox(new QComboBox), m_title(new QLineEdit),
      m_xlabel(new QLineEdit), m_ylabel(new QLineEdit), m_curveType(1) {
  // Chart
  QChart *chart(new QChart);
  m_chartView->setChart(chart);
  chart->legend()->hide();

  // Start with a scatter series
  auto *series0 = new QScatterSeries();
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
  auto layout = new QHBoxLayout;
  layout->addWidget(m_chartView);

  // Properties
  m_propsLayout = new QGridLayout();
  m_propsLayout->addWidget(new QLabel("Title"), 0, 0);
  m_propsLayout->addWidget(m_title, 0, 1);
  connect(m_title, SIGNAL(textEdited(const QString &)), this,
          SLOT(onTitleTextEdited(const QString &)));
  m_propsLayout->addWidget(new QLabel("X Axis"), 1, 0);
  m_propsLayout->addWidget(m_xlabel, 1, 1);
  connect(m_xlabel, SIGNAL(textEdited(const QString &)), this,
          SLOT(onXLabelTextEdited(const QString &)));
  m_propsLayout->addWidget(new QLabel("Y Axis"), 2, 0);
  m_propsLayout->addWidget(m_ylabel, 2, 1);
  connect(m_ylabel, SIGNAL(textEdited(const QString &)), this,
          SLOT(onYLabelTextEdited(const QString &)));
  // Curve type selection
  m_typeBox->addItem("Points");
  m_typeBox->addItem("Line");
  m_typeBox->addItem("Line + Points");
  connect(m_typeBox, SIGNAL(currentIndexChanged(int)), this,
          SLOT(onCurveTypeChanged(int)));

  m_propsLayout->addWidget(new QLabel("Curve Type"), 3, 0);
  m_propsLayout->addWidget(m_typeBox, 3, 1);
  m_propsLayout->setRowStretch(4, 1);

  layout->addLayout(m_propsLayout);
  this->setLayout(layout);

  // signals
}

void Figure::onTitleTextEdited(const QString &newTitle) {
  setTitleText(newTitle);
}

void Figure::onXLabelTextEdited(const QString &newLabel) {
  setXLabelText(newLabel);
}

void Figure::onYLabelTextEdited(const QString &newLabel) {
  setYLabelText(newLabel);
}

void Figure::onCurveTypeChanged(int newIndex) {
  switchToSeriesType(newIndex + 1);
}

void Figure::setTitleText(const QString &text) {
  m_chartView->chart()->setTitle(text);
}

void Figure::setXLabelText(const QString &text) {
  m_chartView->chart()->axisX()->setTitleText(text);
}

void Figure::setYLabelText(const QString &text) {
  m_chartView->chart()->axisY()->setTitleText(text);
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
