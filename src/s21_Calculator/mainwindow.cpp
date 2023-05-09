#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "../C_header.h"
#include "../c_main.c"
bool is_operation(char leter);
char change_view(char leter);

bool dot = true;
char * res_show=(char*)calloc(300,sizeof(char));

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //digit
    connect(ui->p0,SIGNAL(clicked()),this,SLOT(digits_num_clicked()));
    connect(ui->p1,SIGNAL(clicked()),this,SLOT(digits_num_clicked()));
    connect(ui->p2,SIGNAL(clicked()),this,SLOT(digits_num_clicked()));
    connect(ui->p3,SIGNAL(clicked()),this,SLOT(digits_num_clicked()));
    connect(ui->p4,SIGNAL(clicked()),this,SLOT(digits_num_clicked()));
    connect(ui->p5,SIGNAL(clicked()),this,SLOT(digits_num_clicked()));
    connect(ui->p6,SIGNAL(clicked()),this,SLOT(digits_num_clicked()));
    connect(ui->p7,SIGNAL(clicked()),this,SLOT(digits_num_clicked()));
    connect(ui->p8,SIGNAL(clicked()),this,SLOT(digits_num_clicked()));
    connect(ui->p9,SIGNAL(clicked()),this,SLOT(digits_num_clicked()));
    //clear
    connect(ui->AC,SIGNAL(clicked()),this,SLOT(AC_clicked()));
    connect(ui->Clear,SIGNAL(clicked()),this,SLOT(Clear_clicked()));
    //brace
    connect(ui->Brace_open,SIGNAL(clicked()),this,SLOT(Brace_open_clicked()));
    connect(ui->Brace_close,SIGNAL(clicked()),this,SLOT(Brace_close_clicked()));
    //operation
    connect(ui->plus,SIGNAL(clicked()),this,SLOT(operation_clicked()));
    connect(ui->minus,SIGNAL(clicked()),this,SLOT(operation_clicked()));
    connect(ui->diverce,SIGNAL(clicked()),this,SLOT(operation_clicked()));
    connect(ui->multi,SIGNAL(clicked()),this,SLOT(operation_clicked()));
    connect(ui->stepen,SIGNAL(clicked()),this,SLOT(operation_clicked()));
    connect(ui->plus_minus,SIGNAL(clicked()),this,SLOT(unary_minus_clicked()));
    //dot
    connect(ui->dot,SIGNAL(clicked()),this,SLOT(dot_clicked()));
    //sin,cos,log and etc...
    connect(ui->sin,SIGNAL(clicked()),this,SLOT(many_leter_operation_clicked()));
    connect(ui->cos,SIGNAL(clicked()),this,SLOT(many_leter_operation_clicked()));
    connect(ui->tan,SIGNAL(clicked()),this,SLOT(many_leter_operation_clicked()));
    connect(ui->ln,SIGNAL(clicked()),this,SLOT(many_leter_operation_clicked()));
    connect(ui->log,SIGNAL(clicked()),this,SLOT(many_leter_operation_clicked()));
    connect(ui->asin,SIGNAL(clicked()),this,SLOT(many_leter_operation_clicked()));
    connect(ui->acos,SIGNAL(clicked()),this,SLOT(many_leter_operation_clicked()));
    connect(ui->atan,SIGNAL(clicked()),this,SLOT(many_leter_operation_clicked()));
    connect(ui->sqrt,SIGNAL(clicked()),this,SLOT(many_leter_operation_clicked()));
    connect(ui->mod,SIGNAL(clicked()),this,SLOT(many_leter_operation_clicked()));
    //x
    connect(ui->xprint,SIGNAL(clicked()),this,SLOT(x_clicked()));
    //
    connect(ui->graph,SIGNAL(clicked()),this,SLOT(graph_clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::graph_clicked(){
    QString res_in = ui->result_show->text();
    QByteArray ba = res_in.toLocal8Bit();
    char * char_in = ba.data();
    QString x_in_eq = ui->x_equation->text();
    QByteArray ba2 = res_in.toLocal8Bit();
    char * x_in = ba.data();
    if (is_x_in(char_in)){
        //realloc(res_show,strlen(char_in));
        strcpy(res_show,char_in);
    }
    else{
        //realloc(res_show,strlen(x_in));
        strcpy(res_show,x_in);
    }
    secwind =  new SecondWindow(this);
    secwind->show();
}


void MainWindow::x_clicked(){
    QString input = ui->x_equation->text();
    QString new_in;
    QString res_in = ui->result_show->text();
    QByteArray ba = res_in.toLocal8Bit();
    char * char_in = ba.data();
    if (input.isEmpty()){
        //if (!is_operation(char_in[strlen(char_in)-1]))
        //    new_in = ui->result_show->text()+'*';
        if (isdigit(char_in[strlen(char_in)-1])||char_in[strlen(char_in)-1]==')'){
            new_in = ui->result_show->text()+'*'+'x';
        }
        else new_in = ui->result_show->text()+'x';
    }
    else {
        if (!is_x_in(char_in))
            new_in = ui->result_show->text()+'x' + '=';
    }
    ui->result_show->setText(new_in);
}


void MainWindow::on_equal_clicked(){
    QString input = ui->result_show->text();
    std::string str = input.toStdString();
    char* cstr = new char[str.length() + 1];
    strcpy(cstr, str.c_str());
    QString check_eq = ui->x_equation->text();
    QByteArray ba = check_eq.toLocal8Bit();
    char * check_equation = ba.data();
    if (is_x_in(cstr)){
        if (check_eq.isEmpty()){
            ui->x_equation->setText(input);
            ui->result_show->clear();
        }
        else {
            int k =0;
            while (cstr[k+2]!='\0') {
                cstr[k]=cstr[k+2];
                k++;
            }
            cstr[k]='\0';
            cstr[k+1]='\0';
            if (is_need_calc(cstr))
                Calculation(cstr);
            char str[500]={0};
            strcpy(str,change_x_str(check_equation,cstr));
            Calculation(str);
            std::string res_str(str);
            QString label = QString::fromStdString(res_str);
            ui->result_show->setText(label);
            ui->x_equation->clear();
        }
    }
    else {
        Calculation(cstr);
        std::string res_str(cstr);
        QString label = QString::fromStdString(res_str);
        ui->result_show->setText(label);
    }
    delete[] cstr;
}

void MainWindow::digits_num_clicked(){
    QPushButton *button = (QPushButton *)sender();
    QString all_input = (ui->result_show->text());
    QByteArray ba = all_input.toLocal8Bit();
    char * input = ba.data();
    if (input[strlen(input)-1]==')'||input[strlen(input)-1]=='x'){
        all_input = (ui->result_show->text()+'*'+button->text());
        dot = true;
    }
    else {
        all_input = (ui->result_show->text()+button->text());
    }
    ui->result_show->setText(all_input);
}


void MainWindow::Clear_clicked(){
    ui->result_show->clear();
    dot = true;
}

void MainWindow::Brace_open_clicked(){
    QString all_input = (ui->result_show->text());
    QByteArray ba = all_input.toLocal8Bit();
    char * input = ba.data();
    //QString add = "*(";
    QString brace_in;
    if (isdigit(input[strlen(input)-1])){
        brace_in = ui->result_show->text()+'*'+'(';
    }
    else brace_in = ui->result_show->text()+'(';
    dot = true;
    ui->result_show->setText(brace_in);
}

void MainWindow::Brace_close_clicked(){
    QString brace_in = ui->result_show->text()+")";
    ui->result_show->setText(brace_in);
}


void MainWindow::AC_clicked(){
    QString all_input = (ui->result_show->text());
    QByteArray ba = all_input.toLocal8Bit();
    char * input = ba.data();
    if (strlen(input)>0){
        input[strlen(input)-1]='\0';
        QString new_in = QString::fromStdString(input);
        ui->result_show->setText(new_in);
    }
}

void MainWindow::operation_clicked(){
    QPushButton *button = (QPushButton *)sender();
    QString but_text = button->text();
    QByteArray text = but_text.toLocal8Bit();
    char *operation = text.data();
    char oper = operation[0];
    //oper =
    oper = change_view(oper);
    QString all_input = ui->result_show->text();
    QByteArray ba = all_input.toLocal8Bit();
    char * input = ba.data();
    if (input[0]!='\0'){
        if (is_operation(input[strlen(input)-1])){
            input[strlen(input)-1] = oper;
            QString new_in = QString::fromStdString(input);
            ui->result_show->setText(new_in);
            dot = true;
        }
        else if (input[strlen(input)-1]!='d'&&input[strlen(input)-1]!='('){
            QString new_in_2 = ui->result_show->text()+oper;
            ui->result_show->setText(new_in_2);
            dot = true;
        }
        else if (input[strlen(input)-1] == '('&&oper == '-'){
            //if (oper == '-'){
                QString new_in_2 = ui->result_show->text()+oper;
                ui->result_show->setText(new_in_2);
            //}
        }
        //else {
        //    QString new_in_2 = ui->result_show->text()+oper;
        //    ui->result_show->setText(new_in_2);
        //}
    }
    //dot = true;
}

char change_view(char leter){
    char res = '0';
    if (leter != '+' && leter != '-' && leter != '*' && leter != '^'){
        res = '/';
    }
    else res = leter;
    return res;
}

bool is_operation(char leter){
    bool result = false;
    if (leter == '+' || leter == '-' || leter == '/' || leter == '*' || leter == '^')
        result = true;
    return result;
}

void MainWindow::dot_clicked(){
    QString all_input = (ui->result_show->text());
    QByteArray ba = all_input.toLocal8Bit();
    char * input = ba.data();
    if (input[0]=='\0'){
        std::string zero_dot = "0.";
        QString new_in = QString::fromStdString(zero_dot);
        ui->result_show->setText(new_in);
        dot = false;
    }
    else {
        if (dot && isdigit(input[strlen(input)-1])){
            all_input = (ui->result_show->text())+'.';
            ui->result_show->setText(all_input);
            dot = false;
        }
    }
}


void MainWindow::many_leter_operation_clicked() {
    QPushButton *button = (QPushButton *)sender();
    QString but_text = button->text();
    //QByteArray text = but_text.toLocal8Bit();
    //char *m_l_operation = text.data();
    QString all_input = ui->result_show->text();
    QByteArray all_in_byte = all_input.toLocal8Bit();
    char *all_in_string = all_in_byte.data();
    if (!is_operation(all_in_string[strlen(all_in_string)-1])&&strlen(all_in_string)>0&&but_text!="mod"&&all_in_string[strlen(all_in_string)-1]!='(')
        all_input = all_input+'*'+but_text+'(';
    else if (but_text!="mod") all_input = all_input+but_text+'(';
    else {
        if (isdigit(all_in_string[strlen(all_in_string)-1]))
            all_input = all_input+but_text;
    }
    dot = true;
    ui->result_show->setText(all_input);
}

void MainWindow::unary_minus_clicked() {
    QString all_input = ui->result_show->text();
    QByteArray all_in_byte = all_input.toLocal8Bit();
    char *all_in_string = all_in_byte.data();
    int len = strlen(all_in_string) - 1;
    if (isdigit(all_in_string[len])){
        while (isdigit(all_in_string[len])||all_in_string[len]=='.') len--;
        len++;
        char first='\0';
        char sec='\0';
        char bufer = '\0';
        first = all_in_string[len];
        all_in_string[len] ='(';
        len++;
        sec = all_in_string[len];
        all_in_string[len] ='-';
        while(first !='\0'){
            len++;
            bufer = all_in_string[len];
            all_in_string[len] = first;
            first = sec;
            sec = bufer;
        }
        //len++;
        all_in_string[++len] = ')';
        QString new_in = QString::fromStdString(all_in_string);
        ui->result_show->setText(new_in);
    }
}
