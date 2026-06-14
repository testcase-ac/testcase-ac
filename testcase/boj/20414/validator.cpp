#include "testlib.h"

#include <string>
#include <vector>
using namespace std;

static pair<int, int> gradeRange(char grade, int s, int g, int p, int d) {
    if (grade == 'B') return {0, s - 1};
    if (grade == 'S') return {s, g - 1};
    if (grade == 'G') return {g, p - 1};
    if (grade == 'P') return {p, d - 1};
    return {d, 2 * d};
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 36, "N");
    inf.readEoln();

    int s = inf.readInt(1, 500, "s");
    inf.readSpace();
    int g = inf.readInt(1, 500, "g");
    inf.readSpace();
    int p = inf.readInt(1, 500, "p");
    inf.readSpace();
    int d = inf.readInt(1, 500, "d");
    inf.readEoln();

    ensuref(s < g, "thresholds must satisfy s < g: s=%d, g=%d", s, g);
    ensuref(g < p, "thresholds must satisfy g < p: g=%d, p=%d", g, p);
    ensuref(p < d, "thresholds must satisfy p < d: p=%d, d=%d", p, d);

    string grades = inf.readToken("[BSGPD]{1,36}", "grades");
    inf.readEoln();
    ensuref((int)grades.size() == n, "grades length must be N: length=%d, N=%d",
            (int)grades.size(), n);

    vector<char> possible(d + 1, false), nextPossible(d + 1, false);
    possible[0] = true;
    for (int i = 0; i < n; ++i) {
        fill(nextPossible.begin(), nextPossible.end(), false);
        auto [low, high] = gradeRange(grades[i], s, g, p, d);
        for (int previous = 0; previous <= d; ++previous) {
            if (!possible[previous]) continue;
            for (int current = 0; current <= d; ++current) {
                int twoMonthTotal = previous + current;
                if (low <= twoMonthTotal && twoMonthTotal <= high) {
                    nextPossible[current] = true;
                }
            }
        }
        possible.swap(nextPossible);
    }

    bool feasible = false;
    for (bool state : possible) feasible = feasible || state;
    ensuref(feasible, "grade history must be achievable with monthly charges from 0 to d");

    inf.readEof();
}
