/* upd
 Proj:      MasterMind-b
 Team:      3-AndBoiOsw
 File:      main.cpp
 Descr:     Calls mastermind & response to simulate a user (codebreaker)
            playing Mastermind against the computer (codemaker).
*/

//#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <random>
#include "mastermind.h"
#include "response.h"
#include "code.h"

using namespace std;

int main()
{
    // seed random generation with current time
    srand(static_cast<unsigned int>(time(NULL)));
    
    // instantiate mastermind
    mastermind m(5,10);

    return m.playGame();
}