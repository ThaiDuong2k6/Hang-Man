#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;
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
    "   |          /|\\ \n"
    "   |               \n"
    "   |    \n"
    " -----  \n",
    "   -------------   \n"
    "   |           |   \n"
    "   |           O   \n"
    "   |          /|\\ \n"
    "   |          /    \n"
    "   |    \n"
    " -----  \n",
    "   -------------   \n"
    "   |           |   \n"
    "   |           O   \n"
    "   |          /|\\ \n"
    "   |          / \\ \n"
    "   |    \n"
    " -----  \n"};

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

void renderGame(string guessedWord, int badGuessCount, const string &wrongGuesses)
{
    system("CLS");
    cout << FIGURE[badGuessCount] << endl;
    cout << guessedWord << endl;
    cout << "Number of wrong guesses: " << badGuessCount << endl;
    cout << "Wrong guesses: ";
    for (char c : wrongGuesses)
    {
        cout << c << " ";
    }
    cout << endl;
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
    renderGame(guessedWord, badGuessCount, wrongGuesses);
    if (badGuessCount < MAX_BAD_GUESSES)
    {
        cout << "Congratulations! You win!" << endl;
    }
    else
    {
        cout << "You lost. The correct word is: " << secretWord << endl;
    }

    return 0;
}
