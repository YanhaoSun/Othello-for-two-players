//
// Created by yanhao sun on 16/04/2021.
//
#include <stdio.h>
#include <string.h>
#include "function.h"

#define fra 18
#define MAX 10
#define space 9

struct name{
    char player1[MAX];
    char player2[MAX];
};

typedef struct score{
    int score1;
    int score2;
}score;

typedef struct boa{
    char frame_row[1][3];
    char frame_column[9];
    int sequence;
    char alpha[8];
}boa;

boa board[fra];
struct name players;
score number;

char dis[9][9];
char pass[4];
int i, j, onlytest;

//for horizontal
int detect_answer_from_right_to_left;
int change_piece_from_right_to_left;
int detect_answer_from_left_to_right;
int change_piece_from_left_to_right;

//for vertical
int detect_answer_from_bot_to_top;
int change_piece_from_bot_to_top;
int detect_answer_from_top_to_bot;
int change_piece_from_top_to_bot;

//for diagonal
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
int count=1;
int initia_count=1;
char dis[space][space];
char alp[8]="abcdefgh";
char alpp[8]="abcdefgh";

void dis_board(void)
{
    number.score1=0;
    number.score2=0;
    for(int m=0; m<8; m++)//if the value in the square is 'B' then number.score1 plus
    {                     //if the value in the square is 'W' then number.score2 plus
        for(int n=0; n<8; n++)
        {
            if(dis[m][n]=='B')
            {
                number.score1++;
            }
            if(dis[m][n]=='W')
            {
                number.score2++;
            }
        }
    }
    //printing out the score of two players
    printf("  Score: %s (Black) %d:%d %s (White)\n", players.player1, number.score1, number.score2, players.player2);
    count=1;
    //i=0 stands for the first row of '---', the number '1' and the first row of '|',
    //i=1 stands for the second row of '---', the number '2' and the second row of '|'
    //i=8 stands for the last row of '---' and alphabets 'a' to 'h'
    for(i=0; i<9; i++)
    {
        //j stands for columns in each row
        for(j=0; j<8; j++)
        {
            if(j==0)//when j=0 we need to print blank space before '---'
            {
                strcpy(board[i].frame_row[j], "   ");
                printf("%s ", board[i].frame_row[j]);
            }
            //when j!=0, we just print '---'
            strcpy(board[i].frame_row[j], "---");
            printf("%s ", board[i].frame_row[j]);
        }
        printf("\n");
        if(i==8)//when i=8, we need to print alphabets from 'a' to 'h'
        {
            for(j=0; j<8; j++)
            {
                if(j==0)//because there is blank space before 'a', so when j==0, we need printf("     %c", board[i].alpha[j]);
                {
                    board[i].alpha[j]=alpp[j];
                    printf("     %c", board[i].alpha[j]);
                }
                else
                {
                    board[i].alpha[j]=alpp[j];
                    printf("   %c", board[i].alpha[j]);
                }
            }
        }
        if(i!=8)//when i!=8, we need to print numbers(count stands for count) before '|', and then print '|'
        {
            printf("%d ", count);
            for (j = 0; j < 9; j++)
            {
                board[i].frame_column[j] = '|';
                printf(" %c ", board[i].frame_column[j]);//printing out '|'
                if(j<8)
                {
                    printf("%c", dis[i][j]);//disks are stored in the array called 'dis', and every time the user enters disks from keyboard, the value will
                                            //be stored in array 'dis'
                }
            }
            count++;
        }
        printf("\n");
    }
}
void initialise_board(void)
{
    number.score1=2;
    number.score2=2;
    int q=0, w=0;
    printf("$ othello\n        *** Welcome to Othello! ***\n\n");
    printf("Enter name of Player 1 (Black): ");
    scanf("%s", players.player1);
    printf("\n");
    printf("Enter name of Player 2 (White): ");
    scanf("%s", players.player2);
    printf("\n");
    printf("                   Score: %s (Black) %d:%d %s (White)\n", players.player1, number.score1, number.score2, players.player2);
    for(i=0; i<17; i++)//the board has 18 rows if '---', '|', alphabets and numbers are counted, so I loop from 0 to 17
    {
        if(i%2==0)//all '---' are in the even row, so i diveds 2, if mod 0, so this row should prints '---'
        {
            for(j=0; j<8; j++)//when i is an even number, loop j from 0 to 7
            {
                if(j==0)//j is equal to 0, printing first '---' by using structure.
                {
                    strcpy(board[i].frame_row[j], "---");
                    printf("                       %s", board[i].frame_row[j]);
                }
                else//j is bigger than 0, printing other '---' by using structure.
                {
                    strcpy(board[i].frame_row[j], "---");
                    printf(" %s", board[i].frame_row[j]);
                }
            }
            printf("\n");
        }
        else//all numbers, '|' and alphabets(at the bottom of the board) are in the odd row
        {
            for(j=0; j<10; j++)//when i is an odd number, loop j from 0 to 7
            {
                board[i].frame_column[j]='|';
                if(j==0)//j is equal to 0, printing first '|'  by using structure.
                {
                    board[i].sequence=initia_count;
                    printf("                   %d  ", board[i].sequence);
                    initia_count++;//initia_count stores the numbers on the very left hand side of the board.
                }

                else if(j!=9)
                {
                    //initia_count-1==4 means the 4th row of the board
                    if(initia_count-1==4)//because initia_count is always 1 more than the numbers on the left hand side of the board, so I initia_count always minus 1.
                    {
                        if(j==4)//j==4 means the 4th column in the board(the number at the beginning of the row is the 1st column)
                        {
                            dis[q][w]='W';//assign white disk to this space
                            printf("%c %c ", board[i].frame_column[j], dis[q][w]);// and print it out
                            w++;//w plus 1 means moving to next space
                        }
                        else if(j==5)//j==5 means the 5th column in the board(the number at the beginning of the row is the 1st column)
                        {
                            dis[q][w]='B';//assign black disk to this space
                            printf("%c %c ", board[i].frame_column[j], dis[q][w]);// and print it out
                            w++;//w plus 1 means moving to next space
                        }
                        else//when initia_count-1==4(4th row of board), j!=4 && j!=5, blank space will be stored to the dis array
                        {
                            dis[q][w]=' ';
                            printf("%c %c ", board[i].frame_column[j], dis[q][w]);
                            w++;
                        }
                    }
                    //initia_count-1==5 means the 5th row of the board
                    else if(initia_count-1==5)//because initia_count is always 1 more than the numbers on the left hand side of the board, so I initia_count always minus 1.
                    {
                        if(j==4)//j==4 means the 4th column in the board(the number at the beginning of the row is the 1st column)
                        {
                            dis[q][w]='B';//assign black disk to this space
                            printf("%c %c ", board[i].frame_column[j], dis[q][w]);// and print it out
                            w++;//w plus 1 means moving to next space
                        }
                        else if(j==5)//j==5 means the 5th column in the board(the number at the beginning of the row is the 1st column)
                        {
                            dis[q][w]='W';//assign white disk to this space
                            printf("%c %c ", board[i].frame_column[j], dis[q][w]);// and print it out
                            w++;//w plus 1 means moving to next space
                        }
                        else//when initia_count-1==5(5th row of board), j!=4 && j!=5, blank space will be stored to the dis array
                        {
                            dis[q][w]=' ';
                            printf("%c %c ", board[i].frame_column[j], dis[q][w]);
                            w++;
                        }
                    }
                    else if(initia_count-1!=4 && initia_count-1!=5)//Except for lines four and five, black space will be allocated to all disks.
                    {
                        dis[q][w]=' ';
                        printf("%c %c ", board[i].frame_column[j], dis[q][w]);
                        w++;
                    }
                }
                else//if j==9, '|' will be printed out
                {
                    printf("%c", board[i].frame_column[j]);
                }
            }
            q++;
            w=0;
            printf("\n");
        }
        if(i==16)//if i==16, alphabets 'a to h' will be printed out.
        {
            for(j=0; j<8; j++)
            {
                if(j==0)//j==0 means the first column of the last row.
                {
                    board[i].alpha[j]=alp[j];//assign every alphabet to board[i].aplha[j] and print it out.
                    printf("                        %c", board[i].alpha[j]);
                }
                else//other columns of the board
                {
                    board[i].alpha[j]=alp[j];
                    printf("   %c", board[i].alpha[j]);
                }
            }
        }
    }

    for(int m=0; m<8; m++)//I assign value for each element in the array.
    {
        for(int n=0; n<8; n++)
        {
            if(m==3)//m==3 stands for the 4th row in the board
            {
                if(n==3)//n==3 stands for the 4th column in the board, and assign 'W'
                {
                    dis[m][n]='W';
                }
                else if(n==4)//n==4 stands for the 5th column in the board, and assign 'B'
                {
                    dis[m][n]='B';
                }
            }
            else if(m==4)//m==4 stands for the 5th row in the board
            {
                if(n==3)//n==3 stands for the 4th column in the board, and assign 'B'
                {
                    dis[m][n]='B';
                }
                else if(n==4)//n==4 stands for the 5th column in the board, and assign 'W'
                {
                    dis[m][n]='W';
                }
            }
            else//assign blank space except the 4th column, 5th column in the 4th row and 4th column, 5th column in the 5th row.
            {
                dis[m][n]=' ';
            }

        }
    }

}
