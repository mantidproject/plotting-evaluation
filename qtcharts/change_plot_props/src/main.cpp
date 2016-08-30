#include "Figure.h"

#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>

#include "WorkspaceFactory.h"

#include <cmath>

QT_CHARTS_USE_NAMESPACE

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  // ---------------------------------------------------------------------------
  // Create data
  // ---------------------------------------------------------------------------
  const double xmin(0.0), xmax(10);
  const size_t npts(50);
  auto wksp = WorkspaceFactory().create1D(
      xmin, xmax, npts, std::ptr_fun<double, double>(std::cos),
      [](double x) { return sqrt(fabs(0.1 * x)); });
  // Introduce some NaNs
  auto &curve0 = (*wksp)[0];
  for(size_t i = 25; i < 35; ++i ) {
    curve0.y[i] = 0.0/0.0;
  }

  // ---------------------------------------------------------------------------
  // Create figure
  // ---------------------------------------------------------------------------
  auto * fig = new Figure(*wksp);

  QMainWindow window;
  window.setCentralWidget(fig);
  window.resize(640, 480);
  window.show();

  return app.exec();
}
