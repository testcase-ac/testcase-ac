#include "testlib.h"

#include <algorithm>
#include <set>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

struct Interaction {
    int time;
    int x;
    int y;
};

string simulate(int n, vector<Interaction> interactions, int patientZero, int k) {
    sort(interactions.begin(), interactions.end(),
         [](const Interaction& a, const Interaction& b) {
             return a.time < b.time;
         });

    vector<int> infected(n + 1, 0);
    vector<int> remaining(n + 1, 0);
    infected[patientZero] = 1;
    remaining[patientZero] = k;

    for (const Interaction& interaction : interactions) {
        int x = interaction.x;
        int y = interaction.y;
        bool xInfected = infected[x];
        bool yInfected = infected[y];

        if (xInfected && remaining[x] > 0) {
            --remaining[x];
            if (!infected[y]) {
                infected[y] = 1;
                remaining[y] = k;
            }
        }
        if (yInfected && remaining[y] > 0) {
            --remaining[y];
            if (!infected[x]) {
                infected[x] = 1;
                remaining[x] = k;
            }
        }
    }

    string finalState;
    finalState.reserve(n);
    for (int i = 1; i <= n; ++i) {
        finalState += char('0' + infected[i]);
    }
    return finalState;
}

void addInteraction(vector<Interaction>& interactions, set<int>& usedTimes, int time,
                    int x, int y) {
    if (x == y || usedTimes.count(time)) {
        return;
    }
    usedTimes.insert(time);
    interactions.push_back({time, x, y});
}

int freshTime(set<int>& usedTimes) {
    int time = rnd.next(1, 250);
    while (usedTimes.count(time)) {
        time = rnd.next(1, 250);
    }
    return time;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, 14);
    int targetT = rnd.next(1, min(60, 250));
    vector<Interaction> interactions;
    set<int> usedTimes;

    if (mode == 0) {
        n = rnd.next(2, 10);
        int t = rnd.next(1, min(2 * n, 20));
        for (int i = 0; i < t; ++i) {
            int x = rnd.next(1, n - 1);
            addInteraction(interactions, usedTimes, freshTime(usedTimes), x, x + 1);
        }
    } else if (mode == 1) {
        n = rnd.next(3, 18);
        int center = rnd.next(1, n);
        int t = rnd.next(n - 1, min(3 * n, 45));
        for (int i = 0; i < t; ++i) {
            int y = rnd.next(1, n - 1);
            if (y >= center) {
                ++y;
            }
            addInteraction(interactions, usedTimes, freshTime(usedTimes), center, y);
        }
    } else if (mode == 2) {
        n = rnd.next(2, 8);
        int a = rnd.next(1, n);
        int b = rnd.next(1, n - 1);
        if (b >= a) {
            ++b;
        }
        int t = rnd.next(1, 35);
        for (int i = 0; i < t; ++i) {
            addInteraction(interactions, usedTimes, freshTime(usedTimes), a, b);
        }
    } else if (mode == 3) {
        n = rnd.next(5, 20);
        int t = rnd.next(n, min(4 * n, 70));
        for (int i = 0; i < t; ++i) {
            int x = rnd.next(1, n);
            int y = rnd.next(1, n - 1);
            if (y >= x) {
                ++y;
            }
            addInteraction(interactions, usedTimes, freshTime(usedTimes), x, y);
        }
    } else if (mode == 4) {
        n = rnd.next(80, 100);
        targetT = rnd.next(120, 250);
        for (int i = 0; i < targetT; ++i) {
            int x = rnd.next(1, n);
            int y = rnd.next(1, n - 1);
            if (y >= x) {
                ++y;
            }
            addInteraction(interactions, usedTimes, freshTime(usedTimes), x, y);
        }
    } else {
        n = rnd.next(2, 12);
        vector<pair<int, int>> pairs;
        for (int x = 1; x <= n; ++x) {
            for (int y = x + 1; y <= n; ++y) {
                pairs.push_back({x, y});
            }
        }
        int t = rnd.next(1, min(30, (int)pairs.size()));
        shuffle(pairs.begin(), pairs.end());
        for (int i = 0; i < t; ++i) {
            addInteraction(interactions, usedTimes, freshTime(usedTimes), pairs[i].first,
                           pairs[i].second);
        }
    }

    if (interactions.empty()) {
        addInteraction(interactions, usedTimes, freshTime(usedTimes), 1, 2);
    }

    int patientZero = rnd.next(1, n);
    int kChoice = rnd.next(0, 5);
    int k;
    if (kChoice == 0) {
        k = 0;
    } else if (kChoice == 1) {
        k = 1;
    } else if (kChoice == 2) {
        k = rnd.next(2, min(8, (int)interactions.size() + 1));
    } else if (kChoice == 3) {
        k = (int)interactions.size() + 1;
    } else {
        k = rnd.next(0, (int)interactions.size() + 1);
    }

    string finalState = simulate(n, interactions, patientZero, k);
    shuffle(interactions.begin(), interactions.end());

    println(n, (int)interactions.size());
    println(finalState);
    for (const Interaction& interaction : interactions) {
        println(interaction.time, interaction.x, interaction.y);
    }

    return 0;
}
