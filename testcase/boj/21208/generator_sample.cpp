#include "testlib.h"

#include <algorithm>
#include <set>
#include <string>
#include <vector>

using namespace std;

string makeNote(int id, int style) {
    static const vector<string> words = {
        "Alpha", "Bravo", "Cafe", "Delta", "Echo", "Food", "Game",
        "Health", "Idea", "Joy", "Kindness", "Lunch", "Music", "Rain",
        "Sleep", "Tea", "Walk", "Work"
    };

    string base = words[id % static_cast<int>(words.size())];
    int suffix = id / static_cast<int>(words.size()) + 1;
    if (style == 0) return base;
    if (style == 1) return base + " " + to_string(suffix);
    if (style == 2) return base + "-" + to_string(suffix) + "!";
    return base + " #" + to_string(suffix);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(1, 14);
    int style = rnd.next(0, 3);
    int poolSize = rnd.next(3, min(28, 3 * n + 4));

    if (mode == 1) poolSize = rnd.next(3, min(8, max(3, 3 * n)));
    if (mode == 2) poolSize = 3 * n;
    if (mode == 3) n = rnd.next(1, 4), poolSize = 3 * n;
    if (mode == 4) n = rnd.next(10, 22), poolSize = rnd.next(4, 10);

    vector<string> pool;
    for (int i = 0; i < poolSize; ++i) pool.push_back(makeNote(i, style));

    vector<vector<string>> days(n);
    vector<int> recentOrder(poolSize);
    for (int i = 0; i < poolSize; ++i) recentOrder[i] = i;
    shuffle(recentOrder.begin(), recentOrder.end());

    for (int day = 0; day < n; ++day) {
        set<int> used;

        if (mode == 0) {
            while (static_cast<int>(used.size()) < 3) used.insert(rnd.next(poolSize));
        } else if (mode == 1) {
            while (static_cast<int>(used.size()) < 3) {
                int pick = rnd.wnext(poolSize, -2);
                used.insert(pick);
            }
        } else if (mode == 2 || mode == 3) {
            used.insert(3 * day);
            used.insert(3 * day + 1);
            used.insert(3 * day + 2);
        } else {
            used.insert(day % poolSize);
            used.insert((day + 1) % poolSize);
            while (static_cast<int>(used.size()) < 3) used.insert(rnd.next(poolSize));
        }

        for (int id : used) days[day].push_back(pool[id]);
        shuffle(days[day].begin(), days[day].end());
    }

    if (mode == 0 && n >= 4 && poolSize >= 6) {
        days[0] = {pool[0], pool[1], pool[2]};
        days[n - 2] = {pool[0], pool[3], pool[4]};
        days[n - 1] = {pool[1], pool[3], pool[5]};
    }

    int k;
    if (rnd.next(0, 4) == 0) {
        k = 3 * n;
    } else if (rnd.next(0, 3) == 0) {
        k = rnd.next(max(1, poolSize - 2), 3 * n);
    } else {
        k = rnd.next(1, min(3 * n, max(1, poolSize)));
    }

    println(n, k);
    for (const vector<string>& day : days) {
        for (const string& note : day) println(note);
    }

    return 0;
}
