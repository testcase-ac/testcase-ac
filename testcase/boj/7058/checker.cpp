#include "testlib.h"

#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int m = inf.readInt();
    int n = inf.readInt();
    vector<vector<int>> grid(m + 1, vector<int>(n + 1));
    for (int r = 1; r <= m; ++r) {
        for (int c = 1; c <= n; ++c) {
            grid[r][c] = inf.readInt();
        }
    }

    auto readAnswer = [&](InStream& stream) {
        int k = stream.readInt(0, m * n, "number of guards");
        vector<vector<int>> occupied(m + 1, vector<int>(n + 1, 0));
        vector<int> rowSegment(m * n + 1, 0), colSegment(m * n + 1, 0);

        int rowSegmentCount = 0;
        vector<vector<int>> rowId(m + 1, vector<int>(n + 1, -1));
        for (int r = 1; r <= m; ++r) {
            for (int c = 1; c <= n; ++c) {
                if (grid[r][c] == 2) {
                    continue;
                }
                if (c == 1 || grid[r][c - 1] == 2) {
                    ++rowSegmentCount;
                }
                rowId[r][c] = rowSegmentCount;
            }
        }

        int colSegmentCount = 0;
        vector<vector<int>> colId(m + 1, vector<int>(n + 1, -1));
        for (int c = 1; c <= n; ++c) {
            for (int r = 1; r <= m; ++r) {
                if (grid[r][c] == 2) {
                    continue;
                }
                if (r == 1 || grid[r - 1][c] == 2) {
                    ++colSegmentCount;
                }
                colId[r][c] = colSegmentCount;
            }
        }

        for (int i = 1; i <= k; ++i) {
            int r = stream.readInt(1, m, format("guard[%d].row", i).c_str());
            int c = stream.readInt(1, n, format("guard[%d].col", i).c_str());
            if (grid[r][c] != 0) {
                stream.quitf(_wa, "guard %d is placed at (%d, %d), which is not a free room", i, r, c);
            }
            if (occupied[r][c]) {
                stream.quitf(_wa, "more than one guard is placed at (%d, %d)", r, c);
            }
            occupied[r][c] = 1;

            int rid = rowId[r][c];
            int cid = colId[r][c];
            if (rowSegment[rid]) {
                stream.quitf(_wa, "guard %d can see another guard in row segment %d", i, rid);
            }
            if (colSegment[cid]) {
                stream.quitf(_wa, "guard %d can see another guard in column segment %d", i, cid);
            }
            rowSegment[rid] = 1;
            colSegment[cid] = 1;
        }

        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after guard list");
        }
        return k;
    };

    int jury = readAnswer(ans);
    int participant = readAnswer(ouf);

    if (participant < jury) {
        quitf(_wa, "jury places more guards: jury=%d participant=%d", jury, participant);
    }
    if (participant > jury) {
        quitf(_fail, "participant places more valid guards than jury: jury=%d participant=%d", jury, participant);
    }
    quitf(_ok, "answer=%d", participant);
}
