#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>
using namespace std;

const int MAX_SCORE = 300000;

struct Update {
    int x;
    int d;
};

string makeColors(int n, int mode) {
    string colors(n, 'C');

    if (mode == 0) {
        for (int i = 0; i < n; ++i) colors[i] = (i % 2 == 0 ? 'C' : 'Z');
    } else if (mode == 1) {
        int split = rnd.next(1, n - 1);
        for (int i = split; i < n; ++i) colors[i] = 'Z';
    } else if (mode == 2) {
        fill(colors.begin(), colors.end(), 'Z');
        colors[rnd.next(0, n - 1)] = 'C';
    } else if (mode == 3) {
        fill(colors.begin(), colors.end(), 'C');
        colors[rnd.next(0, n - 1)] = 'Z';
    } else {
        bool hasC = false;
        bool hasZ = false;
        for (int i = 0; i < n; ++i) {
            colors[i] = rnd.next(0, 1) ? 'C' : 'Z';
            hasC |= colors[i] == 'C';
            hasZ |= colors[i] == 'Z';
        }
        if (!hasC) colors[rnd.next(0, n - 1)] = 'C';
        if (!hasZ) colors[rnd.next(0, n - 1)] = 'Z';
    }

    return colors;
}

int randomPositiveDelta(int current, int mode) {
    int remaining = MAX_SCORE - current;
    if (mode == 0) return 1;
    if (mode == 1) return rnd.next(1, min(remaining, 7));
    if (mode == 2) return rnd.next(1, min(remaining, 1000));
    if (mode == 3) return max(1, remaining);
    return rnd.next(1, remaining);
}

int chooseContestant(const string& colors, int mode) {
    vector<int> candidates;
    for (int i = 0; i < (int)colors.size(); ++i) {
        if ((mode == 1 && colors[i] == 'C') || (mode == 2 && colors[i] == 'Z')) {
            candidates.push_back(i + 1);
        }
    }
    if (candidates.empty()) return rnd.next(1, (int)colors.size());
    return rnd.any(candidates);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = (mode == 5 ? rnd.next(20, 40) : rnd.next(2, 12));
    int q = (mode == 5 ? rnd.next(35, 80) : rnd.next(n, 30));

    string colors = makeColors(n, rnd.next(0, 4));
    vector<int> score(n, 0);
    vector<Update> updates;
    updates.reserve(q);

    while ((int)updates.size() < q) {
        int x;
        if (mode == 0) {
            x = rnd.next(1, n);
        } else if (mode == 1 || mode == 2) {
            x = chooseContestant(colors, mode);
        } else if (mode == 3) {
            x = 1 + ((int)updates.size() % n);
        } else if (mode == 4) {
            x = rnd.any(vector<int>{1, n, rnd.next(1, n)});
        } else {
            x = rnd.next(1, n);
        }

        int current = score[x - 1];
        if (current == MAX_SCORE) {
            bool found = false;
            for (int i = 0; i < n; ++i) {
                if (score[i] < MAX_SCORE) {
                    x = i + 1;
                    current = score[i];
                    found = true;
                    break;
                }
            }
            if (!found) break;
        }

        int deltaMode = rnd.next(0, 4);
        int d = randomPositiveDelta(current, deltaMode);
        score[x - 1] += d;
        updates.push_back({x, d});
    }

    println(n, (int)updates.size());
    println(colors);
    for (const Update& update : updates) {
        println(update.x, update.d);
    }

    return 0;
}
