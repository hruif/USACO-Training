/*
ID: ruifanl1
TASK: calfflac
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <ctype.h>

using namespace std;

vector<char> input;
vector<int> letters; // indexes of letters in input

bool isLetter(char c) {
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool sameLetter(char a, char b) {
	if (isupper(a)) {
		a -= 'A';
		a += 'a';
	}
	if (isupper(b)) {
		b -= 'A';
		b += 'a';
	}
	return a == b;
}

int longestPalindrome(int middle) {
	int left = middle - 1;
	int right = middle + 1;
	while (left >= 0 && right < letters.size() && sameLetter(input[letters[left]], input[letters[right]])) {
		left--;
		right++;
	}
	left++;
	right--;
	int len1 = right - left + 1;

	left = middle;
	right = middle + 1;
	while (left >= 0 && right < letters.size() && sameLetter(input[letters[left]], input[letters[right]])) {
		left--;
		right++;
	}
	left++;
	right--;
	int len2 = right - left + 1;

	return len1 > len2 ? len1 : len2;
}

int main() {
	ifstream fin("calfflac.in");
	char c;
	while (fin.get(c)) {
		if (isLetter(c)) {
			letters.push_back(input.size());
		}
		input.push_back(c);
	}

	int middle = letters.size() / 2;
	int longest = longestPalindrome(middle);
	int bestIndex = middle;
	for (int i = 1; i <= middle; i++) {
		int t = longestPalindrome(middle - i);
		if (t >= longest) {
			longest = t;
			bestIndex = middle - i;
		}
		t = longestPalindrome(middle + i);
		if (t > longest) {
			longest = t;
			bestIndex = middle + i;
		}
		if ((middle - i) * 2 < longest) {
			break;
		}
	}

	int left;
	int right;
	if (longest % 2 == 0) {
		left = bestIndex - longest / 2 + 1;
		right = bestIndex + longest / 2;
	}
	else {
		left = bestIndex - longest / 2;
		right = bestIndex + longest / 2;
	}

	ofstream fout("calfflac.out");
	fout << right - left + 1 << '\n';
	left = letters[left];
	right = letters[right];
	for (int i = left; i <= right; i++) {
		fout << input[i];
	}
	fout << '\n';
}