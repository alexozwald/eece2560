/*
Proj:      MasterMind-a
Team:      3-AndBoiOsw
File:      code.h
Descr:     Implements the constructor and destructor of the code class,
           and the declarations and implementations for the guessCorrect,
           guessIncorrect, welcome, guess, print, and randomize functions
*/

#ifndef code_h
#define code_h
using namespace std;

/*
 Initializes the class for the guess and secret codes of numbers to be used
 in the MasterMind game.
 */
class code
{
public:
    code();                                     // constructor
    ~code(){};                                  // destructor
    void welcome();
    void randomize();
    
    void play();                                // controls gameplay (<=10 rounds)
    
    // helper functions
    vector<int> guess();                        // applies guessing
    void checkCorrect(vector<int> userGuess);   // correct overall digits
    void checkIncorrect(vector<int> userGuess); // correct digit+location
    string gstr();
    bool vectorRange(vector<int> guessvect);    // checks for valid input
    bool vecContains(vector<int> tempCorrect, int userGuessInt);
    void printSecret();

private:
    vector<int> secret;
    int guesses;
    int n;
    int m;
};

code::code() {
    n = 5;
    m = 7;
    guesses = 1;
}

/* WELCOME & DEFAULT SETTINGS
 *  Asks the user whether they want to use the default code length
 *  and number range settings or whether they
 *  would like to choose their own settings.
 *  Allows for a new range and amount of numbers for the code
 *  to be selected if they want custom settings.
 */
void code::welcome(){
    cout << "Welcome to Mastermind!" << endl;
    
    char def; // random default to begin loop
    do {
        cout << "Do you wish to play with default settings? (y/n) ";
        cin >> def;

        if(def=='y'){
            cout << "Defaults selected." << endl;
        } else if(def=='n'){
            cout << "Please input the code length: ";
            cin >> n;
            cout << "Please input the code range:  ";
            cin >> m;
        } else{
            cout << "Invalid Input. Try again." << endl;
        }
    } while((def != 'y') && (def != 'n'));
    
    cout << "Code length: " << n << ".  Code range: [0," << m-1 << "]." << endl << endl;
    randomize();
}

/*
 *  Randomizes and generates a
 *  unique secret code into a vector to be guessed by the player
 */
void code::randomize(){
    // generate secret code
    vector<int> codevect{};
    
    // loop to generate
    for(int i=0;i<n;i++){
        // randomize
        codevect.push_back(rand()%m);
    }
    secret = codevect;
}

/*
 *  Allows the user to guess the secret code by individually
 *  entering the digits of the code. Checks to see if the code entered
 *  is out of range and prompts the user to enter a new digit if this
 *  is the case. Prints the guessed code from the user.
 */
vector<int> code::guess(){
    int input;
    vector<int> guessvect;
    
    do {
        cout << gstr() << "Guess the code (spaced): ";
        for (int i=0; i<n; i++){
            cin >> input;
            guessvect.push_back(input);
        }
        if (vectorRange(guessvect)) {
            cout << gstr() << "Invalid range.  Try again." << endl;
            guessvect.clear();
        }
    } while (vectorRange(guessvect));
    
    /* DEBUGGING INFO
     * // pretty print users input
     * cout << gstr() << "You guessed:  ";
     * for(int i=0; i < guessvect.size(); i++){
     *     cout << guessvect.at(i) << ' ';
     * }
     * cout << endl;
     */
        
    return guessvect;
}

/*
 *  Uses the guess function to allow the user to play the game
 *  until the number of turns allowed is exceeded,
 *  at which point the user either wins or loses the
 *  game based on their guesses of the secret code.
 */
void code::play(){
    vector<int> currentGuess;
    
    printSecret();
    
    while ((guesses <=10) && (currentGuess != secret)){
        currentGuess = guess();
        checkCorrect(currentGuess);
        checkIncorrect(currentGuess);
        guesses++;
    }
    cout << endl;
    
    printSecret();
    
    if (guesses > 10) {
        cout << "The mastermind wins again!" << endl;
    } else {
        cout << "Congratulations! You outsmarted the mastermind!" << endl;
    }
}

// Prints the secret code
void code::printSecret(){
    cout << "The secret code was (";
    
    cout << secret.at(0);
    for(int i=1; i<n; i++) {
        cout << ',' << secret.at(i);
    }
    cout << ")." << endl;
}

/*
 *  Prints the amount of digits that the user guessed
 *  exactly correct, meaning that it was in the right
 *  location and the right digit of the secret code.
 */
void code::checkCorrect(vector<int> userGuess){
    int tally = 0;
    
    // loop to check exact placement
    for(int i=0; i<n; i++){
        if(userGuess[i] == secret[i]) { tally++; }
    }
    
    // print readable output
    cout << gstr() << "You guessed " << tally << " digits in the correct spot."
        << endl;
}

/*
 *  Checks which digits are present in the vector but not in the correct
 *  position and prints this value
 */
void code::checkIncorrect(vector<int> userGuess){
    int tally = 0;

    for(int i=0; i<n; i++)
    {
        if (vecContains(secret, userGuess[i])) { tally++; }
    }
    
    // print readable output
    cout << gstr() << "You guessed " << tally << " digits overall."
        << endl;
}

/*
 *  Checks if a given vector contains a provided number.
 *  Assists checkIncorrect() with cross-checking the secret code
 *  with all indices of the current guess vector.
 */
bool code::vecContains(vector<int> tempCorrect, int userGuessInt) {
    
    // if int is contained
    for (int i=0; i<tempCorrect.size(); i++)
    {
        if (tempCorrect[i] == userGuessInt)
        {
            return true;
        }
    }
    
    // if int is not contained
    return false;
}
               
/*
 Evaluates range of vector.  If guessed vector is not within
 range of game rules, the attempt can be redone.
 */
bool code::vectorRange(vector<int> guessvect){

    int min = *min_element(guessvect.begin(), guessvect.end());
    int max = *max_element(guessvect.begin(), guessvect.end());
    
    if (min < 0){
        return true;
    } else if (max > m-1){
        return true;
    } else{
        return false;
    }
}

// Allows for cleaner code.  Simplified attempt counter.
string code::gstr(){
    return "[try" + to_string(guesses) + "] ";
}

#endif /* code_h */
