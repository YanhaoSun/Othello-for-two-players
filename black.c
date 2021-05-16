//
// Created by yanhao sun on 15/05/2021.
//
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
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
bool test1=false;
bool test2=false;
bool test3=false;

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

int player_black(void)
{
    int scan, count_board_space=0;
    int return_horizontal_black;
    int return_vertical_black;
    int return_diagonal_left_black;
    int return_diagonal_right_black;
    int valid_black=0;
    char compare[]="pass";
    char coordinates[2];
    test1=false;
    test2=false;
    test3=false;
    onlytest=0;
    //this for loop is used to detect every squares to see if there are valid squares in the board
    for(int o=0; o<8; o++)
    {
        for(int p=0; p<8; p++)
        {
            y_axis=o;
            x_axis=p;
            return_horizontal_black=horizontal_black();//firstly, detect horizontal, if return_horizontal_black=1 then there are valid movements in horizontal,
                                                       //if return_horizontal_black=0, then there are no valid movements in horizontal
            return_vertical_black=vertical_black();//secondly, detect vertical, if return_vertical_black=1 then there are valid movements in vertical,
                                                   //if return_vertical_black=0, then there are no valid movements in vertical
            return_diagonal_left_black=diagonal_black_left();//thirdly, detect left diagonal, if return_diagonal_left_black=1 then there are valid movements in left diagonal,
                                                             // if return_diagonal_left_black=0, then there are no valid movements in left diagonal
            return_diagonal_right_black=diagonal_black_right();//forth, detect right diagonal, if return_diagonal_right_black=1 then there are valid movements in right diagonal,
                                                               // if return_diagonal_right_black=0, then there are no valid movements in right diagonal

            //if one of them above is not zero then there are valid movements and valid_black plus one
            if(return_horizontal_black!=0 || return_vertical_black!=0 || return_diagonal_left_black!=0 || return_diagonal_right_black!=0)
            {
                valid_black++;
            }
        }
    }
    onlytest=1;

    if(valid_black==0)//valid_black==0, this means no valid movements in these four direction
    {
        //this for loop is used to detect if the board is full
        for(int z=0; z<8; z++)
        {
            for(int x=0; x<8; x++)
            {
                if(dis[z][x]==' ')//if square has black space, then count_board_space will plus one
                {
                    count_board_space++;
                }
            }
        }
        //if count_board_space==0 then there are no valid movements in the board and return -1
        if(count_board_space==0)
        {
            return -1;
        }
        //if count_board_space!=0 then there are valid movements in the board
        else
        {
            //this user has to enter 'pass' to continue the game
            printf("%s(Black), you don not have any squares to make a valid move, please enter 'pass' for pass:\n",
                   players.player1);
            again:
            scanf("%s", pass);
            scan = strcmp(pass, compare);
            if (scan == 0)//if the user enter 'pass' correctly then return -1
            {
                return -1;
            }
            //if the user does not enter 'pass' then the program will ask the user to enter again
            else
                {
                printf("You must input 'pass', please enter again.\n");
                goto again;
            }
        }
    }
    again_black:
    printf("%s(Black), please enter the coordinates of the pieces you want to place in this form: 1d\n", players.player1);//user enters the coordinates of the pieces
    again_input_black:
    scanf("%s", coordinates);
    if((coordinates[0]<='0' || coordinates[0]>='9') && (coordinates[1]<='a' || coordinates[1]>='h'))//if the coordinates that user input is outside the board, user must enter again
    {
        printf("Invalid Input, please enter again in this form: 1d\n");
        goto again_input_black;
    }
    //transfer character into integer
    y_axis=coordinates[0]-49;
    x_axis=coordinates[1]-97;
    return_horizontal_black=horizontal_black();//detect horizontal first
    if(return_horizontal_black==1)
    {
        test1=true;
    }
    return_vertical_black=vertical_black();//detect vertical second
    if(return_vertical_black==1)
    {
        test2=true;
    }
    return_diagonal_left_black=diagonal_black_left();//detect left diagonal
    if(return_diagonal_left_black==1)
    {
        test3=true;
    }
    return_diagonal_right_black=diagonal_black_right();//detect right diagonal
    //if four directions are invalid, then print 'Invalid Move'
    if(return_horizontal_black==0 && return_vertical_black==0 && return_diagonal_left_black==0 && return_diagonal_right_black==0)
    {
        printf("Invalid Move.\n");
        goto again_black;
    }
    //else return 1
    else if(return_horizontal_black==1 || return_vertical_black==1 || return_diagonal_left_black==1 || return_diagonal_right_black==1)
    {
        dis_board();
        return 1;
    }
    return 0;
}

