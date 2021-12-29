/*
Proj:		MasterMind-a
Team:		3-AndBoiOsw
File:		card.h
Descr:		contains card declarations & implementations for gameplay.  principal
			control of card nodes.
*/

#include <ostream>
#include "d_node.h"
using namespace std;

#ifndef card_h
#define card_h

/*
	Card class that initializes an individual card in the deck of the game.
	Provides get and set functions for the suit and value of the card.
	Provides an overloaded operator to print out the individual cards.
*/
class card
{
public:
	// Constructor
	card();
	card(int v, char s);
    //Copy Constructor
    card(const card &copy);
	// Set and get functions for the private variables
	void setValue(int val);
	void setSuit(char sui);
	int getValue();
	char getSuit();
	//Overloaded << operator
	friend ostream& operator<< (ostream& ostr, card& c);
    //Overloaded assignment operator
    card& operator= (card& c);
private:
	// Private variables for the card value and suit.
	int value;
	char suit;
};

//Constructor for the card class
card::card()
{
	value = 0;
	suit = 'b';
}

//Populated constructor for the card class
card::card(int v, char s)
{
	value = v;
	suit = s;
}
//Copy constructor for the card class
card::card(const card &copy)
{
    value = copy.value;
    suit = copy.suit;
}

//Sets the value of the card
void card::setValue (int val)
{
  value = val;
}

//Sets the value for the suit
void card::setSuit (char sui)
{
  suit = sui;
}

//Gets the value of the card
int card::getValue()
{
  return value;
}

//Gets the suit for the card
char card::getSuit()
{
  return suit;
}

//Declaration of the overloaded output operator
//Prints the value and suit of the current card
ostream &operator<<(ostream &ostr, card &c)
{
	int value = c.getValue();
	char suit = c.getSuit();

	/* TABLED BC NOT ALL TERMINALS SUPPORT UNICODE CHARS
	char sweetSuit = u8'x';
	// pretty swuit formatting 
	switch (suit)
	{
		case 'c':
			sweetSuit = '♣';
			break;
		case 'd':
			sweetSuit = '♦';
			break;
		case 'h':
			sweetSuit = '♥';
			break;
		case 's':
			sweetSuit = '♠';
			break;
	}
	ostr << "(" << value << "," << sweetSuit << ")";
	*/

	// cute formatting 
	ostr << "(" << value << ",";
	if (value < 10)  { ostr << " "; }
	ostr << suit << ")";
	
	return ostr;
}

// operator that sets two cards equal to each other
card& card::operator= (card& c)
{
    // get values of card in node
    value = c.value;
    suit = c.suit;

    // create new (copied) card obj to return
    card newCard(value, suit);

    return newCard;
}

#endif	// card_h

