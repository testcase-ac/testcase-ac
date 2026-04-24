#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<pair<long long, long long>> segs;

    int type = rnd.next(0, 7); // choose scenario

    if (type == 0) {
        // Exact sample from the statement
        segs.push_back({1, 3});
        segs.push_back({2, 5});
        segs.push_back({3, 5});
        segs.push_back({6, 7});
    } else if (type == 1) {
        // Single random interval
        long long x = rnd.next(-20LL, 20LL);
        long long len = rnd.next(1LL, 20LL);
        long long y = x + len;
        segs.push_back({x, y});
    } else if (type == 2) {
        // Many overlapping intervals in a small range
        long long baseStart = rnd.next(-10LL, 0LL);
        int N = rnd.next(5, 15);
        // One big covering segment
        segs.push_back({baseStart, baseStart + 20});
        for (int i = 1; i < N; i++) {
            long long x = rnd.next(baseStart - 5, baseStart + 20);
            long long y = rnd.next(x + 1, baseStart + 25);
            segs.push_back({x, y});
        }
    } else if (type == 3) {
        // Chain of touching segments [i, i+1]
        long long start = rnd.next(-10LL, 0LL);
        int len = rnd.next(5, 15);
        for (int i = 0; i < len; i++) {
            segs.push_back({start + i, start + i + 1});
        }
        // Optionally a big segment covering the whole chain
        if (rnd.next(0, 1) == 1) {
            segs.push_back({start - 1, start + len + 1});
        }
        // Optionally duplicate one segment
        if (!segs.empty() && rnd.next(0, 2) == 0) {
            segs.push_back(rnd.any(segs));
        }
    } else if (type == 4) {
        // Nested intervals
        long long a = rnd.next(5LL, 50LL);
        segs.push_back({-a, a});
        long long b = a / 2;
        if (b > 0) segs.push_back({-b, b});
        segs.push_back({-a, 0});
        segs.push_back({0, a});
        segs.push_back({-1, 1});
        int extra = rnd.next(0, 3);
        for (int i = 0; i < extra; i++) {
            // Ensure valid range: x in [-a+1, a-2] so that x+1 <= a-1
            long long x = rnd.next(-a + 1, a - 2);
            long long y = rnd.next(x + 1, a - 1);
            segs.push_back({x, y});
        }
    } else if (type == 5) {
        // Random moderate intervals with small coordinates
        int N = rnd.next(5, 25);
        for (int i = 0; i < N; i++) {
            long long x = rnd.next(-30LL, 29LL);
            long long y = rnd.next(x + 1, 30LL);
            segs.push_back({x, y});
        }
    } else if (type == 6) {
        // Intervals using extreme coordinates near -1e9 and 1e9
        const long long L = -1000000000LL;
        const long long R =  1000000000LL;
        segs.push_back({L, R});
        segs.push_back({L, L + 10});
        segs.push_back({R - 10, R});
        segs.push_back({-500000000LL, 0});
        segs.push_back({0, 500000000LL});
        segs.push_back({-10, 10});
        int add = rnd.next(0, 2);
        for (int i = 0; i < add; i++) {
            long long x = rnd.next(L, 999999900LL);
            long long y = x + rnd.next(1LL, 100LL);
            if (y > R) y = R;
            segs.push_back({x, y});
        }
    } else if (type == 7) {
        // General random intervals with medium coordinates, some duplicates
        int N = rnd.next(5, 20);
        while ((int)segs.size() < N) {
            if (!segs.empty() && rnd.next(0, 4) == 0) {
                // 20% chance to duplicate an existing segment
                segs.push_back(rnd.any(segs));
            } else {
                long long x = rnd.next(-1000000LL, 999999LL);
                long long y = rnd.next(x + 1, 1000000LL);
                segs.push_back({x, y});
            }
        }
    }

    // Shuffle order of segments
    shuffle(segs.begin(), segs.end());

    int N = (int)segs.size();
    println(N);
    for (auto &p : segs) {
        println(p.first, p.second);
    }

    return 0;
}
