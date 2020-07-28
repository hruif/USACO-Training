/*
ID: ruifanl1
TASK: lgame
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <string.h>

using namespace std;

int values[26], maxVal, letterTimes[26];
vector<char> letters;
vector<bool> isInDict;
vector<string> ans;
vector<vector<int>> trie;

void setVals() {
	values['q' - 'a'] = 7;
	values['w' - 'a'] = 6;
	values['e' - 'a'] = 1;
	values['r' - 'a'] = 2;
	values['t' - 'a'] = 2;
	values['y' - 'a'] = 5;
	values['u' - 'a'] = 4;
	values['i' - 'a'] = 1;
	values['o' - 'a'] = 3;
	values['p' - 'a'] = 5;
	values['a' - 'a'] = 2;
	values['s' - 'a'] = 1;
	values['d' - 'a'] = 4;
	values['f' - 'a'] = 6;
	values['g' - 'a'] = 5;
	values['h' - 'a'] = 5;
	values['j' - 'a'] = 7;
	values['k' - 'a'] = 6;
	values['l' - 'a'] = 3;
	values['z' - 'a'] = 7;
	values['x' - 'a'] = 7;
	values['c' - 'a'] = 4;
	values['v' - 'a'] = 6;
	values['b' - 'a'] = 5;
	values['n' - 'a'] = 2;
	values['m' - 'a'] = 5;
	return;
}

bool hasLetters(string& word) {
	vector<int> used(26, 0);
	for (int i = 0; i < word.size(); i++) {
		if (word[i] == ' ') {
			continue;
		}
		used[word[i] - 'a']++;
		if (used[word[i] - 'a'] > letterTimes[word[i] - 'a']) {
			return false;
		}
	}
	return true;
}

void dictToTrie(ifstream& fin) {
	string word;
	vector<int> start(26, -1);
	isInDict.push_back(false);
	trie.push_back(start);
	int maxLen = letters.size();
	while (getline(fin, word)) {
		if (word.size() > maxLen) {
			continue;
		}
		if (word == ".") {
			return;
		}
		if (!hasLetters(word)) {
			continue;
		}
		int current = 0;
		for (int i = 0; i < word.length(); i++) {
			if (trie[current][word[i] - 'a'] == -1) {
				vector<int> next(26, -1);
				int nextIndex = trie.size();
				trie.push_back(next);
				isInDict.push_back(false);
				trie[current][word[i] - 'a'] = nextIndex;
				current = nextIndex;
			}
			else {
				current = trie[current][word[i] - 'a'];
			}
		}
		isInDict[current] = true;
	}
}

bool isWord(string& word) {
	int index = 0;
	for (int i = 0; i < word.size(); i++) {
		if (word[i] == ' ') {
			if (!isInDict[index]) {
				return false;
			}
			index = 0;
			continue;
		}
		int next = trie[index][word[i] - 'a'];
		if (next > 0) {
			index = next;
		}
		else {
			return false;
		}
	}
	if (!isInDict[index]) {
		return false;
	}
	return true;
}

bool isWords(string& words) {
	int space = 0;
	while (words[space] != ' ') {
		space++;
	}
	space++;
	for (int i = 0; i < 3; i++) {
		if (words[i] > words[i + space]) {
			return false;
		}
		else if (words[i] < words[i + space]) {
			return true;
		}
	}
	return true;
}

int findVal(string& word) {
	int val = 0;
	for (int i = 0; i < word.size(); i++) {
		if (word[i] == ' ') {
			continue;
		}
		val += values[word[i] - 'a'];
	}
	return val;
}

void addLetter(int index, string& word, int len, int maxLen, int numWords) {
	if (len != maxLen) {
		for (int i = 0; i < 26; i++) {
			int next = trie[index][i];
			if (next > 0) {
				word.push_back(i + 'a');
				addLetter(next, word, len + 1, maxLen, numWords);
				word.pop_back();
			}
		}
		if (len == 3 || len == 4) {
			word.push_back(' ');
			addLetter(0, word, len + 1, maxLen + 1, numWords + 1);
			word.pop_back();
		}
	}
	if (isWord(word)) {
		if (numWords > 1) {
			if (!hasLetters(word)) {
				return;
			}
			if (!isWords(word)) {
				return;
			}
		}
		int val = findVal(word);
		if (val == maxVal) {
			for (int i = 0; i < ans.size(); i++) {
				if (word == ans[i]) {
					return;
				}
			}
			ans.push_back(word);
		}
		if (val > maxVal) {
			ans.clear();
			ans.push_back(word);
			maxVal = val;
		}
	}
	return;
}

void genAndTest() {
	string word;
	addLetter(0, word, 0, letters.size(), 1);

}

void sortInput() {
	for (int i = 0; i < letters.size() - 1; i++) {
		for (int j = i + 1; j < letters.size(); j++) {
			if (letters[i] > letters[j]) {
				char tmp = letters[i];
				letters[i] = letters[j];
				letters[j] = tmp;
			}
		}
	}
}

int main() {
	setVals();
	ifstream fin("lgame.in");
	char letter;
	while (fin >> letter) {
		letterTimes[letter - 'a']++;
		letters.push_back(letter);
	}
	sortInput();

	ifstream dictFin("lgame.dict");
	dictToTrie(dictFin);

	genAndTest();

	ofstream fout("lgame.out");
	fout << maxVal << '\n';
	for (int i = 0; i < ans.size(); i++) {
		fout << ans[i] << '\n';
	}
}