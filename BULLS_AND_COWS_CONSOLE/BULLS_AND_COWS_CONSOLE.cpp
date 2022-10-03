#define _CRT_RAND_S
#include <iostream>
#include <conio.h>
#include <ctime>
#include <stdlib.h>
#include <string>
#include "Game.h"
using namespace std;

uint16_t InputCountOfDigits() {
    string s;
    uint16_t countofdigits;
    printf("Enter the number of digits, ranging from 2 to 10:\n");
    cin >> s;
    try { countofdigits = stoi(s, nullptr, 16); }
    catch (const invalid_argument& ia) { cout << "Invalid argument: " << ia.what() << "\n"; exit(EXIT_FAILURE); }
    if (countofdigits < 2) { printf("No-no-no, it's so easy, please enter value bigger than 1\n"); exit(EXIT_FAILURE); }
    if (countofdigits > 10) { printf("Your value is too big for this game\n"); exit(EXIT_FAILURE); }
    return countofdigits;
}

int main()
{
    cout << "Hello World!\n";
    srand(time(NULL));
    while (true) {
        uint16_t game;
        printf("what game do you want to play: computer sets number, you sets number, and game 1v1.\nEnter the phrase number:\n");
        cin >> game;
        switch (game) {
        case 1:
        {
            Game session = Game(1, InputCountOfDigits());
            cout << session.GetCompNumStr() << endl;
        }
            break;
        case 2:
        {

        }
            break;
        }
    }
}