#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(3, 7);
    vector<int> xs;
    // always include edge cases
    xs.push_back(10);
    xs.push_back(1000000);
    // ranges for additional random X values
    vector<pair<int,int>> ranges = {
        {11, 100},
        {101, 10000},
        {10001, 999999}
    };
    for (int i = 2; i < T; ++i) {
        auto pr = rnd.any(ranges);
        xs.push_back(rnd.next(pr.first, pr.second));
    }
    shuffle(xs.begin(), xs.end());
    for (int x : xs) println(x);
    println(0);
    return 0;
}
