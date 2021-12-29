/* upd
 Proj:      MasterMind-B
 Team:      3-AndBoiOsw
 File:      response.h
 Descr:     Implements the constructor and destructor of the response class,
            and the declarations and implementations for getting and setting
            the response variables, and overloaded operators for the 
            == and << operations to work in line with the response.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#ifndef response_h
#define response_h

/*
 Implement the class response which stores the response to a guess 
 (number correct and number incorrect), and which includes:
 */
class response
{
public:
    // Constructor for the response class
    response(int nn, int mm);
    response();
    // Functions to set and get the individual stored values within a response,
    //Functions to set and get the private variables
    int getIncorrect() const;
    int getCorrect() const;
    void setIncorrect(int inc);
    void setCorrect(int cor);
    
    // Overloaded operators for == and <<
    friend bool operator==(const response &lhs, const response &rhs);
    friend ostream &operator<<(ostream &ostr, const response &r);

private:
    //Private correct and incorrect guess count variables
    int correct;
    int incorrect;
};

// constructor default
response::response()
{
    correct = 0;
    incorrect = 0;
}
//Initializes the constructor for the response class
response::response(int nn, int mm)
{
    correct = nn;
    incorrect = mm;
}

//Gets and returns the correct guesses variable
int response::getCorrect() const
{
    return correct;
}

//Gets and returns the incorrect guesses variable
int response::getIncorrect() const
{
    return incorrect;
}

//Sets correct guesses variable
void response::setCorrect(int cor) 
{
    correct = cor;
}

//Sets incorrect guesses variable
void response::setIncorrect(int inc)
{
    incorrect = inc;
}


// Definition of overloaded == , where when two responses are directly compared
// /it will return whether the number of correct and incorrect numbers are equal
bool operator == (const response &lhs, const response &rhs)
{
    return lhs.getIncorrect() == rhs.getIncorrect() & lhs.getCorrect() == rhs.getIncorrect();
}

// Definition of overloaded <<, where when used with a response it will print
// the correct and incorrect values of the response and returns the combination
ostream &operator<<(ostream &ostr, const response &r)
{
    ostr << "Number correct: " << r.getCorrect() << endl;
    ostr << "Number incorrect: " << r.getIncorrect();
    return ostr;
}

#endif /* response_h */
