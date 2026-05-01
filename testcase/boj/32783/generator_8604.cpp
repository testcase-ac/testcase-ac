#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int CMAX = 300000;

    int n;
    vector<long long> a, mm; // power (W), minutes

    int type = rnd.next(0, 5); // 6 types: 0..5

    if (type == 0) {
        // Tiny n, small random usages
        n = rnd.next(1, 3);
        a.assign(n, 0);
        mm.assign(n, 0);
        for (int i = 0; i < n; i++) {
            int x = rnd.next(1, 10);  // a = 250 * x
            int y = rnd.next(1, 10);  // m = 15 * y
            a[i] = 250LL * x;
            mm[i] = 15LL * y;
        }
    } else if (type == 1) {
        // All identical small computers
        n = rnd.next(5, 15);
        a.assign(n, 0);
        mm.assign(n, 0);
        int x = rnd.next(1, 5);
        int y = rnd.next(1, 5);
        long long aval = 250LL * x;
        long long mval = 15LL * y;
        for (int i = 0; i < n; i++) {
            a[i] = aval;
            mm[i] = mval;
        }
    } else if (type == 2) {
        // Random moderate-sized usages
        n = rnd.next(5, 15);
        a.assign(n, 0);
        mm.assign(n, 0);
        for (int i = 0; i < n; i++) {
            int x = rnd.next(1, 20);
            int y = rnd.next(1, 20);
            a[i] = 250LL * x;
            mm[i] = 15LL * y;
        }
    } else if (type == 3) {
        // Structured increasing pattern
        n = rnd.next(4, 10);
        a.assign(n, 0);
        mm.assign(n, 0);
        int baseX = rnd.next(1, 20);
        int baseY = rnd.next(1, 20);
        for (int i = 0; i < n; i++) {
            int mulX = (i % 3) + 1;
            int mulY = ((i / 3) % 3) + 1;
            long long x = 1LL * baseX * mulX;
            long long y = 1LL * baseY * mulY;
            a[i] = 250LL * x;
            mm[i] = 15LL * y;
        }
    } else if (type == 4) {
        // Mix of small useful and huge useless computers
        n = rnd.next(5, 15);
        a.assign(n, 0);
        mm.assign(n, 0);
        int kSmall = rnd.next(1, n - 1);
        for (int i = 0; i < kSmall; i++) {
            int x = rnd.next(1, 30);
            int y = rnd.next(1, 30);
            a[i] = 250LL * x;
            mm[i] = 15LL * y;
        }
        for (int i = kSmall; i < n; i++) {
            while (true) {
                long long x = rnd.next(1000, 4000000); // ensures a <= 1e9
                long long y = rnd.next(1, 2976);       // ensures m <= 44640
                long long cost = 6LL * x * y;
                if (cost > CMAX) {
                    a[i] = 250LL * x;
                    mm[i] = 15LL * y;
                    break;
                }
            }
        }
    } else { // type == 5
        // All computers individually too expensive (no non-empty valid subset)
        n = rnd.next(1, 10);
        a.assign(n, 0);
        mm.assign(n, 0);
        for (int i = 0; i < n; i++) {
            while (true) {
                long long x = rnd.next(1000, 4000000);
                long long y = rnd.next(1, 2976);
                long long cost = 6LL * x * y;
                if (cost > CMAX) {
                    a[i] = 250LL * x;
                    mm[i] = 15LL * y;
                    break;
                }
            }
        }
    }

    // Compute cost per computer in won:
    // cost_i = 6 * (a/250) * (m/15)
    vector<long long> cost(n);
    for (int i = 0; i < n; i++) {
        long long x = a[i] / 250;
        long long y = mm[i] / 15;
        cost[i] = 6LL * x * y;
    }

    // Enumerate all non-empty subset sums up to CMAX
    vector<int> possible;
    int totalMasks = 1 << n;
    for (int mask = 1; mask < totalMasks; mask++) {
        long long sum = 0;
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                sum += cost[i];
                if (sum > CMAX) break;
            }
        }
        if (sum <= CMAX) possible.push_back((int)sum);
    }
    sort(possible.begin(), possible.end());
    possible.erase(unique(possible.begin(), possible.end()), possible.end());

    int c1, c2;
    int mode = rnd.next(0, 5); // ways to choose [c1, c2]

    if (possible.empty()) {
        // No achievable non-empty sum within [1, CMAX]
        if (mode == 0) {
            c1 = 1;
            c2 = CMAX;
        } else {
            c1 = rnd.next(1, CMAX);
            c2 = rnd.next(c1, CMAX);
        }
    } else {
        switch (mode) {
            case 0: {
                // Full range
                c1 = 1;
                c2 = CMAX;
                break;
            }
            case 1: {
                // Exact one achievable sum
                int s = rnd.any(possible);
                c1 = s;
                c2 = s;
                break;
            }
            case 2: {
                // Interval from one achievable sum to another
                int i1 = rnd.next(0, (int)possible.size() - 1);
                int i2 = rnd.next(i1, (int)possible.size() - 1);
                c1 = possible[i1];
                c2 = possible[i2];
                break;
            }
            case 3: {
                // Interval lying in a gap with no achievable sums, if possible
                vector<pair<int,int>> gaps;
                if (possible[0] > 1) {
                    gaps.push_back(make_pair(1, possible[0] - 1));
                }
                for (int i = 0; i + 1 < (int)possible.size(); i++) {
                    int L = possible[i] + 1;
                    int R = possible[i + 1] - 1;
                    if (L <= R) gaps.push_back(make_pair(L, R));
                }
                if (possible.back() < CMAX) {
                    gaps.push_back(make_pair(possible.back() + 1, CMAX));
                }
                if (!gaps.empty()) {
                    pair<int,int> g = rnd.any(gaps);
                    c1 = rnd.next(g.first, g.second);
                    c2 = rnd.next(c1, g.second);
                } else {
                    // No gaps; fallback to full range
                    c1 = 1;
                    c2 = CMAX;
                }
                break;
            }
            case 4: {
                // Small window around some achievable sum (possibly including neighbors)
                int s = rnd.any(possible);
                int leftOffset = rnd.next(0, 5);
                int rightOffset = rnd.next(0, 5);
                c1 = s - leftOffset;
                if (c1 < 1) c1 = 1;
                c2 = s + rightOffset;
                if (c2 > CMAX) c2 = CMAX;
                if (c2 < c1) c2 = c1;
                break;
            }
            case 5: {
                // Interval misaligned with multiples of 6 around an achievable sum
                int s = rnd.any(possible);
                int low = s + 1;
                int high = s + 5;
                if (low < 1) low = 1;
                if (high > CMAX) high = CMAX;
                if (low <= high) {
                    c1 = rnd.next(low, high);
                    c2 = rnd.next(c1, high);
                } else {
                    // Fallback random interval
                    c1 = rnd.next(1, CMAX);
                    c2 = rnd.next(c1, CMAX);
                }
                break;
            }
        }
    }

    // Output
    println(n);
    for (int i = 0; i < n; i++) {
        println(a[i], mm[i]);
    }
    println(c1, c2);

    return 0;
}
