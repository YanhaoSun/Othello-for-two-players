#include <stdio.h>
#include <time.h>
#include "function.h"

#define fra 18
#define MAX 10
#define space 9

//this is the structure for two players
struct name{
    char player1[MAX];
    char player2[MAX];
};
//this structure is used for keeping track of each player's score
typedef struct score{
    int score1;
    int score2;
}score;
//this structure is used for initialising the board.
typedef struct boa{
    char frame_row[1][3];
    char frame_column[9];
    int sequence;
    char alpha[8];
}boa;

boa board[fra];
struct name players;
score number;

char dis[9][9];//this string stores disks which are 'B' and 'W', this string has 9 columns and 9 rows, and the last row and last
               //column are empty, this row and this column will be used in horizontal, vertical and diagonal of the board.
char pass[4];
int i, j, onlytest;

//variables for horizontal
int detect_answer_from_right_to_left;
int change_piece_from_right_to_left;
int detect_answer_from_left_to_right;
int change_piece_from_left_to_right;

//variables for vertical
int detect_answer_from_bot_to_top;
int change_piece_from_bot_to_top;
int detect_answer_from_top_to_bot;
int change_piece_from_top_to_bot;

//variables for diagonal
int detect_answer_left_bot_top;
int change_piece_left_bot_topxxx;
int change_piece_left_bot_topyyy;
int detect_answer_left_top_bot;
int change_piece_left_top_botxxx;
int change_piece_left_top_botyyy;
int detect_answer_right_bot_top;
int change_piece_right_bot_topxxx;
int change_piece_right_bot_topyyy;
int detect_answer_right_top_bot;
int change_piece_right_top_botxxx;
int change_piece_right_top_botyyy;


int x_axis, y_axis;
char dis[space][space];

int main()
{
    FILE *fp;
    int time_start, time_end, duration_min, duration_sec;
    time_t tal_ptr;//declare a variable called tal_ptr, type is time_t
    struct tm *tmp_ptr = NULL;//declare a pointer, and the type is struct tm

    time(&tal_ptr);//obtain the current system time
    tmp_ptr = localtime(&tal_ptr);//obtain the current system time
    printf ("Game begins, the time is:%d.%d.%d   ", (1900+tmp_ptr->tm_year), (1+tmp_ptr->tm_mon), tmp_ptr->tm_mday);//printing out year
    printf("%d(hour):%d(min):%d(sec)\n", tmp_ptr->tm_hour, tmp_ptr->tm_min, tmp_ptr->tm_sec);//printing out current time
    time_start=tmp_ptr->tm_hour*3600+tmp_ptr->tm_min*60+tmp_ptr->tm_sec;//this is the time of game begins and transfer time from hours into seconds

    int return_player_black=1;
    int return_player_white=1;
    for(int e=0; e<9; e++)//assign blank space to the last row and the last column, the other square will be assigned value in the initialise_board() sub-function
    {
        dis[e][8]=' ';
        dis[8][e]=' ';
    }
    initialise_board();//initialise board
    printf("\n\n\n");
    //
    while(return_player_black>0 || return_player_white>0)//this while loop will be used to print board with different disks made by users.
    {
        //return_player_black==1 && return_player_white==1 means black and white all make a valid movement
        //return_player_black==-1 || return_player_white==-1 means one of the black and white makes a invalid movement
        //return_player_black==-1 && return_player_white==-1 means the board is full and game ends
        return_player_black=player_black();
        return_player_white=player_white();
        if(return_player_white<0 && return_player_black<0)
        {
            printf("      **********Game ends**********\n");
            break;
        }
    }
    //print out two players' name with their score.
    printf("Score for %s : %d  ******  Score for %s : %d\n", players.player1, number.score1, players.player2, number.score2);
    //and then compare their score to determine who is winner or they have the same score.
    if(number.score1>number.score2)
    {
        printf("********* The winner is %s, score is %d *********\n", players.player1, number.score1);
    }
    else if(number.score1<number.score2)
    {
        printf("********* The winner is %s, score is %d *********\n", players.player2, number.score2);
    }
    else
    {
        printf("This game that ends with the score even.\n");
    }

    time(&tal_ptr);//obtain the current system time again
    tmp_ptr = localtime(&tal_ptr);//obtain the current system time
    printf ("Game ends, the time is:%d.%d.%d   ", (1900+tmp_ptr->tm_year), (1+tmp_ptr->tm_mon), tmp_ptr->tm_mday);//printing out year
    printf("%d(hour):%d(min):%d(sec)\n", tmp_ptr->tm_hour, tmp_ptr->tm_min, tmp_ptr->tm_sec);//printing out current time
    time_end=tmp_ptr->tm_hour*3600+tmp_ptr->tm_min*60+tmp_ptr->tm_sec;//this is the time of game ends and transfer time from hours into seconds

    duration_min=(time_end-time_start)/60;//game duration in minutes
    duration_sec=(time_end-time_start)%60;//game duration in seconds
    printf("Game duration=%d(min):%d(sec)\n", duration_min, duration_sec);//printing out game duration

    //create and open one file to append Date, game duration and winner into the file called othello-results.txt.
    if((fp=fopen("/Users/doraemon/Desktop/software engine assign/assignment2/othello-results.txt", "w"))==NULL)
    {
        printf("No file found\n");
    }
    else
    {
        if(number.score1>number.score2)
        {
            fprintf(fp, "Date:%d.%d.%d %d:%d:%d.\nThe time of the game is %d(min):%d(sec).\nThe winner is %s, and score is %d.", (1900+tmp_ptr->tm_year), (1+tmp_ptr->tm_mon), tmp_ptr->tm_mday, tmp_ptr->tm_hour, tmp_ptr->tm_min, tmp_ptr->tm_sec, duration_min, duration_sec, players.player1, number.score1);
        }
        if(number.score1<number.score2)
        {
            fprintf(fp, "Date:%d.%d.%d %d:%d:%d.\nThe time of the game is %d(min):%d(sec).\nThe winner is %s, and score is %d.", (1900+tmp_ptr->tm_year), (1+tmp_ptr->tm_mon), tmp_ptr->tm_mday, tmp_ptr->tm_hour, tmp_ptr->tm_min, tmp_ptr->tm_sec, duration_min, duration_sec, players.player2, number.score2);
        }
        if(number.score1==number.score2)
        {
            fprintf(fp, "Date:%d.%d.%d %d:%d:%d.\nThe time of the game is %d(min):%d(sec).\nNo winner, and %s is tied with %s, and score is %d.", (1900+tmp_ptr->tm_year), (1+tmp_ptr->tm_mon), tmp_ptr->tm_mday, tmp_ptr->tm_hour, tmp_ptr->tm_min, tmp_ptr->tm_sec, duration_min, duration_sec, players.player1, players.player2, number.score2);
        }
    }
    printf("The result of the game has been appended to the file called 'othello-results.txt'.\n***GOOD BYE***");
    return 0;
}