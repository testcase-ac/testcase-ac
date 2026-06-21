#include "testlib.h"
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

char randomUpper() {
    return char('A' + rnd.next(26));
}

char randomLower() {
    return char('a' + rnd.next(26));
}

char randomNonTarget(char bomb) {
    char shield = char(bomb - 'A' + 'a');
    while (true) {
        char c = rnd.next(2) == 0 ? randomUpper() : randomLower();
        if (c != bomb && c != shield) return c;
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    char bomb = randomUpper();
    char shield = char(bomb - 'A' + 'a');
    int mode = rnd.next(5);
    int n = 1;
    string s;

    if (mode == 0) {
        n = rnd.next(1, 3);
        s.append(rnd.next(1, n), bomb);
        while ((int)s.size() < n) s.push_back(rnd.next(2) == 0 ? shield : randomNonTarget(bomb));
    } else if (mode == 1) {
        n = rnd.next(4, 18);
        int bombs = rnd.next(1, max(1, n * 2 / 3));
        s.append(bombs, bomb);
        while ((int)s.size() < n) s.push_back(randomNonTarget(bomb));
    } else if (mode == 2) {
        n = rnd.next(5, 24);
        int bombs = rnd.next(1, max(1, n / 4));
        int shields = rnd.next(2, n - bombs);
        s.append(bombs, bomb);
        s.append(shields, shield);
        while ((int)s.size() < n) s.push_back(randomNonTarget(bomb));
    } else if (mode == 3) {
        bomb = char('B' + rnd.next(25));
        shield = char(bomb - 'A' + 'a');
        n = rnd.next(6, 26);
        int bombs = rnd.next(1, 4);
        s.append(bombs, bomb);
        int beforeCount = rnd.next(1, min(6, n - bombs));
        for (int i = 0; i < beforeCount; ++i) {
            s.push_back(rnd.next(2) == 0 ? char('A' + rnd.next(bomb - 'A')) : randomLower());
        }
        while ((int)s.size() < n) s.push_back(rnd.next(3) == 0 ? shield : randomNonTarget(bomb));
    } else {
        n = rnd.next(8, 30);
        int bombs = rnd.next(1, 6);
        int shields = rnd.next(0, 6);
        s.append(bombs, bomb);
        s.append(min(shields, n - (int)s.size()), shield);
        while ((int)s.size() < n) s.push_back(randomNonTarget(bomb));
    }

    shuffle(s.begin(), s.end());

    println(n, bomb);
    println(s);
    return 0;
}
