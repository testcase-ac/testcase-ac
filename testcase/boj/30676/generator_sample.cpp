#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> edges = {380, 425, 450, 495, 570, 590, 620, 780};
    vector<pair<int, int>> ranges = {
        {380, 424}, {425, 449}, {450, 494}, {495, 569},
        {570, 589}, {590, 619}, {620, 780},
    };

    int mode = rnd.next(0, 2);
    int lambda;

    if (mode == 0) {
        lambda = rnd.any(edges);
    } else if (mode == 1) {
        int edge = rnd.any(vector<int>{425, 450, 495, 570, 590, 620});
        lambda = edge + rnd.any(vector<int>{-1, 0, 1});
    } else {
        auto range = rnd.any(ranges);
        lambda = rnd.next(range.first, range.second);
    }

    println(lambda);
    return 0;
}
