#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>
using namespace std;

string rowWithZeroCount(int m, int zeros) {
    string row(m, '1');
    vector<int> positions(m);
    for (int i = 0; i < m; ++i) positions[i] = i;
    shuffle(positions.begin(), positions.end());
    for (int i = 0; i < zeros; ++i) row[positions[i]] = '0';
    return row;
}

string randomRow(int m, int zeroBias) {
    string row;
    for (int i = 0; i < m; ++i) {
        row += rnd.wnext(2, zeroBias) == 0 ? '0' : '1';
    }
    return row;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 14);
    int m = rnd.next(1, 18);
    int k = rnd.next(0, 30);
    vector<string> rows;

    if (mode == 0) {
        n = rnd.next(1, 8);
        m = rnd.next(1, 10);
        k = rnd.next(0, 12);
        int zeros = rnd.next(0, min(m, k + 2));
        string target = rowWithZeroCount(m, zeros);
        int copies = rnd.next(1, n);
        for (int i = 0; i < copies; ++i) rows.push_back(target);
        while ((int)rows.size() < n) rows.push_back(randomRow(m, rnd.next(-2, 2)));
    } else if (mode == 1) {
        n = rnd.next(4, 14);
        m = rnd.next(2, 12);
        int zeros = rnd.next(0, m);
        k = zeros + (rnd.next(0, 1) ? 0 : 1);
        if (k > 1000) k = zeros;
        string parityRow = rowWithZeroCount(m, zeros);
        string nearRow = rowWithZeroCount(m, rnd.next(0, m));
        for (int i = 0; i < n; ++i) rows.push_back(i % 2 == 0 ? parityRow : nearRow);
    } else if (mode == 2) {
        n = rnd.next(1, 12);
        m = rnd.next(1, 15);
        k = rnd.any(vector<int>{0, 1, 2, 999, 1000});
        for (int i = 0; i < n; ++i) rows.push_back(rowWithZeroCount(m, rnd.next(0, m)));
    } else if (mode == 3) {
        n = rnd.next(10, 50);
        m = rnd.next(10, 50);
        k = rnd.next(0, 1000);
        vector<string> patterns;
        int patternCount = rnd.next(2, 5);
        for (int i = 0; i < patternCount; ++i) {
            patterns.push_back(rowWithZeroCount(m, rnd.next(0, m)));
        }
        for (int i = 0; i < n; ++i) rows.push_back(rnd.any(patterns));
    } else if (mode == 4) {
        n = rnd.next(1, 10);
        m = rnd.next(1, 10);
        k = rnd.next(0, 20);
        for (int i = 0; i < n; ++i) rows.push_back(string(m, rnd.next(0, 1) ? '1' : '0'));
    } else {
        n = rnd.next(1, 14);
        m = rnd.next(1, 18);
        k = rnd.next(0, 40);
        int zeroBias = rnd.next(-3, 3);
        for (int i = 0; i < n; ++i) rows.push_back(randomRow(m, zeroBias));
    }

    shuffle(rows.begin(), rows.end());

    println(n, m);
    for (const string& row : rows) println(row);
    println(k);
    return 0;
}
