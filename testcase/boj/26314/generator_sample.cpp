#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

string makeName(int len, int mode) {
    const string vowels = "aeiou";
    const string consonants = "bcdfghjklmnpqrstvwxyz";
    string s;
    s.reserve(len);

    int vowelCount;
    if (mode == 0) {
        vowelCount = rnd.next(len / 2 + 1, len);
    } else if (mode == 1) {
        vowelCount = rnd.next(0, (len - 1) / 2);
    } else if (mode == 2) {
        vowelCount = len / 2;
    } else {
        vowelCount = rnd.next(0, len);
    }

    for (int i = 0; i < vowelCount; ++i) {
        s += rnd.any(vowels);
    }
    for (int i = vowelCount; i < len; ++i) {
        s += rnd.any(consonants);
    }
    shuffle(s.begin(), s.end());
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(1, 12);
    println(n);

    for (int i = 0; i < n; ++i) {
        int mode = rnd.next(0, 3);
        int lengthMode = rnd.next(0, 4);
        int len;
        if (lengthMode == 0) {
            len = 1;
        } else if (lengthMode == 1) {
            len = 20;
        } else if (lengthMode == 2) {
            len = rnd.next(2, 5);
        } else {
            len = rnd.next(6, 19);
        }
        println(makeName(len, mode));
    }

    return 0;
}
