//Kevin Carlisle
//82682616


//------------------------------------------------
//  COMPILE AND RUN INSTRUCTIONS
//
//  COMPILED USING -std=c99
//
//  #include<assert.h>
//
//-------------------------------------------------


#include <stdio.h>
#include <stdlib.h>
#include "strlib.h"
#include <assert.h>

//#include <string.h>

int test_memchr()
{
    const char str[] = "http://www.tutorialspoint.com";
    const char ch = '.';
    //char *ret = ics53_memchr(str, ch, ics53_strlen(str));
    char *ret = ics53_memchr(str, ch, 30);

    return ret == str + 10;
}
int test_memcmp()
{
    assert(ics53_memcmp("aaab","aaaa",4) == 1);
    assert(ics53_memcmp("aaaa","aaaa",4) == 0);
    assert(ics53_memcmp("aaaa","aaab",4) == -1);
    int ret;
    ret = ics53_memcmp("aaab","aaaa",4);

    return ret;
}
int test_memcpy()
{
   const char src[50] = "http://www.tutorialspoint.com";
   char dest[50] = "SOME RANDOM TEXT";

   printf("Before memcpy dest = %s\n", dest);
   ics53_memcpy(dest, src, 29);
   printf("After memcpy dest = %s\n", dest);


   return 1;

}
int test_memmove()
{
    char str1[]= "abcde";
    //char str2[] = "ABCDE";
    int l;
    l = ics53_strlen(str1);
    printf("LEN: %d\n",l);

    printf("1: %s  2: %s\n", str1, str1);
    printf("Memmove: %s\n", ics53_memmove(str1+2, str1, ics53_strlen(str1)));
    printf("1: %s  2: %s\n", str1, str1);
    //printf("Memmove: %s\n", ics53_memmove(str1+4, str1, 4));

    //return ics53_memmove();
    return 1;

}
int test_memset(){
    char str[50];
    ics53_memset(str, '$', 7);
    int i;
    for (i = 0; i < 7; i++)
    {
        if (str[i] != '$')
            return 0;

    }

    return 1;
}
int test_strcat()
{
    char src[50], dest[50];
    ics53_strcpy(src,  "src");
    ics53_strcpy(dest,  "dest");
    ics53_strcat(dest, src);
    char res[] = "destsrc";
    int i;
    for (i = 0; res[i]; i++)
        if (res[i] != dest[i])
            return 0;

    return 1;
}
int test_strncat()
{

    char src[50], dest[50];
    ics53_strncpy(src,  "src",3);
    ics53_strncpy(dest,  "dest",4);
    ics53_strcat(dest, src);
    char res[] = "destsrc";
    int i;
    for (i = 0; res[i]; i++)
        if (res[i] != dest[i])
            return 0;
    printf("%s = %s-\n", res, dest);
    return 1;
}
int test_strchr()
{
    char test[50];
    ics53_strcpy(test, "test");
    printf("test -> e : %s\n", ics53_strchr(test, 'e'));
    return 1;

}
int test_strcmp()
{
    char test1[50];
    char test2[50];
    char test3[50];
    ics53_strcpy(test1, "test");
    ics53_strcpy(test2, "test");
    ics53_strcpy(test3, "test2");
    printf("%s = %s -> %d\n", test1, test2, ics53_strcmp(test1, test2));
    printf("%s = %s -> %d\n", test1, test3, ics53_strcmp(test1, test3));
    printf("%s = %s -> %d\n", test3, test1, ics53_strcmp(test3, test1));
    return 1;

}

