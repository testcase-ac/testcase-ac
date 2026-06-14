#include "testlib.h"

#include <algorithm>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

string formatProbability(int millionths) {
    if (millionths == 0) {
        return "0";
    }
    if (millionths == 1000000) {
        return "1";
    }

    string frac = to_string(millionths);
    while (frac.size() < 6) {
        frac = "0" + frac;
    }
    while (!frac.empty() && frac.back() == '0') {
        frac.pop_back();
    }
    return "0." + frac;
}

int chooseN() {
    int mode = rnd.next(0, 5);
    if (mode == 0) {
        return 1;
    }
    if (mode == 1) {
        return rnd.next(2, 12);
    }
    if (mode == 2) {
        return rnd.next(13, 80);
    }
    if (mode == 3) {
        return rnd.next(200, 1000);
    }
    return 1000;
}

pair<int, int> chooseProbabilities() {
    int mode = rnd.next(0, 7);
    if (mode == 0) {
        return {0, 0};
    }
    if (mode == 1) {
        return rnd.next(0, 1) == 0 ? make_pair(1000000, 0) : make_pair(0, 1000000);
    }
    if (mode == 2) {
        int p = rnd.next(0, 1000000);
        return {p, 1000000 - p};
    }
    if (mode == 3) {
        int p = rnd.next(0, 500000);
        return {p, p};
    }
    if (mode == 4) {
        int l = rnd.next(0, 10000);
        int r = rnd.next(0, 10000);
        return {l, r};
    }
    if (mode == 5) {
        int l = rnd.next(900000, 1000000);
        int r = rnd.next(0, 1000000 - l);
        return {l, r};
    }
    if (mode == 6) {
        int r = rnd.next(900000, 1000000);
        int l = rnd.next(0, 1000000 - r);
        return {l, r};
    }

    int l = rnd.next(0, 1000000);
    int r = rnd.next(0, 1000000 - l);
    return {l, r};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int p = rnd.next(1, 15);
    vector<tuple<int, int, int>> cases;
    cases.reserve(p);

    cases.emplace_back(1, 500000, 500000);
    if (p >= 2) {
        cases.emplace_back(1000, 500000, 400000);
    }
    if (p >= 3) {
        cases.emplace_back(rnd.next(1, 8), 0, 1000000);
    }

    while (static_cast<int>(cases.size()) < p) {
        auto probs = chooseProbabilities();
        cases.emplace_back(chooseN(), probs.first, probs.second);
    }

    shuffle(cases.begin(), cases.end());

    println(p);
    for (const auto& [n, l, r] : cases) {
        println(n, formatProbability(l), formatProbability(r));
    }

    return 0;
}
