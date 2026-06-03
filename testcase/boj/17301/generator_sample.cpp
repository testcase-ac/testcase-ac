#include "testlib.h"

#include <set>
#include <string>
#include <vector>

using namespace std;

string randomWord(int mode) {
    int len = rnd.next(1, 10);
    string word(len, 'A');

    if (mode == 0) {
        for (char& ch : word) ch = rnd.any(string("NC"));
    } else if (mode == 1) {
        for (char& ch : word) ch = rnd.any(string("ABCDEFGHIJKLMNOPQRSTUVWXYZ"));
        word[rnd.next(len)] = rnd.any(string("NC"));
    } else if (mode == 2) {
        for (char& ch : word) ch = rnd.any(string("ABDEFGHIJKLMOPQRSTUVWXYZ"));
        word[rnd.next(len)] = 'N';
    } else if (mode == 3) {
        for (char& ch : word) ch = rnd.any(string("ABDEFGHIJKLMOPQRSTUVWXYZ"));
        word[rnd.next(len)] = 'C';
    } else {
        len = rnd.next(2, 10);
        word.assign(len, 'A');
        for (char& ch : word) ch = rnd.any(string("ADEFGHIJKLMOPQRSTUVWXYZ"));
        int first = rnd.next(0, len - 2);
        int second = rnd.next(first + 1, len - 1);
        word[first] = 'N';
        word[second] = 'C';
    }

    return word;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int sizeMode = rnd.next(5);
    int n;
    if (sizeMode == 0) {
        n = 1;
    } else if (sizeMode <= 2) {
        n = rnd.next(2, 8);
    } else {
        n = rnd.next(9, 25);
    }

    set<string> used;
    vector<string> words;
    while ((int)words.size() < n) {
        string word = randomWord(rnd.next(5));
        if (used.insert(word).second) words.push_back(word);
    }

    shuffle(words.begin(), words.end());

    println(n);
    for (const string& word : words) println(word);

    return 0;
}
