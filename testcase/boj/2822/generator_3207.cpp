#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameter: bias mode (0=low, 1=uniform, 2=high)
    int mode = rnd.next(0, 2);
    int t = (mode == 1 ? 0 : (mode == 0 ? -2 : 2));
    // Sometimes force include 0 or 150
    bool forceZero = rnd.next(0, 3) == 0;
    bool forceMax  = rnd.next(0, 3) == 0;
    set<int> used;
    vector<int> scores;
    if (forceZero) {
        used.insert(0);
        scores.push_back(0);
    }
    if (forceMax && !used.count(150)) {
        used.insert(150);
        scores.push_back(150);
    }
    // Fill up to 8 distinct scores
    while ((int)scores.size() < 8) {
        int x;
        if (t == 0)
            x = rnd.next(0, 150);
        else
            x = rnd.wnext(151, t);
        if (used.insert(x).second)
            scores.push_back(x);
    }
    // Randomize problem order
    shuffle(scores.begin(), scores.end());
    // Output 8 lines
    for (int x : scores)
        println(x);
    return 0;
}
