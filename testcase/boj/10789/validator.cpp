#include "testlib.h"
#include <vector>
#include <queue>
#include <string>
#include <set>
#include <map>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read r and c
    int r = inf.readInt(1, 50, "r");
    inf.readSpace();
    int c = inf.readInt(1, 50, "c");
    inf.readEoln();

    // Read keyboard grid
    vector<string> grid(r);
    // Track positions of each character
    map<char, vector<pair<int,int>>> occ;
    for (int i = 0; i < r; i++) {
        // read the entire line
        string row = inf.readLine("[^]+", "row");
        // length must be exactly c
        ensuref((int)row.length() == c,
                "Row %d length must be %d, but got %d", i+1, c, (int)row.length());
        // validate characters
        for (int j = 0; j < c; j++) {
            char ch = row[j];
            bool ok = false;
            if (ch >= 'A' && ch <= 'Z') ok = true;
            if (ch >= '0' && ch <= '9') ok = true;
            if (ch == '-' || ch == '*') ok = true;
            ensuref(ok, "Invalid character '%c' at grid position (%d,%d)", ch, i+1, j+1);
            occ[ch].push_back({i, j});
        }
        grid[i] = row;
    }

    // Ensure Enter key '*' exists at least once
    ensuref(occ.count('*') && !occ['*'].empty(),
            "Enter key '*' must appear at least once in the keyboard");

    // For each character, ensure its occurrences form a single 4-connected component
    vector<vector<bool>> seen(r, vector<bool>(c, false));
    const int dx[4] = {1, -1, 0, 0};
    const int dy[4] = {0, 0, 1, -1};
    for (auto &kv : occ) {
        char ch = kv.first;
        auto &positions = kv.second;
        // BFS from first occurrence
        int total = positions.size();
        queue<pair<int,int>> q;
        // reset seen
        for (auto &p : positions) {
            seen[p.first][p.second] = false;
        }
        auto start = positions[0];
        seen[start.first][start.second] = true;
        q.push(start);
        int cnt = 0;
        while (!q.empty()) {
            auto [x,y] = q.front(); q.pop();
            cnt++;
            for (int d = 0; d < 4; d++) {
                int nx = x + dx[d], ny = y + dy[d];
                if (nx < 0 || nx >= r || ny < 0 || ny >= c) continue;
                if (seen[nx][ny]) continue;
                if (grid[nx][ny] != ch) continue;
                seen[nx][ny] = true;
                q.push({nx,ny});
            }
        }
        ensuref(cnt == total,
                "Character '%c' has %d occurrences but only %d are connected",
                ch, total, cnt);
    }

    // Read text to input
    string text = inf.readToken("[^]+", "text");
    inf.readEoln();
    int n = text.length();
    ensuref(n >= 1 && n <= 10000,
            "Text length must be between 1 and 10000, but got %d", n);
    // Text must not contain '*'
    for (int i = 0; i < n; i++) {
        char ch = text[i];
        ensuref(ch != '*',
                "Text must not contain '*', but found at position %d", i+1);
        // Only valid keys: uppercase, digit, dash
        bool ok = false;
        if (ch >= 'A' && ch <= 'Z') ok = true;
        if (ch >= '0' && ch <= '9') ok = true;
        if (ch == '-') ok = true;
        ensuref(ok, "Invalid character '%c' in text at position %d", ch, i+1);
        // Ensure key exists
        ensuref(occ.count(ch),
                "Character '%c' in text at position %d does not exist on keyboard",
                ch, i+1);
    }

    // No extra input
    inf.readEof();
    return 0;
}
