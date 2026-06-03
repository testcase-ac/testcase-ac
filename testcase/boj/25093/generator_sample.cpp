#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

char randomLetter(char lo = 'A', char hi = 'Z') {
    return char('A' + rnd.next(lo - 'A', hi - 'A'));
}

string repeatedChar() {
    int len = rnd.next(1, 30);
    return string(len, randomLetter());
}

string monotoneRuns(bool increasing) {
    int groups = rnd.next(2, 10);
    string s;
    char cur = randomLetter('A', 'Z' - groups + 1);
    if (!increasing) cur = randomLetter('A' + groups - 1, 'Z');

    for (int i = 0; i < groups; ++i) {
        int run = rnd.next(1, 5);
        s += string(run, cur);
        cur += increasing ? 1 : -1;
    }
    return s;
}

string alternatingSlope() {
    int len = rnd.next(2, 35);
    string s;
    char low = randomLetter('A', 'M');
    char high = randomLetter('N', 'Z');
    for (int i = 0; i < len; ++i) {
        s += (i % 2 == 0 ? low : high);
        if (rnd.next(4) == 0) low = randomLetter('A', 'M');
        if (rnd.next(4) == 0) high = randomLetter('N', 'Z');
    }
    return s;
}

string repeatedBlock() {
    int blockLen = rnd.next(2, 8);
    int repeats = rnd.next(2, 8);
    string block;
    for (int i = 0; i < blockLen; ++i) block += randomLetter('A', 'F');

    string s;
    for (int i = 0; i < repeats; ++i) s += block;
    return s;
}

string alphabetWindow() {
    int len = rnd.next(5, 50);
    char hi = randomLetter('C', 'Z');
    string s;
    for (int i = 0; i < len; ++i) s += randomLetter('A', hi);
    return s;
}

string fullRandom() {
    int len = rnd.next(1, 100);
    string s;
    for (int i = 0; i < len; ++i) s += randomLetter();
    return s;
}

string makeCase() {
    int mode = rnd.next(7);
    if (mode == 0) return repeatedChar();
    if (mode == 1) return monotoneRuns(true);
    if (mode == 2) return monotoneRuns(false);
    if (mode == 3) return alternatingSlope();
    if (mode == 4) return repeatedBlock();
    if (mode == 5) return alphabetWindow();
    return fullRandom();
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 20);
    println(t);
    for (int i = 0; i < t; ++i) {
        println(makeCase());
    }

    return 0;
}
