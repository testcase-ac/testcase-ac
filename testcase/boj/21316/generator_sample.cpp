#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<pair<int, int>> edges = {
        {1, 2},  {2, 3},  {3, 4},   {4, 5},
        {3, 7},  {4, 9},  {6, 7},   {7, 8},
        {8, 9},  {9, 10}, {10, 11}, {11, 12},
    };

    vector<int> label(13);
    iota(label.begin(), label.end(), 0);

    int mode = rnd.next(0, 4);
    if (mode == 0) {
        vector<int> perm(12);
        iota(perm.begin(), perm.end(), 1);
        shuffle(perm.begin(), perm.end());
        for (int i = 1; i <= 12; ++i) {
            label[i] = perm[i - 1];
        }
    } else if (mode == 1) {
        for (int i = 1; i <= 12; ++i) {
            label[i] = 13 - i;
        }
        int swaps = rnd.next(1, 4);
        for (int i = 0; i < swaps; ++i) {
            swap(label[rnd.next(1, 12)], label[rnd.next(1, 12)]);
        }
    } else if (mode == 2) {
        int shift = rnd.next(0, 11);
        for (int i = 1; i <= 12; ++i) {
            label[i] = (i + shift - 1) % 12 + 1;
        }
    } else {
        int spicaLabel = rnd.next(1, 12);
        vector<int> remainingLabels;
        for (int i = 1; i <= 12; ++i) {
            if (i != spicaLabel) {
                remainingLabels.push_back(i);
            }
        }
        shuffle(remainingLabels.begin(), remainingLabels.end());
        label[7] = spicaLabel;
        int idx = 0;
        for (int i = 1; i <= 12; ++i) {
            if (i != 7) {
                label[i] = remainingLabels[idx++];
            }
        }
    }

    shuffle(edges.begin(), edges.end());
    for (auto [u, v] : edges) {
        if (rnd.next(0, 1)) {
            swap(u, v);
        }
        println(label[u], label[v]);
    }

    return 0;
}
