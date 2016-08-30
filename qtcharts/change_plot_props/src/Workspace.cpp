#include "Workspace.h"

const Spectrum &Workspace::operator[](const std::size_t index) const {
  return *m_spectra[index];
}

Spectrum &Workspace::operator[](const std::size_t index) {
  return *m_spectra[index];
}

void Workspace::push_back(std::unique_ptr<Spectrum> spectrum) {
  m_spectra.push_back(std::move(spectrum));
}
