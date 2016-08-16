#ifndef WORKSPACE_H_
#define WORKSPACE_H_

#include <memory>
#include <vector>

using DoubleVector = std::vector<double>;

struct Spectrum {
  Spectrum(std::size_t npts) : x(npts, 0.0), y(npts, 0.0), dy(npts, 0.0) {}
  DoubleVector x, y, dy;
};

using SpectrumVector = std::vector<std::unique_ptr<Spectrum>>;

class Workspace {
public:
  /// Const access
  const Spectrum &operator[](const std::size_t index) const;
  /// Non-const access
  Spectrum &operator[](const std::size_t index);

  /// Modification
  void push_back(std::unique_ptr<Spectrum> spectrum);

private:
  SpectrumVector m_spectra;
};

#endif // WORKSPACE_H_
