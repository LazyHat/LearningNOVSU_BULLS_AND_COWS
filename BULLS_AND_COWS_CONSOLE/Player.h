#pragma once
#include <iostream>
#include <vector>
using namespace std;
typedef tuple<int, int> index2;
typedef tuple<int, int, int> index3;
class Player
{
#pragma region Variables
private:
	vector<int> bakbulls, bakcows;
	vector<int> cnumv;
	vector<vector<int>> bakcnumv;
	vector<int> flags;
	vector<int> excludes;
public:
	vector<int> snumv;
#pragma endregion
public:
	Player(int cod) {
		cnumv = vector<int>(cod);
		snumv = vector<int>(cod);
		excludes = vector<int>();
		flags = vector<int>(10);
	}
	void Begin(bool FlagMakeNumber) {
		if (FlagMakeNumber) {
			FillVecRand(cnumv);
		}
		else {
			bakcnumv = { {vector<int>(cnumv.size())}, {vector<int>(cnumv.size())},{vector<int>(cnumv.size())}};
			bakbulls = vector<int>(3);
			bakcows = vector<int>(3);
			flags[0] = 0;
			FillVecRand(cnumv);
			FillVecRand(snumv); //типо я кго загадал
		}
	}
	void GuessNum() {
		switch (cnumv.size()) {
		case 1:
			GuessNum1Digit(0);
			break;
		case 2:
			GuessNum2Digits(make_tuple(0,1));
			break;
		case 3:
			GuessNum3Digits(make_tuple(0, 1, 2));
			break;
		}
		Backup();
	}
public:
#pragma region GettersBullsCows
	int GetBulls() {
		int k = 0;
		for (int i = 0; i < cnumv.size(); i++) {
			if (cnumv[i] == snumv[i]) k++;
		}
		if (k == cnumv.size()) return -1;
		return k;
	}
	int GetCows() {
		int k = 0;
		for (int i = 0; i < cnumv.size(); i++) {
			for (int j = 0; j < cnumv.size(); j++) {
				if (cnumv[i] == snumv[j]) k++;
			}
		}
		return k - GetBulls();
	}
	int GetCows(index2 index) {
		int k = 0;
		for (int i = 0; i < cnumv.size(); i++) {
			if(CheckNumToTuple(i, index)){
				for (int j = 0; j < cnumv.size(); j++) {
					if (CheckNumToTuple(j, index)) {
						if (cnumv[i] == snumv[j]) k++;
					}
				}
			}
		}
		return k - GetBulls(index);
	}
	int GetBulls(index2 index) {
		int k = 0;
		for (int i = 0; i < cnumv.size(); i++) {
			if (CheckNumToTuple(i, index)) {
				if (cnumv[i] == snumv[i]) k++;
			}
		}
		if (k == cnumv.size()) return -1;
		return k;
	}
	int GetBulls(index3 index) {
		int k = 0;
		for (int i = 0; i < cnumv.size(); i++) {
			if (CheckNumToTuple(i, index)) {
				if (cnumv[i] == snumv[i]) k++;
			}
		}
		if (k == cnumv.size()) return -1;
		return k;
	}
	int GetCows(index3 index) {
		int k = 0;
		for (int i = 0; i < cnumv.size(); i++) {
			if (CheckNumToTuple(i, index)) {
				for (int j = 0; j < cnumv.size(); j++) {
					if (CheckNumToTuple(j, index)) {
						if (cnumv[i] == snumv[j]) k++;
					}
				}
			}
		}
		return k - GetBulls(index);
	}
#pragma endregion
	string GetMNum() {
		string s = "";
		for (int i = 0; i < cnumv.size(); i++)
		{
			s += to_string(cnumv[i]);
		}
		return s;
	}
	string GetSNum() {
		string s = "";
		for (int i = 0; i < snumv.size(); i++)
		{
			s += to_string(snumv[i]);
		}
		return s;
	}
	static bool CheckVecDigits(vector<int>& v) {
		if (v.size() == 0) return 0;
		if (v[0] == 0) return 0;
		if (v.size() == 1) return 1;
		int k = 0;
		for (int i = 0; i < v.size(); i++) {
			k = 0;
			for (int j = 0; j < v.size(); j++)
			{
				if (v[i] == v[j]) k++;
			}
			if (k > 1) return false;
		}
		return true;
	}
private:
	void GuessNum1Digit(int indexofdigit) {
		cnumv[indexofdigit]++;
		if (cnumv[indexofdigit] > 9) cnumv[indexofdigit] = 0;
	}
	void GuessNum2Digits(index2 index) {
		int a = get<0>(index), b = get<1>(index);
		switch (GetBulls(index)) {
		case 0:
			switch (GetCows(index))
			{
			case 0:
				excludes.push_back(cnumv[a]);
				excludes.push_back(cnumv[b]);
				if ((bakbulls[1] - bakbulls[0]) == 1) {
					cnumv = bakcnumv[1];
				}
				else FillVecRand(cnumv, index);
					break;
			case 1:
			case 2:
				Swap(cnumv, make_tuple(a,b));
				break;
			}
			break;
		case 1:
			switch (GetCows(index)) {
			case 0:
				if (flags[0] != 0) {
					GuessNum1Digit(flags[0]);
					while (cnumv[a] == cnumv[b] || !CheckNumToExclude(cnumv[flags[0]])) GuessNum1Digit(flags[0]);
				}
				else if (bakcnumv[0] == bakcnumv[2]) {
					int k;
					GuessNum1Digit(k = CompareVectorsToEqualIndex(cnumv, bakcnumv[1], index));
					while (cnumv[a] == cnumv[b] || !CheckNumToExclude(cnumv[k])) GuessNum1Digit(k);
					flags[0] = k;
				}
				else {
					GuessNum1Digit(0);
					while (cnumv[a] == cnumv[b] || !CheckNumToExclude(cnumv[a])) GuessNum1Digit(a);
				}
				break;
			}
		}
	}
	void GuessNum3Digits(index3 index) {
		int a = get<0>(index), b = get<1>(index), c = get<2>(index);
		switch (GetBulls(index)) {
		case 0:
			switch (GetCows()) {
			case 0:
				if (bakbulls[1] - bakbulls[0] >= 1) {
					cnumv = bakcnumv[1];
				}
				else {
					FillVecRand(cnumv, index);
				}
				break;
			case 1:
				Swap(cnumv, make_tuple(flags[1] = CompareVectorsToEqualIndex(bakcnumv[1], bakcnumv[0], index), flags[2] = CompareVectorsToEqualIndex(bakcnumv[1], bakcnumv[0], index, CompareVectorsToEqualIndex(bakcnumv[1], bakcnumv[0], index))));
			}
			break;
		case 1:

			break;
		}
	}
	void Backup() {
		bakcnumv.insert(bakcnumv.begin(), cnumv);
		bakbulls.insert(bakbulls.begin(), GetBulls());
		bakcows.insert(bakcows.begin(), GetCows());
		bakcnumv.pop_back();
		bakcows.pop_back();
		bakbulls.pop_back();
	}
	void FillVecRand(vector<int>& v) {
		uint32_t k;
		do {
			for (int i = 0; i < v.size(); i++) {
				do {
					rand_s(&k);
					k %= 10;
				} while (!CheckNumToExclude(k));
				v[i] = k;
			}
		}
		while (!CheckVecDigits(v));
	}
	void FillVecRand(vector<int>& v, index2 index) {
		uint32_t k;
		do {
			for (int i = 0; i < v.size(); i++) {
				if (CheckNumToTuple(i, index)) {
					do {
						rand_s(&k);
						k %= 10;
					} while (!CheckNumToExclude(k));
					v[i] = k;
				}
			}
		} while (!CheckVecDigits(v));
	}
	void FillVecRand(vector<int>& v, index3 index) {
		uint32_t k;
		do {
			for (int i = 0; i < v.size(); i++) {
				if (CheckNumToTuple(i, index)) {
					do {
						rand_s(&k);
						k %= 10;
					} while (!CheckNumToExclude(k));
					v[i] = k;
				}
			}
		} while (!CheckVecDigits(v));
	}
	void Swap(vector<int> &v, index2 index) {
		do {
			int k = v[get<0>(index)];
			v[get<0>(index)] = v[get<1>(index)];
			v[get<1>(index)] = k;
		} while (v[get<0>(index)] == 0);
	}
	void Swap(vector<int>& v, index3 index) {
		Swap(v, make_tuple(get<0>(index), get<1>(index)));
		Swap(v, make_tuple(get<1>(index), get<2>(index)));
	}
	int CompareVectorsToEqualIndex(vector<int> &a, vector<int> &b, index2 index) {
		for (int i = 0; i < a.size(); i++) {
			if (CheckNumToTuple(i, index)) {
				if (a[i] == b[i]) return i;
			}
		}
		return get<0>(index);
	}
	int CompareVectorsToEqualIndex(vector<int>& a, vector<int>& b, index3 index) {
		for (int i = 0; i < a.size(); i++) {
			if (CheckNumToTuple(i, index)) {
				if (a[i] == b[i]) return i;
			}
		}
		return get<0>(index);
	}
	int CompareVectorsToEqualIndex(vector<int>& a, vector<int>& b, index3 index, int excludeindex) {
		for (int i = 0; i < a.size(); i++) {
			if (CheckNumToTuple(i, index) && i != excludeindex) {
				if (a[i] == b[i]) return i;
			}
		}
		return ((get<0>(index) == excludeindex)? get<1>(index): get<0>(index));
	}
	int CompareVectorsToDiffIndex(vector<int>& a, vector<int>& b, index3 index) {
		for (int i = 0; i < a.size(); i++) {
			if (CheckNumToTuple(i, index)) {
				if (a[i] != b[i]) return i;
			}
		}
		return get<0>(index);
	}
	vector<int> toVector(int value, int cod) {
		vector<int> v = vector<int>(cod);
		for (int i = v.size() - 1; i >= 0; i--) {
			v[i] = value % 10;
			value /= 10;
		}
		return v;
	}
	bool CheckNumToExclude(int n) {
		for (int i = 0; i < excludes.size(); i++) {
			if (n == excludes[i]) return false;
		}
		return true;
	}
	bool CheckNumToTuple(int n, index2 index) { return ((n == get<0>(index)) or (n == get<1>(index))); }
	bool CheckNumToTuple(int n, index3 index) { return ((n == get<0>(index)) or (n == get<1>(index)) or (n == get<2>(index))); }
};

