#include"C_header.h"
#include<stdio.h>

struct st{
    char c;
    struct st* next;
};

int is_need_calc(char * text){
    int res = 0;
    for (int i = 0; i < (int)strlen(text); i++){
        if ((text[i]>96&& text[i]<123)||is_operation_or_func(text[i]))
            res = 1;
    }
    return res;
}

int is_x_in(char * text){
    return strchr(text,'x')!=NULL ? 1:0;
}

char* change_x_str (char * all_str, char* x_eq_num){
    char* result_str = (char*)calloc(256,sizeof(char));
    int j = 0;
    for(int i = 0; i < (int)strlen(all_str);i++){
        if (all_str[i]=='x'){
            for (int k = 0; k < (int)strlen(x_eq_num);k++) result_str[j++] = x_eq_num[k];
        }
        else result_str[j++] = all_str[i];
    }
    return result_str;
}

void Calculation (char *text){
    if (!all_ok(text)){
        strcpy(text,"EROR, incorect braces");
    }
    else{
        change_view(text);
        rev_polish_notation(text);
        count_result(text);
    }
}

void change_view(char *text){
    char leter = '\0';
    int i = 0;
    while (text[i]!='\0'){
        if (text[i]>96&& text[i]<123){
            leter = get_leter(text[i],text[i+1]);
            shift_all(leter,i, text);
        }
        if (text[i]=='-'&&text[i-1]=='(') text[i]='u';
        i++;
    }
    for (;i<(int)strlen(text);i++){
        text[i]='\0';
    }
}

void shift_all(char leter, int i, char* text){
    int k = i;
    text[k] = leter;
    k++;
    while (text[k]>96&& text[k]<123) k++;
    int count_shift = k-i;
    for(k=i+1; k<=(int)strlen(text)-count_shift;k++){
        text[k] = text[k+count_shift-1];
    }
    text[k++]='\0';
}

char get_leter(char first, char second){
    char res = '\0';
    switch (first) {
    case 'a':
        if(second=='c')
            res = 'C';
        else if (second=='s')        //  asin = S, sin = s
            res='S';                 //  acos = C, cos = c
        else res = 'T';              //  atan = T, tan = t
        break;                       //  sqrt = q, mod = m
    case 'c':                        //  ln = l, log = L
        res = 'c';
        break;
    case 's':
        if (second=='i')
            res = 's';
        else res = 'q';
        break;
    case 't':
        res = 't';
        break;
    case 'l':
        if (second == 'n')
            res = 'l';
        else res = 'L';
        break;
    case 'm':
        res = 'm';
        break;
    default:
        break;
    }
    return res;
}

int all_ok(char * text){
    int res = 0;
    int open_brace = 0;
    int close_brace = 0;
    int flag_eror_open_first = 0;
    for (int i = 0; i <(int) strlen(text);i++){
        if (text[i]=='('){
            if(close_brace>open_brace)
                flag_eror_open_first = 1;
            open_brace++;
        }
        if (text[i]==')')
            close_brace++;
    }
    if ((open_brace == close_brace) && flag_eror_open_first == 0)
        res = 1;
    return res;
}

void rev_polish_notation(char * text){
    struct st* operation = NULL;
    char *output = (char*)calloc(strlen(text),sizeof(char));
    int k = 0, point = 0;
    while(text[k]!='\0'){

        // Скобки

        if (text[k] == '(') operation = push(operation, '(');

        //Закрывающаяся скобка

        if (text[k]==')'){
            if ((operation->c)!='('){
                while(operation!=NULL && (operation->c)!='('){
                    output[point++] = del(&operation);
                    printf("%c\n",output[point]);
                    output[point++] = ' ';
                }
            }
            if ((operation!=NULL)&&(operation->c=='('))
                del(&operation);
        }

        // Цифры
        if ((text[k]>='0'&&text[k]<='9') || text[k]=='.'){
            while ((text[k]>='0'&&text[k]<='9') || text[k]=='.') {
                output[point++] = text[k];
                k++;
            }
            k--;
            output[point++] = ' ';
        }


        // Операции
        if(is_operation_or_func(text[k])){
            if (operation == NULL) operation = push(operation, text[k]);
            else {
                if (prior(operation->c) < prior(text[k])){
                    operation = push (operation, text[k]);
                }
                else {
                    while ((operation!= NULL)&& (prior(operation->c)>=prior(text[k]))) {
                        output[point++] = del(&operation);
                        output[point++] = ' ';
                    }
                    operation = push(operation,text[k]);
                }
            }

        }



        k++;
    }
    while (operation != NULL) {
        output[point++] = del(&operation);
        output[point++] = ' ';
    }
    output[point] = '\0';
    text[0]='\0';
    strcpy(text,output);
    free(output);
}

