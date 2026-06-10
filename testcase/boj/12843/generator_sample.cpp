#include "testlib.h"
#include <algorithm>
#include <set>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = 2;
    } else if (mode == 1) {
        n = rnd.next(3, 8);
    } else if (mode == 2) {
        n = rnd.next(4, 12);
    } else if (mode == 3) {
        n = rnd.next(6, 14);
    } else if (mode == 4) {
        n = rnd.next(8, 18);
    } else {
        n = rnd.next(20, 45);
    }

    vector<int> ids(n);
    for (int i = 0; i < n; ++i) ids[i] = i + 1;
    shuffle(ids.begin(), ids.end());

    int cCount = rnd.next(1, n - 1);
    if (mode == 0) cCount = 1;
    if (mode == 3) cCount = 1;
    if (mode == 5) cCount = rnd.next(max(1, n / 3), min(n - 1, 2 * n / 3));

    vector<char> dept(n + 1, 's');
    vector<int> cCourses;
    vector<int> sCourses;
    for (int i = 0; i < n; ++i) {
        if (i < cCount) {
            dept[ids[i]] = 'c';
            cCourses.push_back(ids[i]);
        } else {
            dept[ids[i]] = 's';
            sCourses.push_back(ids[i]);
        }
    }

    vector<pair<int, int>> candidates;
    for (int c : cCourses) {
        for (int s : sCourses) candidates.emplace_back(c, s);
    }
    shuffle(candidates.begin(), candidates.end());

    set<pair<int, int>> chosen;
    auto addEdge = [&](int a, int b) {
        if (dept[a] == dept[b]) return;
        chosen.insert(minmax(a, b));
    };

    if (mode == 0) {
        addEdge(cCourses[0], sCourses[0]);
    } else if (mode == 1) {
        int m = rnd.next(1, (int)candidates.size());
        for (int i = 0; i < m; ++i) addEdge(candidates[i].first, candidates[i].second);
    } else if (mode == 2) {
        vector<int> left = cCourses;
        vector<int> right = sCourses;
        if (rnd.next(0, 1)) swap(left, right);
        for (int i = 0; i + 1 < n; ++i) {
            int a = (i % 2 == 0) ? left[i / 2 % left.size()] : right[i / 2 % right.size()];
            int b = (i % 2 == 0) ? right[i / 2 % right.size()] : left[(i + 1) / 2 % left.size()];
            addEdge(a, b);
        }
        int extra = rnd.next(0, min((int)candidates.size(), n));
        for (int i = 0; i < extra; ++i) addEdge(candidates[i].first, candidates[i].second);
    } else if (mode == 3) {
        int center = cCourses[0];
        for (int s : sCourses) addEdge(center, s);
        int extra = rnd.next(0, min((int)candidates.size(), n / 2));
        for (int i = 0; i < extra; ++i) addEdge(candidates[i].first, candidates[i].second);
    } else if (mode == 4) {
        double density = rnd.next(0.45, 0.85);
        for (auto edge : candidates) {
            if (rnd.next() < density) addEdge(edge.first, edge.second);
        }
        if (chosen.empty()) addEdge(candidates[0].first, candidates[0].second);
    } else {
        int target = rnd.next(max(1, (int)candidates.size() / 3), (int)candidates.size());
        for (int i = 0; i < target; ++i) addEdge(candidates[i].first, candidates[i].second);
    }

    vector<pair<int, int>> edges(chosen.begin(), chosen.end());
    shuffle(edges.begin(), edges.end());
    for (auto& edge : edges) {
        if (rnd.next(0, 1)) swap(edge.first, edge.second);
    }

    println(n, (int)edges.size());
    shuffle(ids.begin(), ids.end());
    for (int id : ids) println(id, string(1, dept[id]));
    for (auto edge : edges) println(edge.first, edge.second);

    return 0;
}
