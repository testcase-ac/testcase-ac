#include "testlib.h"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 36, "n");
    inf.readEoln();

    int s = inf.readInt(1, 49997, "s");
    inf.readSpace();
    int g = inf.readInt(s + 1, 49998, "g");
    inf.readSpace();
    int p = inf.readInt(g + 1, 49999, "p");
    inf.readSpace();
    int d = inf.readInt(p + 1, 50000, "d");
    inf.readEoln();

    string grades = inf.readToken("[BSGPD]{1,36}", "grades");
    inf.readEoln();
    ensuref((int)grades.size() == n, "grade record length is %d, expected %d",
            (int)grades.size(), n);

    auto bounds = [&](char grade) -> pair<int, int> {
        if (grade == 'B') return {0, s - 1};
        if (grade == 'S') return {s, g - 1};
        if (grade == 'G') return {g, p - 1};
        if (grade == 'P') return {p, d - 1};
        return {d, 2 * d};
    };

    vector<char> possible(d + 1, false), next_possible(d + 1, false);
    vector<int> prefix(d + 1, 0);
    auto first = bounds(grades[0]);
    for (int paid = first.first; paid <= min(first.second, d); ++paid) {
        possible[paid] = true;
    }

    for (int month = 1; month < n; ++month) {
        fill(next_possible.begin(), next_possible.end(), false);
        prefix[0] = possible[0] ? 1 : 0;
        for (int paid = 1; paid <= d; ++paid) {
            prefix[paid] = prefix[paid - 1] + (possible[paid] ? 1 : 0);
        }

        auto current = bounds(grades[month]);
        for (int paid = 0; paid <= d; ++paid) {
            int low_previous = max(0, current.first - paid);
            int high_previous = min(d, current.second - paid);
            if (low_previous <= high_previous) {
                int reachable = prefix[high_previous] -
                                (low_previous == 0 ? 0 : prefix[low_previous - 1]);
                if (reachable > 0) {
                    next_possible[paid] = true;
                }
            }
        }
        possible.swap(next_possible);
    }

    ensuref(any_of(possible.begin(), possible.end(), [](char ok) { return ok; }),
            "grade record cannot be achieved with monthly payment limit d=%d", d);

    inf.readEof();
}
