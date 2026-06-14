#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

const string VOWELS = "aeiou";
const string CONSONANTS = "bcdfghjklmnpqrstvwxyz";

char randomVowel() {
    return rnd.any(VOWELS);
}

char randomConsonant() {
    return rnd.any(CONSONANTS);
}

string consonantRun(int len) {
    string s;
    for (int i = 0; i < len; ++i) {
        s += randomConsonant();
    }
    return s;
}

string makeNoVowel(int len) {
    return consonantRun(len);
}

string makeAllVowels(int len) {
    string s;
    for (int i = 0; i < len; ++i) {
        s += randomVowel();
    }
    return s;
}

string makeAlternating(int len) {
    string s;
    bool vowelTurn = rnd.next(0, 1) == 0;
    for (int i = 0; i < len; ++i) {
        s += vowelTurn ? randomVowel() : randomConsonant();
        vowelTurn = !vowelTurn;
    }
    return s;
}

string makeSyllableBoundaryCase() {
    int vowelCount = rnd.next(2, 8);
    string s = consonantRun(rnd.next(0, 4));
    for (int i = 0; i < vowelCount; ++i) {
        s += randomVowel();
        if (i + 1 < vowelCount) {
            int runLength = rnd.next(0, 7);
            s += consonantRun(runLength);
        }
    }
    s += consonantRun(rnd.next(0, 4));
    return s;
}

string makeLongMiddleRun() {
    string s = consonantRun(rnd.next(0, 3));
    s += randomVowel();
    s += consonantRun(rnd.next(8, 25));
    s += randomVowel();
    s += consonantRun(rnd.next(0, 3));
    return s;
}

string makeWord() {
    int mode = rnd.next(0, 5);
    if (mode == 0) return makeNoVowel(rnd.next(1, 25));
    if (mode == 1) return makeAllVowels(rnd.next(1, 25));
    if (mode == 2) return makeAlternating(rnd.next(1, 30));
    if (mode == 3) return makeSyllableBoundaryCase();
    if (mode == 4) return makeLongMiddleRun();

    string s = makeSyllableBoundaryCase();
    if (rnd.next(0, 1) == 0) {
        s = consonantRun(rnd.next(5, 12)) + s;
    } else {
        s += consonantRun(rnd.next(5, 12));
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 35);
    vector<string> words;

    for (int i = 0; i < t; ++i) {
        string s = makeWord();
        words.push_back(s);
    }

    println(t);
    for (const string& word : words) {
        println(word);
    }

    return 0;
}
