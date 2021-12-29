/* upd
 Proj:      MasterMind-B
 Team:      3-AndBoiOsw
 File:      mastermind.h
 Descr:     Implements the constructor and destructor of the code class,
            and the declarations and implementations for the guessCorrect,
            guessIncorrect, welcome, guess, print, and randomize functions
*/

#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include "code.h"
#include "response.h"

using namespace std;

#ifndef mastermind_h
#define mastermind_h

/*
 Initializes the class for handling the playing of the game and all
 the function that take in human guesses, return reponses, and determine
 the amount of correct and incorrect guesses for each player response.
 */
class mastermind 
{
public:
    //Base constructors
    mastermind(int n = 5, int m = 10);   // custom game
    mastermind();               // default game

    //Function that prints the secret code
    void printSecret();

    //Function that takes in a human guess
    code humanGuess();

    //Function that passes in the human guess and gets a response
    response getResponse(code &guess, code &secret);

    //Function that determines whether the board is solved
    bool isSolved(response responseObj);

    //initializes random code + controls gameplay
    int playGame();

private:
    //Code object as a data member
    code codee;
    int guesses;
};

// constructor: initializes with default settings
mastermind::mastermind()
{
    code codee;
    codee.set(5, 10);
    codee.secretInit();
}
// constructor: initializes with custom settings
mastermind::mastermind(int n, int m)
{
    code codee;
    codee.set(n, m);
    codee.secretInit();
}

//Reads in a human guess 
code mastermind::humanGuess()
{
    code guess(codee.get('n'),codee.get('m'));
    int input;
    vector<int> guessvect;

    string g = "[try" + to_string(guesses) + "] ";
    cout << g << "Guess the code (spaced): ";

    for (int i=0; i<codee.get('n'); i++)
    {
        cin >> input;
        guessvect.push_back(input);
    }
    guess.setSecret(guessvect);
    return guess;
}

//Prints the secret code
void mastermind::printSecret()
{
    vector<int> secret = codee.getSecret();
    cout << "The secret code was (";
    
    cout << codee.getSecret()[0];
    if (secret.size() > 1)
    {
        for(int i=1; i<codee.get('n'); i++) {
            cout << ',' << codee.getSecret()[i];
        }
    }
    cout << ")." << endl;
}

// Compares the two codes and gets the response using the code functions
// and setting the new correct and incorrect variables
response mastermind::getResponse(code &guess, code &secret)
{
    response userResponse; //New response
    //Sets new correct and incorrect values
    userResponse.setCorrect(secret.checkCorrect(guess));
    userResponse.setIncorrect(secret.checkIncorrect(guess));
    return userResponse;
}

//Returns whether the game has been solved yet
bool mastermind::isSolved(response userResponse)
{
    //Returns true if the number of correct guesses is equal
    //to the size of the secret code
    bool solved = userResponse.getCorrect() == codee.get('n');
    return solved;
}

int mastermind::playGame()
{
    // part 1
    // declare data member

    cout << "Welcome to Mastermind!" << endl;
    //     
    cout << "Code length: " << codee.get('n') << ".  Code range: [0," << codee.get('m')-1 << "]." << endl << endl;

    //Generate and print the secret code
    codee.secretInit();
    printSecret();
    
    //Makes variables to store player guesses and the subsequent response
    code playerGuess;
    response playerResponse;

    //Allows the user to guess no more than 10 times
    for (int i = 0; i < 10; i++)
    {
        //Allows user to guess
        playerGuess = mastermind::humanGuess();
        //Determines amount of correct and incorrect guesses
        playerResponse = getResponse(playerGuess, codee);
        cout << playerResponse << endl;

        if (isSolved(playerResponse))
        {
            cout << "You have guessed correctly and won the game!";
            i = 10; //Ends the loop
        }
        else
        {
             //Keeps going if wrong
            cout << "Incorrect, please guess again" << endl;
        }
    }
    return 0;
}

#endif /* mastermind_h */
