#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

string randomName(int length, char first) {
    string s;
    s += first;
    for (int i = 1; i < length; ++i) {
        s += char('A' + rnd.next(26));
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int n;
    if (mode == 0) {
        n = 1;
    } else if (mode == 1) {
        n = rnd.next(2, 8);
    } else if (mode == 2) {
        n = rnd.next(9, 25);
    } else {
        n = rnd.next(26, 100);
    }

    vector<string> names;
    names.reserve(n);

    for (int i = 0; i < n; ++i) {
        bool startsWithC;
        if (mode == 0) {
            startsWithC = rnd.next(2) == 0;
        } else if (mode == 1) {
            startsWithC = i % 2 == 0;
        } else if (mode == 2) {
            startsWithC = rnd.next(100) < 70;
        } else if (mode == 3) {
            startsWithC = rnd.next(100) < 15;
        } else {
            startsWithC = rnd.next(100) < 50;
        }

        int length;
        if (mode == 4 && rnd.next(3) == 0) {
            length = 20;
        } else {
            length = rnd.next(1, 12);
        }

        char first = 'C';
        if (!startsWithC) {
            first = char('A' + rnd.next(25));
            if (first >= 'C') ++first;
        }
        names.push_back(randomName(length, first));
    }

    shuffle(names.begin(), names.end());

    println(n);
    for (const string& name : names) {
        println(name);
    }

    return 0;
}
