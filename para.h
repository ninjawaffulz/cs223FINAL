//
//  para.h
//  diff
//
//  Created by William McCarthy on 5/9/19.
//  Copyright © 2019 William McCarthy. All rights reserved.
//

#ifndef para_h
#define para_h

#include <stdio.h>
#ifndef HEADER_H
#define HEADER_H
#include "options.h"
#endif

typedef struct para para;
struct para {
  char** base;
  int filesize;
  int start;
  int stop;
  char* firstline;   // DEBUG only
  char* secondline;
};

para* para_make(char* base[], int size, int start, int stop);
para* para_first(char* base[], int size);
para* para_next(para* p);
size_t para_filesize(para* p);
size_t para_size(para* p);
char** para_base(para* p);
char* para_info(para* p);
int   para_equal(para* p, para* q);
int   para_equalc(para* p, para* q);
void para_print(para* p, void (*fp)(const char*, struct options), struct options op);
void para_printinfo(para* p, para* q, struct options op);
void para_printboth(para* p, para* q, struct options op);
void para_printfile(char* base[], int count, void (*fp)(const char*, struct options), struct options op);


#endif /* para_h */
