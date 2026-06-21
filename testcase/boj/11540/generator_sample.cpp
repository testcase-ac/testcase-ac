#include "testlib.h"

#include <algorithm>
#include <set>
#include <vector>
using namespace std;

static void addUnique(vector<int>& values, set<int>& seen, int value) {
    if (seen.insert(value).second) values.push_back(value);
}

static void addRange(vector<int>& values, set<int>& seen, int from, int to, int step) {
    for (int x = from; x <= to; x += step) addUnique(values, seen, x);
}

static void fillRandom(vector<int>& values, set<int>& seen, int target, int n) {
    while ((int)values.size() < target) {
        addUnique(values, seen, rnd.next(1, n));
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int n;
    vector<int> alice, bob;
    set<int> seenAlice, seenBob;

    if (mode == 0) {
        n = rnd.next(1, 8);
        int a = rnd.next(1, n);
        int b = rnd.next(1, n);
        fillRandom(alice, seenAlice, a, n);
        fillRandom(bob, seenBob, b, n);
    } else if (mode == 1) {
        n = rnd.next(6, 18);
        addRange(alice, seenAlice, 1, n, 2);
        addRange(bob, seenBob, 2, n, 2);
        if (rnd.next(2)) {
            addUnique(alice, seenAlice, n);
            addUnique(bob, seenBob, 1);
        }
    } else if (mode == 2) {
        n = rnd.next(8, 25);
        int sharedStart = rnd.next(1, n / 2);
        int sharedEnd = rnd.next(sharedStart, n);
        addRange(alice, seenAlice, sharedStart, sharedEnd, 1);
        addRange(bob, seenBob, sharedStart, sharedEnd, 1);
        fillRandom(alice, seenAlice, rnd.next((int)alice.size(), min(n, (int)alice.size() + 4)), n);
        fillRandom(bob, seenBob, rnd.next((int)bob.size(), min(n, (int)bob.size() + 4)), n);
    } else if (mode == 3) {
        n = 1000000000;
        vector<int> anchors = {1, 2, 3, 999999997, 999999998, 999999999, 1000000000};
        shuffle(anchors.begin(), anchors.end());
        for (int i = 0; i < 4; ++i) addUnique(alice, seenAlice, anchors[i]);
        for (int i = 3; i < 7; ++i) addUnique(bob, seenBob, anchors[i]);
        fillRandom(alice, seenAlice, rnd.next(4, 8), n);
        fillRandom(bob, seenBob, rnd.next(4, 8), n);
    } else {
        n = rnd.next(20, 60);
        int a = rnd.next(8, 20);
        int b = rnd.next(8, 20);
        for (int x = 1; x <= n; ++x) {
            if (x % 3 != 0 && (int)alice.size() < a) addUnique(alice, seenAlice, x);
            if (x % 3 != 1 && (int)bob.size() < b) addUnique(bob, seenBob, x);
        }
        fillRandom(alice, seenAlice, a, n);
        fillRandom(bob, seenBob, b, n);
    }

    shuffle(alice.begin(), alice.end());
    shuffle(bob.begin(), bob.end());

    println(n, (int)alice.size(), (int)bob.size());
    println(alice);
    println(bob);

    return 0;
}
