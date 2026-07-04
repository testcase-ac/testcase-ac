#include "testlib.h"

#include <array>
#include <vector>

using namespace std;

struct Case {
    int n;
    array<int, 6> counts;
};

Case makeCase(array<int, 6> counts) {
    int n = 0;
    for (int count : counts) n += count;
    return {n, counts};
}

Case impossibleComposition(int n, int activeColors) {
    vector<int> colors = {0, 1, 2, 3, 4, 5};
    shuffle(colors.begin(), colors.end());
    colors.resize(activeColors);

    array<int, 6> counts{};
    counts[colors[0]] = rnd.next(n / 2 + 1, n);
    for (int i = counts[colors[0]]; i < n; ++i) {
        ++counts[colors[rnd.next(1, (int)colors.size() - 1)]];
    }
    return makeCase(counts);
}

Case primaryDominant() {
    int n = rnd.next(3, 40);
    array<int, 6> counts{};
    int primaryColors[] = {0, 2, 4};
    int dominant = primaryColors[rnd.next(3)];
    counts[dominant] = rnd.next(n / 2 + 1, n);
    for (int i = counts[dominant]; i < n; ++i) {
        int color = primaryColors[rnd.next(3)];
        while (color == dominant) color = primaryColors[rnd.next(3)];
        ++counts[color];
    }
    return makeCase(counts);
}

Case secondaryDominant() {
    int n = rnd.next(3, 50);
    array<int, 6> counts{};
    int secondaryColors[] = {1, 3, 5};
    int dominant = secondaryColors[rnd.next(3)];
    counts[dominant] = rnd.next(n / 2 + 1, n);
    for (int i = counts[dominant]; i < n; ++i) {
        int color = rnd.next(6);
        while (color == dominant) color = rnd.next(6);
        ++counts[color];
    }
    return makeCase(counts);
}

Case sparseDominant() {
    int n = rnd.next(3, 80);
    array<int, 6> counts{};
    int dominant = rnd.next(6);
    counts[dominant] = rnd.next(n / 2 + 1, n);
    for (int i = counts[dominant]; i < n; ++i) {
        int color = rnd.next(6);
        while (color == dominant) color = rnd.next(6);
        ++counts[color];
    }
    return makeCase(counts);
}

Case nearLimit() {
    int n = rnd.next(900, 1000);
    return impossibleComposition(n, rnd.next(2, 6));
}

Case makeRandomCase() {
    int mode = rnd.next(5);
    if (mode == 0) return primaryDominant();
    if (mode == 1) return secondaryDominant();
    if (mode == 2) return sparseDominant();
    if (mode == 3) return nearLimit();
    return impossibleComposition(rnd.next(3, 60), rnd.next(2, 6));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(8, 30);
    println(t);
    for (int tc = 0; tc < t; ++tc) {
        Case c = makeRandomCase();
        println(c.n, c.counts[0], c.counts[1], c.counts[2], c.counts[3], c.counts[4], c.counts[5]);
    }

    return 0;
}
