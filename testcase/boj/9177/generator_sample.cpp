#include "testlib.h"

#include <string>

using namespace std;

string makeWord(int length, const string& alphabet) {
    string result;
    result.reserve(length);
    for (int i = 0; i < length; ++i) {
        result.push_back(rnd.any(alphabet));
    }
    return result;
}

string interleaveWords(const string& a, const string& b, int mode) {
    int i = 0;
    int j = 0;
    string c;
    c.reserve(a.size() + b.size());

    while (i < static_cast<int>(a.size()) || j < static_cast<int>(b.size())) {
        bool takeA;
        if (i == static_cast<int>(a.size())) {
            takeA = false;
        } else if (j == static_cast<int>(b.size())) {
            takeA = true;
        } else if (mode == 0) {
            takeA = true;
        } else if (mode == 1) {
            takeA = false;
        } else if (mode == 2) {
            takeA = ((i + j) % 2 == 0);
        } else {
            takeA = rnd.next(0, 1) == 0;
        }

        if (takeA) {
            c.push_back(a[i++]);
        } else {
            c.push_back(b[j++]);
        }
    }

    return c;
}

char absentLetter(const string& a, const string& b) {
    string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    for (char candidate : letters) {
        if (a.find(candidate) == string::npos && b.find(candidate) == string::npos) {
            return candidate;
        }
    }
    return 'A';
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(3, 12);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int mode = rnd.next(0, 5);
        int lenA = rnd.next(1, mode == 5 ? 25 : 10);
        int lenB = rnd.next(1, mode == 5 ? 25 : 10);

        string alphabet;
        if (mode == 0) {
            alphabet = "ab";
        } else if (mode == 1) {
            alphabet = "AaBb";
        } else if (mode == 2) {
            alphabet = "abcXYZ";
        } else {
            int alphabetSize = rnd.next(2, 8);
            alphabet = string("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ").substr(0, alphabetSize);
        }

        string a = makeWord(lenA, alphabet);
        string b = makeWord(lenB, alphabet);
        string c = interleaveWords(a, b, rnd.next(0, 3));

        if (mode == 4 || (mode == 5 && rnd.next(0, 1) == 0)) {
            int pos = rnd.next(0, static_cast<int>(c.size()) - 1);
            c[pos] = absentLetter(a, b);
        }

        println(a, b, c);
    }

    return 0;
}
