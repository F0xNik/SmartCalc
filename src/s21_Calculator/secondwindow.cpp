#include "secondwindow.h"
#include "ui_secondwindow.h"
#include "mainwindow.h"

extern char * res_show;
//int x_minimum = 0;
//int x_maximum = 0;

int is_digit_only(char * str){
    int res = 1;
    for(int i = 0;i< (int)strlen(str);i++){
        if (!isdigit(str[i])&&str[i]!='.')
            res = 0;
    }
    return res;
}

SecondWindow::SecondWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SecondWindow)
{
    ui->setupUi(this);
    ui->name_graph->setText(res_show);
}

SecondWindow::~SecondWindow()
{
    delete ui;
}

void SecondWindow::on_draw_graph_clicked()
{
    //Qstring name_graph = ui->name_graph->text();
    //name_graph =

    //double x_min = 10;//x_minimum;
    //double x_max = 10;//x_maximum;
    double x_min = ui->X_down->value();
    double x_max = ui->X_up->value();
    int Count_dot = 1000;
    if ((x_min+x_max)!=0){
    double step = (x_min+x_max)/Count_dot;
    x_min = -1 * x_min;
    ui->widget->clearPlottables();
    double xBegin = x_min;
    double xEnd = x_max;
    ui->widget->xAxis->setRange(x_min,x_max);
    ui->widget->yAxis->setRange(-5,5);
    char str_res[255] = {0};
    strcpy(str_res, res_show);
    //char temp[255] = {0};
    QVector<double> x, y;
    for (double X = xBegin; X < xEnd; X +=step){
//        char* x_num = (char*)calloc(100,sizeof(char));
//        if (X<0) sprintf(x_num,"(%lf)",X);
//        else sprintf(x_num,"%lf",X);
//        char *str_copy=(char*)calloc(256,sizeof(char));
//        strcpy(str_copy,str);
//        change_x_str(str_copy,x_num);
//        //change_x_str(str, x_num);



//        x.push_back(X);
//        Calculation(str_copy);
//        y.push_back(atof(str_copy));
//        free(x_num);
//        free(str_copy);



                x.push_back(X);
                char* x_num = (char*)calloc(100,sizeof(char));
                if (X<0) sprintf(x_num,"(%lf)",X);
                else sprintf(x_num,"%lf",X);
                //printf("%s\n",x_num);
                char *str=(char*)calloc(256,sizeof(char));
                strcpy(str,str_res);
                //printf("%s\n",str);
                strcpy(str,change_x_str(str,x_num));
                //printf("%s\n",str);
                //if (!is_digit_only(str))
                    //printf("%s\n",str);
                    Calculation(str);
                    //printf("%s\n",str);
                //else
                    y.push_back(atof(str));//y[i] = atof(str);
                //X+=step;
                //if (X >= x_max) break;
                free(x_num);
                free(str);





    }
    ui->widget->addGraph();
    ui->widget->graph(0)->addData(x,y);

    double minY = y[0], maxY = y[0];
    for (int i = 1; i < Count_dot; i++) {
      if (y[i] < minY) minY = y[i];
      if (y[i] > maxY) maxY = y[i];
    }
    ui->widget->yAxis->setRange(minY, maxY);
    ui->widget->replot();

    //ui->widget->replot();
    x.clear();
    y.clear();
    }
}




//    double x_min = 100;//x_minimum;
//    double x_max = 100;//x_maximum;
//    int Count_dot = 1000;
//    if ((x_min+x_max)!=0){
//    ui->widget->clearPlottables();
//    double step = (x_min+x_max)/Count_dot;
//    x_min = -1 * x_min;
//    QVector<double> x,y;//(Count_dot), y(Count_dot);
//    int i = 0;
//    char* Func=(char*)calloc(300,sizeof(char));
//    strcpy(Func,res_show);
//    double X = x_min;
//    while(i!=Count_dot){
//        x.push_back(X);
//        char* x_num = (char*)calloc(100,sizeof(char));
//        if (X<0) sprintf(x_num,"(%lf)",X);
//        else sprintf(x_num,"%lf",X);
//        char *str=(char*)calloc(256,sizeof(char));
//        strcpy(str,change_x_str(Func,x_num));
//        if (!is_digit_only(str))
//            Calculation(str);
//        if (str[0]>='A'&&str[0]<='Z') y[i]=0;
//        //if (is_digit_only(str))
//        else y.push_back(atof(str));//y[i] = atof(str);
//        //else y[i] = 0;
//        i++;
//        X+=step;
//        if (X >= x_max) break;
//        free(x_num);
//        free(str);
//    }
//    free(Func);

//    //ui->widget->clearPlottables();
//    ui->widget->addGraph();
//    ui->widget->graph(0)->addData(x,y);
//    ui->widget->xAxis->setLabel("X");
//    ui->widget->yAxis->setLabel("Y");
//    ui->widget->xAxis->setRange(x_min, x_max);
//    double minY = y[0], maxY = y[0];
//    for (int i = 1; i < Count_dot; i++) {
//      if (y[i] < minY) minY = y[i];
//      if (y[i] > maxY) maxY = y[i];
//    }
//    //printf("y max - %lf\n",maxY);
//    ui->widget->yAxis->setRange(minY, maxY);
//    ui->widget->replot();
    //}
//}

//void SecondWindow::on_X_down_textChanged(const QString &arg1)
//{
//    QByteArray ba = arg1.toLocal8Bit();
//    char * x_min = ba.data();
//    x_minimum = atof(x_min);
//}


//void SecondWindow::on_X_up_textChanged(const QString &arg1)
//{
//    QByteArray ba = arg1.toLocal8Bit();
//    char * x_max = ba.data();
//    x_maximum = atof(x_max);
//}

