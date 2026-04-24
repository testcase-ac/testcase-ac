#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

pair<int,int> simulateSet(int idx, int forcedWinner = -1) {
    // idx: 0-based set index; forcedWinner: -1=random, 0=p1, 1=p2
    int win = (forcedWinner == -1 ? rnd.next(0,1) : forcedWinner);
    bool allowTB = (idx < 2);
    // tie-break possibility in first two sets
    if (allowTB && rnd.next(0,9) < 3) {
        return win == 0 ? make_pair(7,6) : make_pair(6,7);
    } else {
        int lose;
        if (win == 0) {
            if (idx < 2) {
                lose = rnd.next(0,4);
                return {6, lose};
            } else {
                if (rnd.next(0,9) < 3) return {7,5};
                lose = rnd.next(0,4);
                return {6, lose};
            }
        } else {
            if (idx < 2) {
                lose = rnd.next(0,4);
                return {lose, 6};
            } else {
                if (rnd.next(0,9) < 3) return {5,7};
                lose = rnd.next(0,4);
                return {lose, 6};
            }
        }
    }
}

vector<pair<int,int>> simulateMatchValid(int forcedWinner = -1) {
    // Simulate until someone wins 2 sets
    int p1s = 0, p2s = 0, idx = 0;
    vector<pair<int,int>> res;
    while (p1s < 2 && p2s < 2) {
        auto s = simulateSet(idx, forcedWinner);
        res.push_back(s);
        if (s.first > s.second) p1s++;
        else p2s++;
        idx++;
    }
    return res;
}

pair<int,int> genInvalidSet(int /*idx*/) {
    // Both scores < 6 => invalid set
    int a = rnd.next(0,5), b = rnd.next(0,5);
    return {a, b};
}

void printMatch(const vector<pair<int,int>>& v) {
    for (int i = 0; i < (int)v.size(); i++) {
        if (i) printf(" ");
        printf("%d:%d", v[i].first, v[i].second);
    }
    printf("\n");
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // -- Generate two distinct names, possibly including federer --
    bool useFed = rnd.next(0,1);
    string p1, p2;
    bool p1fed = false, p2fed = false;
    auto randName = [&]() {
        int L = rnd.next(3,8);
        string s;
        for (int i = 0; i < L; i++) s += char('a' + rnd.next(0,25));
        if (s == "federer") s = "x" + s; // avoid accidental federer
        return s;
    };
    if (useFed) {
        if (rnd.next(0,1) == 0) {
            p1 = "federer"; p1fed = true;
            p2 = randName();
        } else {
            p2 = "federer"; p2fed = true;
            p1 = randName();
        }
    } else {
        p1 = randName();
        do { p2 = randName(); } while (p2 == p1);
    }
    println(p1, p2);
    int N = rnd.next(1, 10);
    println(N);

    for (int i = 0; i < N; i++) {
        double choose = rnd.next();
        if (choose < 0.7) {
            // Valid match
            int forced = -1;
            if (p1fed) forced = 0;
            else if (p2fed) forced = 1;
            auto match = simulateMatchValid(forced);
            printMatch(match);
        } else {
            // Invalid match
            int type = rnd.next(0,3);
            if (type == 1) {
                // Extra sets after match end (but ≤5 total)
                int forced = -1;
                if (p1fed) forced = 0;
                else if (p2fed) forced = 1;
                auto match = simulateMatchValid(forced);
                if ((int)match.size() < 5) {
                    // add a spurious set
                    match.push_back(simulateSet((int)match.size(), -1));
                }
                printMatch(match);
            } else if (type == 3 && (p1fed || p2fed)) {
                // Federer's set loss (always invalid)
                auto match = simulateMatchValid();
                bool fedIsP1 = p1fed;
                bool hasLose = false;
                for (auto &s : match) {
                    if (fedIsP1 && s.first < s.second) hasLose = true;
                    if (!fedIsP1 && s.second < s.first) hasLose = true;
                }
                if (!hasLose) {
                    int pos = rnd.next(0, (int)match.size() - 1);
                    // swap to make federer lose that set
                    swap(match[pos].first, match[pos].second);
                }
                printMatch(match);
            } else {
                // Corrupt a random set's score
                int K = rnd.next(2, 5);
                vector<pair<int,int>> match;
                for (int j = 0; j < K; j++) {
                    match.push_back(simulateSet(j));
                }
                int pos = rnd.next(0, K-1);
                match[pos] = genInvalidSet(pos);
                printMatch(match);
            }
        }
    }
    return 0;
}
