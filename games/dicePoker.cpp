/*
 *	Game: Poker dice
 *	Rules: 5 dices, 3 rolls,
 *	allowed to keep dices
 *	between rolls.
 *	2 players.
 *	
 **/

#include <iostream> 
#include <cstdlib>	// to use EXIT_SUCCESS
#include <sstream>	// for converting string to number
#include <time.h>	// using it to seed rand
#include <stdlib.h>	// rand uses this library
#include <string>
#include <vector>
#include <algorithm> // to use count
#include <iterator> // for converting string to number


using namespace std;

void num_to_letters(int);
void roll_dices(int *dice_ptr, int pass_roll);
void save_numbers(int *dice_ptr, int *c_ptr, int iter, int cards_left);
void determine_winner(const vector <int>& hand_pl1, const vector <int>& hand_pl2);
int high_card(int, int, int, int *, int *);
bool sort_hands (int x,int y) { return (x<y); }

int main(void) 
{
	vector <int> hand_pl1; 	// store player 1 hand
	vector <int> hand_pl2;	// store player 2 hand 
	int i, i2;
	int pass_roll = 0;	// pass roll_dices: 5 - hand_pl{1,2}.size
	int current[5];		// current hand after function save_numbers
	int *c_ptr;			// pointer to current[]
	int dice[6];		// 1 = A; 2 = K; 3 = Q; 4 = J; 5 = 10; 6 = 9
	int saving_status;	// card picking sanitazer
	int *dice_ptr;		// pointer to dice[] 
	dice_ptr = dice;	// make dice_ptr point to &dice[0]
	c_ptr = current;	// make c_ptr point to &current[0]
	srand(time(NULL)); 	// seed: timer to avoid repetitions@runtime


	for(i = 0; i < 3; i++) {
		
		// Player 1 iterations
		pass_roll = 5 - hand_pl1.size();
		if(pass_roll > 0) {
			cout << endl << "Player 1 roll: ";
			roll_dices(dice_ptr, pass_roll);
			// To show chosen cards
			if(hand_pl1.size() > 0) {
				cout << "\nYou've chosen: ";
					for(i2 = 0;i2 < hand_pl1.size(); i2++) 
						num_to_letters(hand_pl1[i2]);	
			}
			save_numbers(dice_ptr, c_ptr, i, hand_pl1.size());

			i2 = 0; 
			// Save chosen cards in hand of pl1
			// iterate until current[] ends
			while((current[i2] <= 6) && (current[i2] > 0)) {
				hand_pl1.push_back (current[i2]);
				i2++;
			}
		}
		
		//Player 2 iterations
		pass_roll = 5 - hand_pl2.size();
		if(pass_roll > 0) {
			cout << endl;
			cout << endl << "Player 2 roll: ";
			roll_dices(dice_ptr, pass_roll);
			// To show chosen cards
			if(hand_pl2.size() > 0) {
				cout << "\nYou've chosen: ";
					for(i2 = 0;i2 < hand_pl2.size(); i2++) 
						num_to_letters(hand_pl2[i2]);
			}
			save_numbers(dice_ptr, c_ptr, i, hand_pl2.size());
		
			i2 = 0; 
			// Save chosen cards in hand of pl2
			// iterate until current[] ends
			while((current[i2] <= 6) && (current[i2] > 0)) {
				hand_pl2.push_back (current[i2]);
				i2++;
			}
		cout << endl;
		}
	}	// End of players iterations	


	//sort hands
	sort(hand_pl1.begin(), hand_pl1.end(), sort_hands);
	sort(hand_pl2.begin(), hand_pl2.end(), sort_hands);
	//determine winner
	determine_winner(hand_pl1, hand_pl2);
	cout << endl;
	return EXIT_SUCCESS;
}

void num_to_letters(int numbers) 
{
	switch(numbers) {
		case 1:	cout << "A ";
			break;
		case 2:	cout << "K ";
			break;
		case 3:	cout << "Q ";
			break;
		case 4:	cout << "J ";
			break;
		case 5:	cout << "10 ";
			break;
		case 6:	cout << "9 ";
			break;
		default:
			break;
	}
}

void roll_dices(int *dice_ptr, int pass_roll) 
{ 
	
	int i;
	for(i = 0; i < 6; i++)
		dice_ptr[i] = 0;

	for(i = 0; i < pass_roll; i++) {
		dice_ptr[i] = (rand() % 6) + 1;
		num_to_letters(dice_ptr[i]);
	}
}


