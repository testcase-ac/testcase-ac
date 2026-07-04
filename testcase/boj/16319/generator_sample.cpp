#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

vector<int> makeHealths(int count, int mode) {
    vector<int> healths(count);

    if (mode == 0) {
        fill(healths.begin(), healths.end(), 1);
    } else if (mode == 1) {
        fill(healths.begin(), healths.end(), 6);
    } else if (mode == 2) {
        int lo = rnd.next(1, 3);
        int hi = rnd.next(4, 6);
        for (int& health : healths) {
            health = rnd.next(lo, hi);
        }
    } else {
        for (int& health : healths) {
            health = rnd.next(1, 6);
        }
    }

    shuffle(healths.begin(), healths.end());
    return healths;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    int m;
    int d;

    if (mode == 0) {
        n = rnd.next(1, 2);
        m = rnd.next(1, 2);
        d = rnd.next(1, 3);
    } else if (mode == 1) {
        n = 5;
        m = 5;
        d = rnd.next(1, 100);
    } else if (mode == 2) {
        n = rnd.next(1, 5);
        m = rnd.next(1, 5);
        d = rnd.next(1, 8);
    } else if (mode == 3) {
        n = rnd.next(1, 5);
        m = rnd.next(1, 5);
        d = rnd.next(20, 100);
    } else if (mode == 4) {
        n = rnd.next(1, 5);
        m = rnd.next(1, 5);
        d = rnd.next(6, 30);
    } else {
        n = rnd.next(1, 5);
        m = rnd.next(1, 5);
        d = rnd.next(1, 100);
    }

    int ownMode = rnd.next(0, 3);
    int opponentMode = rnd.next(0, 3);
    vector<int> ownHealth = makeHealths(n, ownMode);
    vector<int> opponentHealth = makeHealths(m, opponentMode);

    if (mode == 2) {
        int totalOpponentHealth = 0;
        for (int health : opponentHealth) {
            totalOpponentHealth += health;
        }
        d = rnd.next(1, max(1, totalOpponentHealth - 1));
    } else if (mode == 3) {
        int totalHealth = 0;
        for (int health : ownHealth) {
            totalHealth += health;
        }
        for (int health : opponentHealth) {
            totalHealth += health;
        }
        d = rnd.next(min(100, totalHealth), 100);
    }

    println(n, m, d);
    println(ownHealth);
    println(opponentHealth);

    return 0;
}
