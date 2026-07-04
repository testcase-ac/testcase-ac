#include "testlib.h"

#include <algorithm>
#include <set>
#include <string>
#include <vector>

using namespace std;

string shuffledWord(string letters) {
    shuffle(letters.begin(), letters.end());
    return letters;
}

string randomSortedLetters(int length, int alphabetSize) {
    string letters;
    for (int i = 0; i < length; ++i) {
        letters.push_back(char('a' + rnd.next(alphabetSize)));
    }
    sort(letters.begin(), letters.end());
    return letters;
}

bool addWord(set<string>& used, vector<string>& words, string letters) {
    for (int attempt = 0; attempt < 20; ++attempt) {
        string word = shuffledWord(letters);
        if (used.insert(word).second) {
            words.push_back(word);
            return true;
        }
    }
    return false;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    set<string> used;
    vector<string> words;

    int alphabetSize = rnd.next(3, 9);
    int chainLength = rnd.next(4, 12);
    string letters = randomSortedLetters(rnd.next(1, 3), alphabetSize);

    vector<string> chainKeys;
    chainKeys.push_back(letters);
    addWord(used, words, letters);

    for (int i = 1; i < chainLength && int(letters.size()) < 20; ++i) {
        letters.push_back(char('a' + rnd.next(alphabetSize)));
        sort(letters.begin(), letters.end());
        chainKeys.push_back(letters);
        addWord(used, words, letters);

        if (rnd.next(2) == 0) {
            addWord(used, words, letters);
        }
    }

    int branchCount = rnd.next(3, 10);
    for (int i = 0; i < branchCount; ++i) {
        string branch = rnd.any(chainKeys);
        if (int(branch.size()) < 20) {
            branch.push_back(char('a' + rnd.next(alphabetSize)));
            sort(branch.begin(), branch.end());
        }
        addWord(used, words, branch);
    }

    int noiseCount = rnd.next(4, 20);
    for (int i = 0; i < noiseCount; ++i) {
        int length = rnd.next(1, 20);
        int localAlphabet = rnd.next(1, alphabetSize);
        addWord(used, words, randomSortedLetters(length, localAlphabet));
    }

    while (words.size() < 2) {
        addWord(used, words, randomSortedLetters(rnd.next(1, 20), alphabetSize));
    }

    shuffle(words.begin(), words.end());
    for (const string& word : words) {
        println(word);
    }

    return 0;
}