//horizontal_black, firstly, we begin with horizontal
int horizontal_black(void)
{
    if(x_axis<=7 && x_axis>=0 && y_axis<=7 && y_axis>=0)//detect if the square is outside the boundaries of the board
    {
        if(dis[y_axis][x_axis]==' ')//detect if this square is occupied
        {
            if(dis[y_axis][x_axis-1]=='W' || dis[y_axis][x_axis+1]=='W')// does it have a disc of the same colour as the one being placed
            {
                //if on the left hand side of the board is 'W' and on the right hand side of the board is blank or 'B' or outside of the board
                //then I only consider the left half of the board
                if(dis[y_axis][x_axis-1]=='W' && (dis[y_axis][x_axis+1]==' ' || dis[y_axis][x_axis+1]=='B' || x_axis+1>7))
                {
                    //I will detect from right to left to see if there is a valid square to make a movement
                    detect_answer_from_right_to_left=detect_from_right_to_left_black(x_axis);
                    if(detect_answer_from_right_to_left>0)//detect_answer_from_right_to_left>0 means we have found a valid movement
                    {
                        if(onlytest==1)//onlytest==1, this means the program is not detecting every squares to see if there are valid squares in the board
                        {
                            //this for loop is used to change all white disks into black disks
                            for(int m=change_piece_from_right_to_left; m<=x_axis; m++)
                            {
                                dis[y_axis][m]='B';
                            }
                        }
                        return 1;//once disks is changed from white into black, the sub-function horizontal_black will return 1
                                 //When onlytest==0, we can return 1, because if program executes here, it has proved that there are valid movements in horizontal
                    }
                    else//detect_answer_from_right_to_left<0, this means no valid movements in horizontal
                    {
                        return 0;
                    }
                }
                    //if on the right hand side of the board is 'W' and on the left hand side of the board is blank or 'B' or outside of the board
                    //then I only consider the right half of the board
                else if(dis[y_axis][x_axis+1]=='W' && (dis[y_axis][x_axis-1]==' ' || dis[y_axis][x_axis-1]=='B' || x_axis-1<0))
                {
                    //I will detect from left to right to see if there is a valid square to make a movement
                    detect_answer_from_left_to_right=detect_from_left_to_right_black(x_axis);
                    if(detect_answer_from_left_to_right>0)//detect_answer_from_left_to_right>0 means we have found a valid movement
                    {
                        if(onlytest==1)//onlytest==1, this means the program is not detecting every squares to see if there are valid squares in the board
                        {
                            //this for loop is used to change all white disks into black disks
                            for(int m=x_axis; m<=change_piece_from_left_to_right; m++)
                            {
                                dis[y_axis][m]='B';
                            }
                        }
                        return 1;//once disks is changed from white into black, the sub-function horizontal_black will return 1
                        //When onlytest==0, we can return 1, because if program executes here, it has proved that there are valid movements in horizontal
                    }
                    else//detect_answer_from_right_to_left<0, this means no valid movements in horizontal
                    {
                        return 0;
                    }
                }
                //if both sides of this square has 'W'
                else
                {
                    //I will detect from left to right and right to left to see if there is a valid square to make a movement
                    detect_answer_from_right_to_left=detect_from_right_to_left_black(x_axis);
                    detect_answer_from_left_to_right=detect_from_left_to_right_black(x_axis);
                    //detect_answer_from_right_to_left>0 && detect_answer_from_left_to_right>0 means we have found a valid movement on both sides
                    if(detect_answer_from_right_to_left>0 && detect_answer_from_left_to_right>0)
                    {
                        if(onlytest==1)//onlytest==1, this means the program is not detecting every squares to see if there are valid squares in the board
                        {
                            //this for loop is used to change all white disks into black disks
                            for(int m=change_piece_from_right_to_left; m<=change_piece_from_left_to_right; m++)
                            {
                                dis[y_axis][m]='B';
                            }
                        }
                        return 1;//once disks is changed from white into black, the sub-function horizontal_black will return 1
                        //When onlytest==0, we can return 1, because if program executes here, it has proved that there are valid movements in horizontal
                    }
                    //detect_answer_from_right_to_left>0 && detect_answer_from_left_to_right<0 means we have found a valid movement on left half of this row
                    if(detect_answer_from_right_to_left>0 && detect_answer_from_left_to_right<0)
                    {
                        if(onlytest==1)//onlytest==1, this means the program is not detecting every squares to see if there are valid squares in the board
                        {
                            //this for loop is used to change all white disks into black disks
                            for(int m=change_piece_from_right_to_left; m<=x_axis; m++)
                            {
                                dis[y_axis][m]='B';
                            }
                        }
                        //once disks is changed from white into black, the sub-function horizontal_black will return 1
                        //When onlytest==0, we can return 1, because if program executes here, it has proved that there are valid movements in horizontal
                        return 1;
                    }
                    //detect_answer_from_right_to_left<0 && detect_answer_from_left_to_right>0 means we have found a valid movement on right half of this row
                    if(detect_answer_from_right_to_left<0 && detect_answer_from_left_to_right>0)
                    {
                        if(onlytest==1)//onlytest==1, this means the program is not detecting every squares to see if there are valid squares in the board
                        {
                            //this for loop is used to change all white disks into black disks
                            for(int m=x_axis; m<change_piece_from_left_to_right; m++)
                            {
                                dis[y_axis][m]='B';
                            }
                        }
                        //once disks is changed from white into black, the sub-function horizontal_black will return 1
                        //When onlytest==0, we can return 1, because if program executes here, it has proved that there are valid movements in horizontal
                        return 1;
                    }
                    //detect_answer_from_right_to_left<0 && detect_answer_from_left_to_right<0 means no valid movements on this row
                    if(detect_answer_from_right_to_left<0 && detect_answer_from_left_to_right<0 )
                    {
                        return 0;
                    }
                }
            }
            else//This square have a disc of the same colour as the one being placed
            {
                return 0;
            }
        }
        else//This square is occupied
        {
            return 0;
        }
    }
    else//the square is outside the boundaries of the board
    {
        return 0;
    }
    return 0;
}
int detect_from_right_to_left_black(int x)//detect if there is a valid square to make a movement from right to left
{
    if(dis[y_axis][x-2]=='B')//from above, we have already knew dis[][]=='W', and now dis[y_axis][x-2]=='B', so this is a valid movement
    {
        change_piece_from_right_to_left=x-2;
        return 1;
    }
    else if(dis[y_axis][x-2]==' ' || x-2<0)//from above, we have already knew dis[][]=='W', and now dis[y_axis][x-2]==' ' or x-2<0, so this is a not valid movement
    {
        return -1;
    }
    else//dis[y_axis][x-2]=='W', we use recursion until we find dis[y_axis][x-2]=='B' or (dis[y_axis][x-2]==' ' || x-2<0)
    {
        return detect_from_right_to_left_black(x-1);
    }
}
int detect_from_left_to_right_black(int x)//detect if there is a valid square to make a movement from left to right
{
    if(dis[y_axis][x+2]=='B')//from above, we have already knew dis[][]=='W', and now dis[y_axis][x+2]=='B', so this is a valid movement
    {
        change_piece_from_left_to_right=x+2;
        return 1;
    }
    else if(dis[y_axis][x+2]==' ' || x+2>7)//from above, we have already knew dis[][]=='W', and now dis[y_axis][x+2]==' ' or x+2<0, so this is a not valid movement
    {
        return -1;
    }
    else//dis[y_axis][x+2]=='W', we use recursion until we find dis[y_axis][x+2]=='B' or (dis[y_axis][x+2]==' ' || x+2<0)
    {
        return detect_from_left_to_right_black(x+1);
    }
}