void save_numbers(int *dice_ptr, int *c_ptr, int iter, int cards_left) 
{
	
	int i, i2, i3;
	int my_count;
	int input_validator = 0; // zero if input is valid
	int number_counter = 0;
	int counter[6] = {0};
	int counter2[6] = {0};
	vector <int> input2; // user input as numbers
	string input; // user input

	// Initialize to 0 
	for(i = 0; i < 5; i++) 
		c_ptr[i] = 0; 	
	
	cout << endl << "Number(s) to save: "; 
	getline(cin, input);
	
	// replace a,k,q,j,10,9 with their 
	// respective numerical value
	for(i = 0; i < input.length(); i++) {
		switch(input[i]) {
			case 'a':
			case 'A':
				input.replace(i,1,"1");
				break;
			case 'k':
			case 'K':
				input.replace(i,1,"2");
				break;
			case 'q':
			case 'Q':
				input.replace(i,1,"3");
				break;
			case 'j':
			case 'J':
				input.replace(i,1,"4");
				break;
			case '9':
				input.replace(i,1,"6");
				break;
			default:
				break;
		}
		if(input[i] == '1' && input[i + 1] == '0')
			input.replace(i,2,"5");
	}
	
	// check if input is valid
	for(i = 0; i < input.length(); i++) {
		
		switch(input[i]) {
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
				number_counter++;	
				break;
			case ' ':
				break;
			default:
				input_validator++;
				break;
		}
	}
	
	
	if((input_validator == 0) && (number_counter > 0)) {
		
		istringstream c(input);	// copy input as numbers in input2
		copy(istream_iterator<int>(c), istream_iterator<int>(), back_inserter(input2));
	
		// get availability of x in counter[x-1]
		for(i = 0; i < 6; i++) {
			my_count = (int) count (dice_ptr, dice_ptr+6, i+1);
			counter[i] = my_count;
		}
		
		// get final stage of input
		i3 = 0;
		for(i = 0; i < 6; i++) {
			my_count = (int) count (input2.begin(), input2.end(), i + 1);
			counter2[i] = my_count;	
			while(counter2[i] > 0) {
				if(counter[i] > 0) {
					if(i3 < 5)
						c_ptr[i3] = i + 1;
					i3++;
					counter2[i]--;
					counter[i]--;
				} else 
					break;
			}
		}
	} 
	
	// If user presses enter and doesn't give any number	
	else if(number_counter == 0 && input_validator == 0) {
		for(i = 0; i < 6; i++) {
			my_count = (int) count (dice_ptr, dice_ptr+6, i + 1);
			counter[i] = my_count;
		}
	
	} else 
		cout << "Invalid input\n";
		
	//for(i=0;i<6;i++){cout<<"::::"<<counter2[i];}
	
	int temp = 0;
	temp = 5 - (input2.size() + cards_left);
	// pick dices for player if player 
	// is missing dices in the last iteration
	if(iter == 2 && temp > 0) {
		i3 = 0;
		for(i = 0; i < temp; i++) {
			for(i2 = 0; i2 < 5; i2++) {
				if(c_ptr[i2] == 0) {
					for(i3 = 0; i3 < 6; i3++) {
						if(counter[i3] > 0) {
							c_ptr[i2] = i3 + 1;
							counter[i3]--;
							break;
						}
					}
					break;	
				}
			}
		}
	}
}


