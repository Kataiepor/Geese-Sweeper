#include "geesespotter_lib.h"
#include <iostream>

char *create_board(std::size_t x_dim, std::size_t y_dim){

    char * array_p = new char [x_dim * y_dim];

    for (int i = 0; i < (x_dim * y_dim); i++){
        array_p[i] = 0; 
    }

    return array_p;
}

void clean_board(char *board){
    
    delete[] board;
    board = nullptr;

}

void print_board(char *board, std::size_t x_dim, std::size_t y_dim){

    int count = 1; 

    for (int i = 0; i < (x_dim * y_dim); i++){

        if ((board[i] & marked_mask()) != 0){
            std::cout << "M";
        }
        
        else if ((board[i] & hidden_mask()) != 0){
            std::cout << "*"; 
        }

        else if (((board[i] & hidden_mask()) && (board[i] & marked_mask())) != true){ ///CHECK THIS LINE
        
        int value = board[i] & value_mask(); 

        std::cout << value; 

        }

        if (i == (count * x_dim) - 1){
            
            count++;
            std::cout << std::endl;

        }

    }

}

void hide_board(char *board, std::size_t x_dim, std::size_t y_dim){

    for (int i = 0; i < (x_dim * y_dim); i++){

       board[i] ^= hidden_mask();
    }

}

int mark(char *board, std::size_t x_dim, std::size_t y_dim, std::size_t x_loc, std::size_t y_loc){

    int coordinate = (x_loc + (y_loc * x_dim));

    if ((board[coordinate]) & (hidden_mask()) == 0){

        return 2; 

    }

    if ((board[coordinate] & marked_mask()) == marked_mask()){ //Marked Case

        board[coordinate] ^= marked_mask();

        return 0; 

    }

    if ((board[coordinate] & marked_mask()) == 0) { //Unmarked Case
            
        board[coordinate] |= marked_mask();

        return 0;

    }

    else {

        return 0; 

    }

}

bool within_border (std::size_t x_dim, std::size_t y_dim, int x, int y);

bool within_border (std::size_t x_dim, std::size_t y_dim, int x, int y){

    if (((x >= 0) && ((y >= 0)) && (x < (y_dim)) && (y < (x_dim)))){

        return true;

    }

    else {

        return false; 

    }

}

void compute_neighbours(char *board, std::size_t x_dim, std::size_t y_dim){

    int board_size = x_dim * y_dim; 
    int GEESE = 9;

    for (int row = 0; row < y_dim; row++){
        for (int col = 0; col < x_dim; col++){
            
            int geese_adjacent = 0; 

            if (within_border (x_dim, y_dim, row, (col - 1)) == true){ //checks on the left col

                int index = ((col - 1) + (row * x_dim));

                if ((board[index] & value_mask()) == GEESE){

                    geese_adjacent++;

                }
            }

            if (within_border (x_dim, y_dim, row, (col + 1)) == true){ //checks on the right col

                int index = ((col + 1) + (row * x_dim));

                if (board[index] == GEESE){

                    geese_adjacent++;

                }

            }

            if (within_border (x_dim, y_dim, (row + 1), col) == true){ //checks on the bottom row

                int index = (col + ((row + 1) * x_dim));

                if (board[index] == GEESE){

                    geese_adjacent++;

                }

            }

            if (within_border (x_dim, y_dim, (row - 1), col) == true){ //checks on the top row

                int index = (col + ((row - 1) * x_dim));

                if (board[index] == GEESE){

                    geese_adjacent++;

                }

            }

            if (within_border (x_dim, y_dim, (row - 1), (col - 1)) == true){ //checks on the top row left col

                int index = ((col - 1) + ((row - 1) * x_dim));

                if (board[index] == GEESE){

                    geese_adjacent++;

                }

            }

            if (within_border (x_dim, y_dim, (row - 1), (col + 1)) == true){ //checks on the top row right col

                int index = ((col + 1) + ((row - 1) * x_dim));

                if (board[index] == GEESE){

                    geese_adjacent++;

                }

            }

            if (within_border (x_dim, y_dim, (row + 1), (col - 1)) == true){ //checks on the bottom row left col

                int index = ((col - 1) + ((row + 1) * x_dim));

                if (board[index] == GEESE){

                    geese_adjacent++;

                }

            }

            if (within_border (x_dim, y_dim, (row + 1), (col + 1)) == true){ //checks on the bottom row right col

                int index = ((col + 1) + ((row + 1) * x_dim));

                if (board[index] == GEESE){

                    geese_adjacent++;

                }

            }
            int index = ((col) + (row * x_dim));
            if (board[index] != GEESE){

                board[index] = geese_adjacent;

            }
         
        }

    }
            
}


