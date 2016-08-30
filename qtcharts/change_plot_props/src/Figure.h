#ifndef FIGURE_H
#define FIGURE_H

#include "Workspace.h"

#include <QWidget>
#include <QtCharts/QAbstractSeries>
#include <QtCharts/QChartView>
#include <QtWidgets/QComboBox>

class Figure : public QWidget {
  Q_OBJECT
public:
  explicit Figure(const Workspace &workspace, QWidget *parent = 0);

private slots:
  void onCurveTypeChanged(int newIndex);
  void switchToSeriesType(int type);

private:
  QT_CHARTS_NAMESPACE::QChartView *m_chartView;
  QComboBox *m_typeBox;
  int m_curveType;
};

#endif // FIGURE_H
