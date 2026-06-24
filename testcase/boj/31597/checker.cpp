#include "testlib.h"

#include <set>
#include <vector>

using namespace std;

struct TestCase {
    int n;
    vector<vector<int>> x;
};

struct Answer {
    vector<int> edits;
};

vector<TestCase> tests;

bool hasDuplicates(const vector<int>& values) {
    set<int> seen(values.begin(), values.end());
    return (int)seen.size() < (int)values.size();
}

Answer readAnswer(InStream& stream) {
    Answer result;

    for (int tc = 0; tc < (int)tests.size(); ++tc) {
        const int n = tests[tc].n;
        vector<vector<int>> matrix = tests[tc].x;
        vector<vector<bool>> modified(n, vector<bool>(n, false));

        int m = stream.readInt(0, n * n, format("m[%d]", tc + 1).c_str());
        stream.readEoln();
        result.edits.push_back(m);

        for (int k = 0; k < m; ++k) {
            int i = stream.readInt(1, n, format("i[%d][%d]", tc + 1, k + 1).c_str());
            int j = stream.readInt(1, n, format("j[%d][%d]", tc + 1, k + 1).c_str());
            int v = stream.readInt(1, n, format("v[%d][%d]", tc + 1, k + 1).c_str());
            stream.readEoln();
            --i;
            --j;

            if (modified[i][j]) {
                stream.quitf(_wa, "test case %d modifies cell (%d,%d) more than once", tc + 1, i + 1, j + 1);
            }
            if (matrix[i][j] == v) {
                stream.quitf(_wa, "test case %d modification %d leaves cell (%d,%d) unchanged", tc + 1, k + 1, i + 1, j + 1);
            }

            modified[i][j] = true;
            matrix[i][j] = v;
        }

        for (int i = 0; i < n; ++i) {
            if (!hasDuplicates(matrix[i])) {
                stream.quitf(_wa, "test case %d row %d has no duplicates after modifications", tc + 1, i + 1);
            }
        }

        for (int j = 0; j < n; ++j) {
            vector<int> column(n);
            for (int i = 0; i < n; ++i) {
                column[i] = matrix[i][j];
            }
            if (!hasDuplicates(column)) {
                stream.quitf(_wa, "test case %d column %d has no duplicates after modifications", tc + 1, j + 1);
            }
        }
    }

    stream.readEof();
    return result;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int t = inf.readInt();
    tests.resize(t);
    for (int tc = 0; tc < t; ++tc) {
        int n = inf.readInt();
        tests[tc].n = n;
        tests[tc].x.assign(n, vector<int>(n));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                tests[tc].x[i][j] = inf.readInt();
            }
        }
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    for (int tc = 0; tc < t; ++tc) {
        if (participant.edits[tc] > jury.edits[tc]) {
            quitf(_wa,
                  "test case %d participant uses more edits than jury: participant=%d jury=%d",
                  tc + 1,
                  participant.edits[tc],
                  jury.edits[tc]);
        }
        if (participant.edits[tc] < jury.edits[tc]) {
            quitf(_fail,
                  "test case %d participant found a better answer: participant=%d jury=%d",
                  tc + 1,
                  participant.edits[tc],
                  jury.edits[tc]);
        }
    }

    quitf(_ok, "all test cases match the jury optimum");
}
