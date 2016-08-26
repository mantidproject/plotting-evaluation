""" Main Evaluation """
from PyQt4 import QtGui, QtCore

import ui_FigureForm


class PlotWindow(QtGui.QMainWindow):
    """
    Main class
    """

    def __init__(self, parent, name):
        """
        Init
        """
        QtGui.QMainWindow.__init__(self, None)

        self.setWindowTitle('Evaluation Main')
        self.ui = ui_FigureForm.Ui_MainWindow()
        self.ui.setupUi(self)

        # event handling
        self.ui.graphicsView.canvas().mpl_connect('button_press_event', self.evt_mouse_press)

        self._name = name

        self._myParentWindow = parent

        return

    # override
    def contextMenuEvent(self, event):
        """

        Args:
            event:

        Returns:

        """
        print 'Got an event on menu bar...', self._name

        return QtGui.QMainWindow.contextMenuEvent(self, event)

    # override
    # def event(self, q_event):
    #     """
    #
    #     Args:
    #         q_event:
    #
    #     Returns:
    #
    #     """
    #     if isinstance(q_event, QtGui.QPaintEvent):
    #         pass
    #     else:
    #         print 'Got an event...', self._name, type(q_event)
    #
    #     return QtGui.QMainWindow.event(self, q_event)

    # override
    # def mousePressEvent(self, event):
    #     """
    #     """
    #     print 'haha... ', self._name
    #
    #     QtGui.QWidget.mousePressEvent(self, event)
    #
    #     return

    def evt_mouse_press(self, event):
        """

        Args:
            event:

        Returns:

        """
        x = event.xdata
        y = event.ydata

        # double click!
        if event.dblclick:
            print 'Double Click!!!', event.button, event.x, event.y, event.xdata, event.ydata
            print 'Legend over: ', self.ui.graphicsView.canvas().get_legend().mouseover

            # identify whether the click is close to Axis

            xAxes, yAxes = self.ui.graphicsView.canvas().axes.transAxes.inverted().transform([event.x, event.y])
            print xAxes, yAxes
            if (-0.02 < xAxes < 0) | (1 < xAxes < 1.02):
                print "just outside x-axis"
            if (-0.02 < yAxes < 0) | (1 < yAxes < 1.02):
                print "just outside y-axis"

        button = event.button

        if button == 1:
            # left button
            self._myParentWindow.write_mouse_position(x, y)

        elif button == 3:
            # right click of mouse will pop up a context-menu
            self.ui.menu = QtGui.QMenu(self)

            # pop_action = QtGui.QAction('Pop', self)
            # pop_action.triggered.connect(self.pop_snap_view)
            # self.ui.menu.addAction(pop_action)

            # add other required actions
            self.ui.menu.popup(QtGui.QCursor.pos())
        # END-IF

    def focusInEvent(self, event):
        """

        Args:
            event:

        Returns:

        """
        print '%s: Got focus' % self._name

        self._myParentWindow.write_note(self._name, append=True)

        self._myParentWindow.set_active_window(self._name)

        return

    def focusOutEvent(self, event):
        """

        Args:
            event:

        Returns:

        """

        self._myParentWindow.delete_note(self._name, partial=True)

        print '%s: Lost focus' % self._name

    def plot(self, vec_x, vec_y):
        """

        Args:
            vec_x:
            vec_y:

        Returns:

        """
        self.ui.graphicsView.add_plot_1d(vec_x, vec_y, label='dd dd dd')

        return

    def set_x_title(self, title):
        """

        Args:
            title:

        Returns:

        """
        self.ui.graphicsView.set_axis_label(axis_x=True, label=title, axis_number=0)

        return


