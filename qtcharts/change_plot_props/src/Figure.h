#ifndef FIGURE_H
#define FIGURE_H

#include "Workspace.h"

#include <QtWidgets/QWidget>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QGridLayout>

#include <QtCharts/QChartView>

class Figure : public QWidget {
  Q_OBJECT
public:
  explicit Figure(const Workspace &workspace, QWidget *parent = 0);

private slots:
  void onTitleTextEdited(const QString &newTitle);
  void onXLabelTextEdited(const QString &newLabel);
  void onYLabelTextEdited(const QString &newLabel);
  void onCurveTypeChanged(int newIndex);

private:
  void setTitleText(const QString &text);
  void setXLabelText(const QString &text);
  void setYLabelText(const QString &text);
  void switchToSeriesType(int type);

private:
  QT_CHARTS_NAMESPACE::QChartView *m_chartView;
  QGridLayout *m_propsLayout;
  QComboBox *m_typeBox;
  QLineEdit *m_title, *m_xlabel, *m_ylabel;
  int m_curveType;
};

#endif // FIGURE_H
