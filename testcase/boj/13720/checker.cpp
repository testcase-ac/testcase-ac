#include "testlib.h"

#include <algorithm>
#include <set>
#include <vector>

using namespace std;

struct Claim {
    bool impossible;
};

int n;

Claim readClaim(InStream& stream) {
    long long first = stream.readLong(-1LL, 999999999LL, "first output value");

    if (first == -1) {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after -1");
        }
        return {true};
    }

    vector<vector<long long>> table(n, vector<long long>(n));
    table[0][0] = first;
    if (table[0][0] <= 0) {
        stream.quitf(_wa, "table[1][1]=%lld is not positive", table[0][0]);
    }

    for (int i = 0; i < n; ++i) {
        for (int j = (i == 0 ? 1 : 0); j < n; ++j) {
            table[i][j] = stream.readLong(1LL, 999999999LL, format("table[%d][%d]", i + 1, j + 1).c_str());
        }
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after table");
    }

    set<long long> used;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (!used.insert(table[i][j]).second) {
                stream.quitf(_wa, "value %lld appears more than once", table[i][j]);
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        long long sum = 0;
        vector<long long> row;
        for (int j = 0; j < n; ++j) {
            sum += table[i][j];
            row.push_back(table[i][j]);
        }
        if (sum % n != 0) {
            stream.quitf(_wa, "row %d sum %lld is not divisible by N=%d", i + 1, sum, n);
        }
        long long average = sum / n;
        if (find(row.begin(), row.end(), average) == row.end()) {
            stream.quitf(_wa, "row %d average %lld is not in the row", i + 1, average);
        }
    }

    for (int j = 0; j < n; ++j) {
        long long sum = 0;
        vector<long long> column;
        for (int i = 0; i < n; ++i) {
            sum += table[i][j];
            column.push_back(table[i][j]);
        }
        if (sum % n != 0) {
            stream.quitf(_wa, "column %d sum %lld is not divisible by N=%d", j + 1, sum, n);
        }
        long long average = sum / n;
        if (find(column.begin(), column.end(), average) == column.end()) {
            stream.quitf(_wa, "column %d average %lld is not in the column", j + 1, average);
        }
    }

    return {false};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt(1, 100, "N");
    if (!inf.seekEof()) {
        quitf(_fail, "extra input after N");
    }

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    if (jury.impossible && participant.impossible) {
        quitf(_ok, "both outputs claim impossible");
    }
    if (jury.impossible && !participant.impossible) {
        quitf(_fail, "participant provided a valid table while jury claims impossible");
    }
    if (!jury.impossible && participant.impossible) {
        quitf(_wa, "jury provides a valid table but participant claims impossible");
    }

    quitf(_ok, "valid table");
}