bool is_game_won(char *board, std::size_t x_dim, std::size_t y_dim){

    int board_size = (x_dim * y_dim); 
    int geese_num = 0;
    int hidden_num = 0;

for (int i = 0; i < board_size; i++){

        if (((board[i] & hidden_mask()) != 0) && ((board[i] & value_mask()) != 9)){

        return false; 

        }

    }
            
    return true; 

} 

int reveal(char *board, std::size_t x_dim, std::size_t y_dim, std::size_t x_loc, std::size_t y_loc){

    int index_board = ((x_loc) + (y_loc * x_dim));

        if ((board[index_board] & marked_mask()) == marked_mask()){ //Case 2

            return 1; 

        }
//&& ((board[index_board] & value_mask()) != 0)
        else if (((board[index_board] & hidden_mask()) == 0) ){ //Case 3

            return 2; 

        }

        else if (((board[index_board] & value_mask()) == 9)){ //Case 1

            board[index_board] &= value_mask();

            return 9; 

        }

        else if (((board[index_board] & value_mask()) != 0)){

            board[index_board] &= value_mask();

            return 0; 

        }

        else if (((board[index_board] & hidden_mask()) != 0) && ((board[index_board] & value_mask()) != 9) || (((board[index_board] & value_mask()) == 0)) && ((board[index_board] & hidden_mask()) == 0)){

                    board[index_board] &= value_mask();

                        if (within_border (x_dim, y_dim, y_loc, (x_loc - 1)) == true){ //checks on the left col

                            int index = ((x_loc - 1) + (y_loc * x_dim));

                            if (((board[index] & marked_mask()) != marked_mask()) || ((board[index] & hidden_mask ()) == hidden_mask())){

                                board[index] &= value_mask();

                            }

                        }

                        if (within_border (x_dim, y_dim, y_loc, (x_loc + 1)) == true){ //checks on the right col

                            int index = ((x_loc + 1) + (y_loc * x_dim));

                            if (((board[index] & marked_mask()) != marked_mask()) || ((board[index] & hidden_mask ()) == hidden_mask())){

                                board[index] &= value_mask();

                            }

                        }

                        if (within_border (x_dim, y_dim, (y_loc + 1), x_loc) == true){ //checks on the bottom row

                            int index = (x_loc + ((y_loc + 1) * x_dim));

                            if (((board[index] & marked_mask()) != marked_mask()) || ((board[index] & hidden_mask ()) == hidden_mask())){

                                board[index] &= value_mask();

                            }


                        }

                        if (within_border (x_dim, y_dim, (y_loc - 1), x_loc) == true){ //checks on the top row

                            int index = (x_loc + ((y_loc - 1) * x_dim));

                            if (((board[index] & marked_mask()) != marked_mask()) || ((board[index] & hidden_mask ()) == hidden_mask())){

                                board[index] &= value_mask();

                            }

                        }

                        if (within_border (x_dim, y_dim, (y_loc - 1), (x_loc - 1)) == true){ //checks on the top row left col

                            int index = ((x_loc - 1) + ((y_loc - 1) * x_dim));

                            if (((board[index] & marked_mask()) != marked_mask()) || ((board[index] & hidden_mask ()) == hidden_mask())){

                                board[index] &= value_mask();

                            }

                        }

                        if (within_border (x_dim, y_dim, (y_loc - 1), (x_loc + 1)) == true){ //checks on the top row right col

                            int index = ((x_loc + 1) + ((y_loc - 1) * x_dim));

                            if (((board[index] & marked_mask()) != marked_mask()) || ((board[index] & hidden_mask ()) == hidden_mask())){

                                board[index] &= value_mask();

                            }

                        }

                        if (within_border (x_dim, y_dim, (y_loc + 1), (x_loc - 1)) == true){ //checks on the bottom row left col

                            int index = ((x_loc - 1) + ((y_loc + 1) * x_dim));

                            if (((board[index] & marked_mask()) != marked_mask()) || ((board[index] & hidden_mask ()) == hidden_mask())){

                                board[index] &= value_mask();

                            }

                        }

                        if (within_border (x_dim, y_dim, (y_loc + 1), (x_loc + 1)) == true){ //checks on the bottom row right col

                            int index = ((x_loc + 1) + ((y_loc + 1) * x_dim));

                            if (((board[index] & marked_mask()) != marked_mask()) || ((board[index] & hidden_mask ()) == hidden_mask())){

                                board[index] &= value_mask();

                            }

                        }
        }

        return 0;
}