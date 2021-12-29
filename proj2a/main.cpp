/*
 * Proj:      Flip-a
 * Team:      3-AndBoiOsw
 * File:      main.cpp
 * Descr:     declares deck and will operate gameplay.  primary file to compile.
 */

#include <stdlib.h>
#include <iostream>
#include "deck.h"
#include "card.h"
#include "d_node.h"

using namespace std;
/*
    The main function creates a deck of cards and shuffles it 3 times,
    and then prompts the user to play the game.
*/
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


    return 0;
}


// unicode symbols:
// ♦♥♣♠ + ♡♢♤♧
