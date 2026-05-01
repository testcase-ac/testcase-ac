#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int MINX = 3;
    const int MAXX = 24999;

    // Precompute Fibonacci numbers with F1 = 1, F2 = 2
    vector<int> fibs;
    fibs.push_back(1);
    fibs.push_back(2);
    while (true) {
        int sz = (int)fibs.size();
        long long nxt = (long long)fibs[sz - 1] + fibs[sz - 2];
        if (nxt > MAXX) break;
        fibs.push_back((int)nxt);
    }

    vector<int> xs;
    vector<bool> used(MAXX + 1, false);

    auto addUnique = [&](int x) {
        if (x < MINX || x > MAXX) return;
        if (!used[x]) {
            used[x] = true;
            xs.push_back(x);
        }
    };

    // Basic edge and small values
    addUnique(MINX);      // 3
    addUnique(MAXX);      // 24999
    for (int v : {4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 21}) {
        addUnique(v);
    }

    // Some Fibonacci numbers and neighbors
    int fibCount = (int)fibs.size();
    if (fibCount > 2) {
        int maxPick = min(7, fibCount - 2); // we skip indices 0,1 (1 and 2)
        int kPick = rnd.next(2, maxPick);   // pick at least 2 fib numbers

        vector<int> indices;
        for (int i = 2; i < fibCount; i++) indices.push_back(i);
        shuffle(indices.begin(), indices.end());

        for (int i = 0; i < kPick; i++) {
            int idx = indices[i];
            int f = fibs[idx];
            addUnique(f);

            if (rnd.next(0, 99) < 70) addUnique(f - 1);
            if (rnd.next(0, 99) < 70) addUnique(f + 1);
        }
    }

    // A short run of consecutive numbers around a random center
    int len = rnd.next(3, 7);
    int center = rnd.next(20, MAXX - 20);
    int start = center - len / 2;
    if (start < MINX) start = MINX;
    int end = start + len - 1;
    if (end > MAXX) {
        end = MAXX;
        start = max(MINX, end - len + 1);
    }
    for (int v = start; v <= end; v++) addUnique(v);

    // Deliberate duplicates of existing values
    int dupCount = rnd.next(1, 3);
    for (int i = 0; i < dupCount; i++) {
        int val = xs[rnd.next((int)xs.size())];
        xs.push_back(val);
    }

    // Some extra random values (may include duplicates)
    int extraRandom = rnd.next(3, 8);
    for (int i = 0; i < extraRandom; i++) {
        int x = rnd.next(MINX, MAXX);
        xs.push_back(x);
    }

    // Shuffle and choose final t
    shuffle(xs.begin(), xs.end());
    int Tmin = 10;
    int Tmax = (int)xs.size();
    if (Tmax < Tmin) Tmin = Tmax; // safety, though it shouldn't happen
    int t = rnd.next(Tmin, Tmax);

    println(t);
    for (int i = 0; i < t; i++) {
        println(xs[i]);
    }

    return 0;
}
