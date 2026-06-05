#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

string makeBlockRow(int a, int b, int c) {
    string row(8, '.');
    row[1] = char('0' + a);
    row[2] = '+';
    row[3] = char('0' + b);
    row[4] = '=';

    if (c < 10) {
        row[5] = char('0' + c);
    } else {
        row[5] = char('0' + c / 10);
        row[6] = char('0' + c % 10);
    }

    return row;
}

int chooseAnswer(int a, int b, bool correct, bool preferTwoDigit) {
    int sum = a + b;
    if (correct) {
        return sum;
    }

    vector<int> candidates;
    int lo = preferTwoDigit ? 10 : 0;
    int hi = preferTwoDigit ? 18 : 9;
    for (int c = lo; c <= hi; ++c) {
        if (c != sum) {
            candidates.push_back(c);
        }
    }
    return rnd.any(candidates);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, mode == 0 ? 1 : 4);
    int m = rnd.next(1, mode == 1 ? 1 : 5);

    vector<string> rows(3 * n, string(8 * m, '.'));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            bool makeCorrect = rnd.next(0, 99) < (mode == 2 ? 80 : mode == 3 ? 25 : 50);
            bool preferTwoDigit = rnd.next(0, 99) < (mode == 4 ? 75 : 35);

            int a = rnd.next(0, 9);
            int b = rnd.next(0, 9);
            if (preferTwoDigit && rnd.next(0, 99) < 85) {
                a = rnd.next(5, 9);
                b = rnd.next(5, 9);
            }
            if (mode == 5 && rnd.next(0, 99) < 65) {
                a = rnd.any(vector<int>{0, 9});
                b = rnd.next(0, 9);
            }

            int c = chooseAnswer(a, b, makeCorrect, preferTwoDigit);
            string blockRow = makeBlockRow(a, b, c);

            int rowBase = 3 * i;
            int colBase = 8 * j;
            for (int k = 0; k < 8; ++k) {
                rows[rowBase + 1][colBase + k] = blockRow[k];
            }
        }
    }

    println(n, m);
    for (const string& row : rows) {
        println(row);
    }

    return 0;
}
