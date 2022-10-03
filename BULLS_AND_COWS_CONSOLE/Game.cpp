#include "Game.h"
#include <iostream>
#include <ctime>
#include <algorithm>
#include <random>
using namespace std;

string Game::GetCompNumStr() {
	string s;
	for (uint16_t i = 0; i < compnumvec.size(); i++) {
		s += to_string(compnumvec[i]);
	}
	return s;
}

Game::Game(uint16_t gamenum, uint16_t countOfDigits) {
	switch (gamenum) {
	case 1:
		random_device rd;
		mt19937 gen(rd());
		uniform_int_distribution<int> dist(0, 9);
		compnumvec = vector<uint16_t>(countOfDigits);
		cout << compnumvec.size() << endl;
		FillVectorRandNum(compnumvec);
		break;
	}
}
void Game::FillVectorRandNum(vector<uint16_t> v, int func) {
	generate(v.begin(), v.end(), Rand1digit);
}

int16_t Game::Rand1digit() {
	uint32_t k;
	rand_s(&k);
	k %= 10;
	return k;
}