#include "testlib.h"

#include <string>

using namespace std;

char rollChar(int pins) {
    return pins == 0 ? '-' : char('0' + pins);
}

char randomRoll(int lo, int hi) {
    return rollChar(rnd.next(lo, hi));
}

string openPair(int style) {
    int first;
    int second;

    if (style == 0) {
        first = rnd.next(0, 1);
        second = rnd.next(0, 1);
    } else if (style == 1) {
        first = rnd.next(0, 9);
        second = rnd.next(0, 9 - first);
    } else {
        first = rnd.next(0, 8);
        second = rnd.next(0, 8 - first);
    }

    return string() + rollChar(first) + rollChar(second);
}

string sparePair(int style) {
    int first = style == 0 ? rnd.next(0, 2) : rnd.next(0, 9);
    return string() + rollChar(first) + 'P';
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    string score;

    for (int frame = 1; frame <= 9; ++frame) {
        int choice;
        if (mode == 0) {
            choice = rnd.next(0, 9) < 7 ? 0 : rnd.next(1, 2);
        } else if (mode == 1) {
            choice = rnd.next(0, 9) < 7 ? 1 : rnd.next(0, 1) * 2;
        } else if (mode == 2) {
            choice = rnd.next(0, 9) < 7 ? 2 : rnd.next(0, 1);
        } else {
            choice = rnd.next(0, 2);
        }

        if (choice == 0) {
            score += 'S';
        } else if (choice == 1) {
            score += sparePair(mode % 2);
        } else {
            score += openPair(mode % 3);
        }
    }

    int tenth = mode == 3 ? rnd.next(0, 1) : rnd.next(0, 2);
    if (tenth == 0) {
        score += 'S';
        if (rnd.next(0, 1) == 0) {
            score += 'S';
            score += rnd.next(0, 2) == 0 ? 'S' : randomRoll(0, 9);
        } else if (rnd.next(0, 1) == 0) {
            score += sparePair(mode % 2);
        } else {
            score += openPair(mode % 3);
        }
    } else if (tenth == 1) {
        score += sparePair(mode % 2);
        score += rnd.next(0, 3) == 0 ? 'S' : randomRoll(0, 9);
    } else {
        score += openPair(mode % 3);
    }

    println(score);
    return 0;
}
