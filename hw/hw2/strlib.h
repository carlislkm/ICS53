#ifndef STR_LIB_H
#define STR_LIB_H
#include <stdlib.h>
#include <stdio.h>
//#include <string.h>

extern void *ics53_memchr(const void *str, int c, size_t n);
extern int ics53_memcmp(const void *str1, const void *str2, size_t n);
extern void *ics53_memcpy(void *dest, const void *src, size_t n);
extern void *ics53_memmove(void *dest, const void *src, size_t n);
extern void *ics53_memset(void *str, int c, size_t n);
extern char *ics53_strcat(char *dest, const char *src);
extern char *ics53_strncat(char *dest, const char *src, size_t n);
extern char *ics53_strchr(const char *str, int c);
extern int ics53_strcmp(const char *str1, const char *str2);
extern int ics53_strncmp(const char *str1, const char *str2, size_t n);
extern int ics53_strcoll(const char *str1, const char *str2);
extern char *ics53_strcpy(char *dest, const char *src);
extern char *ics53_strncpy(char *dest, const char *src, size_t n);
extern size_t ics53_strcspn(const char *str1, const char *str2);
extern char *ics53_strerror(int errnum);
extern size_t ics53_strlen(const char *str);
extern char *ics53_strpbrk(const char *str1, const char *str2);
extern char *ics53_strrchr(const char *str, int c);
extern size_t ics53_strspn(const char *str1, const char *str2);
extern char *ics53_strstr(const char *haystack, const char *needle);
extern char *ics53_strtok(char *str, const char *delim);
extern size_t ics53_strxfrm(char *dest, const char *src, size_t n);

#endif
