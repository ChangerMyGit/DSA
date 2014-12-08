#ifndef _STRING_H
#define _STRING_H
// 字符串匹配
int matchString(char * p , char * t);
// 蛮力匹配法
int matchString2(char * p , char * t);
// 构造next表
int * buildNext(char * p);
// kmp 匹配
int kmpMatch(char * p , char * t);
#endif