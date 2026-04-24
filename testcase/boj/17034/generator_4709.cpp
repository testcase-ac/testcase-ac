#include "testlib.h"
#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of plates
    int N = rnd.next(2, 10);
    // Choose generation type: 0=random, 1=sorted, 2=reversed, 3=block shuffle
    int type = rnd.next(0, 3);

    vector<int> perm(N);
    iota(perm.begin(), perm.end(), 1);

    if (type == 0) {
        // Fully random permutation
        shuffle(perm.begin(), perm.end());
    } else if (type == 1) {
        // Already sorted: 1,2,...,N
        // nothing to do
    } else if (type == 2) {
        // Completely reversed: N,N-1,...,1
        reverse(perm.begin(), perm.end());
    } else {
        // Block shuffle: split into a few blocks and permute blocks
        int B = rnd.next(2, min(N, 4));
        vector<pair<int,int>> blocks;
        int base = N / B, rem = N % B, idx = 0;
        for (int i = 0; i < B; i++) {
            int sz = base + (i < rem ? 1 : 0);
            blocks.emplace_back(idx, idx + sz);
            idx += sz;
        }
        shuffle(blocks.begin(), blocks.end());
        vector<int> tmp;
        tmp.reserve(N);
        for (auto &b : blocks) {
            for (int i = b.first; i < b.second; i++)
                tmp.push_back(perm[i]);
        }
        perm = tmp;
    }

    // Output
    println(N);
    for (int x : perm) {
        println(x);
    }
    return 0;
}
