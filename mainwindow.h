#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionSave_triggered();
    void on_actionOpen_triggered();
    void on_actionAdd_triggered();
    void on_actionDel_triggered();
    void on_actionEdit_triggered();
    void on_actionRateRailStations_triggered();
    void on_actionShowTrip_triggered();
    void on_actionShowByRoute_triggered();
    void on_actionShow_triggered();

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
