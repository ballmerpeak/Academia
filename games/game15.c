#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

void print_table(int *numbers_ptr);
void random_shuffle(int *numbers_ptr);
void swap_variables(int *numbers_ptr, int user_input2);
int compare_arrays(int *numbers_ptr);

int main(void)
{
	//0 in numbers[] will represent an empty space
	int numbers[16] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0};
	int *numbers_ptr;
	int user_input2 = 0;	//user input after sanity check
	char user_input[10];	//user input originally
	
	numbers_ptr = numbers;
	
	srand(time(NULL));				//Seed: Timer to avoid repetitions@runtime
	random_shuffle(numbers_ptr);	//Shuffle numbers[]
	printf("Let's start a game!\n");
	print_table(numbers_ptr);
	
	while(1)
	{
		printf("Enter a number: ");
		fflush(stdout);
		fgets(user_input, sizeof user_input, stdin);
		sscanf(user_input, "%d", &user_input2);
		

		if(isdigit(*user_input)) {
			swap_variables(numbers_ptr, user_input2);
			print_table(numbers_ptr);
			
			if(compare_arrays(numbers_ptr) == EXIT_SUCCESS) {
				printf("Congratulations. You have completed the game!\n");
				break;
			}
		
		}
		
		else if(*user_input == 'q')
			break;
		
		else 
			printf("You did not enter a number!\n");
	}

	return(EXIT_SUCCESS);
}


void print_table(int *numbers_ptr)
{
	int i;
	for(i = 0; i < 16; i++) {
		if(numbers_ptr[i] == 0)
			printf("    ");
		else
			printf("%4d", numbers_ptr[i]);
		// i+1 fixes computations for formatting purposes
		if((i + 1) % 4 == 0)
			printf("\n");
	}
}


void swap_variables(int *numbers_ptr, int user_input2)
{
	int i,swap;
	int loc1,loc2; //Store indexes that need swapping
					// loc1 is 0 and loc2 is the user input.
	
	for(i = 0; i < 16; i++) {
		if(numbers_ptr[i] == 0)
			loc1 = i;
		else if(numbers_ptr[i] == user_input2)
			loc2 = i;
	}
	// Make sure you can swap only with contigous numbers
	if(loc2+1 == loc1 || loc2-1 == loc1 || loc2 + 4 == loc1 || loc2-4 == loc1){
		swap = numbers_ptr[loc1];
		numbers_ptr[loc1] = numbers_ptr[loc2];
		numbers_ptr[loc2] = swap;
	} else
		printf("That move is not allowed\n");
}

void random_shuffle(int *numbers_ptr)
{
    /* TODO: Fix function so that only solvable games are generated */
	int i;
	int swaping_index,swap;

	for(i = 0; i < 16; i++) {
		swaping_index = (rand() % 15) + 1; //Choose an index randomly
		swap = numbers_ptr[i];
		numbers_ptr[i] = numbers_ptr[swaping_index];
		numbers_ptr[swaping_index] = swap;
	}
}

int compare_arrays(int *numbers_ptr)
{
	int numbers_final[16] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0};
	int i;
	for(i = 0; i < 16; i++) {
		if(numbers_final[i] != numbers_ptr[i])
			return(1);
	}
	return(EXIT_SUCCESS);
}
