#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<pair<int, int>> ranges = {
        {200, 260},
        {261, 7499},
        {7501, 9000},
        {9001, 197499},
        {197501, 210000},
        {210001, 1000000000},
        {1000000000 - 10000, 1000000000},
    };

    vector<int> anchors = {
        201,
        7499,
        7501,
        197499,
        197501,
        999999999,
        1000000000,
    };

    int k;
    if (rnd.next(4) == 0) {
        k = rnd.any(anchors);
    } else {
        auto range = rnd.any(ranges);
        k = rnd.next(range.first, range.second);
    }

    println(k);
    return 0;
}
