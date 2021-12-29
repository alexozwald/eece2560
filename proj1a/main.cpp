/*
 Proj:      MasterMind-a
 Team:      3-AndBoiOsw
 File:      main.cpp
 Descr:     Calls class-controls and manages execution of gameplay.
 */

#include <stdio.h>
#include <iostream>
#include <vector>
#include "code.h"
using namespace std;

/*
 Sample Guesses: (5, 0, 3, 2, 6),  (2, 1, 2, 2, 2),  (1, 3, 3, 4, 5))
 SAMPLE OUTPUT:

 Welcome to Mastermind!
 Do you wish to play with default settings? (y/n) y
 Defaults selected.
 Code length: 5.  Code range: [0,6].

 The secret code was (6,1,5,3,3).
 [try1] Guess the code (spaced): 5 0 3 2 6
 [try1] You guessed 0 digits in the correct spot.
 [try1] You guessed 3 digits overall.
 [try2] Guess the code (spaced): 2 1 2 2 2
 [try2] You guessed 1 digits in the correct spot.
 [try2] You guessed 1 digits overall.
 [try3] Guess the code (spaced): 1 3 3 4 5
 [try3] You guessed 0 digits in the correct spot.
 [try3] You guessed 4 digits overall.
 [try4] Guess the code (spaced): 6 1 5 3 3
 [try4] You guessed 5 digits in the correct spot.
 [try4] You guessed 5 digits overall.

 The secret code was (6,1,5,3,3).
 Congratulations! You outsmarted the mastermind!
 Program ended with exit code: 0
 */

int main()
{
    // seed random generation with current time
    srand(static_cast<unsigned int>(time(NULL)));
    
    // execute mastermind
    code x;
    x.welcome();
    x.play();
    
    return 0;
}


