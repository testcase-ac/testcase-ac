#include "testlib.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

namespace {

using Run = pair<char, int>;

char differentLetter(char from) {
    char candidate = static_cast<char>('A' + rnd.next(26));
    if (candidate == from) {
        candidate = static_cast<char>('A' + (candidate - 'A' + 1) % 26);
    }
    return candidate;
}

vector<Run> randomRle(int pairs, int maxLen) {
    vector<Run> runs;
    for (int i = 0; i < pairs; ++i) {
        char letter = static_cast<char>('A' + rnd.next(26));
        if (!runs.empty() && runs.back().first == letter) {
            letter = differentLetter(letter);
        }
        int len = rnd.next(1, maxLen);
        runs.emplace_back(letter, len);
    }
    return runs;
}

void printRle(const vector<Run>& runs) {
    for (const auto& run : runs) {
        cout << run.first << ' ' << run.second << ' ';
    }
    cout << "$\n";
}

}  // namespace

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(4);
    vector<Run> a;
    vector<Run> b;
    vector<Run> c;

    if (mode == 0) {
        int pairs = rnd.next(4, 8);
        a = randomRle(pairs, 20);
        int start = rnd.next(0, pairs - 2);
        int length = rnd.next(2, min(4, pairs - start));

        b.reserve(length);
        b.emplace_back(a[start].first, rnd.next(1, a[start].second));
        for (int i = start + 1; i < start + length - 1; ++i) {
            b.push_back(a[i]);
        }
        b.emplace_back(a[start + length - 1].first, rnd.next(1, a[start + length - 1].second));

        c = randomRle(rnd.next(1, 4), 15);
    } else if (mode == 1) {
        int pairs = rnd.next(3, 7);
        a = randomRle(pairs, 25);
        char absent = 'A';
        vector<bool> used(26, false);
        for (const auto& run : a) {
            used[run.first - 'A'] = true;
        }
        while (used[absent - 'A']) {
            absent++;
        }

        b.emplace_back(absent, rnd.next(1, 10));
        if (rnd.next(2) == 1) {
            b.emplace_back(differentLetter(absent), rnd.next(1, 10));
        }
        c = randomRle(rnd.next(1, 3), 10);
    } else if (mode == 2) {
        char x = static_cast<char>('A' + rnd.next(26));
        char y = differentLetter(x);
        char z = differentLetter(y);
        if (z == x) {
            z = differentLetter(x);
        }

        int left = rnd.next(1, 8);
        int middle = rnd.next(3, 20);
        int remove = rnd.next(1, middle);
        int right = rnd.next(1, 8);
        a = {{y, left}, {x, middle}, {z, right}};
        b = {{x, remove}};
        c = {{y, rnd.next(1, 8)}, {z, rnd.next(1, 8)}};
    } else {
        char x = static_cast<char>('A' + rnd.next(26));
        char y = differentLetter(x);
        char z = differentLetter(y);
        if (z == x) {
            z = differentLetter(x);
        }

        int leftX = rnd.next(2, 15);
        int middleY = rnd.next(1, 15);
        int rightX = rnd.next(2, 15);
        a = {{x, leftX}, {y, middleY}, {x, rightX}, {z, rnd.next(1, 10)}};
        b = {{x, rnd.next(1, leftX)}, {y, middleY}, {x, rnd.next(1, rightX)}};
        c = {{x, rnd.next(1, 12)}};
    }

    printRle(a);
    printRle(b);
    printRle(c);
    return 0;
}
