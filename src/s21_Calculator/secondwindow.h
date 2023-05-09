#ifndef SECONDWINDOW_H
#define SECONDWINDOW_H

#include <qcustomplot.h>

#include <QDialog>

namespace Ui {
class SecondWindow;
}

class SecondWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SecondWindow(QWidget *parent = nullptr);
    ~SecondWindow();

private slots:
    void on_draw_graph_clicked();

    //void on_X_down_textChanged(const QString &arg1);

    //void on_X_up_textChanged(const QString &arg1);

private:
    Ui::SecondWindow *ui;
};

#endif // SECONDWINDOW_H
