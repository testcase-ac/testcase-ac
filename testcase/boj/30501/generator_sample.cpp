#include "testlib.h"

#include <string>
#include <vector>
using namespace std;

string randomName(int len, bool containsS) {
    const string noSAlphabet = "ABCDEFGHIJKLMNOPQRTUVWXYZ";
    string name;
    name.reserve(len);

    for (int i = 0; i < len; ++i) {
        name += rnd.any(noSAlphabet);
    }

    if (containsS) {
        name[rnd.next(len)] = 'S';
    }

    return name;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n;
    if (mode == 0) {
        n = 1;
    } else if (mode == 1) {
        n = rnd.next(2, 5);
    } else if (mode == 2) {
        n = rnd.next(6, 20);
    } else if (mode == 3) {
        n = rnd.next(21, 60);
    } else if (mode == 4) {
        n = rnd.next(61, 120);
    } else {
        n = rnd.next(900, 1000);
    }

    vector<string> names;
    names.reserve(n);

    bool longNames = rnd.next(5) == 0;
    for (int i = 0; i < n; ++i) {
        int len;
        if (longNames && rnd.next(4) == 0) {
            len = rnd.next(80, 100);
        } else {
            len = rnd.next(1, 18);
        }
        names.push_back(randomName(len, false));
    }

    if (n > 1 && rnd.next(3) == 0) {
        string repeated = randomName(rnd.next(1, 12), false);
        int repetitions = rnd.next(2, min(n, 8));
        for (int i = 0; i < repetitions; ++i) {
            names[i] = repeated;
        }
    }

    int answerIndex;
    if (mode == 0) {
        answerIndex = 0;
    } else if (mode == 1) {
        answerIndex = rnd.any(vector<int>{0, n - 1});
    } else {
        answerIndex = rnd.next(n);
    }

    int answerLength = longNames ? rnd.next(80, 100) : rnd.next(1, 30);
    names[answerIndex] = randomName(answerLength, true);

    println(n);
    for (const string& name : names) {
        println(name);
    }

    return 0;
}
