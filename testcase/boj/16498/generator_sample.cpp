#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

const int MIN_CARD = -100000000;
const int MAX_CARD = 100000000;

int clampCard(long long x) {
    return int(max<long long>(MIN_CARD, min<long long>(MAX_CARD, x)));
}

vector<int> makeCluster(int n, int center, int radius, bool manyDuplicates) {
    vector<int> cards;
    cards.reserve(n);
    for (int i = 0; i < n; ++i) {
        int delta = manyDuplicates && rnd.next(100) < 45 ? 0 : rnd.next(-radius, radius);
        cards.push_back(clampCard((long long)center + delta));
    }
    shuffle(cards.begin(), cards.end());
    return cards;
}

vector<int> makeRange(int n, int lo, int hi) {
    vector<int> cards;
    cards.reserve(n);
    for (int i = 0; i < n; ++i) {
        cards.push_back(rnd.next(lo, hi));
    }
    shuffle(cards.begin(), cards.end());
    return cards;
}

void printCards(const vector<int>& a, const vector<int>& b, const vector<int>& c) {
    println((int)a.size(), (int)b.size(), (int)c.size());
    println(a);
    println(b);
    println(c);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    vector<int> a, b, c;

    if (mode == 0) {
        int base = rnd.next(-20, 20);
        a = {base};
        b = {clampCard((long long)base + rnd.next(-3, 3))};
        c = {clampCard((long long)base + rnd.next(-3, 3))};
    } else if (mode == 1) {
        int center = rnd.next(-1000, 1000);
        int radius = rnd.next(0, 12);
        a = makeCluster(rnd.next(1, 9), center + rnd.next(-5, 5), radius, true);
        b = makeCluster(rnd.next(1, 9), center + rnd.next(-5, 5), radius, true);
        c = makeCluster(rnd.next(1, 9), center + rnd.next(-5, 5), radius, true);
    } else if (mode == 2) {
        int start = rnd.next(-10000, 9900);
        int gap1 = rnd.next(0, 80);
        int gap2 = rnd.next(0, 80);
        a = makeRange(rnd.next(2, 8), start, start + rnd.next(0, 30));
        b = makeRange(rnd.next(2, 8), start + gap1, start + gap1 + rnd.next(0, 30));
        c = makeRange(rnd.next(2, 8), start + gap1 + gap2, start + gap1 + gap2 + rnd.next(0, 30));
    } else if (mode == 3) {
        vector<int> anchors = {MIN_CARD, MIN_CARD + 1, -1, 0, 1, MAX_CARD - 1, MAX_CARD};
        int n1 = rnd.next(1, 7), n2 = rnd.next(1, 7), n3 = rnd.next(1, 7);
        for (int i = 0; i < n1; ++i) a.push_back(rnd.any(anchors));
        for (int i = 0; i < n2; ++i) b.push_back(rnd.any(anchors));
        for (int i = 0; i < n3; ++i) c.push_back(rnd.any(anchors));
        shuffle(a.begin(), a.end());
        shuffle(b.begin(), b.end());
        shuffle(c.begin(), c.end());
    } else {
        int shared = rnd.next(-50000, 50000);
        a = makeCluster(rnd.next(3, 12), shared, rnd.next(0, 100), rnd.next(0, 1));
        b = makeCluster(rnd.next(3, 12), shared + rnd.next(-50, 50), rnd.next(0, 100), rnd.next(0, 1));
        c = makeCluster(rnd.next(3, 12), shared + rnd.next(-50, 50), rnd.next(0, 100), rnd.next(0, 1));
        if (rnd.next(100) < 60) a[rnd.next((int)a.size())] = shared;
        if (rnd.next(100) < 60) b[rnd.next((int)b.size())] = shared;
        if (rnd.next(100) < 60) c[rnd.next((int)c.size())] = shared;
    }

    printCards(a, b, c);
    return 0;
}
