#include <iostream>
using namespace std;
const string WORD_LIST[] = {"dog", "cat", "human"};
const int WORD_COUNT = sizeof(WORD_LIST) / sizeof(string);
const int MAX_BAD_GUESSES = 7;
const string FIGURE[] = {
"   -------------   \n"
"   |               \n"
"   |               \n"
"   |               \n"
"   |               \n"
"   |    \n"
" -----  \n",
"   -------------   \n"
"   |           |   \n"
"   |               \n"
"   |               \n"
"   |               \n"
"   |    \n"
" -----  \n",
"   -------------   \n"
"   |           |   \n"
"   |           O   \n"
"   |               \n"
"   |               \n"
"   |    \n"
" -----  \n",
"   -------------   \n"
"   |           |   \n"
"   |           O   \n"
"   |           |   \n"
"   |               \n"
"   |    \n"
" -----  \n",
"   -------------   \n"
"   |           |   \n"
"   |           O   \n"
"   |          /|   \n"
"   |               \n"
"   |    \n"
" -----  \n",
"   -------------   \n"
"   |           |   \n"
"   |           O   \n"
"   |          /|\  \n"
"   |               \n"
"   |    \n"
" -----  \n",
"   -------------   \n"
"   |           |   \n"
"   |           O   \n"
"   |          /|\  \n"
"   |          /    \n"
"   |    \n"
" -----  \n",
"   -------------   \n"
"   |           |   \n"
"   |           O   \n"
"   |          /|\  \n"
"   |          / \  \n"
"   |    \n"
" -----  \n"};

string chooseWord()
{
    int randomIndex = rand() % WORD_COUNT;
    return WORD_LIST[randomIndex];
}

void renderGame(string guessedWord, int badGuessCount)
{
    cout << FIGURE[badGuessCount] << endl;
    cout << guessedWord << endl;
    cout << "Number of wrong guesses: " << badGuessCount << endl;
}

void update(string &guessedWord, const string &secretWord, char guess)
{
    for(int i = secretWord.length() - 1; i >= 0; i--)
    {
        if(secretWord[i] == guess)
        {
            guessedWord[i] = guess;
        }
    }
}

bool contains(string secretWord, char guess)
{
    if (secretWord.find(guess) != string::npos)
    {
        return 1;
    }
    return 0;
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
    string secretWord = chooseWord();
    string guessedWord = string(secretWord.length(), '-');
    int badGuessCount = 0;

    do
    {
        renderGame(guessedWord, badGuessCount);
            char guess = readAGuess();
            if (contains(secretWord, guess))
            {
                update(guessedWord, secretWord, guess);
            }
            else
            {
                badGuessCount++;
            }
    }
    while(badGuessCount < MAX_BAD_GUESSES && secretWord != guessedWord);

    renderGame(guessedWord, badGuessCount);
    if(badGuessCount < MAX_BAD_GUESSES)
    {
        cout << "Congratulations! You win!";
    }
    else
    {
        cout << "You lost. The correct word is: " << secretWord;
    }
}
