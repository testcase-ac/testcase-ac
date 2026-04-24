#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of days/plants
    int N = rnd.next(1, 10);
    // x-coordinate bound, ensuring some room for segments
    int xBound = rnd.next(max(5, N + 1), 15);

    // Probability to try overlapping with a previous segment
    double overlapProb = rnd.next();
    vector<pair<int,int>> segs;
    segs.reserve(N);

    for (int i = 0; i < N; i++) {
        int L, R;
        bool made = false;
        if (i >= 1 && rnd.next() < overlapProb) {
            // Try to overlap with a random previous segment
            int j = rnd.next(0, i - 1);
            int Lj = segs[j].first;
            int Rj = segs[j].second;
            // Attempt two kinds of partial overlap if possible
            if (Rj - Lj > 1 && Rj < xBound && rnd.next() < 0.5) {
                // Stem start inside [Lj+1, Rj-1], end to the right
                L = rnd.next(Lj + 1, Rj - 1);
                R = rnd.next(Rj + 1, xBound);
                made = true;
            } else if (Rj - Lj > 1 && Lj > 1) {
                // Stem end inside [Lj+1, Rj-1], start to the left
                R = rnd.next(Lj + 1, Rj - 1);
                L = rnd.next(1, Lj - 1);
                made = true;
            }
        }
        if (!made) {
            // Pure random segment [L, R]
            L = rnd.next(1, xBound - 1);
            R = rnd.next(L + 1, xBound);
        }
        segs.emplace_back(L, R);
    }

    // Output
    println(N);
    for (auto &p : segs) {
        println(p.first, p.second);
    }
    return 0;
}
