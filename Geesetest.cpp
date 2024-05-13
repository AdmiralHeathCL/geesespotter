#include "geesespotter_lib.h"
#include <iostream>

char *create_board(std::size_t x_dim, std::size_t y_dim){
	int mat{st::size_t x_dim*st::size_t y_dim};
	char arr[mat]{};
	for(int i{0};i<x_dim;i++){
		for(int j(0);j<y_dim;j++){
			arr[i*x_dim + j] = 0;
		}
	}
	return arr;
}




void clean_board(char *board);

void print_board(char *board, std::size_t x_dim, std::size_t y_dim);

void hide_board(char *board, std::size_t x_dim, std::size_t y_dim);

int mark(char *board, std::size_t x_dim, std::size_t y_dim, std::size_t x_loc, std::size_t y_loc);

void compute_neighbours(char *board, std::size_t x_dim, std::size_t y_dim);

bool is_game_won(char *board, std::size_t x_dim, std::size_t y_dim);

int reveal(char *board, std::size_t x_dim, std::size_t y_dim, std::size_t x_loc,
std::size_t y_loc);
