#include "testlib.h"

#include <algorithm>
#include <array>
#include <set>
#include <string>
#include <utility>
#include <vector>

using namespace std;

namespace {

constexpr int kDirections = 4;
const array<int, kDirections> dr{-1, 0, 1, 0};
const array<int, kDirections> dc{0, 1, 0, -1};
const array<char, kDirections> startChar{'N', 'E', 'S', 'W'};

bool insideInterior(int r, int c, int h, int w) {
    return 1 <= r && r + 1 < h && 1 <= c && c + 1 < w;
}

vector<pair<int, int>> makePath(int h, int w) {
    for (int attempt = 0; attempt < 200; ++attempt) {
        int sr = rnd.next(1, h - 2);
        int sc = rnd.next(1, w - 2);
        int targetLength = rnd.next(2, min(18, (h - 2) * (w - 2)));

        vector<pair<int, int>> path{{sr, sc}};
        set<pair<int, int>> used{{sr, sc}};

        while (static_cast<int>(path.size()) < targetLength) {
            vector<int> candidates;
            auto [r, c] = path.back();
            for (int dir = 0; dir < kDirections; ++dir) {
                int nr = r + dr[dir];
                int nc = c + dc[dir];
                if (insideInterior(nr, nc, h, w) && !used.count({nr, nc})) {
                    candidates.push_back(dir);
                }
            }
            if (candidates.empty()) {
                break;
            }

            int dir = rnd.any(candidates);
            int nr = r + dr[dir];
            int nc = c + dc[dir];
            path.push_back({nr, nc});
            used.insert({nr, nc});
        }

        if (path.size() >= 2) {
            return path;
        }
    }

    int r = rnd.next(1, h - 2);
    int c = rnd.next(1, w - 3);
    return {{r, c}, {r, c + 1}};
}

}  // namespace

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int h = rnd.next(4, 12);
    int w = rnd.next(4, 12);
    vector<string> grid(h, string(w, '.'));

    vector<pair<int, int>> path = makePath(h, w);
    for (auto [r, c] : path) {
        grid[r][c] = '#';
    }

    int spurBudget = rnd.next(0, 6);
    for (int i = 0; i < spurBudget; ++i) {
        auto [r, c] = rnd.any(path);
        vector<int> candidates;
        for (int dir = 0; dir < kDirections; ++dir) {
            int nr = r + dr[dir];
            int nc = c + dc[dir];
            if (insideInterior(nr, nc, h, w) && grid[nr][nc] == '.') {
                candidates.push_back(dir);
            }
        }
        if (candidates.empty()) {
            continue;
        }

        int dir = rnd.any(candidates);
        grid[r + dr[dir]][c + dc[dir]] = '#';
    }

    auto [sr, sc] = path.front();
    auto [fr, fc] = path.back();
    int sd = rnd.next(0, kDirections - 1);
    grid[sr][sc] = startChar[sd];
    grid[fr][fc] = 'F';

    println(h, w);
    for (const string& row : grid) {
        println(row);
    }

    return 0;
}
