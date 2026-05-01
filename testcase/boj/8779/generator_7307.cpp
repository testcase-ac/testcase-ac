#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int Z = rnd.next(1, 6);
    println(Z);
    for (int tc = 0; tc < Z; ++tc) {
        // Dimensions W x K with bias to small and large
        int W = rnd.wnext(10, rnd.next(-1, 1)) + 1;
        int K = rnd.wnext(10, rnd.next(-1, 1)) + 1;
        // Hyper-parameter for R: small, full, or random
        int choice = rnd.next(1, 4);
        int R;
        if (choice == 1) {
            R = 1;
        } else if (choice == 2) {
            R = max(W, K);
        } else {
            R = rnd.next(1, max(W, K));
        }
        println(W, K, R);
        // Sometimes use a constant grid
        bool constant = rnd.next(0, 9) == 0;
        int const_val = constant ? rnd.next(1, 1000) : 0;
        for (int i = 0; i < W; ++i) {
            vector<int> row;
            row.reserve(K);
            for (int j = 0; j < K; ++j) {
                int v;
                if (constant) {
                    v = const_val;
                } else if (rnd.next(0, 9) == 0) {
                    // Rare large values
                    v = rnd.next(100000, 1000000);
                } else {
                    v = rnd.next(1, 100);
                }
                row.push_back(v);
            }
            println(row);
        }
    }
    return 0;
}
