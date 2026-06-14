#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int total = rnd.next(1, 30);
    int n;
    if (mode == 0) {
        n = total;
    } else if (mode == 1) {
        n = 1;
    } else {
        n = rnd.next(1, min(total, 10));
    }

    vector<int> len(n, 1);
    for (int extra = total - n; extra > 0; --extra) {
        ++len[rnd.next(n)];
    }
    if (mode == 2) {
        sort(len.begin(), len.end());
    } else if (mode == 3) {
        sort(len.rbegin(), len.rend());
    } else {
        shuffle(len.begin(), len.end());
    }

    vector<int> people(total);
    iota(people.begin(), people.end(), 1);
    if (mode != 2) {
        shuffle(people.begin(), people.end());
    }

    vector<vector<int>> lines(n);
    int at = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < len[i]; ++j) {
            lines[i].push_back(people[at++]);
        }
        if (mode == 4 && rnd.next(0, 1)) {
            reverse(lines[i].begin(), lines[i].end());
        }
    }

    int q = rnd.next(1, 40);
    println(n);
    for (const vector<int>& line : lines) {
        vector<int> row;
        row.push_back((int)line.size());
        row.insert(row.end(), line.begin(), line.end());
        println(row);
    }
    println(q);

    vector<int> ids(total);
    iota(ids.begin(), ids.end(), 1);
    for (int i = 0; i < q; ++i) {
        int op;
        if (i % 7 == 0) {
            op = 2;
        } else if (i % 5 == 0) {
            op = 1;
        } else {
            op = rnd.next(1, 2);
        }

        int a = rnd.any(ids);
        int b;
        if (rnd.next(0, 9) == 0) {
            b = a;
        } else if (mode == 0 && rnd.next(0, 2) == 0) {
            b = rnd.next(1, total);
        } else {
            b = rnd.any(ids);
        }
        println(op, a, b);
    }

    return 0;
}
