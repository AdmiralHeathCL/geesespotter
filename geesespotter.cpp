#include "geesespotter_lib.h"
#include <iostream>

char *create_board(std::size_t x_dim, std::size_t y_dim){
    char *board{new char[x_dim*y_dim]{}};
    for(int i{0};i<x_dim*y_dim;i++){
        board[i] = 0;
    }
    return board;
}

void clean_board(char *board){
    delete[] board;
}

void print_board(char *board, std::size_t x_dim, std::size_t y_dim){
    for(std::size_t i{0};i<y_dim;i++){
        for(std::size_t j{0};j<x_dim;j++){
            if(board[i*x_dim + j] & marked_mask()){
                std::cout << "M";
            }
            else if(board[i*x_dim + j] & hidden_mask()){
                std::cout << "*";
            }
            else{
                std::cout << (board[i*x_dim + j] & value_mask());
            }
        }
        std::cout << std::endl;
    }
}

void hide_board(char *board, std::size_t x_dim, std::size_t y_dim){
    for(std::size_t i{0};i<(x_dim*y_dim);i++){
       board[i] |= hidden_mask();
    }
}   

int mark(char *board, std::size_t x_dim, std::size_t y_dim, std::size_t x_loc, std::size_t y_loc){
    if(board[y_loc*x_dim + x_loc] & hidden_mask()){
        if(board[y_loc*x_dim + x_loc] & marked_mask()){
            board[y_loc*x_dim + x_loc] &= ~marked_mask();
            return 0;
        }
        else{
            board[y_loc*x_dim + x_loc] |= marked_mask();
            return 0;
        }
    }
    else{
        return 2;
    }
}

void compute_neighbours(char *board, std::size_t x_dim, std::size_t y_dim){
    std::size_t geese{};
    for(std::size_t i{0};i<y_dim;i++){
        for(std::size_t j{0};j<x_dim;j++){
            if((board[i*x_dim + j] & value_mask())!=9){
                geese = 0;
                if(j!=0 && (board[i*x_dim + j - 1] & value_mask())==9){
                    geese++;
                }
                if(j!=(x_dim-1) && (board[i*x_dim + j + 1] & value_mask())==9){
                    geese++;
                }
                if(i!=0 && (board[(i-1)*x_dim + j] & value_mask())==9){
                    geese++;
                }
                if(i!=0 && j!=0 && (board[(i-1)*x_dim + j - 1] & value_mask())==9){
                    geese++;
                }
                if(i!=0 && j!=(x_dim-1) && (board[(i-1)*x_dim + j + 1] & value_mask())==9){
                    geese++;
                }
                if(i!=(y_dim-1) && (board[(i+1)*x_dim + j] & value_mask())==9){
                    geese++;
                }
                if(i!=(y_dim-1) && j!=0 && (board[(i+1)*x_dim + j - 1] & value_mask())==9){
                    geese++;
                }
                if(i!=(y_dim-1) && j!=(x_dim-1) && (board[(i+1)*x_dim + j + 1] & value_mask())==9){
                    geese++;
                }
                board[i*x_dim + j] = (board[i*x_dim + j] & 0xF0) + geese;
            }
        }
    }
}

bool is_game_won(char *board, std::size_t x_dim, std::size_t y_dim){
    bool is_won = true;
    for(std::size_t i{0};i<y_dim;i++){
        for(std::size_t j{0};j<x_dim;j++){
            if((board[i*x_dim + j] & value_mask())!=9 && (board[i*x_dim + j] & hidden_mask())){
                is_won = false;
                break;
            }
        }
    }
    if(is_won){
        return true;
    }
    else{
        return false;
    }

}

int reveal(char *board, std::size_t x_dim, std::size_t y_dim, std::size_t x_loc, std::size_t y_loc){
    if(board[y_loc*x_dim + x_loc] & marked_mask()){
        return 1;
    }
    else if(!(board[y_loc*x_dim + x_loc] & hidden_mask())){
        return 2;
    }
    else if((board[y_loc*x_dim + x_loc] & value_mask())==9){
        board[y_loc*x_dim + x_loc] -= hidden_mask();
        return 9;
    }
    else{
        board[y_loc*x_dim + x_loc] = board[y_loc*x_dim + x_loc] - hidden_mask();
        if(board[y_loc*x_dim + x_loc] == 0){
            if(x_loc!=0 && (board[y_loc*x_dim + x_loc - 1] & marked_mask())==0 && (board[y_loc*x_dim + x_loc - 1] & hidden_mask())){
                board[y_loc*x_dim + x_loc - 1] -= hidden_mask();
            }
            if(x_loc!=(x_dim-1) && (board[y_loc*x_dim + x_loc + 1] & marked_mask())==0 && (board[y_loc*x_dim + x_loc + 1] & hidden_mask())){
                board[y_loc*x_dim + x_loc + 1] -= hidden_mask();
            }
            if(y_loc!=0 && (board[(y_loc-1)*x_dim + x_loc] & marked_mask())==0 && (board[(y_loc-1)*x_dim + x_loc] & hidden_mask())){
                board[(y_loc-1)*x_dim + x_loc] -= hidden_mask();
            }
            if(y_loc!=0 && x_loc!=0 && (board[(y_loc-1)*x_dim + x_loc - 1] & marked_mask())==0 && (board[(y_loc-1)*x_dim + x_loc - 1] & hidden_mask())){
                board[(y_loc-1)*x_dim + x_loc - 1] -= hidden_mask();
            }
            if(y_loc!=0 && x_loc!=(x_dim-1) && (board[(y_loc-1)*x_dim + x_loc + 1] & marked_mask())==0 && (board[(y_loc-1)*x_dim + x_loc + 1] & hidden_mask())){
                board[(y_loc-1)*x_dim + x_loc + 1] -= hidden_mask();
            }
            if(y_loc!=(y_dim-1) && (board[(y_loc+1)*x_dim + x_loc] & marked_mask())==0 && (board[(y_loc+1)*x_dim + x_loc] & hidden_mask())){
                board[(y_loc+1)*x_dim + x_loc] -= hidden_mask();
            }
            if(y_loc!=(y_dim-1) && x_loc!=0 && (board[(y_loc+1)*x_dim + x_loc - 1] & marked_mask())==0 && (board[(y_loc+1)*x_dim + x_loc - 1] & hidden_mask())){
                board[(y_loc+1)*x_dim + x_loc - 1] -= hidden_mask();
            }
            if(y_loc!=(y_dim-1) && x_loc!=(x_dim-1) && (board[(y_loc+1)*x_dim + x_loc + 1] & marked_mask())==0 && (board[(y_loc+1)*x_dim + x_loc + 1] & hidden_mask())){
                board[(y_loc+1)*x_dim + x_loc + 1] -= hidden_mask();
            }
        }
        return 0; 
    }
}
