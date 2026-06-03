#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

static string makeWord(int length, const string& alphabet) {
    string word;
    word.reserve(length);
    for (int i = 0; i < length; ++i) {
        word.push_back(rnd.any(alphabet));
    }
    return word;
}

static string makeDistinctWord(int length, char base) {
    string word;
    word.reserve(length);
    for (int i = 0; i < length; ++i) {
        word.push_back(static_cast<char>(base + rnd.next(0, 2)));
    }
    return word;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int firstLength = rnd.next(1, 24);
    int secondLength = rnd.next(1, 24);
    string first;
    string second;

    if (mode == 0) {
        firstLength = rnd.next(1, 8);
        secondLength = rnd.next(1, 8);
        first = string(firstLength, 'a');
        second = string(secondLength, 'a');
    } else if (mode == 1) {
        first = makeWord(firstLength, "ab");
        second = makeWord(secondLength, "ab");
    } else if (mode == 2) {
        first = makeDistinctWord(firstLength, 'a');
        second = makeDistinctWord(secondLength, 'x');
    } else if (mode == 3) {
        string alphabet = "abcde";
        first = makeWord(firstLength, alphabet);
        second = first.substr(0, min(firstLength, secondLength));
        while (static_cast<int>(second.size()) < secondLength) {
            second.push_back(rnd.any(alphabet));
        }
    } else if (mode == 4) {
        firstLength = rnd.next(18, 30);
        secondLength = rnd.next(18, 30);
        first = makeWord(firstLength, "abc");
        second = makeWord(secondLength, "bcd");
    } else {
        first = makeWord(firstLength, "abcdefghijklmnopqrstuvwxyz");
        second = makeWord(secondLength, "abcdefghijklmnopqrstuvwxyz");
    }

    int firstPos = 0;
    int secondPos = 0;
    string screen;
    screen.reserve(first.size() + second.size());
    int turn = rnd.next(0, 1);

    while (firstPos < static_cast<int>(first.size()) || secondPos < static_cast<int>(second.size())) {
        if (firstPos == static_cast<int>(first.size())) {
            turn = 1;
        } else if (secondPos == static_cast<int>(second.size())) {
            turn = 0;
        } else if (rnd.next(0, 99) < 35) {
            turn ^= 1;
        }

        int remaining = turn == 0 ? static_cast<int>(first.size()) - firstPos
                                  : static_cast<int>(second.size()) - secondPos;
        int chunk = rnd.next(1, min(remaining, rnd.next(1, 5)));
        if (turn == 0) {
            screen += first.substr(firstPos, chunk);
            firstPos += chunk;
        } else {
            screen += second.substr(secondPos, chunk);
            secondPos += chunk;
        }
    }

    println(first);
    println(second);
    println(screen);
    return 0;
}
