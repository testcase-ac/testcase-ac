#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of lights
    int N = rnd.next(2, 10);
    bool c_same_flag = (rnd.next(0, 9) == 0); // 10% chance all c's same across rows

    // Partition N into K rows
    int K;
    vector<int> sizes;
    if (c_same_flag) {
        K = N;
        sizes.assign(N, 1);
    } else {
        K = rnd.next(1, min(N, 5));
        sizes.assign(K, 1);
        int rem = N - K;
        for (int i = 0; i < rem; i++) {
            int j = rnd.next(0, K - 1);
            sizes[j]++;
        }
    }

    // Determine H and row indices
    int H;
    vector<int> rows;
    bool smallH = rnd.next(0, 1) == 0;
    if (smallH) {
        H = K;
        rows.resize(K);
        for (int i = 0; i < K; i++) rows[i] = i + 1;
        shuffle(rows.begin(), rows.end());
    } else {
        int H_low = 1000000000 - 1000;
        int H_high = 1000000000;
        H = rnd.next(H_low, H_high);
        set<int> s;
        while ((int)s.size() < K) {
            int r = rnd.next(1, H);
            s.insert(r);
        }
        rows.assign(s.begin(), s.end());
    }

    // Generate positions
    vector<pair<int,int>> items;
    if (c_same_flag) {
        // All columns same, distinct rows guaranteed since K=N
        int baseC = rnd.next(100000000, 100000100);
        for (int j = 0; j < K; j++) {
            items.emplace_back(rows[j], baseC);
        }
    } else {
        for (int j = 0; j < K; j++) {
            int sz = sizes[j];
            bool smallC = rnd.next(0, 1) == 0;
            int c = smallC ? rnd.next(1, 5) : rnd.next(100000000, 100000100);
            for (int t = 0; t < sz; t++) {
                items.emplace_back(rows[j], c);
                if (smallC)
                    c += rnd.next(1, 3);
                else
                    c += rnd.next(1, 1000);
            }
        }
    }

    // Shuffle input order
    shuffle(items.begin(), items.end());

    // Output
    println(H, N);
    for (auto &p : items)
        println(p.first, p.second);

    return 0;
}
