/*
ID: ruifanl1
TASK: lgame
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int totalWords, maxLen;
vector<char> usable;
vector<int> inputLetters(26);
vector<vector<char>> allWords, ans;
vector<vector<int>> wordLens(8);

int letterToScore(char l) {
	if (l == 'q') {
		return 7;
	}
	if (l == 'w') {
		return 6;
	}
	if (l == 'e') {
		return 1;
	}
	if (l == 'r') {
		return 2;
	}
	if (l == 't') {
		return 2;
	}
	if (l == 'y') {
		return 5;
	}
	if (l == 'u') {
		return 4;
	}
	if (l == 'i') {
		return 1;
	}
	if (l == 'o') {
		return 3;
	}
	if (l == 'p') {
		return 5;
	}
	if (l == 'a') {
		return 2;
	}
	if (l == 's') {
		return 1;
	}
	if (l == 'd') {
		return 4;
	}
	if (l == 'f') {
		return 6;
	}
	if (l == 'g') {
		return 5;
	}
	if (l == 'h') {
		return 5;
	}
	if (l == 'j') {
		return 7;
	}
	if (l == 'k') {
		return 6;
	}
	if (l == 'l') {
		return 3;
	}
	if (l == 'z') {
		return 7;
	}
	if (l == 'x') {
		return 7;
	}
	if (l == 'c') {
		return 4;
	}
	if (l == 'v') {
		return 6;
	}
	if (l == 'b') {
		return 5;
	}
	if (l == 'n') {
		return 2;
	}
	if (l == 'm') {
		return 5;
	}
	return 0;
}

bool checkWorks(vector<char>& word) {
	vector<bool> foundLetters(26, false);
	int len = word.size();
	if (len > maxLen) {
		return false;
	}
	for (int i = 0; i < len; i++) {
		char letter = word[i];
		if (letter == ' ') {
			continue;
		}
		if (foundLetters[letter - 'a']) {
			return false;
		}
		bool found = false;
		for (int j = 0; j < usable.size(); j++) {
			if (usable[i] == word[j]) {
				found = true;
				foundLetters[letter - 'a'] = true;
				break;
			}
		}
		if (!found) {
			return false;
		}
	}
	return true;
}

void getWords(ifstream& fin) {
	int letter;
	fin >> letter;
	vector<char> tmp;
	allWords.push_back(tmp);
	while (letter != '.') {
		if (letter == '\n') {
			if (!checkWorks(allWords[totalWords])) {
				allWords[totalWords].clear();
				continue;
			}
			wordLens[allWords[totalWords].size()].push_back(totalWords);
			vector<char> word;
			allWords.push_back(word);
			totalWords++;
			continue;
		}
		allWords[totalWords].push_back(letter);
	}
}

void findWords(int len, int totalLen, vector<char>& words, vector<int>& usedLetters) {
	for (int i = 0; i < wordLens[len].size(); i++) {
		int word = wordLens[len][i];
		bool works = true;
		for (int j = 0; j < allWords[word].size(); j++) {
			int letter = allWords[word][j];
			usedLetters[letter - 'a']++;
			if (usedLetters[letter - 'a'] > inputLetters[letter - 'a']) {
				works = false;
			}
			words.push_back(letter);
		}
		if (works) {
			for (int j = maxLen - totalLen; j > 0; j--) {
				findWords(j, totalLen + j, words, usedLetters);
			}
		}
		if (totalLen == maxLen) {
			if (checkWorks(words)) {
				ans.push_back(words);
			}
		}
		for (int j = 0; j < allWords[word].size(); j++) {
			int letter = allWords[word][j];
			usedLetters[letter - 'a']--;
			words.pop_back();
		}
	}
}

void solve() {
	for (int i = 0; i < wordLens[maxLen].size(); i++) {
		ans.push_back(allWords[wordLens[maxLen][i]]);
	}
	vector<char> nextWords;
	vector<bool> usedLetters(26, false);
	int nextLen = maxLen - 1;
	while (nextLen > maxLen - nextLen) {

	}
}

int main() {
	ifstream fin("lgame.in");
	char letter;
	while (fin.get(letter)) {
		if (letter == '\n') {
			break;
		}
		usable.push_back(letter);
		inputLetters[letter - 'a']++;
		maxLen++;
	}
	
	int max = 0;
	for (int i = 0; i < usable.size(); i++) {
		max += letterToScore(usable[i]);
	}

	ifstream finDict("lgame.dict");
	getWords(finDict);



	ofstream fout("lgame.out");
	fout << max << '\n';
	for (int i = 0; i < ans.size(); i++) {
		for (int j = 0; j < ans[i].size(); j++) {
			fout << ans[i][j];
		}
		fout << '\n';
	}
}