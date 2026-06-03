#include "testlib.h"
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

string shuffledLetters(int k) {
    string letters = "abcdefghijklmnopqrstuvwxyz";
    shuffle(letters.begin(), letters.end());
    return letters.substr(0, k);
}

string makeString(int mode) {
    int alphabetSize;
    int len;

    if (mode == 0) {
        alphabetSize = 1;
        len = rnd.next(1, 30);
    } else if (mode == 1) {
        alphabetSize = 2;
        len = rnd.next(2, 40);
    } else if (mode == 2) {
        alphabetSize = 3;
        len = rnd.next(3, 45);
    } else if (mode == 3) {
        alphabetSize = rnd.next(4, 10);
        len = rnd.next(alphabetSize, 55);
    } else {
        alphabetSize = rnd.next(11, 26);
        len = rnd.next(alphabetSize, 100);
    }

    string letters = shuffledLetters(alphabetSize);
    vector<int> counts(alphabetSize, 1);
    int remaining = len - alphabetSize;

    if (mode == 1 && remaining > 0) {
        int firstExtra = rnd.next(0, remaining);
        counts[0] += firstExtra;
        counts[1] += remaining - firstExtra;
    } else if (mode == 2 && remaining > 0) {
        counts[0] += rnd.next(max(0, remaining - 2), remaining);
        remaining = len - alphabetSize - (counts[0] - 1);
        counts[1] += rnd.next(0, remaining);
        counts[2] += remaining - (counts[1] - 1);
    } else {
        while (remaining-- > 0) {
            int idx = rnd.next(alphabetSize);
            if (mode >= 3 && rnd.next(0, 3) == 0) idx = rnd.wnext(alphabetSize, 3);
            counts[idx]++;
        }
    }

    string s;
    for (int i = 0; i < alphabetSize; ++i) s += string(counts[i], letters[i]);
    shuffle(s.begin(), s.end());
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(1, 25);
    println(n);

    for (int i = 0; i < n; ++i) {
        int mode = rnd.next(0, 4);
        if (i < 5) mode = i;
        println(makeString(mode));
    }

    return 0;
}
