#include "testlib.h"

#include <algorithm>
#include <set>
#include <vector>
using namespace std;

const int MIN_VALUE = -10000000;
const int MAX_VALUE = 10000000;

int randomValue(int lo, int hi) {
    return rnd.next(lo, hi);
}

void addUnique(set<int>& used, vector<int>& values, int x) {
    if (x < MIN_VALUE || x > MAX_VALUE) return;
    if (used.insert(x).second) values.push_back(x);
}

int nearbyAbsent(const set<int>& cards, int anchor) {
    int x = anchor + rnd.next(-3, 3);
    x = max(MIN_VALUE, min(MAX_VALUE, x));
    for (int tries = 0; tries < 20 && cards.count(x); ++tries) {
        x += rnd.next(0, 1) == 0 ? -1 : 1;
        x = max(MIN_VALUE, min(MAX_VALUE, x));
    }
    while (cards.count(x)) {
        x = randomValue(MIN_VALUE, MAX_VALUE);
    }
    return x;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 30);
    set<int> used;
    vector<int> cards;

    if (mode == 0) {
        int lo = rnd.next(-20, 10);
        int hi = rnd.next(lo + n + 4, lo + n + 35);
        while ((int)cards.size() < n) addUnique(used, cards, randomValue(lo, hi));
    } else if (mode == 1) {
        vector<int> special = {MIN_VALUE, MIN_VALUE + 1, -1, 0, 1, MAX_VALUE - 1, MAX_VALUE};
        shuffle(special.begin(), special.end());
        for (int x : special) {
            if ((int)cards.size() < n) addUnique(used, cards, x);
        }
        while ((int)cards.size() < n) addUnique(used, cards, randomValue(-100, 100));
    } else if (mode == 2) {
        int start = rnd.next(-1000, 1000);
        int step = rnd.next(1, 7);
        for (int i = 0; i < n; ++i) addUnique(used, cards, start + i * step);
    } else if (mode == 3) {
        n = rnd.next(20, 80);
        while ((int)cards.size() < n) addUnique(used, cards, randomValue(-1000000, 1000000));
    } else if (mode == 4) {
        n = rnd.next(1, 8);
        while ((int)cards.size() < n) addUnique(used, cards, randomValue(-5, 5));
    } else {
        while ((int)cards.size() < n) addUnique(used, cards, randomValue(MIN_VALUE, MAX_VALUE));
    }

    shuffle(cards.begin(), cards.end());

    int m = rnd.next(1, 40);
    vector<int> queries;
    for (int i = 0; i < m; ++i) {
        int choice = rnd.next(0, 99);
        if (choice < 45) {
            queries.push_back(rnd.any(cards));
        } else if (choice < 75) {
            queries.push_back(nearbyAbsent(used, rnd.any(cards)));
        } else if (!queries.empty() && choice < 90) {
            queries.push_back(rnd.any(queries));
        } else {
            queries.push_back(randomValue(MIN_VALUE, MAX_VALUE));
        }
    }

    println((int)cards.size());
    println(cards);
    println((int)queries.size());
    println(queries);

    return 0;
}
