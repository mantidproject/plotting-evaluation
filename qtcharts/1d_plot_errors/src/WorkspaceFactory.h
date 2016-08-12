#ifndef WORKSPACEFACTORY_H_
#define WORKSPACEFACTORY_H_

#include "Workspace.h"
#include <algorithm>
#include <memory>

class WorkspaceFactory {
public:
  template <typename FuncY, typename FuncDy>
  std::unique_ptr<Workspace> create1D(double xmin, double xmax,
                                      std::size_t npoints, const FuncY &ygen,
                                      const FuncDy & dygen) const {
    std::unique_ptr<Spectrum> curve(new Spectrum(npoints));
    const double dx = (xmax - xmin) / static_cast<double>(npoints - 1);
    // Fill vectors
    double xvalue = xmin;
    std::generate_n(std::begin(curve->x), npoints, [&xvalue, dx]() {
      double tmp = xvalue;
      xvalue += dx;
      return tmp;
    });
    std::transform(std::begin(curve->x), std::end(curve->x),
                   std::begin(curve->y), ygen);
    std::transform(std::begin(curve->y), std::end(curve->y),
                   std::begin(curve->dy), dygen);
    std::unique_ptr<Workspace> wksp(new Workspace);
    wksp->push_back(std::move(curve));
    return wksp;
  }
};

#endif // WORKSPACEFACTORY_H_
