#include "testlib.h"
using namespace std;

void applyOp(vector<int>& a, int l, int r) {
    reverse(a.begin() + l, a.begin() + r + 1);
    for (int i = l; i <= r; ++i)
        a[i] = -a[i];
}

pair<int,int> randInterval(int N) {
    int a = rnd.next(1, N);
    int b = rnd.next(1, N);
    if (a > b) swap(a, b);
    return make_pair(a, b);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int scenario = rnd.next(0, 4);
    int N;
    vector<int> a;

    if (scenario == 0) {
        // Identity or very simple case
        N = rnd.next(1, 10);
        a.assign(N + 1, 0);
        for (int i = 1; i <= N; ++i) a[i] = i;
        // Sometimes make a simple single-element flip when N > 1
        if (N > 1 && rnd.next(0, 1) == 1) {
            int pos = rnd.next(1, N);
            applyOp(a, pos, pos);
        }
    } else if (scenario == 1) {
        // Single interval operation, often easy to reason about
        N = rnd.next(1, 15);
        a.assign(N + 1, 0);
        for (int i = 1; i <= N; ++i) a[i] = i;

        int l, r;
        if (N == 1) {
            l = r = 1;
        } else {
            int choice = rnd.next(0, 2);
            if (choice == 0) {
                l = 1; r = N;          // whole array
            } else {
                pair<int,int> p = randInterval(N);
                l = p.first; r = p.second;
            }
        }
        applyOp(a, l, r);
    } else if (scenario == 2) {
        // Exactly two structured intervals: disjoint / nested / overlapping
        N = rnd.next(4, 15);
        a.assign(N + 1, 0);
        for (int i = 1; i <= N; ++i) a[i] = i;

        int pattern = rnd.next(0, 2);
        pair<int,int> p1, p2;

        if (pattern == 0) {
            // Disjoint intervals
            while (true) {
                p1 = randInterval(N);
                p2 = randInterval(N);
                if (p1.second < p2.first || p2.second < p1.first) break;
            }
        } else if (pattern == 1) {
            // Properly nested intervals
            while (true) {
                p1 = randInterval(N);
                if (p1.second - p1.first + 1 < 2) continue; // need length >= 2
                int l2 = rnd.next(p1.first, p1.second);
                int r2 = rnd.next(l2, p1.second);
                p2 = make_pair(l2, r2);
                if (!(p2.first == p1.first && p2.second == p1.second)) break;
            }
        } else {
            // Overlapping but neither contains the other: l1 < l2 <= r1 < r2
            int l1 = rnd.next(1, N - 3);
            int l2 = rnd.next(l1 + 1, N - 2);
            int r1 = rnd.next(l2, N - 1);
            int r2 = rnd.next(r1 + 1, N);
            p1 = make_pair(l1, r1);
            p2 = make_pair(l2, r2);
        }

        vector<pair<int,int>> ops;
        ops.push_back(p1);
        ops.push_back(p2);
        shuffle(ops.begin(), ops.end());

        for (auto op : ops) applyOp(a, op.first, op.second);
    } else if (scenario == 3) {
        // Moderate N, several random intervals
        N = rnd.next(5, 25);
        a.assign(N + 1, 0);
        for (int i = 1; i <= N; ++i) a[i] = i;

        int K = rnd.next(3, 7);
        pair<int,int> last = make_pair(-1, -1);
        for (int i = 0; i < K; ++i) {
            pair<int,int> p;
            do {
                p = randInterval(N);
            } while (p == last); // avoid immediate cancellation
            applyOp(a, p.first, p.second);
            last = p;
        }
    } else {
        // scenario == 4: Larger N (still small), more random operations
        N = rnd.next(15, 30);
        a.assign(N + 1, 0);
        for (int i = 1; i <= N; ++i) a[i] = i;

        int K = rnd.next(5, 15);
        pair<int,int> last = make_pair(-1, -1);
        for (int i = 0; i < K; ++i) {
            pair<int,int> p;
            do {
                p = randInterval(N);
            } while (p == last);
            applyOp(a, p.first, p.second);
            last = p;
        }

        // With small probability, add one more structured operation on a big block
        if (rnd.next(0, 3) == 0) {
            int l = rnd.next(1, N / 2);
            int r = rnd.next((N + 1) / 2, N);
            if (l > r) swap(l, r);
            applyOp(a, l, r);
        }
    }

    // Prepare output (1-based a -> 0-based vector for println)
    vector<int> out(N);
    for (int i = 1; i <= N; ++i) out[i - 1] = a[i];

    println(N);
    println(out);

    return 0;
}
