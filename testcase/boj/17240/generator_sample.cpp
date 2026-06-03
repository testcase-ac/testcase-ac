#include "testlib.h"

#include <array>
#include <vector>
using namespace std;

using Row = array<int, 5>;

Row randomRow(int lo, int hi) {
    Row row{};
    for (int j = 0; j < 5; ++j) row[j] = rnd.next(lo, hi);
    return row;
}

Row specialistRow(int role, int highLo, int highHi, int otherLo, int otherHi) {
    Row row = randomRow(otherLo, otherHi);
    row[role] = rnd.next(highLo, highHi);
    return row;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    vector<Row> rows;

    if (mode == 0) {
        int base = rnd.next(700, 1000);
        for (int role = 0; role < 5; ++role) {
            rows.push_back(specialistRow(role, base - rnd.next(0, 80), base, 0, 40));
        }
        int extra = rnd.next(0, 4);
        for (int i = 0; i < extra; ++i) rows.push_back(randomRow(0, base - 1));
    } else if (mode == 1) {
        int strong = rnd.next(500, 900);
        rows.push_back(Row{strong, strong, strong, strong, strong});
        for (int role = 0; role < 5; ++role) {
            rows.push_back(specialistRow(role, strong + 1, 1000, 0, strong / 3));
        }
        int extra = rnd.next(0, 3);
        for (int i = 0; i < extra; ++i) rows.push_back(randomRow(0, 1000));
    } else if (mode == 2) {
        int n = rnd.next(5, 12);
        int value = rnd.next(0, 1000);
        for (int i = 0; i < n; ++i) {
            Row row{};
            for (int j = 0; j < 5; ++j) {
                row[j] = max(0, min(1000, value + rnd.next(-3, 3)));
            }
            rows.push_back(row);
        }
    } else if (mode == 3) {
        int n = rnd.next(5, 15);
        for (int i = 0; i < n; ++i) {
            Row row{};
            int filled = rnd.next(1, 3);
            vector<int> roles = {0, 1, 2, 3, 4};
            shuffle(roles.begin(), roles.end());
            for (int k = 0; k < filled; ++k) row[roles[k]] = rnd.next(1, 1000);
            rows.push_back(row);
        }
    } else if (mode == 4) {
        int n = rnd.next(20, 60);
        int lo = rnd.next(0, 700);
        int hi = rnd.next(lo, 1000);
        for (int i = 0; i < n; ++i) rows.push_back(randomRow(lo, hi));
    } else {
        int n = rnd.next(5, 20);
        for (int i = 0; i < n; ++i) rows.push_back(randomRow(0, 1000));
    }

    shuffle(rows.begin(), rows.end());

    println((int)rows.size());
    for (const Row& row : rows) {
        println(row[0], row[1], row[2], row[3], row[4]);
    }

    return 0;
}
