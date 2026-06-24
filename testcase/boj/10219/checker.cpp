#include "testlib.h"
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

struct TestCase {
    int h;
    int w;
    vector<string> grid;
    vector<vector<pair<int, int>>> allowedShapes[26];
    vector<int> cellCount;
};

vector<pair<int, int>> normalize(vector<pair<int, int>> cells) {
    int minR = cells[0].first;
    int minC = cells[0].second;
    for (auto [r, c] : cells) {
        minR = min(minR, r);
        minC = min(minC, c);
    }
    for (auto& [r, c] : cells) {
        r -= minR;
        c -= minC;
    }
    sort(cells.begin(), cells.end());
    return cells;
}

vector<vector<pair<int, int>>> buildAllowedShapes(const vector<pair<int, int>>& cells) {
    vector<vector<pair<int, int>>> shapes;
    for (int rot = 0; rot < 4; ++rot) {
        vector<pair<int, int>> transformed;
        for (auto [r, c] : cells) {
            int x = r;
            int y = -c;
            int nr = x;
            int nc = y;
            if (rot == 1) {
                nr = -y;
                nc = x;
            } else if (rot == 2) {
                nr = -x;
                nc = -y;
            } else if (rot == 3) {
                nr = y;
                nc = -x;
            }
            transformed.push_back({nr, nc});
        }
        transformed = normalize(transformed);
        if (find(shapes.begin(), shapes.end(), transformed) == shapes.end()) {
            shapes.push_back(transformed);
        }
    }
    return shapes;
}

bool matchesAnyAllowedShape(const vector<pair<int, int>>& cells,
                            const vector<vector<pair<int, int>>>& allowedShapes) {
    vector<pair<int, int>> normalized = normalize(cells);
    return find(allowedShapes.begin(), allowedShapes.end(), normalized) != allowedShapes.end();
}

vector<string> readOutput(InStream& stream, const vector<TestCase>& tests) {
    vector<string> rows;
    for (int tc = 0; tc < (int)tests.size(); ++tc) {
        const TestCase& test = tests[tc];
        vector<vector<pair<int, int>>> cells(26);

        for (int r = 0; r < test.h; ++r) {
            string row = stream.readToken(format("[.a-z]{%d}", test.w).c_str(),
                                          format("case %d row %d", tc + 1, r + 1).c_str());
            rows.push_back(row);
            for (int c = 0; c < test.w; ++c) {
                char ch = row[c];
                if (ch != '.') {
                    cells[ch - 'a'].push_back({r, c});
                }
            }
        }

        for (int ch = 0; ch < 26; ++ch) {
            if ((int)cells[ch].size() != test.cellCount[ch]) {
                stream.quitf(_wa,
                             "case %d: piece '%c' has %d cells, expected %d",
                             tc + 1,
                             char('a' + ch),
                             (int)cells[ch].size(),
                             test.cellCount[ch]);
            }
            if (test.cellCount[ch] == 0) {
                continue;
            }
            if (!matchesAnyAllowedShape(cells[ch], test.allowedShapes[ch])) {
                stream.quitf(_wa,
                             "case %d: piece '%c' is not a flipped original piece under rotation",
                             tc + 1,
                             char('a' + ch));
            }
        }
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after the required grill rows");
    }
    return rows;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int t = inf.readInt();
    vector<TestCase> tests(t);
    for (int tc = 0; tc < t; ++tc) {
        TestCase& test = tests[tc];
        test.h = inf.readInt();
        test.w = inf.readInt();
        test.grid.resize(test.h);
        test.cellCount.assign(26, 0);
        vector<vector<pair<int, int>>> cells(26);

        for (int r = 0; r < test.h; ++r) {
            test.grid[r] = inf.readToken();
            for (int c = 0; c < test.w; ++c) {
                char ch = test.grid[r][c];
                if (ch != '.') {
                    cells[ch - 'a'].push_back({r, c});
                }
            }
        }

        for (int ch = 0; ch < 26; ++ch) {
            test.cellCount[ch] = (int)cells[ch].size();
            if (!cells[ch].empty()) {
                test.allowedShapes[ch] = buildAllowedShapes(cells[ch]);
            }
        }
    }

    readOutput(ans, tests);
    readOutput(ouf, tests);

    quitf(_ok, "valid flipped grill layout");
}
