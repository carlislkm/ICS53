//Kevin Carlisle
//82682616


//------------------------------------------------
//  COMPILE AND RUN INSTRUCTIONS
//
//  COMPILED USING -std=c99
//
//-------------------------------------------------

#include "strlib.h"
//#include <string.h>


//--------HELPER FUNCTIONS --------------------

char d_cp(const void* str)
{
    //RETURNS CHAR FROM VOID*
    return *(char*)str;
}
char ud_cp(const void* str)
{
    //RETURNS CHAR FROM VOID*
    return *(unsigned char*)str;
}
void reg_copy(char* d,const char* s, size_t n)
{
    for (int i = 0; i < n; d++, s++, i++)
    {
        *d = *s;
    }
}
void rev_copy(char* d,const char* s, size_t n)
{
    for(; n!= 0; n--,d--,s--)
    {
        *d = *s;
    }
}

//--------END OF HELPER FUNCTIONS--------------

// -------MAIN PROGRAM FUNCTIONS---------------

void *ics53_memchr(const void *str, int c, size_t n){

    for(int i = 0; i < n ; str++,i++)
    {
        if (*(char *)str == (char)c)
        {
            return (void*) str;
        }

    }
    return NULL;
}


int ics53_memcmp(const void *str1, const void *str2, size_t n){

    for (int i = 0; i < n; str1++,str2++,i++)
    {
        if(d_cp(str1) != d_cp(str2))
        {
            return (d_cp(str1) < d_cp(str2)) ? -1 : 1;
        }
    }
    return 0;
}

void *ics53_memcpy(void *dest, const void *src, size_t n){

    char* d = dest;
    const char* s = src;

    for (int i = 0; i < n; d++, s++, i++)
    {
        *d = *s;
    }
    return dest;

}

void *ics53_memmove(void *dst, const void *src, size_t n){

  char *d = dst;
  const char *s = src;

  (d <= s || s >= (d + n))?reg_copy(d,s,n):rev_copy(d+n-1,s+n-1,n);

  return dst;
}

void *ics53_memset(void *str, int c, size_t n){

    for (char* d = str; n != 0; n--,d++)
    {
        *d = (char)c;
    }
    return str;
}

char *ics53_strcat(char *dest, const char *src){

    char* p = dest;
    while (*p != '\0')
    {
        p++;
    }
    ics53_strcpy(p,src);

    return dest;
}

char *ics53_strncat(char *dest, const char *src, size_t n){

    char* p = dest;

    while (p != '\0'){p++;}
    for(;n != 0 && *src != '\0'; n--,p++,src++){*p = *src;}
    if (*p != '\0'){*p = '\0';}

    return dest;

}

char *ics53_strchr(const char *str, int c){

    while (*str != (char)c && *str != '\0')
    {
        str++;
    }
    return ((*str == (char) c)? (char*)str : NULL);
}

int ics53_strcmp(const char *str1, const char *str2){

    for(; *str1 == *str2 && *str1 != '\0';str1++, str2++){}

    return (!(ud_cp(str1) < ud_cp(str2)))?((ud_cp(str1) > ud_cp(str2))):(-1);

}

int ics53_strncmp(const char *str1, const char *str2, size_t n){

    if (n == 0 ){return 0;}

    for( ; n > 0 && *str1 == *str2; n--, str1++, str2++)
        {if (str1 == '\0' || n == 0){return 0;}}

    return (!(ud_cp(str1) < ud_cp(str2)))?((ud_cp(str1) > ud_cp(str2))):(-1);
}

int ics53_strcoll(const char *str1, const char *str2){

    //IGNORE COLLATING SEQUENCE
    return ics53_strcmp(str1, str2);
}

char *ics53_strcpy(char *dest, const char *src){

    for (char* p = dest; (*p = *src) != '\0'; p++, src++){}

    return dest;
}
//LONGER THAN 5 LINES
char *ics53_strncpy(char *dest, const char *src, size_t n){

    int flag = 0;
    char* p = dest;
    while (n--)
    {
        if (*src != '\0' && flag == 0){*p = *src;}
        else
        {
            *p = '\0';
            flag = 1;   
        }
        p++;
        src++;
    }
    *p = '\0';

    return dest;
}
size_t ics53_strcspn(const char *str1, const char *str2){

    const char* p;
    for (p = str1; *p != '\0'; p++)
    {
        if ( ics53_strchr(str2, *p) != NULL)
            {return (p-str1);}
    }
    return (p-str1);
}

char *ics53_strerror(int errnum){
    //Incomplete
    return NULL;
}

size_t ics53_strlen(const char *str){

    const char *p = str;
    while (*p != '\0'){p++;}

    return (size_t)(p - str);
}

char *ics53_strpbrk(const char *str1, const char *str2){

    const char* p;
    for (p = str1; *p != '\0'; p++)
    {
        if ( ics53_strchr(str2, *p) != NULL)
        {
            return (char*)p;
        }
    }
    return NULL;
}

char *ics53_strrchr(const char *str, int c){

    char* r = NULL;
    do{if (*str == c){r = (char*)str;}}while(*str++);
    return r;
}

size_t ics53_strspn(const char *str1, const char *str2){

    const char* p;
    for (p = str1; *p != '\0'; p++)
    {
        if ( ics53_strchr(str2, *p) == NULL)
        {
            return (p-str1);
        }
    }
    return (p-str1);

}
//FUNCTION IS OVER 5 LINE LIMIT
char *ics53_strstr(const char *haystack, const char *needle){

    if (*needle == '\0'){return (char*)haystack;}

    for ( ; *haystack != '\0'; haystack++)
    {
        const char* h;
        const char* n;

        for(h = haystack, n = needle; n != '\0' && *h==*n; h++, n++){}
        if (*n == '\0')
            {return (char*)haystack;}
    }
    return NULL;
}

char *ics53_strtok(char *str, const char *delim){
    //Incomplete
    return NULL;
}

size_t ics53_strxfrm(char *dest, const char *src, size_t n){

    return (size_t)ics53_strncpy(dest, src, n);
}
