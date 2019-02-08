/*
 * =====================================================================================
 *
 *       Filename:  direction.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  17/01/2019 13:19:21
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jonathan Matthews
 *	    Email:  jonathanpetermatthews@protonmail.com
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

size_t size = 1;
size_t * map = NULL;


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  remap
 *  Description:  
 * =====================================================================================
 */
size_t * remap (size_t * map)
{
	size = size + 2;
	size_t * new_map = calloc(size * size, sizeof(size_t));
	size_t y = 1;
	while (y < size - 1) {
		size_t x = 1;
		while (x < size - 1) {
			*(new_map + (y * size) + x) = *(map + ((y - 1) * (size - 2)) + (x - 1));
			x++;
		}
		y++;
	}
	return new_map;
}		/* -----  end of function remap  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
int main ( int argc, char *argv[] )
{
	if (argc != 2) {
		return 1;
	}
	size_t input_length = strlen(argv[1]) + 1;
	char input[input_length];
	strncpy(input, argv[1], input_length);
	map = calloc(size, sizeof(size_t));
	size_t i = 0;
	map[0] = 1;
	size_t one_current_x_pos = 0;
	size_t one_current_y_pos = 0;
	size_t two_current_x_pos = 0;
	size_t two_current_y_pos = 0;
	while (i < input_length - 1) {
		if (i % 2 == 0) {
			if (input[i] == '>') {
				if (one_current_x_pos + 1 >= size) {
					size_t * old_map = map;
					map = remap(old_map);
					free(old_map);
					one_current_x_pos = size - 2;
					one_current_y_pos++;
					two_current_x_pos++;
					two_current_y_pos++;
				}
				one_current_x_pos++;
				*(map + (one_current_y_pos * size) + one_current_x_pos) = 1;
			}
			else if (input[i] == 'v') {
				if (one_current_y_pos + 1 >= size) {
					size_t * old_map = map;
					map  = remap(old_map);
					free(old_map);
					one_current_x_pos++;
					one_current_y_pos = size - 2;
					two_current_x_pos++;
					two_current_y_pos++;
				}
				one_current_y_pos++;
				*(map + (one_current_y_pos * size) + one_current_x_pos) = 1;
			}
			else if (input[i] == '<') {
				if (one_current_x_pos <= 0) {
					size_t * old_map = map;
					map = remap(old_map);
					free(old_map);
					one_current_y_pos++;
					one_current_x_pos = 1;
					two_current_x_pos++;
					two_current_y_pos++;
				}
				one_current_x_pos--;
				*(map + (one_current_y_pos * size) + one_current_x_pos) = 1;
			}
			else {
				if (one_current_y_pos <= 0) {
					size_t * old_map = map;
					map = remap(old_map);
					free(old_map);
					one_current_x_pos++;
					one_current_y_pos = 1;
					two_current_x_pos++;
					two_current_y_pos++;
				}
				one_current_y_pos--;
				*(map + (one_current_y_pos * size) + one_current_x_pos) = 1;
			}
		}
		else {
			if (input[i] == '>') {
				if (two_current_x_pos + 1 >= size) {
					size_t * old_map = map;
					map = remap(old_map);
					free(old_map);
					two_current_x_pos = size - 2;
					two_current_y_pos++;
					one_current_x_pos++;
					one_current_y_pos++;
				}
				two_current_x_pos++;
				*(map + (two_current_y_pos * size) + two_current_x_pos) = 1;
			}
			else if (input[i] == 'v') {
				if (two_current_y_pos + 1 >= size) {
					size_t * old_map = map;
					map  = remap(old_map);
					free(old_map);
					two_current_x_pos++;
					two_current_y_pos = size - 2;
					one_current_x_pos++;
					one_current_y_pos++;
				}
				two_current_y_pos++;
				*(map + (two_current_y_pos * size) + two_current_x_pos) = 1;
			}
			else if (input[i] == '<') {
				if (two_current_x_pos <= 0) {
					size_t * old_map = map;
					map = remap(old_map);
					free(old_map);
					two_current_y_pos++;
					two_current_x_pos = 1;
					one_current_x_pos++;
					one_current_y_pos++;
				}
				two_current_x_pos--;
				*(map + (two_current_y_pos * size) + two_current_x_pos) = 1;
			}
			else {
				if (two_current_y_pos <= 0) {
					size_t * old_map = map;
					map = remap(old_map);
					free(old_map);
					two_current_x_pos++;
					two_current_y_pos = 1;
					one_current_x_pos++;
					one_current_y_pos++;
				}
				two_current_y_pos--;
				*(map + (two_current_y_pos * size) + two_current_x_pos) = 1;
			}
		
		}
		i++;
	}
	i = 0;
	size_t houses = 0;
	while (i < (size * size)) {
		if (*(map + i) == 1) {
			houses++;
		}
		i++;
	}
	i = 0;
	while (i < size) {
		size_t j = 0;
		while (j < size) {
			size_t value = *(map + (i * size) + j);
			if (value == 1) {
				printf("1");
			}
			else {
				printf("*");
			}
			j++;
		}
		i++;
		printf("\n");
	}
	free(map);
	printf("%zu \n", houses);
	return 0;
}				/* ----------  end of function main  ---------- */
