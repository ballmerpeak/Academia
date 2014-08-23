#include "libs/colors.h"

#include <stdio.h>
#include <stdlib.h> // EXIT_* macros, srand(), rand(), system()
#include <ctype.h> // isdigit()
#include <time.h>
#include <stdbool.h> // Boolean stuff

#define INDEX_SIZE 16

void print_table(int* numbers_ptr);
void random_shuffle(int* numbers_ptr);
void swap_variables(int* numbers_ptr, int user_input2);
bool swap_valid_number(int loc1, int loc2);
bool array_in_order(int* numbers_ptr);

int main(void)
{
	// Zero in the array represents an empty space
	int numbers[INDEX_SIZE] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0};
	int *numbers_ptr;    // A pointer to the numbers[] array
	int user_input2 = 0; // User input after sanity check
	char user_input[10]; // User input originally

	numbers_ptr = numbers;

	srand(time(NULL));				//Seed: Timer to avoid repetitions@runtime
	random_shuffle(numbers_ptr);	//Shuffle numbers[]

	while(1) {
        print_table(numbers_ptr);
		fflush(stdout);
		fgets(user_input, sizeof(user_input), stdin);
		sscanf(user_input, "%d", &user_input2);

		if (isdigit(*user_input)) {
			swap_variables(numbers_ptr, user_input2);
			/* print_table(numbers_ptr); */

			if (array_in_order(numbers_ptr)) {
				printf("Congratulations. You have completed the game!\n");
				break;
			}
		}

		else if (*user_input == 'q')
			break;
		else
			printf("You did not enter a number!\n");
	} // End of while(1) loop
	return EXIT_SUCCESS;
}

void print_table(int *numbers_ptr) {
    /* system("clear"); */
	printf("Let's start a game!\n");
	int i;
	for(i = 0; i < INDEX_SIZE; i++) {
		if (numbers_ptr[i] == 0)
			printf("    ");
        else if (numbers_ptr[i] == i + 1) {
            printf("%s", color_green);
			printf("%4d", numbers_ptr[i]);
            printf("%s", color_reset);
        } else
			printf("%4d", numbers_ptr[i]);
		// i+1 fixes computations for formatting purposes
		if ((i + 1) % 4 == 0)
			printf("\n");
	}
    printf("Enter a number: ");
}

void random_shuffle(int *numbers_ptr) {
    // Perform the shuffle between a randomly
    // selected num on the rage [50, 100]
    int i = 0, i2 = 0;
    int zeros_index, swap;
    int rand_num = 50 + rand() % 50;
    int rand_num2 = 0;

    for (; i < rand_num; ++i) {
        // Update zeros_index
        for (i2 = 0; i2 < INDEX_SIZE; ++i2) {
            if (numbers_ptr[i2] == 0)
                zeros_index = i2;
        }
        // Update rand_num2
        rand_num2 = 1 + rand() % 15;
        // Get a random contiguous number. The var rand_num2, if valid, is the index
        // of the array that is contiguous to the index where the value 0 is located at
        if (swap_valid_number(zeros_index, rand_num2)) {
            /*********************/
            /* Code for swapping */
            /*********************/
            swap = numbers_ptr[zeros_index];
            numbers_ptr[zeros_index] = numbers_ptr[rand_num2];
            numbers_ptr[rand_num2] = swap;
        }
    }
}

void swap_variables(int *numbers_ptr, int user_input2) {
	int i, swap;
    // zeros_index is for storing the index where 0 is found
    // inputs_index is for the index where user_input2 is found
	int zeros_index, inputs_index;

    // Grab the indexes for number 0 and user_input2
	for (i = 0; i < INDEX_SIZE; i++) {
		if (numbers_ptr[i] == 0)
			zeros_index = i;
		else if (numbers_ptr[i] == user_input2)
			inputs_index = i;
	}

	// Make sure you can swap only with contigous numbers
	if (swap_valid_number(zeros_index, inputs_index)) {
		swap = numbers_ptr[zeros_index];
		numbers_ptr[zeros_index] = numbers_ptr[inputs_index];
		numbers_ptr[inputs_index] = swap;
	} else
		printf("That move is not allowed\n");
}

bool swap_valid_number(int zero, int input) {
    if (input < 0 && input > INDEX_SIZE)
        return false;
	// Make sure you can swap only with contigous numbers
	if (input+1 == zero || input-1 == zero || input + 4 == zero || input-4 == zero) {
        /* printf("%d +1/-1/+4/-4 = %d\n", input, zero); */
        return true;
    } else
        return false;
}

// Determine if the game has been successfully completed
bool array_in_order(int *numbers_ptr) {
	int numbers_final[INDEX_SIZE] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0};
	int i;
	for (i = 0; i < INDEX_SIZE; i++) {
		if (numbers_final[i] != numbers_ptr[i])
			return false;
	}
	return true;
}
