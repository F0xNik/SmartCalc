#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "secondwindow.h"
#include "../C_header.h"
#include <qcustomplot.h>
#ifdef __cplusplus
extern "C"
{
#endif

#ifdef __cplusplus
}
#endif

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    SecondWindow *secwind;

private slots:
    void on_equal_clicked();

private slots:
    void digits_num_clicked();

private slots:
    void AC_clicked();
    void Clear_clicked();

private slots:
    void Brace_open_clicked();
    void Brace_close_clicked();

private slots:
    void operation_clicked();

private slots:
    void many_leter_operation_clicked();

private slots:
    void unary_minus_clicked();

private slots:
    void x_clicked();

private slots:
    void dot_clicked();

private slots:
    void graph_clicked();

};
#endif // MAINWINDOW_H
