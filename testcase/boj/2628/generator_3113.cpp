#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Small paper size
    int W = rnd.next(1, 10);
    int H = rnd.next(1, 10);
    int maxC = (W > 0 ? W - 1 : 0) + (H > 0 ? H - 1 : 0);
    // Hyper-parameter for number of cuts C
    double p = rnd.next();
    int C;
    if (p < 0.3) {
        C = rnd.next(0, min(maxC, 5));
    } else if (p < 0.6) {
        if (maxC == 0) C = 0;
        else C = rnd.next(max(0, maxC - 5), maxC);
    } else {
        C = rnd.next(0, maxC);
    }
    // Distribute between horizontal and vertical cuts
    int ch = 0;
    if (maxC > 0 && C > 0) {
        int min_ch = max(0, C - (W - 1));
        int max_ch = min(C, H - 1);
        if (min_ch > max_ch) min_ch = max_ch;
        ch = rnd.next(min_ch, max_ch);
    }
    int cv = C - ch;
    // Choose distinct cut lines
    set<int> hset, vset;
    while ((int)hset.size() < ch) {
        if (H > 1) hset.insert(rnd.next(1, H - 1));
        else break;
    }
    while ((int)vset.size() < cv) {
        if (W > 1) vset.insert(rnd.next(1, W - 1));
        else break;
    }
    // Prepare and shuffle cuts
    vector<pair<int,int>> cuts;
    for (int x : hset) cuts.emplace_back(0, x);
    for (int x : vset) cuts.emplace_back(1, x);
    shuffle(cuts.begin(), cuts.end());
    // Output
    println(W, H);
    println((int)cuts.size());
    for (auto &pr : cuts) {
        println(pr.first, pr.second);
    }
    return 0;
}
