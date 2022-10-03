#pragma once
#define _CRT_RAND_S
#include <stdint.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <random>

using namespace std;
class Game
{
private:
	vector<uint16_t> compnumvec;
public:
	string GetCompNumStr();
	Game(uint16_t gamenum, uint16_t countOfDigits);
private:
	void FillVectorRandNum(vector<uint16_t> v);
	int16_t Rand1digit();
};