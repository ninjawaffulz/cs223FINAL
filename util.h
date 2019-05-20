//
//  util.h
//  diff
//
//  Created by William McCarthy on 5/9/19.
//  Copyright © 2019 William McCarthy. All rights reserved.
//

#ifndef util_h
#define util_h

#include <stdio.h>
#ifndef HEADER_H
#define HEADER_H
#include "options.h"
#endif
#define BUFLEN 256
char* diff_last_modified(const char* filename);
char* yesorno(int condition);
FILE* openfile(const char* filename, const char* openflags);

void diff(const char* left, const char* right, struct options op);
void printleft(const char* left, struct options op);
void printright(const char* right, struct options op);
void printboth(const char* left, const char* right, struct options op);

void printline(void);

#endif /* util_h */
