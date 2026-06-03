#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int lowerBound(char grade, int s, int g, int p, int d) {
    if (grade == 'B') return 0;
    if (grade == 'S') return s;
    if (grade == 'G') return g;
    if (grade == 'P') return p;
    return d;
}

int upperBound(char grade, int s, int g, int p, int d) {
    if (grade == 'B') return s - 1;
    if (grade == 'S') return g - 1;
    if (grade == 'G') return p - 1;
    if (grade == 'P') return d - 1;
    return 2 * d;
}

int gradeRank(char grade) {
    if (grade == 'B') return 0;
    if (grade == 'S') return 1;
    if (grade == 'G') return 2;
    if (grade == 'P') return 3;
    return 4;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 36, "n");
    inf.readEoln();

    int s = inf.readInt(1, 500, "s");
    inf.readSpace();
    int g = inf.readInt(1, 500, "g");
    inf.readSpace();
    int p = inf.readInt(1, 500, "p");
    inf.readSpace();
    int d = inf.readInt(1, 500, "d");
    inf.readEoln();

    ensuref(s < g && g < p && p < d,
            "thresholds must satisfy 0 < s < g < p < d <= 500: %d %d %d %d",
            s, g, p, d);

    string grades = inf.readToken("[BSGPD]{1,36}", "grades");
    inf.readEoln();
    ensuref((int)grades.size() == n, "grade string length must be n: expected %d, got %d",
            n, (int)grades.size());

    for (int i = 1; i < n; ++i) {
        ensuref(gradeRank(grades[i - 1]) <= gradeRank(grades[i]),
                "grades must not decrease at month %d: %c to %c", i + 1, grades[i - 1],
                grades[i]);
    }

    vector<int> possible(d + 1, false), nextPossible(d + 1, false);
    possible[0] = true;
    for (int month = 0; month < n; ++month) {
        fill(nextPossible.begin(), nextPossible.end(), false);
        int lo = lowerBound(grades[month], s, g, p, d);
        int hi = upperBound(grades[month], s, g, p, d);
        for (int previous = 0; previous <= d; ++previous) {
            if (!possible[previous]) continue;
            for (int current = 0; current <= d; ++current) {
                int total = previous + current;
                if (lo <= total && total <= hi) {
                    nextPossible[current] = true;
                }
            }
        }
        ensuref(any_of(nextPossible.begin(), nextPossible.end(), [](int ok) { return ok; }),
                "grade record is impossible through month %d", month + 1);
        possible.swap(nextPossible);
    }

    inf.readEof();
}
