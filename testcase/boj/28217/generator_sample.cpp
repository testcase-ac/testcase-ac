#include "testlib.h"
#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

using Triangle = vector<vector<int>>;

Triangle rotate(const Triangle& a) {
    int n = a.size();
    Triangle result(n);
    for (int i = 0; i < n; ++i) {
        result[i].resize(i + 1);
        for (int j = 0; j <= i; ++j)
            result[i][j] = a[n - 1 - j][i - j];
    }
    return result;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(1, 7);
    Triangle a(n), b;
    for (int i = 0; i < n; ++i) {
        a[i].resize(i + 1);
        for (int& value : a[i])
            value = rnd.next(0, 1);
    }

    b = a;
    int orientation = rnd.next(0, 5);
    if (orientation >= 3) {
        for (auto& row : b)
            reverse(row.begin(), row.end());
    }
    for (int i = 0; i < orientation % 3; ++i)
        b = rotate(b);

    vector<int> positions(n * (n + 1) / 2);
    iota(positions.begin(), positions.end(), 0);
    shuffle(positions.begin(), positions.end());
    int flips = rnd.next(0, min(3, static_cast<int>(positions.size())));
    for (int k = 0; k < flips; ++k) {
        int position = positions[k];
        int row = 0;
        while (position > row)
            position -= ++row;
        b[row][position] ^= 1;
    }

    println(n);
    for (const auto& row : a)
        println(row);
    for (const auto& row : b)
        println(row);
}
