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

bool feasible(const string& grades, int s, int g, int p, int d) {
    vector<int> possible(d + 1, false), nextPossible(d + 1, false);
    possible[0] = true;
    for (char grade : grades) {
        fill(nextPossible.begin(), nextPossible.end(), false);
        int lo = lowerBound(grade, s, g, p, d);
        int hi = upperBound(grade, s, g, p, d);
        for (int previous = 0; previous <= d; ++previous) {
            if (!possible[previous]) continue;
            for (int current = 0; current <= d; ++current) {
                int total = previous + current;
                if (lo <= total && total <= hi) nextPossible[current] = true;
            }
        }
        if (!any_of(nextPossible.begin(), nextPossible.end(), [](int ok) { return ok; })) {
            return false;
        }
        possible.swap(nextPossible);
    }
    return true;
}

string makeGrades(int n) {
    const string alphabet = "BSGPD";
    int mode = rnd.next(5);
    string grades;

    if (mode == 0) {
        grades.assign(n, alphabet[rnd.next(5)]);
    } else if (mode == 1) {
        int rank = rnd.next(5);
        for (int i = 0; i < n; ++i) {
            if (rank < 4 && rnd.next(100) < 35) ++rank;
            grades += alphabet[rank];
        }
    } else {
        int start = rnd.next(5);
        int finish = rnd.next(start, 4);
        vector<int> cuts;
        for (int rank = start; rank <= finish; ++rank) cuts.push_back(rank);
        for (int i = 0; i < n; ++i) {
            int rank = cuts[min((int)cuts.size() - 1, i * (int)cuts.size() / n)];
            if (mode == 2 && rnd.next(100) < 20 && rank < finish) ++rank;
            grades += alphabet[rank];
        }
        sort(grades.begin(), grades.end(), [](char a, char b) {
            return string("BSGPD").find(a) < string("BSGPD").find(b);
        });
    }

    return grades;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(1, 18);
    if (rnd.next(100) < 12) n = rnd.next(19, 36);

    int d = rnd.next(4, 500);
    int s, g, p;
    if (rnd.next(100) < 35) {
        s = rnd.next(1, min(20, d - 3));
        g = rnd.next(s + 1, min(d - 2, s + 20));
        p = rnd.next(g + 1, min(d - 1, g + 40));
    } else {
        vector<int> points;
        while ((int)points.size() < 3) {
            int x = rnd.next(1, d - 1);
            if (find(points.begin(), points.end(), x) == points.end()) points.push_back(x);
        }
        sort(points.begin(), points.end());
        s = points[0];
        g = points[1];
        p = points[2];
    }

    string grades;
    do {
        grades = makeGrades(n);
    } while (!feasible(grades, s, g, p, d));

    println(n);
    println(s, g, p, d);
    println(grades);

    return 0;
}
