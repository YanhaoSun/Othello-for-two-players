//
// Created by yanhao sun on 15/05/2021.
//

#include <stdbool.h>
#include <stdio.h>
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
bool test4=false;
bool test5=false;
bool test6=false;

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

int player_white(void)
{
    int scan, count_board_space=0;
    int return_horizontal_white;
    int return_vertical_white;
    int return_diagonal_left_white;
    int return_diagonal_right_white;
    int valid_white=0;
    char compare[]="pass";
    char coordinates[2];
    test4=false;
    test5=false;
    test6=false;
    onlytest=0;
    //this for loop is used to detect every squares to see if there are valid squares in the board
    for(int m=0; m<8; m++)
    {
        for(int n=0; n<8; n++)
        {
            y_axis=m;
            x_axis=n;
            return_horizontal_white=horizontal_white();//firstly, detect horizontal, if return_horizontal_white=1 then there are valid movements in horizontal,
            //if return_horizontal_white=0, then there are no valid movements in horizontal
            return_vertical_white=vertical_white();//secondly, detect vertical, if return_vertical_white=1 then there are valid movements in vertical,
            //if return_vertical_white=0, then there are no valid movements in vertical
            return_diagonal_left_white=diagonal_white_left();//thirdly, detect left diagonal, if return_diagonal_left_white=1 then there are valid movements in left diagonal,
            // if return_diagonal_left_white=0, then there are no valid movements in left diagonal
            return_diagonal_right_white=diagonal_white_right();//forth, detect right diagonal, if return_diagonal_right_white=1 then there are valid movements in right diagonal,
            // if return_diagonal_right_white=0, then there are no valid movements in right diagonal

            //if one of them above is not zero then there are valid movements and valid_white plus one
            if(return_horizontal_white!=0 || return_vertical_white!=0 || return_diagonal_left_white!=0 || return_diagonal_right_white!=0)
            {
                valid_white++;
            }
        }
    }
    onlytest=1;
    if(valid_white==0)//valid_white==0, this means no valid movements in these four direction
    {
        //this for loop is used to detect if the board is full
        for(int z=0; z<8; z++)
        {
            for(int x=0; x<8; x++)
            {
                if(dis[z][x]==' ')//if square has white space, then count_board_space will plus one
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
            printf("%s(White), you don not have any squares to make a valid move, please enter 'pass' for pass:\n", players.player2);
            again_wwwhite:
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
                goto again_wwwhite;
            }
        }
    }
    again_white:
    printf("%s(White), please enter the coordinates of the pieces you want to place in this form: 1d\n", players.player2);//user enters the coordinates of the pieces
    again_input_white:
    scanf("%s", coordinates);
    if((coordinates[0]<='0' || coordinates[0]>='9') && (coordinates[1]<'a' || coordinates[1]>'h'))//if the coordinates that user input is outside the board, user must enter again
    {
        printf("Invalid Input, please enter again in this form: 1d\n");
        goto again_input_white;
    }
    //transfer character into integer
    y_axis=coordinates[0]-49;
    x_axis=coordinates[1]-97;
    return_horizontal_white=horizontal_white();//detect horizontal first
    if(return_horizontal_white==1)
    {
        test4=true;
    }
    return_vertical_white=vertical_white();//detect vertical second
    if(return_vertical_white==1)
    {
        test5=true;
    }
    return_diagonal_left_white=diagonal_white_left();//detect left diagonal
    if(return_diagonal_left_white==1)
    {
        test6=true;
    }
    return_diagonal_right_white=diagonal_white_right();//detect right diagonal
    //if four directions are invalid, then print 'Invalid Move'
    if(return_horizontal_white==0 && return_vertical_white==0 && return_diagonal_left_white==0 && return_diagonal_right_white==0)
    {
        printf("Invalid Move.\n");
        goto again_white;
    }
        //else return 1
    else if(return_horizontal_white==1 || return_vertical_white==1 || return_diagonal_left_white==1 || return_diagonal_right_white==1)
    {
        dis_board();
        return 1;
    }
    return 0;
}
//horizontal_white, firstly, we begin with horizontal
int horizontal_white(void)
{
    if(x_axis<=7 && x_axis>=0 && y_axis<=7 && y_axis>=0)//is the square outside the boundaries of the board
    {
        if(dis[y_axis][x_axis]==' ')//is this square occupied
        {
            if(dis[y_axis][x_axis-1]=='B' || dis[y_axis][x_axis+1]=='B')// does it have a disc of the same colour as the one being placed
            {
                //if on the left hand side of the board is 'B' and on the right hand side of the board is blank or 'W' or outside of the board
                //then I only consider the left half of the board
                if(dis[y_axis][x_axis-1]=='B' && (dis[y_axis][x_axis+1]==' ' || dis[y_axis][x_axis+1]=='W' || x_axis+1>7))
                {
                    //I will detect from right to left to see if there is a valid square to make a movement
                    detect_answer_from_right_to_left=detect_from_right_to_left_white(x_axis);
                    if(detect_answer_from_right_to_left>0)//detect_answer_from_right_to_left>0 means we have found a valid movement
                    {
                        if(onlytest==1)//onlytest==1, this means the program is not detecting every squares to see if there are valid squares in the board
                        {
                            //this for loop is used to change all balck disks into white disks
                            for(int m=change_piece_from_right_to_left; m<=x_axis; m++)
                            {
                                dis[y_axis][m]='W';
                            }
                        }
                        return 1;//once disks is changed from black into white, the sub-function horizontal_white will return 1
                        //When onlytest==0, we can return 1, because if program executes here, it has proved that there are valid movements in horizontal
                    }
                    else//detect_answer_from_right_to_left<0, this means no valid movements in horizontal
                    {
                        return 0;
                    }
                }
                    //if on the right hand side of the board is 'B' and on the left hand side of the board is blank or 'W' or outside of the board
                    //then I only consider the right half of the board
                else if(dis[y_axis][x_axis+1]=='B' && (dis[y_axis][x_axis-1]==' ' || dis[y_axis][x_axis-1]=='W' || x_axis-1<0))
                {
                    //I will detect from left to right to see if there is a valid square to make a movement
                    detect_answer_from_left_to_right=detect_from_left_to_right_white(x_axis);
                    if(detect_answer_from_left_to_right>0)//detect_answer_from_left_to_right>0 means we have found a valid movement
                    {
                        if(onlytest==1)//onlytest==1, this means the program is not detecting every squares to see if there are valid squares in the board
                        {
                            //this for loop is used to change all black disks into white disks
                            for(int m=x_axis; m<=change_piece_from_left_to_right; m++)
                            {
                                dis[y_axis][m]='W';
                            }
                        }
                        return 1;//once disks is changed from black into white, the sub-function horizontal_white will return 1
                        //When onlytest==0, we can return 1, because if program executes here, it has proved that there are valid movements in horizontal
                    }
                    else//detect_answer_from_right_to_left<0, this means no valid movements in horizontal
                    {
                        return 0;
                    }

                }
                    //if both sides of this square has 'B'
                else
                {
                    //I will detect from left to right and right to left to see if there is a valid square to make a movement
                    detect_answer_from_right_to_left=detect_from_right_to_left_white(x_axis);
                    detect_answer_from_left_to_right=detect_from_left_to_right_white(x_axis);
                    //detect_answer_from_right_to_left>0 && detect_answer_from_left_to_right>0 means we have found a valid movement on both sides
                    if(detect_answer_from_right_to_left>0 && detect_answer_from_left_to_right>0)
                    {
                        if(onlytest==1)//onlytest==1, this means the program is not detecting every squares to see if there are valid squares in the board
                        {
                            //this for loop is used to change all black disks into white disks
                            for(int m=change_piece_from_right_to_left; m<=change_piece_from_left_to_right; m++)
                            {
                                dis[y_axis][m]='W';
                            }
                        }
                        return 1;//once disks is changed from balck into white, the sub-function horizontal_white will return 1
                        //When onlytest==0, we can return 1, because if program executes here, it has proved that there are valid movements in horizontal
                    }
                    //detect_answer_from_right_to_left>0 && detect_answer_from_left_to_right<0 means we have found a valid movement on left half of this row
                    if(detect_answer_from_right_to_left>0 && detect_answer_from_left_to_right<0)
                    {
                        if(onlytest==1)//onlytest==1, this means the program is not detecting every squares to see if there are valid squares in the board
                        {
                            //this for loop is used to change all black disks into white disks
                            for(int m=change_piece_from_right_to_left; m<=x_axis; m++)
                            {
                                dis[y_axis][m]='W';
                            }
                        }
                        return 1;//once disks is changed from black into white, the sub-function horizontal_white will return 1
                        //When onlytest==0, we can return 1, because if program executes here, it has proved that there are valid movements in horizontal
                    }
                    //detect_answer_from_right_to_left<0 && detect_answer_from_left_to_right>0 means we have found a valid movement on right half of this row
                    if(detect_answer_from_right_to_left<0 && detect_answer_from_left_to_right>0)
                    {
                        if(onlytest==1)//onlytest==1, this means the program is not detecting every squares to see if there are valid squares in the board
                        {
                            //this for loop is used to change all black disks into white disks
                            for(int m=x_axis; m<change_piece_from_left_to_right; m++)
                            {
                                dis[y_axis][m]='W';
                            }
                        }
                        return 1;//once disks is changed from black into white, the sub-function horizontal_white will return 1
                        //When onlytest==0, we can return 1, because if program executes here, it has proved that there are valid movements in horizontal
                    }
                    //detect_answer_from_right_to_left<0 && detect_answer_from_left_to_right<0 means no valid movements on this row
                    if(detect_answer_from_right_to_left<0 && detect_answer_from_left_to_right<0)
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
int detect_from_right_to_left_white(int x)//detect if there is a valid square to make a movement from right to left
{
    if(dis[y_axis][x-2]=='W')//from above, we have already knew dis[][]=='B', and now dis[y_axis][x-2]=='W', so this is a valid movement
    {
        change_piece_from_right_to_left=x-2;
        return 1;
    }
    else if(dis[y_axis][x-2]==' ' || x-2<0)//from above, we have already knew dis[][]=='B', and now dis[y_axis][x-2]==' ' or x-2<0, so this is a not valid movement
    {
        return -1;
    }
    else//dis[y_axis][x-2]=='B', we use recursion until we find dis[y_axis][x-2]=='W' or (dis[y_axis][x-2]==' ' || x-2<0)
    {
        return detect_from_right_to_left_white(x-1);
    }
}
int detect_from_left_to_right_white(int x)//detect if there is a valid square to make a movement from left to right
{
    if(dis[y_axis][x+2]=='W')//from above, we have already knew dis[][]=='B', and now dis[y_axis][x+2]=='W', so this is a valid movement
    {
        change_piece_from_left_to_right=x+2;
        return 1;
    }
    else if(dis[y_axis][x+2]==' ' || x+2>7)//from above, we have already knew dis[][]=='B', and now dis[y_axis][x+2]==' ' or x+2<0, so this is a not valid movement
    {
        return -1;
    }
    else//dis[y_axis][x+2]=='B', we use recursion until we find dis[y_axis][x+2]=='W' or (dis[y_axis][x+2]==' ' || x+2<0)
    {
        return detect_from_left_to_right_white(x+1);
    }
}


//vertical_white
int vertical_white(void)
{
    if(x_axis<=7 && x_axis>=0 && y_axis<=7 && y_axis>=0)//is the square outside the boundaries of the board
    {
        if(dis[y_axis][x_axis]==' ' || test4)//is this square occupied
        {
            if(dis[y_axis-1][x_axis]=='B' || dis[y_axis+1][x_axis]=='B')// does it have a disc of the same colour as the one being placed
            {
                //if the upper part of the board in this column is 'B' and on the lower part of the board in this column is blank or 'W' or outside of the board
                //then I only consider the upper half of the board in this column
                if(dis[y_axis-1][x_axis]=='B' && (dis[y_axis+1][x_axis]==' ' || dis[y_axis+1][x_axis]=='W' || y_axis+1>7))
                {
                    //I will detect from bottom to top to see if there is a valid square to make a movement
                    detect_answer_from_bot_to_top=detect_from_bot_to_top_white(y_axis);
                    if(detect_answer_from_bot_to_top>0)//detect_answer_from_bot_to_top>0 means we have found a valid movement
                    {
                        if(onlytest==1)//onlytest==1, this means the program is not detecting every squares to see if there are valid squares in the board
                        {
                            //this for loop is used to change all black disks into white disks
                            for(int m=change_piece_from_bot_to_top; m<=y_axis; m++)
                            {
                                dis[m][x_axis]='W';
                            }
                        }
                        return 1;//once disks is changed from balck into white, the sub-function vertical_white will return 1
                        //When onlytest==0, we can return 1, because if program executes here, it has proved that there are valid movements in vertical
                    }
                    else//detect_answer_from_bot_to_top<0, this means no valid movements in vertical
                    {
                        return 0;
                    }
                }
                    //if the lower part of the board in this column is 'B' and on the upper part of the board in this column is blank or 'W' or outside of the board
                    //then I only consider the lower half of the board in this column
                else if(dis[y_axis+1][x_axis]=='B' && (dis[y_axis-1][x_axis]==' ' || dis[y_axis-1][x_axis]=='W' || y_axis-1<0))
                {
                    //I will detect from top to bottom to see if there is a valid square to make a movement
                    detect_answer_from_top_to_bot=detect_from_top_to_bot_white(y_axis);
                    if(detect_answer_from_top_to_bot>0)//detect_answer_from_top_to_bot>0 means we have found a valid movement
                    {
                        if(onlytest==1)//onlytest==1, this means the program is not detecting every squares to see if there are valid squares in the board
                        {
                            //this for loop is used to change all black disks into white disks
                            for(int m=y_axis; m<=change_piece_from_top_to_bot; m++)
                            {
                                dis[m][x_axis]='W';
                            }
                        }
                        return 1;//once disks is changed from black into white, the sub-function vertical_white will return 1
                        //When onlytest==0, we can return 1, because if program executes here, it has proved that there are valid movements in vertical
                    }
                    else//detect_answer_from_bot_to_top<0, this means no valid movements in vertical
                    {
                        return 0;
                    }

                }
                    //if both top and bottom of this square has 'B'
                else
                {
                    //I will detect from bottom to top and top to bottom to see if there is a valid square to make a movement
                    detect_answer_from_bot_to_top=detect_from_bot_to_top_white(y_axis);
                    detect_answer_from_top_to_bot=detect_from_top_to_bot_white(y_axis);
                    //detect_answer_from_bot_to_top>0 && detect_answer_from_top_to_bot>0 means we have found a valid movement on both sides
                    if(detect_answer_from_bot_to_top>0 && detect_answer_from_top_to_bot>0)
                    {
                        if(onlytest==1)//onlytest==1, this means the program is not detecting every squares to see if there are valid squares in the board
                        {
                            //this for loop is used to change all black disks into white disks
                            for(int m=change_piece_from_bot_to_top; m<=change_piece_from_top_to_bot; m++)
                            {
                                dis[m][x_axis]='W';
                            }
                        }
                        return 1;//once disks is changed from black into white, the sub-function vertical_white will return 1
                        //When onlytest==0, we can return 1, because if program executes here, it has proved that there are valid movements in vertical
                    }
                    //detect_answer_from_bot_to_top>0 && detect_answer_from_top_to_bot<0 means we have found a valid movement on both sides
                    if(detect_answer_from_bot_to_top>0 && detect_answer_from_top_to_bot<0)
                    {
                        if(onlytest==1)//onlytest==1, this means the program is not detecting every squares to see if there are valid squares in the board
                        {
                            //this for loop is used to change all black disks into white disks
                            for(int m=change_piece_from_bot_to_top; m<=y_axis; m++)
                            {
                                dis[m][x_axis]='W';
                            }
                        }
                        return 1;//once disks is changed from black into white, the sub-function vertical_white will return 1
                        //When onlytest==0, we can return 1, because if program executes here, it has proved that there are valid movements in vertical
                    }
                    //detect_answer_from_bot_to_top<0 && detect_answer_from_top_to_bot>0 means we have found a valid movement on both sides
                    if(detect_answer_from_bot_to_top<0 && detect_answer_from_top_to_bot>0)
                    {
                        if(onlytest==1)//onlytest==1, this means the program is not detecting every squares to see if there are valid squares in the board
                        {
                            //this for loop is used to change all black disks into white disks
                            for(int m=y_axis; m<change_piece_from_top_to_bot; m++)
                            {
                                dis[m][x_axis]='W';
                            }
                        }
                        return 1;//once disks is changed from black into white, the sub-function vertical_white will return 1
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
int detect_from_bot_to_top_white(int y)//detect if there is a valid square to make a movement from bottom to top
{
    if(dis[y-2][x_axis]=='W')//from above, we have already knew dis[][]=='B', and now dis[y-2][x_axis]=='W', so this is a valid movement
    {
        change_piece_from_bot_to_top=y-2;
        return 1;
    }
    else if(dis[y-2][x_axis]==' ' || y-2<0)//from above, we have already knew dis[][]=='B', and now dis[y-2][x_axis]==' ' || y-2<0, so this is a not valid movement
    {
        return -1;
    }
    else//dis[y-2][x_axis]=='B', we use recursion until we find dis[y-2][x_axis]=='W' or (dis[y-2][x_axis]==' ' || y-2<0)
    {
        return detect_from_bot_to_top_white(y-1);
    }
}
int detect_from_top_to_bot_white(int y)//detect if there is a valid square to make a movement from top to bottom
{
    if(dis[y+2][x_axis]=='W')//from above, we have already knew dis[][]=='B', and now dis[y+2][x_axis]=='W', so this is a valid movement
    {
        change_piece_from_top_to_bot=y+2;
        return 1;
    }
    else if(dis[y+2][x_axis]==' ' || y+2>7)//from above, we have already knew dis[][]=='B', and now dis[y+2][x_axis]==' ' || y+2<0, so this is a not valid movement
    {
        return -1;
    }
    else//dis[y+2][x_axis]=='B', we use recursion until we find dis[y+2][x_axis]=='W' or (dis[y+2][x_axis]==' ' || y+2<0)
    {
        return detect_from_top_to_bot_white(y+1);
    }
}


//diagonal_white
int diagonal_white_left(void)
{
    if(x_axis<=7 && x_axis>=0 && y_axis<=7 && y_axis>=0)//is the square outside the boundaries of the board
    {
        if(dis[y_axis][x_axis]==' ' || test4 || test5)//is this square occupied
        {
            if(dis[y_axis-1][x_axis-1]=='B' || dis[y_axis+1][x_axis+1]=='B')// does it have a disc of the same colour as the one being placed
            {
                //if on the upper left corner of the board is 'B' and on the lower right corner of the board is blank or 'W' or outside of the board
                //then I only consider the upper left corner of the board
                if(dis[y_axis-1][x_axis-1]=='B' && (dis[y_axis+1][x_axis+1]==' ' || dis[y_axis+1][x_axis+1]=='W' || (x_axis+1>7 || y_axis+1>7)))
                {
                    //I will detect from the lower right corner to the upper left corner to see if there is a valid square to make a movement
                    detect_answer_left_bot_top=detect_left_bot_top_white(x_axis, y_axis);
                    if(detect_answer_left_bot_top>0)//detect_answer_left_bot_top>0 means we have found a valid movement
                    {
                        if(onlytest==1)//onlytest==1, this means the program is not detecting every squares to see if there are valid squares in the board
                        {
                            //this while loop is used to change all black disks into white disks
                            int l=change_piece_left_bot_topyyy;
                            int m=change_piece_left_bot_topxxx;
                            while(m<=x_axis && l<=y_axis)
                            {
                                dis[l][m]='W';
                                m++;
                                l++;
                            }
                        }
                        return 1;//once disks is changed from black into white, the sub-function diagonal_white_left will return 1
                        //When onlytest==0, we can return 1, because if program executes here, it has proved that there are valid movements in diagonal
                    }
                    else//detect_answer_left_bot_top<0, this means no valid movements in diagonal
                    {
                        return 0;
                    }

                }
                    //if on the lower right corner of the board is 'B' and on the upper left corner of the board is blank or 'W' or outside of the board
                    //then I only consider the lower right corner of the board
                else if(dis[y_axis+1][x_axis+1]=='B' && (dis[y_axis-1][x_axis-1]==' ' || dis[y_axis-1][x_axis-1]=='W' || (x_axis-1<0 || y_axis-1<0)))
                {
                    //I will detect from the upper left corner to the lower right corner to see if there is a valid square to make a movement
                    detect_answer_left_top_bot=detect_left_top_bot_white(x_axis, y_axis);
                    if(detect_answer_left_top_bot>0)//detect_answer_left_top_bot>0 means we have found a valid movement
                    {
                        if(onlytest==1)//onlytest==1, this means the program is not detecting every squares to see if there are valid squares in the board
                        {
                            //this while loop is used to change all black disks into white disks
                            int m=x_axis;
                            int l=y_axis;
                            while(m<=change_piece_left_top_botxxx && l<=change_piece_left_top_botyyy)
                            {
                                dis[l][m]='W';
                                m++;
                                l++;
                            }
                        }
                        return 1;//once disks is changed from black into white, the sub-function diagonal_white_left will return 1
                        //When onlytest==0, we can return 1, because if program executes here, it has proved that there are valid movements in diagonal
                    }
                    else//detect_answer_left_top_bot<0, this means no valid movements in diagonal
                    {
                        return 0;
                    }

                }
                    //if both sides of this square has 'B'
                else
                {
                    //I will detect from left upper corner to right lower corner and right lower corner to left upper corner to see if there is a valid square to make a movement
                    detect_answer_left_bot_top=detect_left_bot_top_white(x_axis, y_axis);
                    detect_answer_left_top_bot=detect_left_top_bot_white(x_axis, y_axis);
                    //detect_answer_left_bot_top>0 && detect_answer_left_top_bot>0 means we have found a valid movement on both sides
                    if(detect_answer_left_bot_top>0 && detect_answer_left_top_bot>0)
                    {
                        if(onlytest==1)//onlytest==1, this means the program is not detecting every squares to see if there are valid squares in the board
                        {
                            //this while loop is used to change all black disks into white disks
                            int m=change_piece_left_bot_topxxx;
                            int l=change_piece_left_bot_topyyy;
                            while(m<=change_piece_left_top_botxxx && l<=change_piece_left_top_botyyy)
                            {
                                dis[l][m]='W';
                                m++;
                                l++;
                            }
                        }
                        return 1;//once disks is changed from black into white, the sub-function diagonal_white_left will return 1
                        //When onlytest==0, we can return 1, because if program executes here, it has proved that there are valid movements in diagonal
                    }
                    //detect_answer_left_bot_top>0 && detect_answer_left_top_bot<0 means we have found a valid movement on both sides
                    if(detect_answer_left_bot_top>0 && detect_answer_left_top_bot<0)
                    {
                        if(onlytest==1)//onlytest==1, this means the program is not detecting every squares to see if there are valid squares in the board
                        {
                            //this while loop is used to change all black disks into white disks
                            int m=change_piece_left_bot_topxxx;
                            int l=change_piece_left_bot_topyyy;
                            while(m<=x_axis && l<=y_axis)
                            {
                                dis[l][m]='W';
                                m++;
                                l++;
                            }
                        }
                        return 1;//once disks is changed from black into white, the sub-function diagonal_white_left will return 1
                        //When onlytest==0, we can return 1, because if program executes here, it has proved that there are valid movements in diagonal
                    }
                    //detect_answer_left_bot_top<0 && detect_answer_left_top_bot>0 means we have found a valid movement on both sides
                    if(detect_answer_left_bot_top<0 && detect_answer_left_top_bot>0)
                    {
                        if(onlytest==1)//onlytest==1, this means the program is not detecting every squares to see if there are valid squares in the board
                        {
                            //this while loop is used to change all black disks into white disks
                            int m=x_axis;
                            int l=y_axis;
                            while(m<=change_piece_left_top_botxxx && l<=change_piece_left_top_botyyy)
                            {
                                dis[l][m]='W';
                                m++;
                                l++;
                            }
                        }
                        return 1;//once disks is changed from black into white, the sub-function diagonal_white_left will return 1
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
int diagonal_white_right(void)
{
    if(x_axis<=7 && x_axis>=0 && y_axis<=7 && y_axis>=0)//is the square outside the boundaries of the board
    {
        if(dis[y_axis][x_axis]==' ' || test4 || test5 || test6)//is this square occupied
        {
            if(dis[y_axis-1][x_axis+1]=='B' || dis[y_axis+1][x_axis-1]=='B')// does it have a disc of the same colour as the one being placed
            {
                //if on the upper right corner of the board is 'B' and on the lower left corner of the board is blank or 'W' or outside of the board
                //then I only consider the upper right corner of the board
                if(dis[y_axis-1][x_axis+1]=='B' && (dis[y_axis+1][x_axis-1]==' ' || dis[y_axis+1][x_axis-1]=='W' || (x_axis-1<0 || y_axis+1>7)))
                {
                    //I will detect from the lower left corner to the upper right corner to see if there is a valid square to make a movement
                    detect_answer_right_bot_top=detect_right_bot_top_white(x_axis, y_axis);
                    if(detect_answer_right_bot_top>0)//detect_answer_right_bot_top>0 means we have found a valid movement
                    {
                        if(onlytest==1)//onlytest==1, this means the program is not detecting every squares to see if there are valid squares in the board
                        {
                            //this while loop is used to change all black disks into white disks
                            int l=change_piece_right_bot_topyyy;
                            int m=change_piece_right_bot_topxxx;
                            while(m>=x_axis && l<=y_axis)
                            {
                                dis[l][m]='W';
                                m--;
                                l++;
                            }
                        }
                        return 1;//once disks is changed from black into white, the sub-function diagonal_white_right will return 1
                        //When onlytest==0, we can return 1, because if program executes here, it has proved that there are valid movements in diagonal
                    }
                    else//detect_answer_right_bot_top<0, this means no valid movements in diagonal
                    {
                        return 0;
                    }
                }
                    //if on the lower left corner of the board is 'B' and on the upper right corner of the board is blank or 'W' or outside of the board
                    //then I only consider the lower left corner of the board
                else if(dis[y_axis+1][x_axis-1]=='B' && (dis[y_axis-1][x_axis+1]==' ' || dis[y_axis-1][x_axis+1]=='W' || (x_axis+1>7 || y_axis-1<0)))
                {
                    //I will detect from the upper right corner to the lower left corner to see if there is a valid square to make a movement
                    detect_answer_right_top_bot=detect_right_top_bot_white(x_axis, y_axis);
                    if(detect_answer_right_top_bot>0)//detect_answer_right_top_bot>0 means we have found a valid movement
                    {
                        if(onlytest==1)//onlytest==1, this means the program is not detecting every squares to see if there are valid squares in the board
                        {
                            //this while loop is used to change all black disks into white disks
                            int m=x_axis;
                            int l=y_axis;
                            while(m>=change_piece_right_top_botxxx && l<=change_piece_right_top_botyyy)
                            {
                                dis[l][m]='W';
                                m--;
                                l++;
                            }
                        }
                        return 1;//once disks is changed from black into white, the sub-function diagonal_white_right will return 1
                        //When onlytest==0, we can return 1, because if program executes here, it has proved that there are valid movements in diagonal
                    }
                    else//detect_answer_right_top_bot<0, this means no valid movements in diagonal
                    {
                        return 0;
                    }
                }
                    //if both sides of this square has 'B'
                else
                {
                    //I will detect from right upper corner to left lower corner and left lower corner to right upper corner to see if there is a valid square to make a movement
                    detect_answer_right_bot_top=detect_right_bot_top_white(x_axis, y_axis);
                    detect_answer_right_top_bot=detect_right_top_bot_white(x_axis, y_axis);
                    //detect_answer_right_bot_top>0 && detect_answer_right_top_bot>0 means we have found a valid movement on both sides
                    if(detect_answer_right_bot_top>0 && detect_answer_right_top_bot>0)
                    {
                        if(onlytest==1)//onlytest==1, this means the program is not detecting every squares to see if there are valid squares in the board
                        {
                            //this while loop is used to change all black disks into white disks
                            int m=change_piece_right_bot_topxxx;
                            int l=change_piece_right_bot_topyyy;
                            while(m>=change_piece_right_top_botxxx && l<=change_piece_right_top_botyyy)
                            {
                                dis[l][m]='W';
                                m--;
                                l++;
                            }
                        }
                        return 1;//once disks is changed from black into white, the sub-function diagonal_white_right will return 1
                        //When onlytest==0, we can return 1, because if program executes here, it has proved that there are valid movements in diagonal
                    }
                    //detect_answer_right_bot_top>0 && detect_answer_right_top_bot<0 means we have found a valid movement on both sides
                    if(detect_answer_right_bot_top>0 && detect_answer_right_top_bot<0)
                    {
                        if(onlytest==1)//onlytest==1, this means the program is not detecting every squares to see if there are valid squares in the board
                        {
                            //this while loop is used to change all black disks into white disks
                            int m=change_piece_right_bot_topxxx;
                            int l=change_piece_right_bot_topyyy;
                            while(m>=x_axis && l<=y_axis)
                            {
                                dis[l][m]='W';
                                m--;
                                l++;
                            }
                        }
                        return 1;//once disks is changed from black into white, the sub-function diagonal_white_right will return 1
                        //When onlytest==0, we can return 1, because if program executes here, it has proved that there are valid movements in diagonal
                    }
                    //detect_answer_right_bot_top<0 && detect_answer_right_top_bot>0 means we have found a valid movement on both sides
                    if(detect_answer_right_bot_top<0 && detect_answer_right_top_bot>0)
                    {
                        if(onlytest==1)//onlytest==1, this means the program is not detecting every squares to see if there are valid squares in the board
                        {
                            //this while loop is used to change all black disks into white disks
                            int m=x_axis;
                            int l=y_axis;
                            while(m>=change_piece_right_top_botxxx && l<=change_piece_right_top_botyyy)
                            {
                                dis[l][m]='W';
                                m--;
                                l++;
                            }
                        }
                        return 1;//once disks is changed from black into white, the sub-function diagonal_white_right will return 1
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
int detect_left_bot_top_white(int x, int y)//detect if there is a valid square to make a movement from left upper corner to right lower corner
{
    if(dis[y-2][x-2]=='W')//from above, we have already knew dis[][]=='B', and now dis[y-2][x-2]=='W', so this is a valid movement
    {
        change_piece_left_bot_topxxx=x-2;
        change_piece_left_bot_topyyy=y-2;
        return 1;
    }
    else if(dis[y-2][x-2]==' ' || (x-2<0 || y-2<0))//from above, we have already knew dis[][]=='B', and now dis[y-2][x-2]==' ' || (x-2<0 || y-2<0), so this is a not valid movement
    {
        return -1;
    }
    else//dis[y-2][x-2]=='B', we use recursion until we find dis[y-2][x-2]=='W' or (dis[y-2][x-2]==' ' || (x-2<0 || y-2<0))
    {
        return detect_left_bot_top_white(x-1, y-1);
    }
}
int detect_left_top_bot_white(int x, int y)//detect if there is a valid square to make a movement from left top corner to right lower corner
{
    if(dis[y+2][x+2]=='W')//from above, we have already knew dis[][]=='B', and now dis[y+2][x+2]=='W', so this is a valid movement
    {
        change_piece_left_top_botxxx=x+2;
        change_piece_left_top_botyyy=y+2;
        return 1;
    }
    else if(dis[y+2][x+2]==' ' || (x+2>7 || y+2>7))//from above, we have already knew dis[][]=='B', and now dis[y+2][x+2]==' ' || (x+2>7 || y+2>7), so this is a not valid movement
    {
        return -1;
    }
    else//dis[y+2][x+2]=='B', we use recursion until we find dis[y+2][x+2]===='W' or (dis[y+2][x+2]==' ' || (x+2>7 || y+2>7))
    {
        return detect_left_top_bot_white(x+1, y+1);
    }
}
int detect_right_bot_top_white(int x, int y)//detect if there is a valid square to make a movement from left bottom corner to right upper corner
{
    if(dis[y-2][x+2]=='W')//from above, we have already knew dis[][]=='B', and now dis[y-2][x+2]=='W', so this is a valid movement
    {
        change_piece_right_bot_topxxx=x+2;
        change_piece_right_bot_topyyy=y-2;
        return 1;
    }
    else if(dis[y-2][x+2]==' ' || (x+2>7 || y-2<0))//from above, we have already knew dis[][]=='B', and now dis[y-2][x+2]==' ' || (x+2>7 || y-2<0), so this is a not valid movement
    {
        return -1;
    }
    else//dis[y-2][x+2]=='B', we use recursion until we find dis[y-2][x+2]=='W' or (dis[y-2][x+2]==' ' || (x+2>7 || y-2<0))
    {
        return detect_right_bot_top_white(x+1, y-1);
    }
}
int detect_right_top_bot_white(int x, int y)//detect if there is a valid square to make a movement from right top corner to left lower corner
{
    if(dis[y+2][x-2]=='W')//from above, we have already knew dis[][]=='B', and now dis[y+2][x-2]=='W', so this is a valid movement
    {
        change_piece_right_top_botxxx=x-2;
        change_piece_right_top_botyyy=y+2;
        return 1;
    }
    else if(dis[y+2][x-2]==' ' || (x-2<0 || y+2>7))//from above, we have already knew dis[][]=='B', and now dis[y+2][x-2]==' ' || (x-2<0 || y+2>7), so this is a not valid movement
    {
        return -1;
    }
    else//dis[y+2][x-2]=='B', we use recursion until we find dis[y+2][x-2]=='W' or (dis[y+2][x-2]==' ' || (x-2<0 || y+2>7))
    {
        return detect_right_top_bot_white(x-1, y+1);
    }
}