int is_operation_or_func(char leter){
    int res = 0;
    if (leter == '+'|| leter =='-'||leter =='*'||leter =='/'||leter =='^'||leter =='s'
      ||leter =='S'||leter =='c'||leter =='C'||leter =='t'||leter =='T'||leter =='l'
      ||leter =='L'||leter =='m'||leter =='q'||leter=='u') res = 1;
    return res;
}

struct st* push (struct st* head, char a){
    struct st* ptr;
    if ((ptr = (struct st*)malloc(sizeof(struct st)))==NULL){
        exit(-1);
    }
    ptr->c = a;
    ptr->next = head;
    return ptr;
}

char del(struct st ** head){
    struct st * ptr;
    char a = '\0';
    if (*head == NULL) return '\0';
    ptr = * head;
    a = ptr->c;
    *head = ptr -> next;
    free(ptr);
    return a;
}

int prior(char a){
    int res = 0;
    if (a =='s'||a=='S'||a=='c'||a=='C'||a=='t'||a=='T'||a=='l'||a =='L'||a =='m'||a =='q')
        res = 4;
    else if (a == 'u') res = 5;
    else {
        switch(a){
        case '^':
            res = 3;
            break;
        case '*':
            res = 2;
            break;
        case '/':
            res = 2;
            break;
        case '-':
            res = 1;
            break;
        case '+':
            res = 1;
            break;
        }
    }
    return res;
}

struct st_num{
    double num;
    struct st_num* next;
};


void count_result(char * text){
    double result = 0;
    struct st_num* stack_num = NULL;
    int eror = 0;
    for(int i = 0;i< (int)strlen(text);i++){
        if(text[i]>='0' && text[i] <= '9'){
            char* number = (char*)calloc(40, sizeof(char));
            int count = 0;
            while((text[i]>='0' && text[i] <= '9')||text[i]=='.'){
                number[count++] = text[i++];
                if (i== (int)strlen(text)) break;
            }
            double buf = atof(number);
            stack_num = push_num(stack_num,buf);
            free(number);
            i--;
        }
        else if (text[i]!=' '){
            double a = 0;
            double b = 0;
            if (stack_num!=NULL) a = del_num(&stack_num);
            if (stack_num!=NULL && is_need_add_value(text[i])) b = del_num(&stack_num);
            switch(text[i]){
            case '+':
                result = b+a;
                break;
            case '-':
                result = b-a;
                break;
            case '/':
                if (a == 0) eror = 1;
                else result = b/a;
                break;
            case '*':
                result = b*a;
                break;
            case '^':
                result = pow(b,a);
                break;
            case 's':
                result = sin(a);
                break;
            case 'S':
                if (a < -1 || a>1) eror = 4;
                else result = asin(a);
                break;
            case 't':
                result = tan(a);
                break;
            case 'T':
                result = atan(a);
                break;
            case 'c':
                result = cos(a);
                break;
            case 'C':
                if (a < -1 || a>1) eror = 4;
                else result = acos(a);
                break;
            case 'q':
                if (a < 0) eror = 2;
                else result = sqrt(a);
                break;
            case 'm':
                result = fmod(b,a);
                break;
            case 'l':
                if (a < 0) eror = 3;
                else result = log(a);
                break;
            case 'L':
                if (a < 0) eror = 3;
                else result = log10(a);
                break;
            case 'u':
                result = -1 * a;
                break;
            }
            stack_num = push_num(stack_num,result);
        }
        if (eror != 0) break;
    }
    text[0]='\0';
    if (eror == 0) sprintf(text,"%lf",result);
    else {
        switch (eror) {
        case 1:
            sprintf(text,"Div by zero");
            break;
        case 2:
            sprintf(text,"Sqrt(x), x < 0");
            break;
        case 3:
            sprintf(text,"Ln(x), x < 0");
        case 4:
            sprintf(text,"Asin(x)/Acos(x), x < -1 or x > 1");
            break;
        default:
            break;
        }
    }
}

int is_need_add_value(char c){
    int res = 0;
    if (c == '+'||c == '-'||c == '/'||c == '*'||c == '^'||c=='m') res = 1;
    return res;
}

struct st_num * push_num (struct st_num* head, double a){
    struct st_num* ptr;
    if ((ptr = (struct st_num*)malloc(sizeof(struct st_num)))==NULL){
        exit(-1);
    }
    ptr->num = a;
    ptr->next = head;
    return ptr;
}

double del_num(struct st_num ** head){
    struct st_num * ptr;
    double a = 0;
    ptr = * head;
    a = ptr->num;
    *head = ptr -> next;
    free(ptr);
    return a;
}
