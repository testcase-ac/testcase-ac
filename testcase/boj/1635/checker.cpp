#include "testlib.h"

#include <set>
#include <vector>

using namespace std;

int n, m;
vector<vector<int>> inputRows;

struct Answer {
    int distinctRows;
};

Answer readAnswer(InStream& stream) {
    set<vector<int>> uniqueRows;

    for (int i = 0; i < m; ++i) {
        vector<int> row(n);
        int productSum = 0;

        for (int j = 0; j < n; ++j) {
            row[j] = stream.readInt(-1, 1, format("b[%d][%d]", i + 1, j + 1).c_str());
            if (row[j] != -1 && row[j] != 1) {
                stream.quitf(_wa, "b[%d][%d] must be -1 or 1, got %d", i + 1, j + 1, row[j]);
            }
            productSum += inputRows[i][j] * row[j];
        }

        if (productSum != 0) {
            stream.quitf(_wa,
                         "row %d has product sequence sum %d instead of 0",
                         i + 1,
                         productSum);
        }

        uniqueRows.insert(row);
    }

    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after %d rows", m);
    }

    int distinctRows = static_cast<int>(uniqueRows.size());
    if (distinctRows > n) {
        stream.quitf(_wa, "uses %d distinct rows, more than N=%d", distinctRows, n);
    }

    return {distinctRows};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    m = inf.readInt();
    inputRows.assign(m, vector<int>(n));
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            inputRows[i][j] = inf.readInt();
        }
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    quitf(_ok,
          "valid output with %d distinct rows; jury uses %d",
          participant.distinctRows,
          jury.distinctRows);
}
