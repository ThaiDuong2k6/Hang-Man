#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "draw.h"
using namespace std;
const int MAX_BAD_GUESSES = 8;

vector<string> loadWordsFromFile(const string &filename)
{
    vector<string> words;
    ifstream file(filename);
    string word;
    while (file >> word)
    {
        words.push_back(word);
    }
    return words;
}

string chooseWord(const vector<string> &WORD_LIST)
{
    int randomIndex = rand() % WORD_LIST.size();
    return WORD_LIST[randomIndex];
}

void update(string &guessedWord, const string &secretWord, char guess)
{
    for (int i = 0; i < secretWord.length(); i++)
    {
        if (secretWord[i] == guess)
        {
            guessedWord[i] = guess;
        }
    }
}

bool contains(const string &secretWord, char guess)
{
    return secretWord.find(guess) != string::npos;
}

char readAGuess()
{
    char guess;
    cout << "Your guess: ";
    cin >> guess;
    return guess;
}

int main()
{
    srand(time(0));
    vector<string> WORD_LIST = loadWordsFromFile("words.txt");
    string wrongGuesses;
    string secretWord = chooseWord(WORD_LIST);
    string guessedWord(secretWord.length(), '-');
    int badGuessCount = 0;
    do
    {
        renderGame(guessedWord, badGuessCount, wrongGuesses);
        char guess = readAGuess();
        if (contains(secretWord, guess))
        {
            update(guessedWord, secretWord, guess);
        }
        else
        {
            badGuessCount++;
            wrongGuesses.push_back(guess);
        }
    }
    while (badGuessCount < MAX_BAD_GUESSES && secretWord != guessedWord);
    displayFinalResult(badGuessCount < MAX_BAD_GUESSES, secretWord);
    return 0;
}

