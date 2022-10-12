#define _CRT_RAND_S
#include <iostream>
#include <conio.h>
#include <ctime>
#include <stdlib.h>
#include <string>
#include <vector>
#include "Player.h"
using namespace std;

#pragma region PrintL()
void PrintL(string s) {
    cout << s << endl;
}
void PrintL(int s) {
    cout << s << endl;
}
void PrintL(string k, int s) {
    cout << k + to_string(s) << endl;
}
#pragma endregion
int InputCountOfDigits() {
    int countofdigits;
    printf("Enter the number of digits, ranging from 1 to 10:\n");
    cin >> countofdigits;
    if (countofdigits < 1) { printf("No-no-no, it's so easy, please enter value bigger than 0\n"); return InputCountOfDigits(); }
    if (countofdigits > 10) { printf("Your value is too big for this game\n"); return InputCountOfDigits(); }
    return countofdigits;
}
int InputGameNumber() {
    int game;
    printf("what game do you want to play: computer sets number, you sets number, and game 1v1.\nEnter the phrase number:\n");
    cin >> game;
    if (game > 3 or game < 1) { PrintL("Incorrect Number"); return InputGameNumber(); }
    return game;
}
int ReadInt() {
    int k;
    cin >> k;
    return k;
}
bool PrintBullsAndCows(Player player) {
    if (player.GetBulls() == -1) {return true;}
    PrintL("Bulls: ", player.GetBulls());
    PrintL("Cows: ", player.GetCows());
    return false;
}
vector<int> SetValToVector(int cod) {
    PrintL("Enter your value");
    int value = ReadInt();
    if (!(value < pow(10, cod)) || !(value > pow(10, cod - 1))) {
        PrintL("Invalid value");
        return SetValToVector(cod);
    }
    vector<int> v = vector<int>(cod);
    for (int i = v.size() - 1; i >= 0; i--) {
        v[i] = value % 10;
        value /= 10;
    }
    if (!Player::CheckVecDigits(v)) { PrintL("Invalid value"); return SetValToVector(cod); }
    return v;
}

int main()
{
    cout << "Hello World!\n";
    srand(time(NULL));
    while (true) {
        switch (InputGameNumber()) {
        case 1:
        {
           Player comp = Player(InputCountOfDigits());
           comp.Begin(true);
           //PrintL("Created number: " + comp.GetMNum());
           do {
               comp.snumv = SetValToVector(comp.snumv.size());
               if (PrintBullsAndCows(comp)) PrintL("You Win!");
           } while (comp.GetBulls() != -1);
        }
        break;
        case 2:
        {
            Player comp = Player(InputCountOfDigits());
            comp.Begin(false);
            PrintL("Created number: " + comp.GetSNum());
            do {
                comp.GuessNum();
                PrintL("My num is: " + comp.GetMNum());
                if (PrintBullsAndCows(comp)) PrintL("I Win!");
            } while (comp.GetBulls() != -1);
        }
        break;
        }
    }
}