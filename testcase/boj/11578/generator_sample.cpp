#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 10);
    int m = rnd.next(1, 10);

    auto printCase = [&](const vector<vector<int>>& students) {
        println(n, m);
        for (const auto& solvable : students) {
            cout << solvable.size();
            for (int p : solvable) cout << ' ' << p;
            cout << '\n';
        }
    };

    if (mode == 0) {
        vector<vector<int>> students(m);
        for (int i = 0; i < m; ++i) {
            if (rnd.next(0, 2) == 0) continue;
            students[i].push_back(rnd.next(1, n));
        }
        printCase(students);
    } else if (mode == 1) {
        n = rnd.next(2, 10);
        m = rnd.next(n, 10);
        vector<vector<int>> students(m);
        vector<int> problems;
        for (int p = 1; p <= n; ++p) problems.push_back(p);
        shuffle(problems.begin(), problems.end());
        for (int p = 1; p <= n; ++p) students[p - 1].push_back(problems[p - 1]);
        for (int i = n; i < m; ++i) {
            int cnt = rnd.next(0, min(n, 3));
            vector<int> pool;
            for (int p = 1; p <= n; ++p) pool.push_back(p);
            shuffle(pool.begin(), pool.end());
            students[i].assign(pool.begin(), pool.begin() + cnt);
            sort(students[i].begin(), students[i].end());
        }
        printCase(students);
    } else if (mode == 2) {
        vector<vector<int>> students(m);
        int missing = rnd.next(1, n);
        for (int i = 0; i < m; ++i) {
            vector<int> pool;
            for (int p = 1; p <= n; ++p) {
                if (p != missing) pool.push_back(p);
            }
            shuffle(pool.begin(), pool.end());
            int cnt = rnd.next(0, (int)pool.size());
            students[i].assign(pool.begin(), pool.begin() + cnt);
            sort(students[i].begin(), students[i].end());
        }
        printCase(students);
    } else if (mode == 3) {
        vector<vector<int>> students(m);
        for (int i = 0; i < m; ++i) {
            vector<int> pool;
            for (int p = 1; p <= n; ++p) pool.push_back(p);
            shuffle(pool.begin(), pool.end());
            int cnt = rnd.next(max(1, n / 2), n);
            students[i].assign(pool.begin(), pool.begin() + cnt);
            sort(students[i].begin(), students[i].end());
        }
        printCase(students);
    } else if (mode == 4) {
        vector<vector<int>> students(m);
        int key = rnd.next(0, m - 1);
        for (int p = 1; p <= n; ++p) students[key].push_back(p);
        for (int i = 0; i < m; ++i) {
            if (i == key) continue;
            int cnt = rnd.next(0, min(n, 4));
            vector<int> pool;
            for (int p = 1; p <= n; ++p) pool.push_back(p);
            shuffle(pool.begin(), pool.end());
            students[i].assign(pool.begin(), pool.begin() + cnt);
            sort(students[i].begin(), students[i].end());
        }
        printCase(students);
    } else {
        n = rnd.next(4, 10);
        m = rnd.next(2, 10);
        vector<vector<int>> students(m);
        int groupSize = rnd.next(2, min(4, m));
        for (int p = 1; p <= n; ++p) {
            int owner = rnd.next(0, groupSize - 1);
            students[owner].push_back(p);
        }
        for (int i = 0; i < m; ++i) {
            for (int p = 1; p <= n; ++p) {
                if (find(students[i].begin(), students[i].end(), p) == students[i].end() &&
                    rnd.next(0, 4) == 0) {
                    students[i].push_back(p);
                }
            }
            sort(students[i].begin(), students[i].end());
        }
        printCase(students);
    }

    return 0;
}