int test_strncmp()
{
    char test1[50];
    char test2[50];
    char test3[50];
    ics53_strcpy(test1, "test");
    ics53_strcpy(test2, "test");
    ics53_strcpy(test3, "test2");
    printf("%s = %s -> %d\n", test1, test2, ics53_strncmp(test1, test2,5));
    printf("%s = %s -> %d\n", test1, test3, ics53_strncmp(test1, test3,5));
    printf("%s = %s -> %d\n", test3, test1, ics53_strncmp(test3, test1,5));
    printf("%s = %s -> %d\n", test3, test1, ics53_strncmp(test3, test1,2));

    return 1;

}
int test_strcoll()
{
    char test1[50];
    char test2[50];
    char test3[50];
    ics53_strcpy(test1, "test");
    ics53_strcpy(test2, "test");
    ics53_strcpy(test3, "test2");
    printf("%s = %s -> %d\n", test1, test2, ics53_strcoll(test1, test2));
    printf("%s = %s -> %d\n", test1, test3, ics53_strcoll(test1, test3));
    printf("%s = %s -> %d\n", test3, test1, ics53_strcoll(test3, test1));
    return 1;

}
int test_strcpy()
{
    char test1[50];
    char test2[50];
    char test3[50];
    ics53_strcpy(test1, "test");
    ics53_strcpy(test2, "hello");
    ics53_strcpy(test3, "abc");
    printf("test = %s \n", test1);
    printf("hello = %s \n", test2);
    printf("abc = %s \n", test3);

    return 1;

}
int test_strncpy()
{
    char test1[50];
    char test2[50];
    char test3[50];
    ics53_strncpy(test1, "ab",5);
    ics53_strncpy(test2, "bbbbbbb",2);
    ics53_strncpy(test3, "ccccccc",3);
    printf("test1: %s-  | test2: %s-\n", test1, test1);
    for(int i = 0; i < 5; i++)
    {
        printf("Char[%d]: *%c*\n",i,test1[i]);
    }
    printf("%s = %s -> %d\n", test1, test2, ics53_strncmp(test1, test2,4));
    printf("%s = %s -> %d\n", test1, test3, ics53_strncmp(test1, test3,5));
    printf("%s = %s -> %d\n", test3, test1, ics53_strncmp(test3, test1,5));
    printf("%s = %s -> %d\n", test3, test1, ics53_strncmp(test3, test1,2));

    return 1;

}
int test_strcspn()
{
    char test1[50];
    char test2[50];
    char test3[50];
    ics53_strcpy(test1, "test");
    ics53_strcpy(test2, "abcd");
    ics53_strcpy(test3, "xxdx");
    printf("%s = %s -> %d\n", test1, test2, ics53_strcspn(test1, test2));
    printf("%s = %s -> %d\n", test2, test3, ics53_strcspn(test2, test3));
    printf("%s = %s -> %d\n", test3, test2, ics53_strcspn(test3, test2));
    return 1;

}
int test_strlen()
{
    char test1[50];
    char test2[50];
    char test3[50];
    ics53_strcpy(test1, "test");
    ics53_strcpy(test2, "hello");
    ics53_strcpy(test3, "abc");
    printf("test = %i \n", ics53_strlen(test1));
    printf("hello = %i \n", ics53_strlen(test2));
    printf("abc = %i \n", ics53_strlen(test3));

    return 1;

}
int test_strpbrk()
{
    char test1[50];
    char test2[50];
    char test3[50];
    ics53_strcpy(test1, "test");
    ics53_strcpy(test2, "abcd");
    ics53_strcpy(test3, "xxdx");
    printf("%s = %s -> %s\n", test1, test2, ics53_strpbrk(test1, test2));
    printf("%s = %s -> %s\n", test2, test3, ics53_strpbrk(test2, test3));
    printf("%s = %s -> %s\n", test3, test2, ics53_strpbrk(test3, test2));
    return 1;

}
int test_strrchr()
{
    char test1[50];
    char test2[50];
    char test3[50];
    ics53_strcpy(test1, "abcdef");
    ics53_strcpy(test2, "test2");
    ics53_strcpy(test3, "test3");
    printf("%s -> %s\n", test1, ics53_strrchr(test1, 'a'));
    printf("%s -> %s\n", test2, ics53_strrchr(test2, 's'));
    printf("%s -> %s\n", test3, ics53_strrchr(test3, 'x'));
    return 1;

}
int test_strspn()
{
    char test1[50];
    char test2[50];
    char test3[50];
    ics53_strcpy(test1, "testqq");
    ics53_strcpy(test2, "tesq");
    ics53_strcpy(test3, "qqxx");
    printf("%s = %s -> %d\n", test1, test2, ics53_strspn(test1, test2));
    printf("%s = %s -> %d\n", test2, test1, ics53_strspn(test2, test1));
    printf("%s = %s -> %d\n", test3, test2, ics53_strspn(test3, test2));
    return 1;

}
int test_strstr()
{
    char test1[50];
    char test2[50];
    char test3[50];
    ics53_strcpy(test1, "xxxabcyyy");
    ics53_strcpy(test2, "");
    ics53_strcpy(test3, "abc");

    printf("%s = %s -> %s\n", test1, test2, ics53_strstr(test1, test3));

    printf("%s = %s -> %s\n", test2, test1, ics53_strstr(test2, test1));

    printf("%s = %s -> %s\n", test3, test2, ics53_strstr(test3, test2));
    return 1;

}
int test_strxfrm()
{
    char test1[50];
    char test2[50];
    char test3[50];
    ics53_strxfrm(test1, "ab",5);
    ics53_strxfrm(test2, "bbbbbbb",2);
    ics53_strxfrm(test3, "ccccccc",3);
    printf("test1: %s-  | test2: %s-\n", test1, test1);
    for(int i = 0; i < 5; i++)
    {
        printf("Char[%d]: *%c*\n",i,test1[i]);
    }
    printf("%s = %s -> %d\n", test1, test2, ics53_strncmp(test1, test2,4));
    printf("%s = %s -> %d\n", test1, test3, ics53_strncmp(test1, test3,5));
    printf("%s = %s -> %d\n", test3, test1, ics53_strncmp(test3, test1,5));
    printf("%s = %s -> %d\n", test3, test1, ics53_strncmp(test3, test1,2));

    return 1;

}




int main()
{
    printf("\nmemchr: %d\n\n",test_memchr());
    printf("\n\nmemcmp: %d\n\n",test_memcmp());
    printf("\n\nmemcpy: %d\n\n",test_memcpy());
    printf("\n\nmemove: %d\n\n",test_memmove());
    printf("\n\nmemset: %d\n\n",test_memset());
    printf("\n\nsrtcat: %d\n\n",test_strcat());
    printf("\n\nsrtncat: %d\n\n",test_strncat());
    printf("\n\nstrchr: %d\n\n",test_strchr());
    printf("\n\nstrcmp: %d\n\n",test_strcmp());
    printf("\n\nstrncmp: %d\n\n",test_strncmp());
    printf("\n\nstrcoll: %d\n\n",test_strcoll());
    printf("\n\nstrcpy: %d\n\n",test_strcpy());
    printf("\n\nstrncpy: %d\n\n",test_strncpy());
    printf("\n\nstrcspn: %d\n\n",test_strcspn());
    printf("\n\nstrlen: %d\n\n",test_strlen());
    printf("\n\nstrpbrk: %d\n\n",test_strpbrk());
    printf("\n\nstrrchr: %d\n\n",test_strrchr());
    printf("\n\nstrspn: %d\n\n",test_strspn());
    printf("\n\nstrstr: %d\n\n",test_strstr());
    printf("\n\nstrxfrm: %d\n\n",test_strxfrm());







    return 0;
}
