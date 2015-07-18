#!/usr/bin/python
#-*- coding: utf-8 -*-
# TODO: make curses and qt version
#       what if dict file has uppercase?

import random
import re
import linecache

def hang_man_ascii():

    print("Welcome to hangman, please try guessing the word I'm thinking")
    print("""
        ________________
       |/              |
       |              (_)
       |              \|/
       |               |
       |              / \\
       |
    ___|___ 
    """)

def initialize_output_word(word):
    tmp_word = ""
    for i in range(len(word)):
        tmp_word = tmp_word + "_"
    return(tmp_word)

def valid_input(secret_word, given_letters):
    while True:
        # Get input from user, and make it lowercase for case
        # insensitivity
        input_letter=input("Please give me a letter: ").lower()
        # If user guesses the secret_word correctly
        if(secret_word == input_letter):
            return input_letter
        # If user gives us more than one letter
        elif(len(input_letter) != 1):
            print("Try writing just one letter at a time")
        # If user gives us a letter he already gave us
        elif(given_letters.find(input_letter) != -1):
            print("You already tried that letter!")
        # If user gives us a valid letter
        elif(len(input_letter) == 1 and input_letter.isalpha()):
            return input_letter
        else:
            print("The character you wrote is not valid, please try again")

def generate_secret_word():
    lines = 0
    try:
        dictionary_file = open("hangman.txt", "rt")
        for line in dictionary_file:
            lines += 1
        dictionary_file.close()
        random_number = random.randint(1, lines)
        random_line = linecache.getline('hangman.txt', random_number)
        return random_line.rstrip()
    except IOError:
        print("A secret word could not be chosen.")
        return "Error"
    
# Initialize variables
secret_word = generate_secret_word()
try:
    tries = 0
    given_letters = ""
    given_word = list(initialize_output_word(secret_word))
    displayed_word = ''.join(given_word)
except TypeError:
    print("Cannot keep executing program, closing.")

while (secret_word != "Error"):
    hang_man_ascii()
    print(" ".join(displayed_word))
    print("So far you've tried:", given_letters)
    input_letter = valid_input(secret_word, given_letters)
    
    # If user gives us just one letter
    if(len(input_letter) == 1):
        # Look for matches of the given word in our secret word
        matches = [m.start() for m in re.finditer(input_letter, secret_word)]
        # Change _ for given letter, if the letter is found
        # in secret_word
        for i in matches:
            given_word[i] = str(input_letter)
        displayed_word = ''.join(given_word)
        given_letters += str(input_letter)
    # If user gives us the secret_word
    else:
        displayed_word = input_letter    
    
    # Check if the player has won the game
    if(secret_word == displayed_word):
        print("Congratulations, you won the game")
        break
    if(len(matches) == 0):
        tries += 1
    if(tries >= 9):
        print("You lose, you've tried too many times")
        print("The word was: ", secret_word)
        break