void determine_winner(const vector <int>& hand_pl1, const vector <int>& hand_pl2) 
{

/*
 * five of a kind 	= 9 points +
 * four of a kind 	= 8 points +
 * full house 		= 7 points +
 * straight 		= 6 points - 
 * Check rules of game, 
 * there are no str8s
 *
 * three of a kind 	= 5 points +
 * two pairs 		= 4 points +
 * one pair 		= 2 points +
 * high card 		= 0 points + 
 *
 */

	int i, my_count, winner;
	// pl[0] = Player 1
	// pl[1] = Player 2
	int points_pl[2];
	int count_pl1[6], count_pl2[6];
	int highest_card1, highest_card2;
	
	i = winner = 0;
	points_pl[0] = points_pl[1] = 0;
	highest_card1 = highest_card2 = 0;
	
	// high_card() variables
	int *count_pl1ptr;
	int *count_pl2ptr;
	int pl1points;
	count_pl1ptr = count_pl1;
	count_pl2ptr = count_pl2;

	// Initialize counters to 0
	for(i = 0; i < 6; i++) {
		count_pl1[i] = 0;
		count_pl2[i] = 0;
	}

	// get count of numbers 1 through 6 in hand of player
	// to check for repetitions later
	// count_pl[dice number] = how many repetitions;
	for(i = 0; i < 6; i++) {
		my_count = (int) count (hand_pl1.begin(), hand_pl1.end(), i + 1);
		count_pl1[i] = my_count;
		
		my_count = (int) count (hand_pl2.begin(), hand_pl2.end(), i + 1);
		count_pl2[i] = my_count;
	}
	
	// assign points
	for(i = 0; i < 6; i++) {
		// five of a kind
		if(count_pl1[i] == 5) {
			points_pl[0] = 9;
			highest_card1 = i;
		}
		if(count_pl2[i] == 5) {
			points_pl[1] = 9;
			highest_card2 = i;
		}
		
		// four of a kind
		if(count_pl1[i] == 4) {
			points_pl[0] = 8;
			highest_card1 = i;
		}
		if(count_pl2[i] == 4) {
			points_pl[1] = 8;
			highest_card2 = i;
		}
		
		// three of a kind
		if(count_pl1[i] == 3) {
			points_pl[0] += 5;
			highest_card1 = i;
		}
		if(count_pl2[i] == 3) {
			points_pl[1] += 5;
			highest_card2 = i;
		}
		
		// one pair
		if(count_pl1[i] == 2)
			points_pl[0] += 2;
		if(count_pl2[i] == 2)
			points_pl[1] += 2;
	}
	
	// high_card() variable
	pl1points = points_pl[0];
	cout << endl << endl;	
	
	//////////////////////////////
	////   DETERMINE WINNER   ///
	////////////////////////////
	
	if(points_pl[0] > points_pl[1]) 
		winner = 1;
	
	else if(points_pl[0] < points_pl[1]) 
		winner = 2;
	
	else 
		winner = high_card(highest_card1, highest_card2, pl1points, count_pl1ptr, count_pl2ptr);
	
	
	if(winner == 1 || winner == 2) {
		
		cout << "Player " << winner << " WINS !!! (";
		// winner-1 to match with pl[0] and pl[1]
		switch(points_pl[winner - 1]) {
			case 0: cout << "high cards)\n";
				break;
			case 2: cout << "one pair)\n";
				break;
			case 4: cout << "two pairs)\n";
				break;
			case 5: cout << "three of a kind)\n";
				break;
			case 7: cout << "full house)\n";
				break;
			case 8: cout << "four of a kind)\n";
				break;
			case 9: cout << "five of a kind)\n";
				break;
			default:
				break;
		}
	}
		
	cout << endl << "Player's 1 hand: ";
	for(i = 0;i < hand_pl1.size(); i++) 
		num_to_letters(hand_pl1[i]);
	cout << endl;
	cout << "Player's 2 hand: ";
	for(i = 0;i < hand_pl2.size(); i++)
		num_to_letters(hand_pl2[i]);
	cout << endl;
}

int high_card(int highest_card1, int highest_card2, int pl1points, int *count_pl1ptr, int *count_pl2ptr) 
{
	
	int i = 0;

	switch(pl1points) {
		case 0: // high card
			for(i = 0; i < 6; i++) {
				if((count_pl1ptr[i] == 1) && (count_pl1ptr[i] > count_pl2ptr[i]))  
					return 1; 
		
				if((count_pl2ptr[i] == 1) && (count_pl2ptr[i] > count_pl1ptr[i]))
					return 2; 
				
				if(i == 5)
					cout << "It is a tie!\n";
			}
			break;
		
		case 2: // one pair
		case 4: // two pairs
			for(i = 0; i < 6; i++) {
				if((count_pl1ptr[i] == 2) && (count_pl1ptr[i] > count_pl2ptr[i]))
					return 1; 
				
				if((count_pl2ptr[i] == 2) && (count_pl2ptr[i] > count_pl1ptr[i]))
					return 2; 
				
				if(i == 5)
					cout << "It is a tie!\n";
				
			} break;
		
		case 7: // full house
			if(highest_card1 < highest_card2)
				return 1;
			
			else if(highest_card2 < highest_card1)
				return 2;
			
			else {
				for(i = 0; i < 6; i++) {
					if((count_pl1ptr[i] == 2) && (count_pl1ptr[i] > count_pl2ptr[i]))
						return 1;
									
					if((count_pl2ptr[i] == 2) && (count_pl2ptr[i] > count_pl1ptr[i]))
						return 2;
				
					if(i == 5)
						cout << "It is a tie!\n";
				}
			} break;
	
		case 5: // three of a kind
		case 8: // four of a kind
		case 9: // five of a kind
			if(highest_card1 < highest_card2)
				return 1;
			
			else if(highest_card1 > highest_card2)
				return 2;
			
			else
				cout << "It is a tie!\n";
			break;
		
		default: 
			break;
	}
}
