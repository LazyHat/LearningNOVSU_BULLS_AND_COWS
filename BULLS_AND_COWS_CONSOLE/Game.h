#pragma once
#define _CRT_RAND_S
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
class Game
{
private:
	uint32_t compnum{}, usernum{};
	uint16_t countofdigits{};
	uint16_t* usernumarr{};
	uint16_t* compnumarr{};
	uint16_t bulls{}, cows{};

public:
	Game() {
		bulls = 0;
		cows = 0;
		countofdigits = 0;
	}
	//comp sets number, user solve
	Game(uint16_t _countofdigits) {
		countofdigits = _countofdigits;
		bulls = 0;
		cows = 0;
		usernumarr = new uint16_t(countofdigits);
		compnumarr = new uint16_t(countofdigits);
		srand(time(NULL));
		do {
			SetRandomCompNum();
			ConvertIntToArray(compnum, compnumarr);
		} while (!TestArrayDigits(compnumarr));
	}

	uint32_t GetCompNum() { return compnum; }
	uint16_t GetCountOfDigits() { return countofdigits;  }
	uint16_t GetBulls() { return bulls; }
	uint16_t GetCows() { return cows; }
	void SetBulls(uint16_t _bulls) { bulls = _bulls; }
	void SetCows(uint16_t _cows) { cows = _cows; }

	void SetRandomCompNum() {
		do {
			rand_s(&compnum);
			compnum %= (int32_t)pow(10, countofdigits);
		} while (!(compnum >= pow(10, countofdigits - 1)));
	}

	void SetUserValue(int32_t uservalue) {
		usernum = uservalue;
		ConvertIntToArray(usernum, usernumarr);
	}

	std::string GetGameResult() {
		if (bulls == countofdigits) return "You win, the hidden number: " + std::to_string(compnum) + "\n";
		else return "BULLS: " + std::to_string(bulls) + ("\nCOWS:") + std::to_string(cows) + "\n";
	}

	bool GetGameResultBool() {
		return bulls == countofdigits;
	}

	uint32_t GetNextNumber() {
		if (bulls == 0 && cows == 0) {
			SetRandomCompNum();
			return compnum;
		}
		else {

		}
	}

	void CalculateBullsCows() {
		bulls = CompareArrays(compnumarr, usernumarr);
		cows = CompareArraysNonEqualPlaces(compnumarr, usernumarr) - bulls;
	}

private:

private:

	uint16_t CompareArrays(uint16_t* arr1, uint16_t* arr2) {
		uint16_t countofequal = 0;
		for (uint16_t i = 0; i <= countofdigits - 1; i++) {
			if (arr1[i] == arr2[i]) countofequal++;
		}
		return countofequal;
	}

	uint16_t CompareArraysNonEqualPlaces(uint16_t* arr1, uint16_t* arr2) {
		uint16_t k = 0;
		for (int16_t i = 0; i < countofdigits; i++) {
			for (int16_t j = 0; j < countofdigits; j++) {
				if (arr1[i] == arr2[j]) k++;
			}
		}
		return k;
	}

	void ConvertIntToArray(uint32_t numtoarr, uint16_t* arr) {
		for (int16_t i = countofdigits - 1; i >= 0; i--) {
			arr[i] = numtoarr % 10;
			numtoarr /= 10;
		}
	}

	bool TestArrayDigits(uint16_t* arr) {
		int16_t k = 0;
		for (int16_t i = 0; i < 10; i++) {
			for (int16_t j = 0; j <= countofdigits - 1; j++) {
				if (arr[j] == i) k++;
			}
			if (k < 2) k = 0;
			else return false;
		}
		return true;
	}
};

