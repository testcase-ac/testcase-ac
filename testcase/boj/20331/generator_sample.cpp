#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 40);
    int p = rnd.next(1, 12);
    int positiveGroups = 0;

    if (mode == 0) {
        positiveGroups = 0;
    } else if (mode == 1) {
        positiveGroups = p;
        n = max(n, positiveGroups);
    } else if (mode == 2) {
        if (p == 1) p = rnd.next(2, 12);
        positiveGroups = rnd.next(1, p - 1);
        n = max(n, positiveGroups);
    } else if (mode == 3) {
        positiveGroups = rnd.next(1, p);
        n = rnd.next(positiveGroups, min(60, positiveGroups + 20));
    } else {
        positiveGroups = rnd.next(1, min(p, 4));
        n = rnd.next(positiveGroups, positiveGroups + 8);
        p = rnd.next(positiveGroups, 10000);
    }

    vector<int> scores;
    int positiveTeams = positiveGroups == 0 ? 0 : rnd.next(positiveGroups, n);
    int zeroTeams = n - positiveTeams;

    int current = rnd.next(400, 999000);
    for (int group = 0; group < positiveGroups; ++group) {
        int remainingGroups = positiveGroups - group;
        int remainingTeams = positiveTeams - (int)scores.size();
        int groupSize = group + 1 == positiveGroups
                            ? remainingTeams
                            : rnd.next(1, remainingTeams - remainingGroups + 1);

        int value = current;
        for (int i = 0; i < groupSize; ++i) {
            if (i > 0 && rnd.next(0, 2) != 0) {
                value += rnd.next(0, 25);
            }
            scores.push_back(value);
        }

        if (group + 1 < positiveGroups) {
            current = rnd.next(1, max(1, scores.back() - 1));
        }
    }

    for (int i = 0; i < zeroTeams; ++i) {
        scores.push_back(0);
    }

    println(n, p);
    for (int score : scores) {
        println(score);
    }

    return 0;
}
