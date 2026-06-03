#include "testlib.h"

#include <set>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(1, 8);
    vector<vector<int>> cases;

    for (int tc = 0; tc < n; ++tc) {
        int mode = tc < 4 ? tc : rnd.next(0, 3);

        set<int> used;
        vector<int> jerseys;
        if (mode == 1 || mode == 3) {
            jerseys.push_back(17);
            used.insert(17);
        }
        if (mode == 2 || mode == 3) {
            jerseys.push_back(18);
            used.insert(18);
        }

        int fillStyle = rnd.next(0, 3);
        while ((int)jerseys.size() < 10) {
            int jersey;
            if (fillStyle == 0) {
                jersey = rnd.next(11, 30);
            } else if (fillStyle == 1) {
                jersey = rnd.next(80, 99);
            } else {
                jersey = rnd.next(11, 99);
            }

            if (jersey == 17 || jersey == 18 || used.count(jersey)) {
                continue;
            }
            jerseys.push_back(jersey);
            used.insert(jersey);
        }

        shuffle(jerseys.begin(), jerseys.end());
        cases.push_back(jerseys);
    }

    println(n);
    for (const auto& jerseys : cases) {
        println(jerseys);
    }

    return 0;
}