//vertical_black, secondly, we begin with vertical
int vertical_black(void)
{
    if(x_axis<=7 && x_axis>=0 && y_axis<=7 && y_axis>=0)//is the square outside the boundaries of the board
    {
        if(dis[y_axis][x_axis]==' ' || test1)//is this square occupied
        {
            if(dis[y_axis-1][x_axis]=='W' || dis[y_axis+1][x_axis]=='W')// does it have a disc of the same colour as the one being placed
            {
                //if the upper part of the board in this column is 'W' and on the lower part of the board in this column is blank or 'B' or outside of the board
                //then I only consider the upper half of the board in this column
                if(dis[y_axis-1][x_axis]=='W' && (dis[y_axis+1][x_axis]==' ' || dis[y_axis+1][x_axis]=='B' || y_axis+1>7))
                {
                    //I will detect from bottom to top to see if there is a valid square to make a movement
                    detect_answer_from_bot_to_top=detect_from_bot_to_top_black(y_axis);
                    if(detect_answer_from_bot_to_top>0)//detect_answer_from_bot_to_top>0 means we have found a valid movement
                    {
                        if(onlytest==1)//onlytest==1, this means the program is not detecting every squares to see if there are valid squares in the board
                        {
                            //this for loop is used to change all white disks into black disks
                            for(int m=change_piece_from_bot_to_top; m<=y_axis; m++)
                            {
                                dis[m][x_axis]='B';
                            }
                        }

                        return 1;//once disks is changed from white into black, the sub-function vertical_black will return 1
                        //When onlytest==0, we can return 1, because if program executes here, it has proved that there are valid movements in vertical
                    }
                    else//detect_answer_from_bot_to_top<0, this means no valid movements in vertical
                    {
                        return 0;
                    }
                }
                    //if the lower part of the board in this column is 'W' and on the upper part of the board in this column is blank or 'B' or outside of the board
                    //then I only consider the lower half of the board in this column
                else if(dis[y_axis+1][x_axis]=='W' && (dis[y_axis-1][x_axis]==' ' || dis[y_axis-1][x_axis]=='B' || y_axis-1<0))
                {
                    //I will detect from top to bottom to see if there is a valid square to make a movement
                    detect_answer_from_top_to_bot=detect_from_top_to_bot_black(y_axis);
                    if(detect_answer_from_top_to_bot>0)//detect_answer_from_top_to_bot>0 means we have found a valid movement
                    {
                        if(onlytest==1)//onlytest==1, this means the program is not detecting every squares to see if there are valid squares in the board
                        {
                            //this for loop is used to change all white disks into black disks
                            for(int m=y_axis; m<=change_piece_from_top_to_bot; m++)
                            {
                                dis[m][x_axis]='B';
                            }
                        }

                        return 1;//once disks is changed from white into black, the sub-function vertical_black will return 1
                        //When onlytest==0, we can return 1, because if program executes here, it has proved that there are valid movements in vertical
                    }
                    else//detect_answer_from_bot_to_top<0, this means no valid movements in vertical
                    {
                        return 0;
                    }
                }
                    //if both top and bottom of this square has 'W'
                else
                {
                    //I will detect from bottom to top and top to bottom to see if there is a valid square to make a movement
                    detect_answer_from_bot_to_top=detect_from_bot_to_top_black(y_axis);
                    detect_answer_from_top_to_bot=detect_from_top_to_bot_black(y_axis);
                    //detect_answer_from_bot_to_top>0 && detect_answer_from_top_to_bot>0 means we have found a valid movement on both sides
                    if(detect_answer_from_bot_to_top>0 && detect_answer_from_top_to_bot>0)
                    {
                        if(onlytest==1)//onlytest==1, this means the program is not detecting every squares to see if there are valid squares in the board
                        {
                            //this for loop is used to change all white disks into black disks
                            for(int m=change_piece_from_bot_to_top; m<=change_piece_from_top_to_bot; m++)
                            {
                                dis[m][x_axis]='B';
                            }
                        }
                        return 1;//once disks is changed from white into black, the sub-function vertical_black will return 1
                        //When onlytest==0, we can return 1, because if program executes here, it has proved that there are valid movements in vertical
                    }
                    //detect_answer_from_bot_to_top>0 && detect_answer_from_top_to_bot<0 means we have found a valid movement on both sides
                    if(detect_answer_from_bot_to_top>0 && detect_answer_from_top_to_bot<0)
                    {
                        if(onlytest==1)//onlytest==1, this means the program is not detecting every squares to see if there are valid squares in the board
                        {
                            //this for loop is used to change all white disks into black disks
                            for(int m=change_piece_from_bot_to_top; m<=y_axis; m++)
                            {
                                dis[m][x_axis]='B';
                            }
                        }

                        return 1;//once disks is changed from white into black, the sub-function vertical_black will return 1
                        //When onlytest==0, we can return 1, because if program executes here, it has proved that there are valid movements in vertical
                    }
                    //detect_answer_from_bot_to_top<0 && detect_answer_from_top_to_bot>0 means we have found a valid movement on both sides
                    if(detect_answer_from_bot_to_top<0 && detect_answer_from_top_to_bot>0)
                    {
                        if(onlytest==1)//onlytest==1, this means the program is not detecting every squares to see if there are valid squares in the board
                        {
                            //this for loop is used to change all white disks into black disks
                            for(int m=y_axis; m<change_piece_from_top_to_bot; m++)
                            {
                                dis[m][x_axis]='B';
                            }
                        }
                        return 1;//once disks is changed from white into black, the sub-function vertical_black will return 1
                        //When onlytest==0, we can return 1, because if program executes here, it has proved that there are valid movements in vertical
                    }
                    //detect_answer_from_bot_to_top<0 && detect_answer_from_top_to_bot<0 means no valid movements on both sides
                    if(detect_answer_from_bot_to_top<0 && detect_answer_from_top_to_bot<0)
                    {
                        return 0;
                    }
                }
            }
            else//This square have a disc of the same colour as the one being placed
            {
                return 0;
            }
        }
        else//This square is occupied
        {
            return 0;
        }
    }
    else//the square is outside the boundaries of the board
    {
        return 0;
    }
    return 0;
}
int detect_from_bot_to_top_black(int y)//detect if there is a valid square to make a movement from bottom to top
{
    if(dis[y-2][x_axis]=='B')//from above, we have already knew dis[][]=='W', and now dis[y-2][x_axis]=='B', so this is a valid movement
    {
        change_piece_from_bot_to_top=y-2;
        return 1;
    }
    else if(dis[y-2][x_axis]==' ' || y-2<0)//from above, we have already knew dis[][]=='W', and now dis[y-2][x_axis]==' ' || y-2<0, so this is a not valid movement
    {
        return -1;
    }
    else//dis[y-2][x_axis]=='W', we use recursion until we find dis[y-2][x_axis]=='B' or (dis[y-2][x_axis]==' ' || y-2<0)
    {
        return detect_from_bot_to_top_black(y-1);
    }
}
int detect_from_top_to_bot_black(int y)//detect if there is a valid square to make a movement from top to bottom
{
    if(dis[y+2][x_axis]=='B')//from above, we have already knew dis[][]=='W', and now dis[y+2][x_axis]=='B', so this is a valid movement
    {
        change_piece_from_top_to_bot=y+2;
        return 1;
    }
    else if(dis[y+2][x_axis]==' ' || y+2>7)//from above, we have already knew dis[][]=='W', and now dis[y+2][x_axis]==' ' || y+2<0, so this is a not valid movement
    {
        return -1;
    }
    else//dis[y+2][x_axis]=='W', we use recursion until we find dis[y+2][x_axis]=='B' or (dis[y+2][x_axis]==' ' || y+2<0)
    {
        return detect_from_top_to_bot_black(y+1);
    }
}

