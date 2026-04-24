#include "testlib.h"
#include <vector>
#include <set>
#include <utility>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Choose grid size
    int N = rnd.next(5, 15);
    // Compute maximum allowed net length
    int maxL = min(4 * N - 4, 100);
    // Generate an even net length l in [4, maxL]
    int choices = (maxL - 4) / 2 + 1;
    int l = 4 + 2 * rnd.next(0, choices - 1);
    // Number of fish
    int M = rnd.next(1, min(N * N, 100));
    
    set<pair<int,int>> fish;
    double mode = rnd.next();
    if (mode < 0.5) {
        // Uniform random placement
        while ((int)fish.size() < M) {
            int x = rnd.next(1, N);
            int y = rnd.next(1, N);
            fish.insert({x, y});
        }
    } else if (mode < 0.8) {
        // Clustered placement
        int cx = rnd.next(1, N);
        int cy = rnd.next(1, N);
        int d = rnd.next(1, min(2, N-1));
        for (int i = 0; i < M; i++) {
            if (rnd.next() < 0.7) {
                int x = rnd.next(max(1, cx - d), min(N, cx + d));
                int y = rnd.next(max(1, cy - d), min(N, cy + d));
                fish.insert({x, y});
            } else {
                int x = rnd.next(1, N);
                int y = rnd.next(1, N);
                fish.insert({x, y});
            }
        }
        // Fill if duplicates shrank count
        while ((int)fish.size() < M) {
            int x = rnd.next(1, N);
            int y = rnd.next(1, N);
            fish.insert({x, y});
        }
    } else {
        // Line pattern placement
        bool isRow = rnd.next(0, 1);
        int rc = rnd.next(1, N);
        int lineCount = rnd.next(1, M);
        for (int i = 0; i < lineCount; i++) {
            int x = isRow ? rc : rnd.next(1, N);
            int y = isRow ? rnd.next(1, N) : rc;
            fish.insert({x, y});
        }
        while ((int)fish.size() < M) {
            int x = rnd.next(1, N);
            int y = rnd.next(1, N);
            fish.insert({x, y});
        }
    }
    
    // Prepare output
    vector<pair<int,int>> v(fish.begin(), fish.end());
    shuffle(v.begin(), v.end());
    
    // Print in required format
    println(N, l, M);
    for (auto &p : v) {
        println(p.first, p.second);
    }
    return 0;
}
