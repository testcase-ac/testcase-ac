#include "testlib.h"

#include <algorithm>
#include <array>
#include <vector>
using namespace std;

int clampRating(int value) {
    return max(0, min(4000, value));
}

array<int, 3> makeTeamForMode(int mode, int k, int l) {
    if (mode == 0) {
        int base = rnd.next(l, 4000);
        return {base, rnd.next(l, 4000), rnd.next(l, 4000)};
    }

    if (mode == 1) {
        int low = l == 0 ? 0 : rnd.next(0, l - 1);
        return {low, rnd.next(0, 4000), rnd.next(0, 4000)};
    }

    if (mode == 2) {
        int a = rnd.next(l, 4000);
        int b = rnd.next(l, 4000);
        int targetSum = max(0, k - rnd.next(1, 30));
        int c = clampRating(targetSum - a - b);
        if (c >= l) {
            c = l == 0 ? 0 : l - 1;
        }
        return {a, b, c};
    }

    if (mode == 3) {
        int a = rnd.next(l, 4000);
        int b = rnd.next(l, 4000);
        int c = clampRating(k - a - b + rnd.next(-2, 2));
        if (c < l) {
            c = l;
        }
        return {a, b, c};
    }

    vector<int> candidates = {
        0,
        1,
        max(0, l - 1),
        l,
        min(4000, l + 1),
        3999,
        4000,
        clampRating(k / 3),
        clampRating((k + 2) / 3),
    };
    return {rnd.any(candidates), rnd.any(candidates), rnd.any(candidates)};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 20);

    int l;
    if (mode == 0) {
        l = rnd.next(0, 20);
    } else if (mode == 1) {
        l = rnd.next(3980, 4000);
    } else {
        vector<int> lCandidates = {0, 1, 2, 1599, 1600, 1601, 3999, 4000};
        l = rnd.any(lCandidates);
    }

    int k;
    if (mode == 2) {
        k = rnd.next(0, 30);
    } else if (mode == 3) {
        k = rnd.next(11970, 12000);
    } else {
        vector<int> kCandidates = {0, 1, 2, 4999, 5000, 5001, 11999, 12000};
        k = rnd.any(kCandidates);
    }

    vector<array<int, 3>> teams;
    for (int i = 0; i < n; ++i) {
        int teamMode;
        if (mode == 4) {
            teamMode = i % 5;
        } else if (mode == 5) {
            teamMode = rnd.next(0, 4);
        } else {
            teamMode = mode;
        }
        teams.push_back(makeTeamForMode(teamMode, k, l));
    }

    shuffle(teams.begin(), teams.end());

    println(n, k, l);
    for (const auto& team : teams) {
        println(team[0], team[1], team[2]);
    }

    return 0;
}
