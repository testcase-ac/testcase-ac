#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string randomString(int length, const string& alphabet) {
    string result;
    result.reserve(length);
    for (int i = 0; i < length; ++i) {
        result += rnd.any(alphabet);
    }
    return result;
}

string nearPalindrome(int length, const string& alphabet) {
    string result(length, alphabet[0]);
    for (int i = 0; i < (length + 1) / 2; ++i) {
        char ch = rnd.any(alphabet);
        result[i] = ch;
        result[length - 1 - i] = ch;
    }

    int edits = rnd.next(1, max(1, length / 3));
    for (int i = 0; i < edits; ++i) {
        int pos = rnd.next(0, length - 1);
        result[pos] = rnd.any(alphabet);
    }
    return result;
}

string runString(int length, const string& alphabet) {
    string result;
    while ((int)result.size() < length) {
        char ch = rnd.any(alphabet);
        int run = rnd.next(1, min(6, length - (int)result.size()));
        result += string(run, ch);
    }
    return result;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 8);
    int m = rnd.next(1, 30);
    if (mode == 0) {
        n = 1;
        m = rnd.next(1, 20);
    } else if (mode == 1) {
        n = rnd.next(2, 5);
        m = rnd.next(1, 25);
    } else if (mode == 5) {
        n = rnd.next(9, 26);
        m = rnd.next(20, 60);
    }

    string letters = "abcdefghijklmnopqrstuvwxyz";
    shuffle(letters.begin(), letters.end());
    string alphabet = letters.substr(0, n);
    sort(alphabet.begin(), alphabet.end());

    string s;
    if (mode == 0) {
        s = string(m, alphabet[0]);
    } else if (mode == 1) {
        s = nearPalindrome(m, alphabet);
    } else if (mode == 2) {
        s = runString(m, alphabet);
    } else if (mode == 3) {
        s = randomString(m, alphabet);
    } else if (mode == 4) {
        string half = randomString((m + 1) / 2, alphabet);
        s = half;
        for (int i = m / 2 - 1; i >= 0; --i) {
            s += half[i];
        }
    } else {
        for (int i = 0; i < m; ++i) {
            s += alphabet[i % n];
        }
    }

    println(n, m);
    println(s);

    for (char ch : alphabet) {
        int costMode = rnd.next(0, 4);
        int insertCost;
        int deleteCost;
        if (costMode == 0) {
            insertCost = 0;
            deleteCost = rnd.next(0, 10000);
        } else if (costMode == 1) {
            insertCost = rnd.next(0, 10000);
            deleteCost = 0;
        } else if (costMode == 2) {
            insertCost = rnd.next(9000, 10000);
            deleteCost = rnd.next(9000, 10000);
        } else if (costMode == 3) {
            insertCost = rnd.next(1, 20);
            deleteCost = rnd.next(1, 20);
        } else {
            insertCost = rnd.next(0, 10000);
            deleteCost = rnd.next(0, 10000);
        }
        println(string(1, ch), insertCost, deleteCost);
    }

    return 0;
}
