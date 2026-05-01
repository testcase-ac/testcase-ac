#include "testlib.h"
#include <vector>
#include <algorithm>
#include <utility>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Universe size for coordinates
    int maxCoord = rnd.next(10, 100);
    // Number of intervals N and queries Q, biased small or large
    int tN = rnd.next(-1, 1);
    int N = rnd.wnext(10, tN) + 1;
    int tQ = rnd.next(-1, 1);
    int Q = rnd.wnext(10, tQ) + 1;
    // Generate intervals with variable lengths
    vector<pair<int,int>> intervals;
    int tL = rnd.next(-2, 2);
    for (int i = 0; i < N; i++) {
        int length = rnd.wnext(maxCoord - 1, tL) + 1;
        int l = rnd.next(1, maxCoord - length);
        int r = l + length;
        intervals.emplace_back(l, r);
    }
    shuffle(intervals.begin(), intervals.end());
    // Generate queries with variable lengths and some edge cases
    vector<pair<int,int>> queries;
    int tQLen = rnd.next(-2, 2);
    for (int j = 0; j < Q; j++) {
        int lenq = rnd.wnext(maxCoord - 1, tQLen) + 1;
        int s, e;
        // 30% chance to touch the boundary of the universe
        if (rnd.next(0, 9) < 3) {
            if (rnd.next(0, 1) == 0) {
                s = 1;
                e = rnd.next(s + 1, maxCoord);
            } else {
                e = maxCoord;
                s = rnd.next(1, e - 1);
            }
        } else {
            s = rnd.next(1, maxCoord - lenq);
            e = s + lenq;
        }
        queries.emplace_back(s, e);
    }
    // Output
    println(N, Q);
    for (auto &p : intervals) println(p.first, p.second);
    for (auto &p : queries) println(p.first, p.second);
    return 0;
}
