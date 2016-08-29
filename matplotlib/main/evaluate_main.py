""" Main Evaluation """
import sys
from PyQt4 import QtGui, QtCore

import plot_window
import function_generator

MplLineMarkers = [
    ". (point         )",
    "* (star          )",
    "x (x             )",
    "o (circle        )",
    "s (square        )",
    "D (diamond       )",
    ", (pixel         )",
    "None (nothing    )",
    "v (triangle_down )",
    "^ (triangle_up   )",
    "< (triangle_left )",
    "> (triangle_right)",
    "1 (tri_down      )",
    "2 (tri_up        )",
    "3 (tri_left      )",
    "4 (tri_right     )",
    "8 (octagon       )",
    "p (pentagon      )",
    "h (hexagon1      )",
    "H (hexagon2      )",
    "+ (plus          )",
    "d (thin_diamond  )",
    "| (vline         )",
    "_ (hline         )"]


class EvaluationMain(QtGui.QMainWindow):
    """
    Main class
    """
    def __init__(self):
        """
        Init
        """
        import ui_TestMainWindow

        QtGui.QMainWindow.__init__(self, None)

        self.setWindowTitle('Evaluation Main')
        self.ui = ui_TestMainWindow.Ui_MainWindow()
        self.ui.setupUi(self)

        # define event handler

        # Task 2
        self.connect(self.ui.pushButton_newPlot, QtCore.SIGNAL('clicked()'),
                     self.do_create_plot)

        # Task 3
        self.connect(self.ui.pushButton_setTitle, QtCore.SIGNAL('clicked()'),
                     self.do_set_x_title)
        for marker in MplLineMarkers:
            self.ui.comboBox_lineSymbol.addItem(marker)

        # Task 6
        self.connect(self.ui.pushButton_addCurve, QtCore.SIGNAL('clicked()'),
                     self.do_add_curve)
        self.connect(self.ui.pushButton_setLineMarker, QtCore.SIGNAL('clicked()'),
                     self.do_set_marker)

        # Class variables
        self._plotWindowDict = dict()
        self._activePlotWindowName = None
        self.plot_counter = 0

        return

    def do_add_curve(self):
        """

        Returns:

        """
        # create curve
        curve_type = str(self.ui.comboBox_functionList.currentText())
        if curve_type == 'Gaussian':
            function_index = 3
        elif curve_type == 'Sin':
            function_index = 0
        elif curve_type == 'Cosine':
            function_index = 4
        else:
            raise RuntimeError('Unsupported function %s' % curve_type)

        vec_x, vec_y = function_generator.function_generator(function_index, 0, 0.5, 10.)
        title = str(self.ui.lineEdit_title.text())

        # plot
        self._plotWindowDict[self._activePlotWindowName].plot(vec_x, vec_y, title=title)
        self._update_line_id_list()

        return

    def do_create_plot(self):
        """
        Create a plot window
        Returns:

        """
        # plt_window = plot_window.PlotWindow()
        # plt_window.show()
        # self._plotWindowList.append(plot_window)

        sub_plot_name = 'plot%d' % self.plot_counter

        # create plot window and show
        self.__dict__['_plot%d' % self.plot_counter] = plot_window.PlotWindow(self, sub_plot_name)
        self.__dict__['_plot%d' % self.plot_counter].show()

        # record
        self._plotWindowDict[sub_plot_name] = self.__dict__['_plot%d' % self.plot_counter]

        # plot
        vec_x, vec_y = function_generator.function_generator(self.plot_counter, 0, 0.5, 10.)
        self.__dict__['_plot%d' % self.plot_counter].plot(vec_x, vec_y)
        self.__dict__['_plot%d' % self.plot_counter].setWindowTitle(sub_plot_name)

        # increase counter
        self.plot_counter += 1
        self._activePlotWindowName = sub_plot_name
        self.write_note(sub_plot_name, append=True)

        # modify combo
        self._update_line_id_list()

        return

    def _update_line_id_list(self):
        """

        Returns:

        """
        self.ui.comboBox_lines.clear()

        line_id_list = self._plotWindowDict[self._activePlotWindowName].get_line_ids()
        for line_id in line_id_list:
            print 'Type of Line ID: ', type(line_id)
            self.ui.comboBox_lines.addItem(str(line_id))

        return

    def do_set_marker(self):
        """
        Set line marker
        Returns:

        """
        # marker
        marker = str(self.ui.comboBox_lineSymbol.currentText())
        marker = marker.split('(')[0].strip()

        # line ID
        line_id = str(self.ui.comboBox_lines.currentText())

        #
        self._plotWindowDict[self._activePlotWindowName].set_line_marker(line_id, marker)

        return

    def do_set_x_title(self):
        """

        Returns:

        """
        x_label = str(self.ui.lineEdit_titleX.text()).strip()
        if len(x_label) == 0:
            return

        if self._activePlotWindowName is None:
            return

        window = self._plotWindowDict[self._activePlotWindowName]
        window.set_x_title(x_label)

        return

    def closeEvent(self, QCloseEvent):
        """

        Args:
            QCloseEvent:

        Returns:

        """
        for window_name in self._plotWindowDict:
            print 'Close window: ', window_name
            self._plotWindowDict[window_name].close()

        self.close()

        return

    def delete_note(self, note, partial):
        """

        Args:
            note:
            partial:

        Returns:

        """
        orig_text = str(self.ui.label_plotOnTop.text())

        if partial:
            if orig_text.count(note) > 0:
                orig_text = orig_text.replace(note, '')
        else:
            orig_text = ''

        self.ui.label_plotOnTop.setText(orig_text)

        return

    def set_active_window(self, window_name):
        """

        Args:
            window_name:

        Returns:

        """
        self._activePlotWindowName = window_name

        self._update_line_id_list()

    def write_mouse_position(self, x, y):
        """

        Args:
            x:
            y:

        Returns:

        """
        self.ui.lineEdit_cursorX.setText(str(x))
        self.ui.lineEdit_cursorY.setText(str(y))

    def write_note(self, note, append):
        """

        Args:
            note:
            append:

        Returns:

        """
        if append:
            note = str(self.ui.label_plotOnTop.text()) + ' ' + note

        self.ui.label_plotOnTop.setText(note)

        return


def main_app():
    """ Main app
    """
    if QtGui.QApplication.instance():
        _app = QtGui.QApplication.instance()
    else:
        _app = QtGui.QApplication(sys.argv)
    return _app

# main entry
app = main_app()

reducer = EvaluationMain()  # the main ui class in this file is called MainWindow
reducer.show()

app.exec_()
