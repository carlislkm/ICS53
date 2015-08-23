//Kevin Carlisle
//ICS 53
//Homework #1
// 01/16/2015

/*

Write an ANSI C program, called MusicLibrary, that allows the user to manage their music collection.  Each MusicLibrary has a name specified as an argument to the command line.  If none is given, use the default name of myMusic.  When the program is run, the named MusicLibrary is loaded from the file (name of file matches name of MusicLibrary) into memory.  If the file does not exist, the in-memory MusicLibrary will be empty.  When the program is exited, the MusicLibrary is saved back to the file from which it came.

A MusicLibrary is a list of songs - each of which has a title, artist, and year published.  Note we may add more fields in the future, but for now, just store those three values.  Songs are retrieved or deleted by using their title.

Your main program will be a loop that prints a prompt “myMuisc Command: “ where myMusic will be the name of the current MusicLibrary.  Each command is a single letter and either upper or lower case letters are treated the same.  Any invalid command character is skipped and ignored.
Implement the following additional commands:

I - insert a new song, prompt for title, artist, and year published, maintain the list in ascending alphabetical order by song title, ignore letter case when doing comparisons, but retain letter case in all stored information
P - print out all the entries in this MusicLibrary
D - delete a specified song, prompt for the title of the song to be deleted, delete all matching songs
L - lookup the song for a specified title, prompt for the title to look-up, use binary search which only works on sorted list.
Q - save the current MusicLibrary to its file and exit (quit) the program.



*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define A_SIZE 10


struct song_struct
{
    char title[50];
    char artist[50];
    char year[50];
};
typedef struct song_struct song;


int SIZE = 0;
char S[2] = ";";
char T[2] = ";\n";
char NAME[50];
song ML[A_SIZE];

char* add_song_title(char* token, int i)
{
     strcpy(ML[i+1].title, token);
     return strtok(NULL, T);

}
char* add_song_artist(char* token, int i)
{
     strcpy(ML[i+1].artist, token);
     return strtok(NULL, T);

}
char* add_song_year(char* token, int i)
{
     strcpy(ML[i+1].year, token);
     return strtok(NULL, T);

}
void add_song_helper(char* token, int i)
{
    token = add_song_title(token,i);
    token = add_song_artist(token,i);
    token = add_song_year(token,i);
}
void add_song_to_ML(char* token)
{
    int i;
     for(i = SIZE-1;strcmp(token,ML[i].title) < 0 && i>=0; i-- )
     {
         ML[i+1] = ML[i];
     }
     add_song_helper(token, i);
}
void insert_song_helper(song temp, int i)
{
    strcpy(ML[i].title,temp.title);
    strcpy(ML[i].artist,temp.artist);
    strcpy(ML[i].year,temp.year);
}
void insert_song_to_ML(song temp)
{
    int i;
    for(i = SIZE-1;strcasecmp(temp.title,ML[i].title) < 0 && i>=0; i-- ){ML[i+1] = ML[i];}
    insert_song_helper(temp, i+1);
}
void delete_and_shift(int i)
{
    int j;
    for (j = i; j < SIZE; ++j)
    {
        ML[j] = ML[j+1];
    }
    SIZE--;
}
void remove_song_from_ML(char* title)
{
//SEE DELETE_CMD
}
char* read_string(char* title)
{
    static char userInput[50];
    printf("%s: ",title);
    fgets(userInput, 50, stdin);
    strcpy(userInput, strtok(userInput, "\n"));
    return userInput;

}
//BINARY SEARCH IS EXTRA LENGTH
int binary_search(char* s_title, int low, int hi)
{
  while (low <= hi)
  {
    int mid = low + (hi-low)/2 ;
    if (strcasecmp(ML[mid].title,s_title) == 0) return mid;
    (strcasecmp(ML[mid].title, s_title) < 0) ? (low = mid + 1) : (hi = mid - 1);
  }
  return -1;
}
void read_song(FILE* file)
{
    char str[250];
    int i = 0;

    for (i = 0; fgets(str, 250, file) != NULL; ++i,++SIZE)
    {
        add_song_to_ML(strtok(str, S));
    }
}
void print_console()
{
    int j = 0;
    while (j < SIZE)
    {
        printf("%d Title: %s, Artist: %s, Year Published: %s\n", j+1, ML[j].title, ML[j].artist, ML[j].year);
        j++;
    }
}

void print_MusicLibrary(int key)
{
    if(key == 0){print_console();};
}
void print_lookup_song(int i)
{
    printf("Title: %s, Artist: %s, Year Published: %s\n", ML[i].title, ML[i].artist, ML[i].year);
}
char read_command_helper(char command)
{
    command = getchar();
    getchar();
    return command;
}
char read_command(char* prompt,char* title )
{
    char command = '\0';
    printf("\n%s %s",title,prompt);
    return read_command_helper(command);

}
song insert_cmd_helper()
{
    song temp;
    strcpy(temp.title,read_string("Title"));
    strcpy(temp.artist,read_string("Artist"));
    strcpy(temp.year,read_string("Year"));
    return temp;
}
void insert_cmd()
{
    insert_song_to_ML(insert_cmd_helper());
    SIZE = SIZE + 1;
}
void delete_cmd()
{
    char* temp = read_string("Title");
    int i = binary_search(temp,0,SIZE-1);
    while(i != -1)
    {
        delete_and_shift(i);
        i = binary_search(temp,0,SIZE-1);
    }
}
void lookup_cmd()
{
    char* temp = read_string("Title");
    int i = binary_search(temp,0,SIZE-1);
    if(i != -1)
    {
        print_lookup_song(i);
    }

}
FILE* open_file(char* name, char* mode)
{
    if (strcmp(mode, "r") == 0 || strcmp(mode, "w") == 0)
    {
        FILE* file = fopen(name, mode);
        return file;
    }
    return NULL;
}
void store_MusicLibrary(FILE* wFile)
{
    int i;
    for (i = 0; i < SIZE; ++i){fprintf(wFile, "%s;%s;%s\n", ML[i].title, ML[i].artist, ML[i].year);}

}
void write_song()
{
    strcat(NAME, ".txt");
    FILE* wFile = open_file(NAME,"w");
    store_MusicLibrary(wFile);
    fclose(wFile);

}

void setup_helper_2(char* temp)
{
    FILE* file = open_file(temp, "r");

    if (file != NULL)
        {
            read_song(file);
            fclose(file);
        }
}
char* setup_helper_1(char* argv)
{
    static char temp[50];
    strcpy(temp, argv);
    strcpy(NAME, argv);
    strcat(temp, ".txt");

    return temp;
}
void handle_setup(char* argv)
{
    if (argv != NULL)
    {
        char* temp = setup_helper_1(argv);
        setup_helper_2(temp);
        return;
    }
    strcpy(NAME, "myMusic");
}
int evaluate_command(char command)
{
            command = toupper(command);
            switch(command)
            {
                case 'I':
                    insert_cmd();
                    break;
                case 'P':
                    print_MusicLibrary(0);
                    break;
                case 'D':
                    delete_cmd();
                    break;
                case 'L':
                    lookup_cmd();
                    break;
                case 'Q':
                    write_song();
                    return 0;
                    break;
                default:
                    printf("Command Not Recognized\n");
                    break;
            }
            return 1;
}
void handle_loop()
{
    int loop_c = 1;

    while(loop_c)
    {
        loop_c = evaluate_command(read_command("Command: ",NAME));
    }
}

int main(int argc, char* argv[])
{
    handle_setup(argv[1]);
    handle_loop();
    
    return 0;
}
