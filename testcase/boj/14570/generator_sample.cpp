#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 3);
    int n = mode == 0 ? 1 : rnd.next(2, 20);
    vector<pair<int, int>> child(n + 1, {-1, -1});

    if (mode == 1) {
        for (int i = 1; i < n; ++i) {
            if (rnd.next(0, 1) == 0) {
                child[i].first = i + 1;
            } else {
                child[i].second = i + 1;
            }
        }
    } else if (mode == 2) {
        for (int i = 1; i <= n; ++i) {
            int left = 2 * i;
            int right = 2 * i + 1;
            if (left <= n) child[i].first = left;
            if (right <= n) child[i].second = right;
        }
    } else if (mode == 3) {
        vector<pair<int, int>> slots;
        slots.push_back({1, 0});
        slots.push_back({1, 1});
        for (int node = 2; node <= n; ++node) {
            int slotIndex = rnd.next(static_cast<int>(slots.size()));
            int parent = slots[slotIndex].first;
            int side = slots[slotIndex].second;
            slots.erase(slots.begin() + slotIndex);

            if (side == 0) {
                child[parent].first = node;
            } else {
                child[parent].second = node;
            }

            slots.push_back({node, 0});
            slots.push_back({node, 1});
        }
    }

    vector<int> label(n + 1);
    label[1] = 1;
    vector<int> labels;
    for (int i = 2; i <= n; ++i) labels.push_back(i);
    shuffle(labels.begin(), labels.end());
    for (int i = 2; i <= n; ++i) label[i] = labels[i - 2];

    vector<pair<int, int>> relabeled(n + 1, {-1, -1});
    for (int i = 1; i <= n; ++i) {
        int out = label[i];
        if (child[i].first != -1) relabeled[out].first = label[child[i].first];
        if (child[i].second != -1) relabeled[out].second = label[child[i].second];
    }

    long long k;
    int kMode = rnd.next(0, 4);
    if (kMode == 0) {
        k = 1;
    } else if (kMode == 1) {
        k = rnd.next(1, 100);
    } else if (kMode == 2) {
        k = rnd.next(1000000, 1000000000);
    } else if (kMode == 3) {
        k = 1000000000000000000LL - rnd.next(0, 1000);
    } else {
        k = rnd.next(1LL, 1000000000000000000LL);
    }

    println(n);
    for (int i = 1; i <= n; ++i) {
        println(relabeled[i].first, relabeled[i].second);
    }
    println(k);

    return 0;
}
