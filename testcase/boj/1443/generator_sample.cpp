#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<pair<int, int>> cases = {
        {2, 0},
        {2, rnd.next(1, 30)},
        {8, 0},
        {8, rnd.next(24, 30)},
        {rnd.next(2, 8), 30},
        {rnd.next(2, 8), rnd.next(0, 30)},
        {rnd.next(2, 4), rnd.next(8, 30)},
        {rnd.next(5, 8), rnd.next(1, 18)},
    };

    shuffle(cases.begin(), cases.end());
    pair<int, int> chosen = cases.front();

    if (rnd.next(5) == 0) {
        chosen.first = rnd.wnext(7, rnd.next(2) ? 2 : -2) + 2;
        chosen.second = rnd.wnext(31, rnd.next(2) ? 3 : -3);
    }

    println(chosen.first, chosen.second);
    return 0;
}
