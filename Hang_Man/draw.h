#include <iostream>
#include <thread>
#include <chrono>
#include <set>
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

void clearScreen()
{
    #ifdef _WIN32
    {
        system("CLS");
    }
    #else
    {
        system("clear");
    }
    #endif
}

void render(int incorrectGuess, const set<char> &previousGuesses, const string &secretWord)
{
    clearScreen();
    cout << endl << "Incorrect guess = " << incorrectGuess << endl << " Previous guesses = ";
    for(char c: previousGuesses)
    {
        cout << c;
    }
    cout << endl << " Secret word = " << secretWord << endl;
    cout << FIGURE[incorrectGuess] << endl;
}

void displayFinalResult(bool isLosing, const string &secretWord)
{
    clearScreen();
    auto start_time = chrono::steady_clock::now();
    while (chrono::duration_cast<chrono::seconds>(chrono::steady_clock::now() - start_time).count() < 10)
    {
        if (isLosing)
        {
            cout << endl << "I lost :(" << endl << "My best word is: " << secretWord << endl;
        }
        else
        {
            cout << endl << "Haha, I win :D" << endl << "The word is: " << secretWord << endl;
        }
        cout << (isLosing ? getNextHangMan() : getNextDancingMan());
        this_thread::sleep_for(chrono::milliseconds(300));
        clearScreen();
    }
}
