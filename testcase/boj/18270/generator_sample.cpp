#include "testlib.h"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<string> cows = {
        "Beatrice", "Belinda", "Bella", "Bessie",
        "Betsy", "Blue", "Buttercup", "Sue",
    };
    shuffle(cows.begin(), cows.end());

    vector<pair<string, string>> adjacent;
    for (int i = 0; i + 1 < (int)cows.size(); ++i) {
        adjacent.push_back({cows[i], cows[i + 1]});
    }

    int mode = rnd.next(0, 3);
    vector<pair<string, string>> constraints;

    if (mode == 0) {
        int n = rnd.next(1, 3);
        shuffle(adjacent.begin(), adjacent.end());
        adjacent.resize(n);
        constraints = adjacent;
    } else if (mode == 1) {
        int start = rnd.next(0, 5);
        int len = rnd.next(2, min(4, 7 - start));
        for (int i = start; i < start + len; ++i) {
            constraints.push_back(adjacent[i]);
        }
        int extras = rnd.next(0, 7 - (int)constraints.size());
        vector<pair<string, string>> candidates;
        for (int i = 0; i < (int)adjacent.size(); ++i) {
            if (i < start || i >= start + len) {
                candidates.push_back(adjacent[i]);
            }
        }
        shuffle(candidates.begin(), candidates.end());
        for (int i = 0; i < extras; ++i) {
            constraints.push_back(candidates[i]);
        }
    } else {
        constraints = adjacent;
    }

    for (auto& constraint : constraints) {
        if (rnd.next(0, 1) == 1) {
            swap(constraint.first, constraint.second);
        }
    }
    shuffle(constraints.begin(), constraints.end());

    println((int)constraints.size());
    for (const auto& constraint : constraints) {
        println(constraint.first, "must be milked beside", constraint.second);
    }

    return 0;
}
