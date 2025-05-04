#pragma once
#include <string>
#include <set>
using namespace std;

set<char> getRemainingChars(const set<char> &previousGuesses)
{
    set<char> remainingChars;
    for(char c = 'a'; c <= 'z'; c++)
    {
        remainingChars.insert(c);
    }
    for(char c: previousGuesses)
    {
        remainingChars.erase(c);
    }
    return remainingChars;
}

char selectRandomChar(const set<char> &s)
{
    int r = rand() % s.size();
    for(char c: s)
    {
        if(r-- == 0)
        {
            return c;
        }
    }
    return 0;
}

char getNextGuess(const set<char> &previousGuesses, const string& secretWord)
{
    set<char> remainingChars = getRemainingChars(previousGuesses);
    if(remainingChars.size() == 0)
    {
        return 0;
    }
    else
    {
        return selectRandomChar(remainingChars);
    }
}
