#include "testlib.h"

#include <vector>

using namespace std;

struct Answer {
    long long score;
};

int n, m, k;

Answer readAnswer(InStream& stream) {
    vector<vector<pair<int, int>>> cells(k + 1);

    for (int r = 1; r <= n; ++r) {
        for (int c = 1; c <= m; ++c) {
            int value = stream.readInt(1, k, format("a[%d][%d]", r, c).c_str());
            cells[value].push_back({r, c});
        }
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after grid");
    }

    long long score = 0;
    for (int value = 1; value <= k; ++value) {
        if (cells[value].size() != 4) {
            stream.quitf(_wa, "value %d appears %d times instead of 4",
                         value, int(cells[value].size()));
        }

        int r1 = cells[value][0].first;
        int r2 = cells[value][0].first;
        int c1 = cells[value][0].second;
        int c2 = cells[value][0].second;
        for (const auto& cell : cells[value]) {
            r1 = min(r1, cell.first);
            r2 = max(r2, cell.first);
            c1 = min(c1, cell.second);
            c2 = max(c2, cell.second);
        }

        if (r1 == r2 || c1 == c2) {
            stream.quitf(_wa, "value %d does not use two distinct rows and columns", value);
        }

        vector<pair<int, int>> expected = {{r1, c1}, {r1, c2}, {r2, c1}, {r2, c2}};
        for (const auto& corner : expected) {
            bool found = false;
            for (const auto& cell : cells[value]) {
                if (cell == corner) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                stream.quitf(_wa, "value %d does not form rectangle corners", value);
            }
        }

        score += 1LL * (r2 - r1) * (c2 - c1);
    }

    return {score};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    m = inf.readInt();
    k = n * m / 4;

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (participant.score < jury.score) {
        quitf(_wa, "participant score %lld is less than jury score %lld",
              participant.score, jury.score);
    }
    if (participant.score > jury.score) {
        quitf(_fail, "participant score %lld is greater than jury score %lld",
              participant.score, jury.score);
    }
    quitf(_ok, "score %lld", participant.score);
}