//diagonal_black
int diagonal_black_left(void)
{
    if(x_axis<=7 && x_axis>=0 && y_axis<=7 && y_axis>=0)//is the square outside the boundaries of the board
    {
        if(dis[y_axis][x_axis]==' ' || test1 || test2)//is this square occupied
        {
            if(dis[y_axis-1][x_axis-1]=='W' || dis[y_axis+1][x_axis+1]=='W')// does it have a disc of the same colour as the one being placed
            {
                //if on the upper left corner of the board is 'W' and on the lower right corner of the board is blank or 'B' or outside of the board
                //then I only consider the upper left corner of the board
                if(dis[y_axis-1][x_axis-1]=='W' && (dis[y_axis+1][x_axis+1]==' ' || dis[y_axis+1][x_axis+1]=='B' || (x_axis+1>7 || y_axis+1>7)))
                {
                    //I will detect from the lower right corner to the upper left corner to see if there is a valid square to make a movement
                    detect_answer_left_bot_top=detect_left_bot_top_black(x_axis, y_axis);
                    if(detect_answer_left_bot_top>0)//detect_answer_left_bot_top>0 means we have found a valid movement
                    {
                        if(onlytest==1)//onlytest==1, this means the program is not detecting every squares to see if there are valid squares in the board
                        {
                            //this while loop is used to change all white disks into black disks
                            int l=change_piece_left_bot_topyyy;
                            int m=change_piece_left_bot_topxxx;
                            while(m<=x_axis && l<=y_axis)
                            {
                                dis[l][m]='B';
                                m++;
                                l++;
                            }
                        }
                        return 1;//once disks is changed from white into black, the sub-function diagonal_black_leftwill return 1
                        //When onlytest==0, we can return 1, because if program executes here, it has proved that there are valid movements in diagonal
                    }
                    else//detect_answer_left_bot_top<0, this means no valid movements in diagonal
                    {
                        return 0;
                    }
                }
                    //if on the lower right corner of the board is 'W' and on the upper left corner of the board is blank or 'B' or outside of the board
                    //then I only consider the lower right corner of the board
                else if(dis[y_axis+1][x_axis+1]=='W' && (dis[y_axis-1][x_axis-1]==' ' || dis[y_axis-1][x_axis-1]=='B' || (x_axis-1<0 || y_axis-1<0)))
                {
                    //I will detect from the upper left corner to the lower right corner to see if there is a valid square to make a movement
                    detect_answer_left_top_bot=detect_left_top_bot_black(x_axis, y_axis);
                    if(detect_answer_left_top_bot>0)//detect_answer_left_top_bot>0 means we have found a valid movement
                    {
                        if(onlytest==1)//onlytest==1, this means the program is not detecting every squares to see if there are valid squares in the board
                        {
                            //this while loop is used to change all white disks into black disks
                            int m=x_axis;
                            int l=y_axis;
                            while(m<=change_piece_left_top_botxxx && l<=change_piece_left_top_botyyy)
                            {
                                dis[l][m]='B';
                                m++;
                                l++;
                            }
                        }
                        return 1;//once disks is changed from white into black, the sub-function diagonal_black_left will return 1
                        //When onlytest==0, we can return 1, because if program executes here, it has proved that there are valid movements in diagonal
                    }
                    else//detect_answer_left_top_bot<0, this means no valid movements in diagonal
                    {
                        return 0;
                    }
                }
                    //if both sides of this square has 'W'
                else
                {
                    //I will detect from left upper corner to right lower corner and right lower corner to left upper corner to see if there is a valid square to make a movement
                    detect_answer_left_bot_top=detect_left_bot_top_black(x_axis, y_axis);
                    detect_answer_left_top_bot=detect_left_top_bot_black(x_axis, y_axis);
                    //detect_answer_left_bot_top>0 && detect_answer_left_top_bot>0 means we have found a valid movement on both sides
                    if(detect_answer_left_bot_top>0 && detect_answer_left_top_bot>0)
                    {
                        if(onlytest==1)//onlytest==1, this means the program is not detecting every squares to see if there are valid squares in the board
                        {
                            //this while loop is used to change all white disks into black disks
                            int m=change_piece_left_bot_topxxx;
                            int l=change_piece_left_bot_topyyy;
                            while(m<=change_piece_left_top_botxxx && l<=change_piece_left_top_botyyy)
                            {
                                dis[l][m]='B';
                                m++;
                                l++;
                            }
                        }
                        return 1;//once disks is changed from white into black, the sub-function diagonal_black_left will return 1
                        //When onlytest==0, we can return 1, because if program executes here, it has proved that there are valid movements in diagonal
                    }
                    //detect_answer_left_bot_top>0 && detect_answer_left_top_bot<0 means we have found a valid movement on both sides
                    if(detect_answer_left_bot_top>0 && detect_answer_left_top_bot<0)
                    {
                        if(onlytest==1)//onlytest==1, this means the program is not detecting every squares to see if there are valid squares in the board
                        {
                            //this while loop is used to change all white disks into black disks
                            int m=change_piece_left_bot_topxxx;
                            int l=change_piece_left_bot_topyyy;
                            while(m<=x_axis && l<=y_axis)
                            {
                                dis[l][m]='B';
                                m++;
                                l++;
                            }
                        }
                        return 1;//once disks is changed from white into black, the sub-function diagonal_black_left will return 1
                        //When onlytest==0, we can return 1, because if program executes here, it has proved that there are valid movements in diagonal
                    }
                    //detect_answer_left_bot_top<0 && detect_answer_left_top_bot>0 means we have found a valid movement on both sides
                    if(detect_answer_left_bot_top<0 && detect_answer_left_top_bot>0)
                    {
                        if(onlytest==1)//onlytest==1, this means the program is not detecting every squares to see if there are valid squares in the board
                        {
                            //this while loop is used to change all white disks into black disks
                            int m=x_axis;
                            int l=y_axis;
                            while(m<=change_piece_left_top_botxxx && l<=change_piece_left_top_botyyy)
                            {
                                dis[l][m]='B';
                                m++;
                                l++;
                            }
                        }
                        return 1;//once disks is changed from white into black, the sub-function diagonal_black_left will return 1
                        //When onlytest==0, we can return 1, because if program executes here, it has proved that there are valid movements in diagonal
                    }
                    //detect_answer_left_bot_top<0 && detect_answer_left_top_bot<0 means no valid movements on this row
                    if(detect_answer_left_bot_top<0 && detect_answer_left_top_bot<0)
                    {
                        return 0;
                    }
                }
            }
            else//This square have a disc of the same colour as the one being placed
            {
                return 0;
            }
        }
        else//This square is occupied
        {
            return 0;
        }
    }
    else//the square is outside the boundaries of the board
    {
        return 0;
    }
    return 0;
}
int diagonal_black_right(void)
{
    if(x_axis<=7 && x_axis>=0 && y_axis<=7 && y_axis>=0)//is the square outside the boundaries of the board
    {
        if(dis[y_axis][x_axis]==' ' || test1 || test2 || test3)//is this square occupied
        {
            if(dis[y_axis-1][x_axis+1]=='W' || dis[y_axis+1][x_axis-1]=='W')// does it have a disc of the same colour as the one being placed
            {
                //if on the upper right corner of the board is 'W' and on the lower left corner of the board is blank or 'B' or outside of the board
                //then I only consider the upper right corner of the board
                if(dis[y_axis-1][x_axis+1]=='W' && (dis[y_axis+1][x_axis-1]==' ' || dis[y_axis+1][x_axis-1]=='B' || (x_axis-1<0 || y_axis+1>7)))
                {
                    //I will detect from the lower left corner to the upper right corner to see if there is a valid square to make a movement
                    detect_answer_right_bot_top=detect_right_bot_top_black(x_axis, y_axis);
                    if(detect_answer_right_bot_top>0)//detect_answer_right_bot_top>0 means we have found a valid movement
                    {
                        if(onlytest==1)//onlytest==1, this means the program is not detecting every squares to see if there are valid squares in the board
                        {
                            //this while loop is used to change all white disks into black disks
                            int l=change_piece_right_bot_topyyy;
                            int m=change_piece_right_bot_topxxx;
                            while(m>=x_axis && l<=y_axis)
                            {
                                dis[l][m]='B';
                                m--;
                                l++;
                            }
                        }
                        return 1;//once disks is changed from white into black, the sub-function diagonal_black_right will return 1
                        //When onlytest==0, we can return 1, because if program executes here, it has proved that there are valid movements in diagonal
                    }
                    else//detect_answer_right_bot_top<0, this means no valid movements in diagonal
                    {
                        return 0;
                    }
                }
                    //if on the lower left corner of the board is 'W' and on the upper right corner of the board is blank or 'B' or outside of the board
                    //then I only consider the lower left corner of the board
                else if(dis[y_axis+1][x_axis-1]=='W' && (dis[y_axis-1][x_axis+1]==' ' || dis[y_axis-1][x_axis+1]=='B' || (x_axis+1>7 || y_axis-1<0)))
                {
                    //I will detect from the upper right corner to the lower left corner to see if there is a valid square to make a movement
                    detect_answer_right_top_bot=detect_right_top_bot_black(x_axis, y_axis);
                    if(detect_answer_right_top_bot>0)//detect_answer_right_top_bot>0 means we have found a valid movement
                    {
                        if(onlytest==1)//onlytest==1, this means the program is not detecting every squares to see if there are valid squares in the board
                        {
                            //this while loop is used to change all white disks into black disks
                            int m=x_axis;
                            int l=y_axis;
                            while(m>=change_piece_right_top_botxxx && l<=change_piece_right_top_botyyy)
                            {
                                dis[l][m]='B';
                                m--;
                                l++;
                            }
                        }
                        return 1;//once disks is changed from white into black, the sub-function diagonal_black_right will return 1
                        //When onlytest==0, we can return 1, because if program executes here, it has proved that there are valid movements in diagonal
                    }
                    else//detect_answer_right_top_bot<0, this means no valid movements in diagonal
                    {
                        return 0;
                    }
                }
                    //if both sides of this square has 'W'
                else
                {
                    //I will detect from right upper corner to left lower corner and left lower corner to right upper corner to see if there is a valid square to make a movement
                    detect_answer_right_bot_top=detect_right_bot_top_black(x_axis, y_axis);
                    detect_answer_right_top_bot=detect_right_top_bot_black(x_axis, y_axis);
                    //detect_answer_right_bot_top>0 && detect_answer_right_top_bot>0 means we have found a valid movement on both sides
                    if(detect_answer_right_bot_top>0 && detect_answer_right_top_bot>0)
                    {
                        if(onlytest==1)//onlytest==1, this means the program is not detecting every squares to see if there are valid squares in the board
                        {
                            //this while loop is used to change all white disks into black disks
                            int m=change_piece_right_bot_topxxx;
                            int l=change_piece_right_bot_topyyy;
                            while(m>=change_piece_right_top_botxxx && l<=change_piece_right_top_botyyy)
                            {
                                dis[l][m]='B';
                                m--;
                                l++;
                            }
                        }
                        return 1;//once disks is changed from white into black, the sub-function diagonal_black_right will return 1
                        //When onlytest==0, we can return 1, because if program executes here, it has proved that there are valid movements in diagonal
                    }
                    //detect_answer_right_bot_top>0 && detect_answer_right_top_bot<0 means we have found a valid movement on both sides
                    if(detect_answer_right_bot_top>0 && detect_answer_right_top_bot<0)
                    {
                        if(onlytest==1)//onlytest==1, this means the program is not detecting every squares to see if there are valid squares in the board
                        {
                            //this while loop is used to change all white disks into black disks
                            int m=change_piece_right_bot_topxxx;
                            int l=change_piece_right_bot_topyyy;
                            while(m>=x_axis && l<=y_axis)
                            {
                                dis[l][m]='B';
                                m--;
                                l++;
                            }
                        }
                        return 1;//once disks is changed from white into black, the sub-function diagonal_black_right will return 1
                        //When onlytest==0, we can return 1, because if program executes here, it has proved that there are valid movements in diagonal
                    }
                    //detect_answer_right_bot_top<0 && detect_answer_right_top_bot>0 means we have found a valid movement on both sides
                    if(detect_answer_right_bot_top<0 && detect_answer_right_top_bot>0)
                    {
                        if(onlytest==1)//onlytest==1, this means the program is not detecting every squares to see if there are valid squares in the board
                        {
                            //this while loop is used to change all white disks into black disks
                            int m=x_axis;
                            int l=y_axis;
                            while(m>=change_piece_right_top_botxxx && l<=change_piece_right_top_botyyy)
                            {
                                dis[l][m]='B';
                                m--;
                                l++;
                            }
                        }
                        return 1;//once disks is changed from white into black, the sub-function diagonal_black_right will return 1
                        //When onlytest==0, we can return 1, because if program executes here, it has proved that there are valid movements in diagonal
                    }
                    //detect_answer_right_bot_top<0 && detect_answer_right_top_bot<0 means no valid movements on this row
                    if(detect_answer_right_bot_top<0 && detect_answer_right_top_bot<0)
                    {
                        return 0;
                    }
                }
            }
            else//This square have a disc of the same colour as the one being placed
            {
                return 0;
            }
        }
        else//This square is occupied
        {
            return 0;
        }
    }
    else//the square is outside the boundaries of the board
    {
        return 0;
    }
    return 0;
}
int detect_left_bot_top_black(int x, int y)//detect if there is a valid square to make a movement from left upper corner to right lower corner
{
    if(dis[y-2][x-2]=='B')//from above, we have already knew dis[][]=='W', and now dis[y-2][x-2]=='B', so this is a valid movement
    {
        change_piece_left_bot_topxxx=x-2;
        change_piece_left_bot_topyyy=y-2;
        return 1;
    }
    else if(dis[y-2][x-2]==' ' || (x-2<0 || y-2<0))//from above, we have already knew dis[][]=='W', and now dis[y-2][x-2]==' ' || (x-2<0 || y-2<0), so this is a not valid movement
    {
        return -1;
    }
    else//dis[y-2][x-2]=='W', we use recursion until we find dis[y-2][x-2]=='B' or (dis[y-2][x-2]==' ' || (x-2<0 || y-2<0))
    {
        return detect_left_bot_top_black(x-1, y-1);
    }
}
int detect_left_top_bot_black(int x, int y)//detect if there is a valid square to make a movement from left top corner to right lower corner
{
    if(dis[y+2][x+2]=='B')//from above, we have already knew dis[][]=='W', and now dis[y+2][x+2]=='B', so this is a valid movement
    {
        change_piece_left_top_botxxx=x+2;
        change_piece_left_top_botyyy=y+2;
        return 1;
    }
    else if(dis[y+2][x+2]==' ' || (x+2>7 || y+2>7))//from above, we have already knew dis[][]=='W', and now dis[y+2][x+2]==' ' || (x+2>7 || y+2>7), so this is a not valid movement
    {
        return -1;
    }
    else//dis[y+2][x+2]=='W', we use recursion until we find dis[y+2][x+2]===='B' or (dis[y+2][x+2]==' ' || (x+2>7 || y+2>7))
    {
        return detect_left_top_bot_black(x+1, y+1);
    }
}
int detect_right_bot_top_black(int x, int y)//detect if there is a valid square to make a movement from left bottom corner to right upper corner
{
    if(dis[y-2][x+2]=='B')//from above, we have already knew dis[][]=='W', and now dis[y-2][x+2]=='B', so this is a valid movement
    {
        change_piece_right_bot_topxxx=x+2;
        change_piece_right_bot_topyyy=y-2;
        return 1;
    }
    else if(dis[y-2][x+2]==' ' || (x+2>7 || y-2<0))//from above, we have already knew dis[][]=='W', and now dis[y-2][x+2]==' ' || (x+2>7 || y-2<0), so this is a not valid movement
    {
        return -1;
    }
    else//dis[y-2][x+2]=='W', we use recursion until we find dis[y-2][x+2]=='B' or (dis[y-2][x+2]==' ' || (x+2>7 || y-2<0))
    {
        return detect_right_bot_top_black(x+1, y-1);
    }
}
int detect_right_top_bot_black(int x, int y)//detect if there is a valid square to make a movement from right top corner to left lower corner
{
    if(dis[y+2][x-2]=='B')//from above, we have already knew dis[][]=='W', and now dis[y+2][x-2]=='B', so this is a valid movement
    {
        change_piece_right_top_botxxx=x-2;
        change_piece_right_top_botyyy=y+2;
        return 1;
    }
    else if(dis[y+2][x-2]==' ' || (x-2<0 || y+2>7))//from above, we have already knew dis[][]=='W', and now dis[y+2][x-2]==' ' || (x-2<0 || y+2>7), so this is a not valid movement
    {
        return -1;
    }
    else//dis[y+2][x-2]=='W', we use recursion until we find dis[y+2][x-2]=='B' or (dis[y+2][x-2]==' ' || (x-2<0 || y+2>7))
    {
        return detect_right_top_bot_black(x-1, y+1);
    }
}





