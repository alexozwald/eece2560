/* upd
Proj:      MasterMind-a
Team:      3-AndBoiOsw
File:      code.h
Descr:     Implements the constructor and destructor of the code class,
           and the declarations and implementations for the guessCorrect,
           guessIncorrect, welcome, guess, print, and randomize functions
*/

//#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#ifndef code_h
#define code_h

/*
 Initializes the class for the guess and secret codes of numbers to be used
 in the MasterMind game.
 */
class code
{
public:
    // constructors
    code(int setN, int setM);   // custom game
    code();                     // default game

    // set values
    void set(int setN, int setM);
    // get values
    int get(char item);

    // access code for mastermind.printSecret()
    vector<int> getSecret() const;
    void setSecret(vector<int> newSecret);

    // generate random code
    void secretInit();

    // checks how many integers are in the correct location
    int checkCorrect(code& guess);

    // checks how many integers are in the incorrect location
    int checkIncorrect(code& guess);

    // runs checkIncorrect and checkCorrect and prints result
    void checkGuess(code& guess, int guesses);

private:
    vector<int> secret;
    int n;
    int m;
};

// constructor: custom game
code::code(int setN, int setM)
{
    set(setN, setM);
}
// constructor: default game
code::code()
{
    set(5, 10);
}

// set values
void code::set(int setN, int setM)
{
    n = setN;
    m = setM;
}
// get values
int code::get(char item)
{
    if (item == 'n')  { return n; }
    else if (item == 'm') { return m;}
    else { return 0; }
}

// access secret code for mastermind.printSecret()
vector<int> code::getSecret() const
{
    return secret;
}
// sets secret code for guesses
void code::setSecret(vector<int> newSecret)
{
    secret = newSecret;
}

// generate random secret code
void code::secretInit()
{
    // loop to each random int in bounds [0,m-1]
    for(int i=0;i<n;i++){
        secret.push_back(rand()%m);
    }
}

/*
 *  Prints the amount of digits that the user guessed
 *  exactly correct, meaning that it was in the right
 *  location and the right digit of the secret code.
 */
int code::checkCorrect(code& guess)
{
    int tally = 0;
    // loop to check exact placement
    for(int i=0; i<n; i++){
        if(guess.getSecret()[i] == getSecret()[i]) { tally++; }
    }
    
    return tally;
}

int code::checkIncorrect(code& guess)
{
    int tally = 0;
    //References of the code so the actual codes aren't altered
    vector<int> userGuessRef = guess.getSecret();
    vector<int> secretRef = getSecret();
    //Runs through two loops that for the entire length of the guess vectors
    for(int i=0; i<secretRef.size(); i++)
    {
        for(int j=0; j<secretRef.size(); j++)
        {
            if (userGuessRef[i] = secretRef[j])
            {
                //Changes values of the vector if they are the same to avoid
                //overlap in judgement, set to -1 to make sure of this
                if(i == j)
                {
                    userGuessRef[i] = -1;
                    secretRef[j] = -1;
                    j = secretRef.size(); //Skips to end of loop
                }
                else
                {
                    //Only works if both values are not in the same position
                    if(userGuessRef[i] != secretRef[i] && userGuessRef[j] != secretRef[j])
                    {
                        userGuessRef[i] = -100;
                        secretRef[j] = -100;
                        tally++; //Increments the tally because this case works
                        j = secretRef.size(); //Skips to end of loop
                    }
                }
            }
        }
    }
    return tally;
}

// runs checkIncorrect and checkCorrect and prints result
void code::checkGuess(code& guess, int guesses)
{
    string g = "[try" + to_string(guesses) + "] You guessed ";
    cout << g << checkCorrect(guess)   << " digits in the correct spot";
    cout << g << checkIncorrect(guess) << " digits in the incorrect spot";
}

#endif /* code_h */
