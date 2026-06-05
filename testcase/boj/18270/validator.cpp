#include "testlib.h"

#include <algorithm>
#include <cstdlib>
#include <map>
#include <string>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const vector<string> cows = {
        "Beatrice", "Belinda", "Bella", "Bessie",
        "Betsy", "Blue", "Buttercup", "Sue",
    };

    map<string, int> cowIndex;
    for (int i = 0; i < (int)cows.size(); ++i) {
        cowIndex[cows[i]] = i;
    }

    int n = inf.readInt(1, 7, "N");
    inf.readEoln();

    vector<pair<int, int>> constraints;
    for (int i = 0; i < n; ++i) {
        string x = inf.readToken("[A-Za-z]{1,9}", "X");
        inf.readSpace();
        string must = inf.readToken("[a-z]{4}", "must");
        inf.readSpace();
        string be = inf.readToken("[a-z]{2}", "be");
        inf.readSpace();
        string milked = inf.readToken("[a-z]{6}", "milked");
        inf.readSpace();
        string beside = inf.readToken("[a-z]{6}", "beside");
        inf.readSpace();
        string y = inf.readToken("[A-Za-z]{1,9}", "Y");
        inf.readEoln();

        ensuref(cowIndex.count(x), "unknown cow X at constraint %d: %s", i + 1, x.c_str());
        ensuref(must == "must", "expected 'must' at constraint %d", i + 1);
        ensuref(be == "be", "expected 'be' at constraint %d", i + 1);
        ensuref(milked == "milked", "expected 'milked' at constraint %d", i + 1);
        ensuref(beside == "beside", "expected 'beside' at constraint %d", i + 1);
        ensuref(cowIndex.count(y), "unknown cow Y at constraint %d: %s", i + 1, y.c_str());

        constraints.push_back({cowIndex[x], cowIndex[y]});
    }

    vector<int> order(8);
    for (int i = 0; i < 8; ++i) {
        order[i] = i;
    }

    bool possible = false;
    do {
        vector<int> pos(8);
        for (int i = 0; i < 8; ++i) {
            pos[order[i]] = i;
        }

        bool ok = true;
        for (const auto& constraint : constraints) {
            if (abs(pos[constraint.first] - pos[constraint.second]) != 1) {
                ok = false;
                break;
            }
        }
        if (ok) {
            possible = true;
            break;
        }
    } while (next_permutation(order.begin(), order.end()));

    ensuref(possible, "constraints must have at least one valid ordering");
    inf.readEof();
}
