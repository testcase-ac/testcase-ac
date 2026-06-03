#include "testlib.h"

#include <algorithm>
#include <set>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n;
    if (mode == 0) {
        n = rnd.next(1, 12);
    } else if (mode == 1) {
        n = rnd.next(2, 20);
    } else {
        n = rnd.next(3, 40);
    }

    vector<int> students;
    if (mode == 4) {
        vector<int> pool = {
            -1000000000, -999999999, -1000000, -1, 0, 1,
            999999, 1000000, 999999998, 999999999, 1000000000
        };
        shuffle(pool.begin(), pool.end());
        n = rnd.next(1, static_cast<int>(pool.size()));
        students.assign(pool.begin(), pool.begin() + n);
    } else {
        set<int> used;
        while (static_cast<int>(students.size()) < n) {
            int x = rnd.next(-3 * n, 3 * n);
            if (used.insert(x).second) {
                students.push_back(x);
            }
        }
    }

    sort(students.begin(), students.end());

    if (mode == 1) {
        reverse(students.begin(), students.end());
    } else if (mode == 2) {
        int swaps = rnd.next(1, max(1, n / 3));
        for (int i = 0; i < swaps; ++i) {
            int pos = rnd.next(0, n - 2);
            swap(students[pos], students[pos + 1]);
        }
    } else if (mode == 3 || mode == 4) {
        shuffle(students.begin(), students.end());
    }

    println(n);
    for (int student : students) {
        println(student);
    }

    return 0;
}
