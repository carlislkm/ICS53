//Kevin Carlisle
//82682616
//1/29/2015
//HW 3
//ICS 53

/*
Write a C program, called my_ls, that behaves like the Unix command ls -lR, e.g.,
$ ls -lR filelist
Use `readdir` and `stat` to write a C program, called my_ls, to implement a subset of 
long, recursive `ls`. Files must be listed one name per line but additionally indented 
by the nesting depth of the directory. If there are no arguments to my_ls, list the 
files in "." (dot) the current working directory. Otherwise, for each command-line 
argument N, do the following. If N is a directory, print the detailed info for the 
directory (same as you would for a plain file as below for myFile), then indent 4 
spaces and do recursive my_ls of each entry in N (i.e., like ls -lR, but you do not
 need to sort the files). If N is a file, print the following information for file N 
 in the format (like ls -l):

 mode  num_links  owner  group  size_in_bytes   modification_timedate   name




*/

#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <locale.h>
#include <langinfo.h>
#include <string.h>


int listdir(const char *name, int level);

void printStat_lR(struct stat fileStat,const char* name)
{
    struct passwd  *pwd;
    struct group   *grp;
    struct tm      *tm;
    char            datestring[256];

    //Permissions
    printf( (S_ISDIR(fileStat.st_mode)) ? "d" : "-");
    printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
    printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
    printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXOTH) ? "x" : "-");

    //Links
    printf(" %d",fileStat.st_nlink);
    // OWNER
    if ((pwd = getpwuid(fileStat.st_uid)) != NULL)
        printf(" %s", pwd->pw_name);
    else
        printf(" %d", fileStat.st_uid);
    //GROUP
    if ((grp = getgrgid(fileStat.st_gid)) != NULL)
        printf(" %s", grp->gr_name);
    else
        printf(" %d", fileStat.st_gid);
    //Size
    printf(" %5jd", fileStat.st_size);
    //TIME
    tm = localtime(&fileStat.st_mtime);
    /* Get localized date string. */
    strftime(datestring, sizeof(datestring), nl_langinfo(D_T_FMT), tm);
    printf(" %s %s\n", datestring, name);
}

int processDir(DIR* dir, struct dirent* entry, struct stat currStat,const char* name, int level)
{
    int localSize = 0;
    do 
    { 
        char path[512];
        int len = snprintf(path, sizeof(path)-1, "%s/%s", name, entry->d_name);
        path[len] = 0;
        stat(path, &currStat);
        
        if (entry->d_type == DT_DIR) 
        {
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0){continue;}
            
            //DIRECTORY
            printf("%*s", level*4, "");
            printStat_lR(currStat, entry->d_name);
            localSize = localSize + listdir(path, level + 1);
        }
        else 
            { 
                //FILE
                printf("%*s", level*4, "");
                printStat_lR(currStat, entry->d_name);
                localSize = localSize + 1;
            }       
    } 
    while (entry = readdir(dir));
    return localSize;
}

int listdir(const char *name, int level)
{
    DIR *dir;
    struct dirent *entry;
    struct stat currStat;
    int size = 0;

    if (!(dir = opendir(name))) { return; }
    if (!(entry = readdir(dir))) { return; }
    
    size = size + processDir(dir, entry, currStat, name, level);
    closedir(dir);
    return size;
}
int call_listdir(char* path)
{
    if (path == NULL)
    {
        printf("DIR:  . \n");
        return listdir(".",0);
    }
    else
    {
        printf("DIR: %s\n", path);
        return listdir(path,0);
        
    }
}
int main(int argc, char* argv[])
{
    printf("\n");
    call_listdir(argv[1]);   
    return 0;
}