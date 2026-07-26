#include "testlib.h"
#include <set>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int k = rnd.next(3, 13);
    int mode = rnd.next(4);
    vector<int> weights;

    if (mode == 0) {
        for (int i = 1; i <= k; ++i) weights.push_back(i);
    } else if (mode == 1) {
        for (int i = 0; i < k; ++i) weights.push_back(1 << i);
    } else if (mode == 2) {
        int step = rnd.next(1, 50);
        for (int i = 0; i < k; ++i) weights.push_back(200000 - i * step);
    } else {
        int limit = rnd.next(k, 200000);
        set<int> uniqueWeights;
        while (int(uniqueWeights.size()) < k)
            uniqueWeights.insert(rnd.next(1, limit));
        weights.assign(uniqueWeights.begin(), uniqueWeights.end());
    }

    shuffle(weights.begin(), weights.end());
    println(k);
    println(weights);
}
