#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "N");
    inf.readEoln();
    int k = inf.readInt(1, 1000, "K");
    inf.readEoln();

    vector<int> weights;
    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        weights.push_back(inf.readInt(1, 1000000, "weight_i"));
    }
    inf.readEoln();
    inf.readEof();

    vector<long long> sums = {0};
    for (int weight : weights) {
        vector<long long> next = sums;
        next.reserve(sums.size() * 2);
        for (long long sum : sums) {
            next.push_back(sum + weight);
        }

        sort(next.begin(), next.end());
        next.erase(unique(next.begin(), next.end()), next.end());
        if (static_cast<int>(next.size()) > k) {
            next.resize(k);
        }
        sums.swap(next);
    }

    ensuref(static_cast<int>(sums.size()) >= k,
            "fewer than K different weight sums exist: have %d, need %d",
            static_cast<int>(sums.size()), k);
}
