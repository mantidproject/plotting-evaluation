# Plotting Evaluation
Contains prototypes for evaluating future plotting packages in Mantid

Examples to implement in each package:

1. Make a plot of a 1D function that contains NaNs and shows error bars. 
2. Make a plot of a 1D function in window 1, then in window 2, then come back in window 1 and add another curve to the plot
3. Make a 1D plot. Then change axis title and min/max. Title should contain something like micro, angstroms, and ^{-1}, maybe hbar
4. On a 1D plot, be able to click at a certain position and it should be able to transform that position into data coordinates (we need this for fitting and for reading data)
5. On the same plot, one should be able to differentiate double clicking on data, title/text, or axis object
6. On a plot with multiple datasets, be able to change plot symbols for one curve and replot
7. Print all graphics in a window to a file, say pdf
8. Make a 2D contour with some area masked (say a Gaussian in 2D with a wedge changed to NaNs)
9. Make a 2D plot with non orthogonal axes
