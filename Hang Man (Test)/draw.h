#include <iostream>
#include <thread>
#include <chrono>
using namespace std;
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

const string getNextHangMan()
{
    const static string figure[] = {
    "   -------------  \n"
    "   |          /   \n"
    "   |         O    \n"
    "   |        /|\\  \n"
    "   |        / \\  \n"
    "   |    \n"
    " -----  \n",
    "   -------------   \n"
    "   |           |   \n"
    "   |           O   \n"
    "   |          /|\\ \n"
    "   |          / \\ \n"
    "   |    \n"
    " -----  \n",
    "   -------------     \n"
    "   |            \\   \n"
    "   |             O   \n"
    "   |            /|\\ \n"
    "   |            / \\ \n"
    "   |    \n"
    " -----  \n",
    "   -------------   \n"
    "   |           |   \n"
    "   |           O   \n"
    "   |          /|\\ \n"
    "   |          / \\ \n"
    "   |    \n"
    " -----  \n"};
    const int NUMBER_OF_FIGURES = sizeof(figure) / sizeof(string);
    static int currentFigure = 0;
    return figure[(currentFigure++) % NUMBER_OF_FIGURES];
}

const string getNextDancingMan()
{
    const static string figure[] = {
    "         \n"
    "     o   \n"
    "    /|\\ \n"
    "    / \\ \n",
    "    \\o/ \n"
    "     |   \n"
    "    / \\ \n"
    "         \n"};
    const int NUMBER_OF_FIGURES = sizeof(figure) / sizeof(string);
    static int currentFigure = 0;
    return figure[(currentFigure++) % NUMBER_OF_FIGURES];
}


void renderGame(string guessedWord, int badGuessCount, const string &wrongGuesses)
{
    cout << "\033[2J\033[H";
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

void displayFinalResult(bool won, const string &secretWord)
{
    while (true)
    {
        for (int i = 0; i < 30; i++)
        {
            cout << endl;
        }
        if (won)
        {
            cout << "Congratulations! You win!" << endl;
        }
        else
        {
            cout << "You lost. The correct word is: " << secretWord << endl;
        }
        cout << (won ? getNextDancingMan() : getNextHangMan());
        this_thread::sleep_for(chrono::milliseconds(300));
    }
}
