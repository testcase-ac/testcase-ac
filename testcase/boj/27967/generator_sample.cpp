#include "testlib.h"

#include <string>

using namespace std;

string randomDyck(int pairs) {
    string result;
    int openUsed = 0;
    int balance = 0;
    while ((int)result.size() < 2 * pairs) {
        if (openUsed == pairs) {
            result += ')';
            --balance;
        } else if (balance == 0) {
            result += '(';
            ++openUsed;
            ++balance;
        } else if (rnd.next(2) == 0) {
            result += '(';
            ++openUsed;
            ++balance;
        } else {
            result += ')';
            --balance;
        }
    }
    return result;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int pairs = rnd.next(1, 10);
    int mode = rnd.next(6);
    string restored;

    if (mode == 0) {
        restored.assign(pairs, '(');
        restored.append(pairs, ')');
    } else if (mode == 1) {
        for (int i = 0; i < pairs; ++i) {
            restored += "()";
        }
    } else if (mode == 2) {
        int prefixPairs = rnd.next(0, pairs - 1);
        restored.assign(prefixPairs, '(');
        restored.append(prefixPairs, ')');
        restored.append(pairs - prefixPairs, '(');
        restored.append(pairs - prefixPairs, ')');
    } else {
        restored = randomDyck(pairs);
    }

    string s = restored;
    if (mode == 3) {
        s.assign(2 * pairs, 'G');
    } else {
        int maskMode = rnd.next(4);
        for (char& c : s) {
            bool mask = false;
            if (maskMode == 0) {
                mask = false;
            } else if (maskMode == 1) {
                mask = rnd.next(100) < 30;
            } else if (maskMode == 2) {
                mask = rnd.next(100) < 70;
            } else {
                mask = true;
            }
            if (mask) c = 'G';
        }
    }

    println((int)s.size());
    println(s);
    return 0;
}
