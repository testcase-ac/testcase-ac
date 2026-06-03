#include "testlib.h"
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

string alphabetPrefix(int count) {
    string letters;
    for (int i = 0; i < count; ++i) letters += char('a' + i);
    return letters;
}

string randomFromAlphabet(int length, const string& alphabet) {
    string s;
    for (int i = 0; i < length; ++i) s += rnd.any(alphabet);
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, 26);
    string s;

    if (mode == 0) {
        int length = rnd.next(1, 30);
        int kinds = rnd.next(1, n);
        s = randomFromAlphabet(length, alphabetPrefix(kinds));
    } else if (mode == 1) {
        int length = rnd.next(max(3, n), 35);
        int kinds = rnd.next(n + 1, 26);
        s = randomFromAlphabet(length, alphabetPrefix(kinds));
    } else if (mode == 2) {
        int length = rnd.next(8, 40);
        int kinds = rnd.next(3, 26);
        n = rnd.next(2, min(25, kinds - 1));
        string letters = alphabetPrefix(kinds);
        for (int i = 0; i < length; ++i) s += letters[i % kinds];
    } else if (mode == 3) {
        int runs = rnd.next(3, 12);
        int kinds = rnd.next(2, 26);
        n = rnd.next(2, kinds);
        string letters = alphabetPrefix(kinds);
        for (int i = 0; i < runs; ++i) {
            int runLength = rnd.next(1, 8);
            s += string(runLength, letters[i % kinds]);
        }
    } else if (mode == 4) {
        n = rnd.next(2, 26);
        string letters = alphabetPrefix(n);
        int left = rnd.next(1, 10);
        int middle = rnd.next(1, 12);
        int right = rnd.next(1, 10);
        s = randomFromAlphabet(left, letters);
        s += string(middle, 'z');
        s += randomFromAlphabet(right, letters);
    } else {
        n = rnd.next(20, 26);
        s = alphabetPrefix(26);
        if (rnd.next(0, 1)) reverse(s.begin(), s.end());
    }

    println(n);
    println(s);
    return 0;
}
