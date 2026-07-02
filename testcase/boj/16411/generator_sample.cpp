#include "testlib.h"
#include <string>

using namespace std;

const string letters = "ABCDEF";

string randomState() {
    string s;
    for (int i = 0; i < 8; ++i) {
        s += rnd.any(letters);
    }
    return s;
}

string repeatedState() {
    return string(8, rnd.any(letters));
}

string patternedState() {
    string base = letters;
    shuffle(base.begin(), base.end());

    string s;
    int period = rnd.next(1, 6);
    for (int i = 0; i < 8; ++i) {
        s += base[i % period];
    }
    return s;
}

string mutateState(string s) {
    int changes = rnd.next(1, 4);
    for (int i = 0; i < changes; ++i) {
        int pos = rnd.next(0, 7);
        char next = rnd.any(letters);
        if (rnd.next(0, 2) == 0) {
            next = char('A' + ((s[pos] - 'A' + rnd.next(1, 5)) % 6));
        }
        s[pos] = next;
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    string start;
    string target;

    if (mode == 0) {
        start = randomState();
        target = start;
    } else if (mode == 1) {
        start = repeatedState();
        target = repeatedState();
    } else if (mode == 2) {
        start = patternedState();
        target = mutateState(start);
    } else if (mode == 3) {
        start = randomState();
        target = mutateState(start);
    } else if (mode == 4) {
        start = patternedState();
        target = patternedState();
    } else if (mode == 5) {
        start = randomState();
        target = repeatedState();
    } else {
        start = randomState();
        target = randomState();
    }

    println(start);
    println(target);

    return 0;
}
