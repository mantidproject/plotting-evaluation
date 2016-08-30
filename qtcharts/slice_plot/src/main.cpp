/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Data Visualization module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>
#include <QtDataVisualization>

using namespace QtDataVisualization;

int main(int argc, char **argv) {
  QApplication app(argc, argv);

  Q3DSurface *surface = new Q3DSurface;
  surface->setOrthoProjection(true);
  surface->setFlags(surface->flags() ^ Qt::FramelessWindowHint);

  QSurfaceDataProxy *dataProxy = new QSurfaceDataProxy();
  QSurface3DSeries *series = new QSurface3DSeries(dataProxy);
  const float sampleMax(10.f), sampleMin(0.f);
  int sampleCountX(50), sampleCountZ(50);
  float stepX = (sampleMax - sampleMin) / float(sampleCountX - 1);
  float stepZ = (sampleMax - sampleMin) / float(sampleCountZ - 1);

  QSurfaceDataArray *dataArray = new QSurfaceDataArray;
  dataArray->reserve(sampleCountZ);
  for (int i = 0; i < sampleCountZ; i++) {
    QSurfaceDataRow *newRow = new QSurfaceDataRow(sampleCountX);
    // Keep values within range bounds, since just adding step can cause minor
    // drift due
    // to the rounding errors.
    float z = qMin(sampleMax, (i * stepZ + sampleMin));
    int index = 0;
    for (int j = 0; j < sampleCountX; j++) {
      float x = qMin(sampleMax, (j * stepX + sampleMin));
      float R = qSqrt(z * z + x * x) + 0.01f;
      float y = (qSin(R) / R + 0.24f) * 1.61f;
      (*newRow)[index++].setPosition(QVector3D(x, y, z));
    }
    *dataArray << newRow;
  }

  dataProxy->resetArray(dataArray);
  surface->addSeries(series);

  //  QSurfaceDataArray *data = new QSurfaceDataArray;
  //  QSurfaceDataRow *dataRow1 = new QSurfaceDataRow;
  //  QSurfaceDataRow *dataRow2 = new QSurfaceDataRow;

  //  *dataRow1 << QVector3D(0.0f, 0.1f, 0.5f) << QVector3D(1.0f, 0.5f, 0.5f);
  //  *dataRow2 << QVector3D(0.0f, 1.8f, 1.0f) << QVector3D(1.0f, 1.2f, 1.0f);
  //  *data << dataRow1 << dataRow2;

  //  QSurface3DSeries *series = new QSurface3DSeries;
  //  series->dataProxy()->resetArray(data);
  //  surface->addSeries(series);

  QWidget *container = QWidget::createWindowContainer(surface);
  QSize screenSize = surface->screen()->size();
  container->setMinimumSize(
      QSize(screenSize.width() / 2, screenSize.height() / 1.6));
  container->setMaximumSize(screenSize);
  container->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  container->setFocusPolicy(Qt::StrongFocus);

  QMainWindow window;
  window.setCentralWidget(container);
  window.show();

  return app.exec();
}
