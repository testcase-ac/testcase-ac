#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <set>
#include <vector>

using namespace std;

static void addCoverage(vector<set<int>>& problems, int m) {
    vector<int> order(m);
    iota(order.begin(), order.end(), 1);
    shuffle(order.begin(), order.end());

    for (int category = 0; category < m; ++category) {
        int problem = rnd.next((int)problems.size());
        problems[problem].insert(order[category]);
    }
}

static void addRandomCategories(vector<set<int>>& problems, int m, int mode) {
    for (int i = 0; i < (int)problems.size(); ++i) {
        int target;
        if (mode == 0) {
            target = rnd.next(1, min(m, 3));
        } else if (mode == 1) {
            target = rnd.next(max(1, m - 2), m);
        } else if (mode == 2) {
            target = (i % 2 == 0 ? rnd.next(1, min(m, 2)) : rnd.next(max(1, m / 2), m));
        } else {
            target = rnd.next(1, m);
        }

        while ((int)problems[i].size() < target) {
            problems[i].insert(rnd.next(1, m));
        }
    }
}

static void printCategories(const set<int>& categories) {
    bool first = true;
    for (int category : categories) {
        if (!first) {
            cout << ' ';
        }
        cout << category;
        first = false;
    }
    cout << '\n';
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int k = rnd.next(1, 5);
    println(k);

    for (int tc = 0; tc < k; ++tc) {
        int mode = rnd.next(4);
        int m;
        int n;

        if (mode == 0) {
            m = rnd.next(1, 6);
            n = rnd.next(m, min(12, m + 5));
        } else if (mode == 1) {
            m = rnd.next(2, 10);
            n = rnd.next(1, 8);
        } else if (mode == 2) {
            m = rnd.next(3, 12);
            n = rnd.next(3, 12);
        } else {
            m = rnd.next(1, 20);
            n = rnd.next(1, 20);
        }

        vector<set<int>> problems(n);

        if (mode == 0) {
            vector<int> categories(m);
            iota(categories.begin(), categories.end(), 1);
            shuffle(categories.begin(), categories.end());
            for (int i = 0; i < m; ++i) {
                problems[i].insert(categories[i]);
            }
        }

        addCoverage(problems, m);
        addRandomCategories(problems, m, mode);

        println(m, n);
        for (const set<int>& categories : problems) {
            printCategories(categories);
        }
    }

    return 0;
}
