#include "testlib.h"

#include <algorithm>
#include <set>
#include <vector>

using namespace std;

vector<int> randomMoves(int mode) {
    set<int> moves;

    if (mode == 0) {
        moves.insert(1);
        moves.insert(rnd.next(2, 10));
        moves.insert(rnd.next(11, 30));
    } else if (mode == 1) {
        moves.insert(rnd.next(1, 5));
        moves.insert(rnd.next(10, 20));
        moves.insert(rnd.next(21, 30));
    } else if (mode == 2) {
        moves.insert(rnd.next(20, 28));
        moves.insert(rnd.next(29, 30));
    }

    while ((int)moves.size() < 3) {
        moves.insert(rnd.next(1, 30));
    }

    return vector<int>(moves.begin(), moves.end());
}

int nearValue(int x) {
    int delta = rnd.next(-2, 2);
    return max(1, min(500, x + delta));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 3);
    vector<int> b = randomMoves(mode);

    vector<pair<int, int>> candidates;
    candidates.push_back({1, 1});
    candidates.push_back({b[0], b[1]});
    candidates.push_back({nearValue(b[2]), rnd.next(1, 40)});
    candidates.push_back({rnd.next(1, 40), nearValue(b[2])});
    candidates.push_back({rnd.next(450, 500), rnd.next(450, 500)});
    candidates.push_back({rnd.next(1, 500), rnd.next(1, 500)});
    candidates.push_back({rnd.next(1, 80), rnd.next(1, 80)});

    shuffle(candidates.begin(), candidates.end());
    candidates.resize(5);

    println(b);
    for (const auto& query : candidates) {
        println(query.first, query.second);
    }

    return 0;
}
