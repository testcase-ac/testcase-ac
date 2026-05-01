#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose N: sometimes zero, small, medium
    int N;
    double p0 = rnd.next();
    if (p0 < 0.2) N = 0;
    else if (p0 < 0.6) N = rnd.next(1, 5);
    else N = rnd.next(6, 12);

    // Choose H: small, mid, or large
    int H;
    double p1 = rnd.next();
    if (p1 < 0.3) H = rnd.next(5, 20);
    else if (p1 < 0.5) H = rnd.next(100, 1000);
    else H = rnd.next(100000, 1000000000);

    // Generate intervals
    vector<pair<int,int>> intervals;
    double overlapProb = rnd.next();
    int lastEnd = 0;
    for (int i = 0; i < N; i++) {
        int a, b;
        if (!intervals.empty() && rnd.next() < overlapProb) {
            // Overlapping based on a random existing interval
            auto pr = rnd.any(intervals);
            int baseA = pr.first, baseB = pr.second;
            int lo = max(1, baseA - rnd.next(0, 3));
            int hi = min(H, baseB + rnd.next(0, 3));
            a = rnd.next(lo, hi);
            int maxLen = min(H - a, 5);
            b = rnd.next(a, a + maxLen);
        } else {
            // Non-overlapping, starting after lastEnd+1 if possible
            int lo = lastEnd + 1;
            if (lo > H) lo = rnd.next(1, H);
            a = rnd.next(lo, H);
            int maxLen = min(H - a, 5);
            b = rnd.next(a, a + maxLen);
            lastEnd = max(lastEnd, b);
        }
        intervals.emplace_back(a, b);
    }
    sort(intervals.begin(), intervals.end());

    // Choose Q: number of queries
    int Q;
    double p2 = rnd.next();
    if (p2 < 0.2) Q = 1;
    else if (p2 < 0.7) Q = rnd.next(2, 5);
    else Q = rnd.next(6, 10);

    // Generate T_i values
    vector<int> T(Q);
    for (int i = 0; i < Q; i++) {
        double pt = rnd.next();
        if (pt < 0.1) T[i] = 1;
        else if (pt < 0.2) T[i] = H;
        else if (pt < 0.4) T[i] = rnd.next(1, min(5, H));
        else if (pt < 0.6) T[i] = rnd.next(max(1, H - 5), H);
        else T[i] = rnd.next(1, H);
    }

    // Output
    println(N, H);
    for (auto &pr : intervals) {
        println(pr.first, pr.second);
    }
    println(Q);
    for (int t : T) {
        println(t);
    }

    return 0;
}
