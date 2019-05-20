#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARGC_ERROR 1
#define TOOMANYFILES_ERROR 2
#define CONFLICTING_OUTPUT_OPTIONS 3

#define MAXSTRINGS 1024
#define MAXPARAS 4096

#define HASHLEN 200

#include "para.h"
#include "util.h"
#ifndef HEADER_H
#define HEADER_H
#include "options.h"
#endif

void version(void);
void todo_list(void);
void setop(struct options* op, int n);
void loadfiles(const char* filename1, const char* filename2, struct options op);
void print_option(const char* name, int value);
void diff_output_conflict_error(void);
void setoption(const char* arg, const char* s, const char* t, int n, struct options* op);
void showoptions(const char* file1, const char* file2, struct options op);
void init_options_files(int argc, const char* argv[], struct options* op);
void showidentical(para* p, para* q, struct options op);
void sidebyside(para* p, para* q, struct options op);
void showunified(para* p, para* q, struct options op);
void showcontext(para* p, para* q, struct options op);
void shownormal(para* p, para* q, struct options op);
