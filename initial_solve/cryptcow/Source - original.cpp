/*
ID: ruifanl1
TASK: cryptcow
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <unordered_set>
#include <unordered_map>

using namespace std;

const int maxlen = 80;
const int compset_size = 50000;
const int results_size = 200000;

char s[maxlen];
int encryptions = 0;
char encrypted[maxlen];
const char* target = "Begin the Escape execution at the Break of Dawn";
int target_len = strlen(target);
int a0 = 0, b0 = target_len;

char comps[maxlen][maxlen];
int comps_len;

char components[maxlen][maxlen];
bool flags[maxlen];
int components_len;
int flags_count;
unordered_map<string, bool> compset;
unordered_set<string> results;


string compress(const char* s) {
	char buf[maxlen];
	int bits = 0;
	int n = 0;
	int pos = 0;
	for (int i = 0; s[i] != 0; i++) {
		int a = 0;
		if (s[i] == 'C') {
			a = 50;
		}
		else if (s[i] == 'O') {
			a = 51;
		}
		else if (s[i] == 'W') {
			a = 52;
		}
		else {
			a = s[i];
		}
		bits <<= 6;
		bits |= a;
		n += 6;
		while (n >= 8) {
			n -= 8;
			unsigned char c = (bits >> n);
			buf[pos++] = c;
			bits ^= (c << n);
		}
	}
	if (n > 0) {
		unsigned char c = bits;
		if (c == 0) {
			c = 53;
		}
		buf[pos++] = c;
	}
	buf[pos] = 0;
	return buf;
}

bool compareComp(int comp_index, int& pos) {
	for (int i = 0; comps[comp_index][i] != 0; i++) {
		if (comps[comp_index][i] != target[pos]) {
			return false;
		}
		pos++;
	}
	return true;
}
bool compareCompReverse(int comp_index, int& pos) {
	int len = strlen(comps[comp_index]);
	for (int i = len - 1; i >= 0; i--) {
		if (comps[comp_index][i] != target[pos]) {
			return false;
		}
		pos--;
	}
	return true;
}

bool validateAllComponents(int a, int b) {
	if (a >= b) {
		return flags_count == 0;
	}
	if (flags_count == 0) {
		return a >= b;
	}
	for (int i = 0; i < components_len; i++) {
		if (flags[i]) {
			continue;
		}
		bool match = true;
		int pos = 0;
		for (; components[i][pos] != 0; pos++) {
			if (a + pos >= b || components[i][pos] != target[a + pos]) {
				match = false;
				break;
			}
		}
		if (!match) {
			continue;
		}
		flags[i] = true;
		flags_count--;
		if (validateAllComponents(a + pos, b)) {
			return true;
		}
		flags_count++;
		flags[i] = false;
	}
	return false;
}

int count_isComponentValid;
bool isComponentValid(int a, int b, char* component) {
	count_isComponentValid++;
	a = a0, b = b0;
	// component exists in s?
	auto it = compset.find(compress(component));
	if (it != compset.end()) {
		return it->second;
	}

	bool found = false;
	int len = strlen(component);
	for (int j = a; j <= b - len; j++) {
		bool match = true;
		int pos = j;
		for (int k = 0; component[k] != 0; k++) {
			if (!compareComp(component[k], pos)) {
				match = false;
				break;
			}
		}
		if (match) {
			found = true;
			break;
		}
	}
	if (compset.size() > compset_size) {
		compset.clear();
	}
	compset[compress(component)] = found;
	return found;
}
bool findComponents(char* s) {
	int start = -1;
	components_len = 0;
	for (int i = 0; ; i++) {
		if (s[i] == 0 || s[i] == 'C' || s[i] == 'O' || s[i] == 'W') {
			if (start != -1) {
				char* buf = components[components_len++];
				int pos = 0;
				for (int j = start; j < i; j++) {
					buf[pos++] = s[j];
				}
				buf[pos] = 0;
				start = -1;
			}
		}
		else {
			if (start == -1) {
				start = i;
			}
		}
		if (s[i] == 0) {
			break;
		}
	}
	return true;
}

bool checkComp(char* buf, int d, int a, int b, int& left) {
	if (buf[d] == 'C' || buf[d] == 'O' || buf[d] == 'W') {
		return true;
	}
	char comp[maxlen];
	left++;
	int pos = 0;
	while (buf[left] != 0) {
		char c = buf[left];
		if (c == 'C' || c == 'O' || c == 'W') {
			break;
		}
		left++;
		comp[pos++] = c;
	}
	comp[pos] = 0;
	if (pos > 0 && !isComponentValid(a, b, comp)) {
		return false;
	}
	return true;
}

void addresult(const char* s) {
	if (results.size() > results_size) {
		results.clear();
	}
	results.insert(compress(s));
}
bool solve(char* s, int slen, int a, int b, int level) {
	int start = 0, end = slen;

	s[slen] = (char)a + 1;
	s[slen + 1] = (char)b + 1;
	s[slen + 2] = 0;
	string s1 = s;
	s[slen] = 0;
	auto it = results.find(compress(s1.c_str()));
	if (it != results.end()) {
		return false;
	}

	// find indexes of first C and last W
	int firstC = 0;
	int pos = a;
	while (true) {
		if (s[firstC] == 'C') {
			break;
		}
		if (s[firstC] == 'O' || s[firstC] == 'W') {
			return false;
		}
		if (!compareComp(s[firstC], pos)) {
			return false;
		}
		if (++firstC >= end) {
			return true;
		}
	}
	int a_next = pos;
	int lastW = end - 1;
	pos = b - 1;
	while (true) {
		if (s[lastW] == 'W') {
			break;
		}
		if (s[lastW] == 'C' || s[lastW] == 'O') {
			return false;
		}
		if (!compareCompReverse(s[lastW], pos)) {
			return false;
		}
		if (--lastW <= firstC) {
			return false;
		}
	}
	int b_next = pos + 1;

	for (int i = firstC; i < lastW; i++) {
		if (s[i] != 'C') {
			continue;
		}
		// s[i] is the first 'C'
		for (int k = lastW; k > i + 1; k--) {
			if (s[k] != 'W') {
				continue;
			}
			// pair s[i] with this 'O'
			for (int j = i + 1; j < k; j++) {
				if (s[j] != 'O') {
					continue;
				}
				// s[i], s[j], s[k] = C O W
				// create a new string
				char buf[maxlen];
				char comp[maxlen];
				int pos = 0;
				int c1b, c2a, c2b, c3a, c3b, c4a;
				c1b = c2b = c3b = 0;
				for (int l = firstC; l < i; l++) {
					if (s[l] == 'C' || s[l] == 'O' || s[l] == 'W') {
						c1b = pos;
					}
					buf[pos++] = s[l];
				}
				for (int l = j + 1; l < k; l++) {
					if (s[l] == 'C' || s[l] == 'O' || s[l] == 'W') {
						c2b = pos;
					}
					buf[pos++] = s[l];
				}
				for (int l = i + 1; l < j; l++) {
					if (s[l] == 'C' || s[l] == 'O' || s[l] == 'W') {
						c3b = pos;
					}
					buf[pos++] = s[l];
				}
				for (int l = k + 1; l <= lastW; l++) {
					buf[pos++] = s[l];
				}
				buf[pos] = 0;

				int d1 = i;
				int d2 = i + k - j - 1;
				int d3 = k - 2;

				bool d1check = checkComp(buf, d1, a, b, c1b);
				if (!d1check) {
					continue;
				}
				bool d2check = c1b >= d2;
				if (!d2check) {
					d2check = checkComp(buf, d2, a, b, c2b);
					if (!d2check) {
						continue;
					}
				}
				else {
					c2b = c1b;
				}
				bool d3check = c2b >= d3;
				if (!d3check) {
					d3check = checkComp(buf, d3, a, b, c3b);
					if (!d3check) {
						continue;
					}
				}

				if (solve(buf, pos, a_next, b_next, level + 1)) {
					encryptions++;
					return true;
				}
			}
		}
	}
	addresult(s1.c_str());
	return false;
}

bool trim(char* s, int& a, int& b) {
	int start = 0, end = strlen(s);
	// find indexes of first C and last W
	int firstC = 0;
	while (true) {
		if (s[firstC] == 'C') {
			break;
		}
		if (s[firstC] != target[a + firstC]) {
			return false;
		}
		if (++firstC >= end) {
			return true;
		}
	}
	int lastW = end - 1;
	while (true) {
		if (s[lastW] == 'W') {
			break;
		}
		if (s[lastW] != target[b - (end - lastW)]) {
			return false;
		}
		if (--lastW <= firstC) {
			return false;
		}
	}

	a0 = a = a + firstC;
	b0 = b = b - (end - lastW) + 1;
	memmove(encrypted, encrypted + firstC, lastW - firstC + 1);
	encrypted[lastW - firstC + 1] = 0;
	return true;
}

bool transform(char* s) {
	// condense s
	if (!findComponents(s)) {
		return false;
	}

	memcpy((char*)comps + sizeof(comps[0]), components, sizeof(components) - sizeof(comps[0]));
	comps_len = components_len;

	// transform s
	char t[maxlen];
	int i = 0;
	int pos = 0;
	int comp_index = 0;
	while (s[i] != 0) {
		if (s[i] == 'C' || s[i] == 'O' || s[i] == 'W') {
			t[pos++] = s[i++];
			continue;
		}
		t[pos++] = ++comp_index;
		do {
			i++;
		} while (s[i] != 0 && s[i] != 'C' && s[i] != 'O' && s[i] != 'W');
	}
	t[pos] = 0;
	memcpy(s, t, maxlen);
	return true;
}

int main() {
	ifstream fin("cryptcow.in");
	fin.getline(encrypted, sizeof(encrypted));

	int a = 0, b = target_len;
	bool canDecrypt = trim(encrypted, a, b);
	canDecrypt = canDecrypt && findComponents(encrypted);

	if (canDecrypt) {
		memset(flags, 0, sizeof(flags));
		flags_count = components_len;
		canDecrypt = validateAllComponents(a, b);

		if (canDecrypt) {
			transform(encrypted);
			canDecrypt = solve(encrypted, strlen(encrypted), a, b, 0);
		}
	}

	ofstream fout("cryptcow.out");
	if (canDecrypt) {
		fout << 1;
	}
	else {
		fout << 0;
	}
	fout << ' ' << encryptions << '\n';
	//cin >> encrypted;
}
