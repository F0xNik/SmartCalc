#ifndef C_HEADER_H
#define C_HEADER_H

#include<string.h>
#include<stdlib.h>
#include<math.h>

void Calculation(char *text);
int all_ok(char * text);
void rev_polish_notation(char * text);

//spisok

struct st* push(struct st*, char);
char del(struct st**);
int prior(char);
void change_view(char *text);
char get_leter(char fisrt, char second);
void shift_all(char leter, int i, char* text);
int is_operation_or_func(char leter);
void count_result(char * text);
struct st_num * push_num (struct st_num* head, double a);
double del_num(struct st_num ** head);
int is_need_add_value(char c);
int is_x_in(char * text);
char* change_x_str (char * all_str, char* x_eq_num);
int is_need_calc(char * text);

#endif // C_HEADER_H
