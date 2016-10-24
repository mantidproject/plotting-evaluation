#!/usr/bin/python
"""Prototype to plot a requested number of curves on a single matplotlib plot

Usage python many_curves.py <number_of_curves> <number_of_x_pts> [0|1]

Final 'boolean' indicates if errors should be plotted
"""
from __future__ import print_function

import sys

import matplotlib.pyplot as plt
import numpy as np

# -----------------------------------------------------------------------------
# Constants
# -----------------------------------------------------------------------------
XMIN = -1.0
XMAX = 1.0
GAUSS_SIGMA = 0.1
GAUSS_AMP = 5.0
GAUSS_XBAR = 0.0

# -----------------------------------------------------------------------------
# Classes
# -----------------------------------------------------------------------------

class Points(object):
    _x = None
    _signal = None
    _errors = None

    def __init__(self, x, y, e):
        if x.shape[0] != y.shape[0]:
            raise RuntimeError("Mismatch in X/Y length. X={}, Y={}".format(x.shape[0], y.shape[0]))
        if x.shape[0] != e.shape[0]:
            raise RuntimeError("Mismatch in X/E length. X={}, E={}".format(x.shape[0], e.shape[0]))
        self._x = x
        self._signal = y
        self._sigma = e

    def x(self):
        return self._x

    def signal(self):
        return self._signal

    def errors(self):
        return self._sigma

# -----------------------------------------------------------------------------
# Functions
# -----------------------------------------------------------------------------

def parse_args(argv):
    """
    Return a tuple of (ncurves,npts,True|False)
    """
    ncurves, npts = int(argv[1]), int(argv[2])
    if len(argv) == 4:
        errors = bool(int(argv[3]))
    else:
        errors = True
    return (ncurves, npts, errors)


def gaussian(x, xbar, sigma, amp):
    return amp*np.exp(-0.5*np.square(x - xbar)/np.square(sigma))


def create_test_data(npts, xbar=GAUSS_XBAR, sigma=GAUSS_SIGMA, amp=GAUSS_AMP):
    x = np.linspace(XMIN, XMAX, npts)
    y = gaussian(x, xbar, sigma, amp)
    e = np.sqrt(0.01*y)
    return Points(x, y, e)


def plot(curves, errors=True):
    for curve in curves:
        if errors:
            plt.errorbar(curve.x(), curve.signal(), yerr=curve.errors())
        else:
            plt.plot(curve.x(), curve.signal())
    plt.show()

def main(argv):
    ncurves, npts, error_bars = parse_args(sys.argv)
    xbar = 0.0
    curves = []
    for i in range(ncurves):
        curves.append(create_test_data(npts, xbar=xbar))
        xbar += 0.1
    plot(curves, errors=error_bars)


# -----------------------------------------------------------------------------
# Main
# -----------------------------------------------------------------------------
if __name__ == '__main__':
    main(sys.argv)
