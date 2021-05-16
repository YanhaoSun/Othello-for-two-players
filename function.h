//
// Created by yanhao sun on 15/05/2021.
//

#ifndef ASSIGNMENT2_FUNCTION_H
#define ASSIGNMENT2_FUNCTION_H

//initialise board
void dis_board(void);
void initialise_board(void);
int player_black(void);
int player_white(void);

//horizontal black
int horizontal_black(void);
int detect_from_right_to_left_black(int x);
int detect_from_left_to_right_black(int x);

//horizontal white
int horizontal_white(void);
int detect_from_right_to_left_white(int x);
int detect_from_left_to_right_white(int x);

//vertical black
int vertical_black(void);
int detect_from_bot_to_top_black(int y);
int detect_from_top_to_bot_black(int y);
//vertical white
int vertical_white(void);
int detect_from_bot_to_top_white(int y);
int detect_from_top_to_bot_white(int y);

//diagonal black
int diagonal_black_left(void);
int diagonal_black_right(void);
int detect_left_bot_top_black(int x, int y);
int detect_left_top_bot_black(int x, int y);
int detect_right_bot_top_black(int x, int y);
int detect_right_top_bot_black(int x, int y);

//diagonal white
int diagonal_white_left(void);
int diagonal_white_right(void);
int detect_left_bot_top_white(int x, int y);
int detect_left_top_bot_white(int x, int y);
int detect_right_bot_top_white(int x, int y);
int detect_right_top_bot_white(int x, int y);

#endif //ASSIGNMENT2_FUNCTION_H
