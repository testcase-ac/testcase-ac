#include "testlib.h"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>
using namespace std;

string makeLabel(int x) {
    string s;
    do {
        s.push_back(char('a' + (x % 26)));
        x /= 26;
    } while (x > 0);
    reverse(s.begin(), s.end());
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = 2 * rnd.next(1, 3);
    } else if (mode == 1) {
        n = 2 * rnd.next(2, 5);
    } else {
        n = 2 * rnd.next(4, 12);
    }

    vector<string> labels(n / 2);
    int offset = rnd.next(0, 200);
    for (int i = 0; i < n / 2; ++i) {
        labels[i] = makeLabel(offset + i);
    }

    vector<string> picture(n + 1);
    vector<int> positions;
    for (int i = 1; i <= n; ++i) {
        positions.push_back(i);
    }
    shuffle(positions.begin(), positions.end());
    for (int i = 0; i < n / 2; ++i) {
        picture[positions[2 * i]] = labels[i];
        picture[positions[2 * i + 1]] = labels[i];
    }

    vector<bool> faceUp(n + 1, false);
    vector<pair<int, int>> pairs;
    for (int a = 1; a <= n; ++a) {
        for (int b = a + 1; b <= n; ++b) {
            if (picture[a] == picture[b]) {
                pairs.push_back({a, b});
            }
        }
    }

    vector<pair<int, int>> turns;
    int maxTurns = min(1000, rnd.next(0, min(4 * n, 60)));
    if (mode == 0) {
        maxTurns = 0;
    } else if (mode == 2) {
        maxTurns = rnd.next(1, min(3 * n, 40));
    } else if (mode == 4) {
        maxTurns = rnd.next(n / 2, min(5 * n, 80));
    }

    for (int step = 0; step < maxTurns; ++step) {
        vector<pair<int, int>> matches;
        vector<pair<int, int>> mismatches;
        int faceDownCount = 0;
        for (int i = 1; i <= n; ++i) {
            if (!faceUp[i]) {
                ++faceDownCount;
            }
        }

        for (int a = 1; a <= n; ++a) {
            if (faceUp[a]) {
                continue;
            }
            for (int b = a + 1; b <= n; ++b) {
                if (faceUp[b]) {
                    continue;
                }
                if (picture[a] == picture[b]) {
                    if (faceDownCount > 4) {
                        matches.push_back({a, b});
                    }
                } else {
                    mismatches.push_back({a, b});
                }
            }
        }

        bool wantMatch = mode == 3 || (mode != 2 && rnd.next(0, 99) < 25);
        pair<int, int> chosen;
        if (wantMatch && !matches.empty()) {
            chosen = rnd.any(matches);
            faceUp[chosen.first] = true;
            faceUp[chosen.second] = true;
        } else if (!mismatches.empty()) {
            chosen = rnd.any(mismatches);
        } else if (!matches.empty()) {
            chosen = rnd.any(matches);
            faceUp[chosen.first] = true;
            faceUp[chosen.second] = true;
        } else {
            break;
        }

        if (rnd.next(0, 1)) {
            swap(chosen.first, chosen.second);
        }
        turns.push_back(chosen);
    }

    println(n);
    println((int)turns.size());
    for (auto [a, b] : turns) {
        println(a, b, picture[a], picture[b]);
    }

    return 0;
}
