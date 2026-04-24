#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases
    int P = rnd.next(1, 10);
    println(P);

    for (int tc = 1; tc <= P; tc++) {
        // Generate base heights as a consecutive range to keep distinct
        int base = rnd.next(1, 1000 - 19);
        vector<int> h(20);
        for (int i = 0; i < 20; i++) {
            h[i] = base + i;
        }

        // Choose a pattern type for diversity
        int type = rnd.next(1, 5);
        if (type == 1) {
            // Already ascending: minimal moves
        } else if (type == 2) {
            // Fully descending: maximal moves
            reverse(h.begin(), h.end());
        } else if (type == 3) {
            // Fully random
            shuffle(h.begin(), h.end());
        } else if (type == 4) {
            // Rotate by a random offset
            int k = rnd.next(1, 19);
            rotate(h.begin(), h.begin() + k, h.end());
        } else {
            // Clustered ascending runs in random order
            vector<int> cs = {2, 4, 5, 10, 20};
            int c = rnd.any(cs);
            int blocks = 20 / c;
            vector<vector<int>> bks(blocks);
            for (int i = 0; i < blocks; i++) {
                bks[i].assign(h.begin() + i * c, h.begin() + i * c + c);
            }
            shuffle(bks.begin(), bks.end());
            vector<int> nh;
            for (auto &bk : bks) {
                for (int x : bk) nh.push_back(x);
            }
            h.swap(nh);
        }

        // Prepare and print the test case line: T and 20 heights
        vector<int> out;
        out.reserve(21);
        out.push_back(tc);
        for (int x : h) out.push_back(x);
        println(out);
    }

    return 0;
}
