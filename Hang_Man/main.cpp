#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "draw.h"
#include "guesser.h"
#include "util.h"
using namespace std;
const int MAX_BAD_GUESSES = 8;

int getUserWordLength()
{
    int wordLength;
    cout << endl << "Enter your word length: ";
    cin >> wordLength;
    return wordLength;
}

string getUserAnswer(char guess)
{
    string answer;
    cout << endl << "I guess " << guess << ", please enter your mask: ";
    cin >> answer;
    return answer;
}

void initialize(int &wordLength, string &secretWord, int &incorrectGuess, set<char> &previousGuesses, bool &stop)
{
    wordLength = getUserWordLength();
    secretWord = string(wordLength, '-');
    incorrectGuess = 0;
    previousGuesses = set<char>();
    stop = false;
}

void update(char guess, const string &mask, int &incorrectGuess, set<char> &previousGuesses, string &secretWord, bool &stop)
{
    if(!isGoodMask(guess, mask, secretWord))
    {
        throw invalid_argument("mistake entering answer");
    }
    previousGuesses.insert(guess);
    if(isAllDash(mask))
    {
        incorrectGuess++;
        if(incorrectGuess == MAX_BAD_GUESSES)
        {
            stop = true;
        }
    }
    else
    {
        updateSecretWord(mask, secretWord);
        if(isAllNotDash(secretWord))
        {
            stop = true;
        }
    }
}

char getNextGuess(const set<char> &previousGuesses, const string& secretWord)
{
    static vector<string> wordList = readWordListFromFile("words.txt");
    set<char> remainingChars = getRemainingChars(previousGuesses);
    if(remainingChars.size() == 0)
    {
        return 0;
    }
    if(isAllDash(secretWord))
    {
        return getVowelGuess(remainingChars);
    }
    vector<string> filteredWordList = getSuitableWords(wordList, secretWord, remainingChars);
    map<char, int> occurenceCount = getOccurenceCount(remainingChars, filteredWordList);
    return getMaxOccurenceChar(remainingChars, occurenceCount);
}

int main()
{
    int wordLength;
    string secretWord;
    int incorrectGuess;
    set<char> previousGuesses;
    bool stop;

    initialize(wordLength, secretWord, incorrectGuess, previousGuesses, stop);

    render(incorrectGuess, previousGuesses, secretWord);
    do
    {
        char guess = getNextGuess(previousGuesses, secretWord);
        if(guess == 0)
        {
            cout << "I give up! What is your word? :3" << endl;
            string newWord;
            cin >> newWord;
            ofstream file("words.txt", ios::app);
            if(file.is_open())
            {
                file << endl << newWord;
                file.close();
                cout << "Your word has been updated to the file.";
            }
            return 0;
        }
        do
        {
            try
            {
                string mask = getUserAnswer(guess);
                update(guess, mask, incorrectGuess, previousGuesses, secretWord, stop);
                break;
            }
            catch(invalid_argument e)
            {
                cout << "Invalid mask, please try again." << endl;
            }
        }
        while(true);
        render(incorrectGuess, previousGuesses, secretWord);
    }
    while(!stop);
    displayFinalResult(incorrectGuess == MAX_BAD_GUESSES, secretWord);
    return 0;
}
