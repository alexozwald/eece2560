/* 
Proj:		 MasterMind-a
Team:		 3-AndBoiOsw
File:		 deck.h
Descr:		contains deck declarations & implementations.  dependent on nodes
			and card files.
*/

#include "card.h" 
#include "d_node.h"
//#include "d_nodel.h"
using namespace std;

#ifndef deck_h
#define deck_h

/*
The deck class contains all the functions for initializing
a full deck of 52 cards, randomizing the order to be shuffled,
and an overloaded operator for printing out all the cards
*/
class deck
{
public:
	deck();							// constructor: initialize
	void shuffle();					// shuffle linked list
	node<card> * getFirst();		// return first card

	// friendly overloaded operator prints whole deck
	friend ostream& operator<< (ostream& ostr, const deck& d);

private:
	node<card> * firstCard;  	// pointer to first card in deck
	node<card> * currCard;		// pointer to the current card
};


// initialize full deck of 52 cards
// order:  club-diamond-heart-spade (1-4), ace-king (1-13)
deck::deck()
{
	// declare linked list deck
	card tempCard(1,'c');							// first (new) card is club-ace
	firstCard = new node<card> (tempCard, NULL);	 // set first card to new card
	currCard = firstCard;							// set curr card to firstCard
	
	// loop through 4 suits
	for (int i=0; i < 4; i++)
	{
	  // determine suit before card
	  char tempSuit;
	  switch (i)
	  {
		 case 0:
			 tempSuit = 'c';
			 break;
		 case 1:
			 tempSuit = 'd';
			 break;
		 case 2 :
			 tempSuit = 'h';
			 break;
		 case 3:
			 tempSuit = 's';
			 break;
		 }

	  // loop through 13 cards per suit
	  for (int j=0; j < 13; j++)
	  {
		 // if first card --> skip
		 if (i==0 && j==0) { continue; }
		 // set cards
		 card newCard(j+1,tempSuit);
		 currCard->next = new node<card> (newCard, NULL);
		 currCard = currCard->next;
		 // if final card -> next card is NULL
		 if (i == 3 && j == 12)  { currCard->next = NULL; }
	  }
	}
}

/*
Function that shuffles the deck by randomly rearranging the cards
for a set amount of time
*/
void deck::shuffle()
{
	int place1;
	int place2;
	int numShuffle = 1000; //Number is big to fully randomize it
	//Initializes variables for switching locations and for transferring swaps
	node<card> * cardSpot1 = firstCard;
	node<card> * cardSpot1Previous = firstCard;
	node<card> * cardTempSpot2 = firstCard;
	node<card> * cardTempSpot2Previous = firstCard;
	node<card> * tempSwap1 = firstCard;
	//Shuffles a random amount of times
	for (int i=0; i < numShuffle; i++)
	{
		//Defaults all variables to start
		cardSpot1 = firstCard;
		cardSpot1Previous = firstCard;
		cardTempSpot2 = firstCard;
		cardTempSpot2Previous = firstCard;
		tempSwap1 = firstCard;
		//Sets to random location in the deck
		place1 = rand() % 52;
		place2 = rand() % 52;
		//Runs if locations are not the same because that wouldn't be a shuffle
		if (place1 != place2)
		{
			//Runs through every card until reaching place1
			for (int j=0; j <= place1; j++)
			{
				//Stops when it's at the first location -- huge nested if/else
				if(j == place1)
				{
					//Runs through every card until reaching place2
					for (int k=0; k <= place2; k++)
					{
						//Stops when it's at the first location
						if(k == place2)
						{
							//Special case for when first location at the front
							if (place1 == 0)
							{
								tempSwap1 = cardSpot1;
								firstCard = cardTempSpot2;
								cardTempSpot2Previous->next = tempSwap1;
								tempSwap1 = cardSpot1->next;
								cardSpot1->next = cardTempSpot2->next;
								cardTempSpot2->next = tempSwap1;
							}
							//Special case for when other location is the front
							else if (place2 == 0)
							{
								tempSwap1 = cardTempSpot2;
								firstCard = cardSpot1;
								cardSpot1Previous->next = tempSwap1;
								tempSwap1 = cardTempSpot2->next;
								cardTempSpot2->next = cardSpot1->next;
								cardSpot1->next = tempSwap1;
							}
							//Shuffles/swaps cards normally otherwise
							else
							{
								tempSwap1 = cardSpot1;
								cardSpot1Previous->next = cardTempSpot2;
								cardTempSpot2Previous->next = tempSwap1;
								tempSwap1 = cardSpot1->next;
								cardSpot1->next = cardTempSpot2->next;
								cardTempSpot2->next = tempSwap1;
							}
						}
						//If we aren't at place 2 yet if continues through list
						else
						{
							  cardTempSpot2Previous = cardTempSpot2;
							  cardTempSpot2 = cardTempSpot2->next;
						}						
					 } // end for loop k
				} // end huge nested if
				else
				//If we aren't at place 1 yet if continues through list
				{
				  cardSpot1Previous = cardSpot1;
				  cardSpot1 = cardSpot1->next;
				}
			} // ends for loop j
		 }
	}
	//Deallocates space for the loop variables
	tempSwap1 = NULL;
	cardSpot1 = NULL;
	cardSpot1Previous = NULL;
	cardTempSpot2 = NULL;
	cardTempSpot2Previous = NULL;
}

// returns first card -- unused rn
node<card> * deck::getFirst()
{
	return firstCard;
}

// overloaded operator to print entire deck.
ostream& operator<< (ostream& ostr, const deck& d)
{
	// declare & set temp vars
	node<card> * currCardAlt;
	currCardAlt = d.firstCard;
	int count = 0;

	// cute formatting
	ostr << "\nCurrent Deck Composition & Order:";

	// loop through all cards in 4 rows of 13
	while (currCardAlt != NULL)
	{
		 count++;
 		 if (count % 13 == 1)  { ostr << "\n"; } // newline after suit/13
		ostr << currCardAlt->nodeValue;		// overloaded card <<
		if (count != 52) { ostr << ", "; }  // no trailing comma after 52nd card
		currCardAlt = currCardAlt->next;	 // set next card
	}
	ostr << "\n\n";

	return ostr;
}


#endif	// deck_h
