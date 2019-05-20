//
//  util.c
//  diff
//
//  Created by William McCarthy on 5/9/19.
//  Copyright © 2019 William McCarthy. All rights reserved.
//

#include <string.h>
#include <stdlib.h>
#include "util.h"

#define BUFLEN 256
#include <sys/stat.h>
#include <time.h>
#define STAT_ERROR  5



char* diff_last_modified(const char* filename) {
  static char diff_formatted_lastmod[BUFLEN];
  char tmzone[10];
  struct stat sb;
  if (lstat(filename, &sb) == -1) {
    fprintf(stderr, "Could not read stat information from file: '%s'", filename);
    exit(STAT_ERROR);
  }
  memset(diff_formatted_lastmod, 0, sizeof(diff_formatted_lastmod));
  struct tm* ti = localtime(&sb.st_mtime);;                     // years start at 1900,  months zero-indexed
  struct tm* gmtimeinfo = gmtime(&sb.st_mtime);
  int gmt = gmtimeinfo->tm_hour;
  if (gmt < 12) { gmt += 24; }    // prevent wrap-around error  (e.g., gmt is 0400, but local time is 2100)
  snprintf(tmzone, sizeof(timezone), "%03d00", (ti->tm_hour - gmt));
  snprintf(diff_formatted_lastmod, sizeof(diff_formatted_lastmod), "%4d-%02d-%02d %02d:%02d:%012.9f %s",
           ti->tm_year + 1900, ti->tm_mon + 1, ti->tm_mday,
           ti->tm_hour, ti->tm_min, (float)ti->tm_sec, tmzone);
  return diff_formatted_lastmod;
}

char* yesorno(int condition) { return condition == 0 ? "no" : "YES"; }

FILE* openfile(const char* filename, const char* openflags) {
  FILE* f;
  if ((f = fopen(filename, openflags)) == NULL) {  printf("can't open '%s'\n", filename);  exit(1); }
  return f;
}

void printline(void) {
  for (int i = 0; i < 10; ++i) { printf("=========="); }
  printf("\n");
}


void printleft(const char* left, struct options op) {
  char buf[BUFLEN];
  if(op.options[9]){
    printf("%s %s", "<" , left);
  }
  else{
    strcpy(buf, left);
    int j = 0, len = (int)strlen(buf) - 1;
    for (j = 0; j <= 48 - len ; ++j) { buf[len + j] = ' '; }//second condition is the offset of the arrow
    buf[len + j++] = '<';
    buf[len + j++] = '\0';
    printf("%s\n", buf);
  }
}

void printright(const char* right, struct options op) {
  if (right == NULL) { return; }
  if(op.options[9]){
    printf("%s %s", ">", right);
  }
  else{
    printf("%50s %s", ">", right);
  }
}
void diff(const char* left, const char* right, struct options op){
  if( strcmp(left,right) != 0){
    printf("< %s---\n> %s", left, right);
  }
}
void printboth(const char* left, const char* right, struct options op) {
  char mark = ' ';
  char buf[BUFLEN];
  char bufright[BUFLEN];
  //processing left side
  size_t len = strlen(left);
  if( strcmp(left,right) != 0){mark = '|';}
  if (len>0){strncpy(buf,left,len);}
  buf[len-1] = '\0';
  //processing right side
  size_t lenright = strlen(right);
  if(lenright > 0){strncpy(bufright,right,lenright);}
  bufright[lenright - 1] = '\0';
  //options
  if(op.options[5] && mark != '|'){
    bufright[0] = '\0';
    mark = '(';
  }
  if(op.options[8] == 0|| mark == '|'){
    printf("%-49s%c %s\n",buf,mark,bufright);
  }
}
