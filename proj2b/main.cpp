/* 
 * Proj:      Flip-a
 * Team:      3-AndBoiOsw
 * File:      main.cpp
 * Descr:     declares deck and will operate gameplay.  primary file to compile.
 */

#include <stdlib.h>
#include <iostream>
#include <vector>
#include "deck.h"
#include "card.h"

using namespace std;
/*
    The main function creates a deck of cards and shuffles it 3 times,
    and then prompts the user to play the game.
*/

//Performs the rules and functions of the game of flip
int playFlip(deck& myDeck)
{
    // list the rules!
    cout << "The rules of FlipCard:" << endl;
    cout <<    "1. The cards are shuffled three times." << endl
    << "2. The player draws 24 cards from the top of the deck, "
    << "without looking at them, and places them face down on the table." << endl
    << "3. The player can either select a card to turn over, or end the game. "
    << "If a card is turned over, the player:" << endl
    << "(a) receives 10 points for an ace," << endl
    << "(b) receives 5 points for a king, queen or jack," << endl
    << "(c) receives 0 points for an 8, 9 or 10, (d) loses half their points for a 7," << endl
    << "(e) loses all their points for a 2, 3, 4, 5 or 6, and" << endl
    << "(f) receives 1 point extra, in addition to the above, for a heart." << endl
    << "4. The goal is to end the game with the most points." << endl;

    int userChoice;             // temp var while selecting
    char keepGame;              // keep game going temp char
    double score = 0;               // game score keeping
    bool gameplay = true;       // default: game starts
    vector<card> dealtList;     // 24 standard

    //Runs while the user still wants to play the game
    while (gameplay)
    {
        // check dealt list size + re- (deal another 24? empty?)
        if (dealtList.size() == 0)
        {
            for (int i = 0; i < 24; i++)
            {
                dealtList.push_back(myDeck.deal());
            }

            cout << "Cards on table:  ";
            for (int i = 0; i < 24; i++)
            {
                cout << dealtList[i] << ", ";
            }
            cout << "\n\nRemaining cards in the deck...";
            cout << myDeck;
        }

        // Current score is displayed and user selects from laid out cards
        cout << "Your current score is: " << score << endl;
        cout << "Which card would you like to choose? (" << dealtList.size() << " left) ";
        cin >> userChoice;

        // mod of choice so input always works
        int selector = userChoice % dealtList.size();

        // tell the user what card they got
        int val = dealtList[selector].getValue();
        char suit = dealtList[selector].getSuit();
        cout << "You selected a " << val << " of " << suit << ".  ";

        // Case statement based on value of the current card
        switch (val)
        {
            case 1:
                score += 10;
                break;
            case 11: case 12: case 13:
                score += 5;
                break;
            case 7:
                score = score / 2;
                break;
            case 2: case 3: case 4: case 5: case 6:
                score = 0;
                break;
        }

        // Adds one to the score if it's a heart
        if (suit == 'h')  { score++; }

        // do you want to keep playing?
        cout << "Do you want to keep playing (y/n)? ";
        cin >> keepGame;
        if (keepGame == 'y') { gameplay = true; }
        else if (keepGame == 'n') { gameplay = false; }
        else { gameplay = true; }
    }
    //Returns the score of the game
    return score;
}

//Main function that shuffles the cards and initiates the game
int main()
{
    // declare deck
    deck myDeck;
    cout << "Deck successfully created!";

    // print deck
    cout << myDeck;

    // shuffle & print deck 3 times
    // shuffle deck
    myDeck.shuffle();
    // print deck again
    cout << myDeck;
    // shuffle deck
    myDeck.shuffle();
    // print deck again
    cout << myDeck;
    // shuffle deck
    myDeck.shuffle();
    // print deck again
    cout << myDeck;

    //Plays the game
    double finalScore = playFlip(myDeck);

    //Prints final score
    cout << "Your final score is: " << finalScore << endl;

    return 0;
}


// unicode symbols:
// ♦♥♣♠ + ♡♢♤♧
