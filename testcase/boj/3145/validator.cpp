#include "testlib.h"

#include <algorithm>
#include <cctype>
#include <functional>
#include <string>
#include <utility>
#include <vector>
using namespace std;

struct Name {
    int row;
    int left;
    int right;
    string text;
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int r = inf.readInt(1, 50, "R");
    inf.readSpace();
    int c = inf.readInt(1, 50, "C");
    inf.readEoln();

    vector<string> grid(r);
    for (int i = 0; i < r; ++i) {
        grid[i] = inf.readToken("[.xA-Z]{1,50}", "map_row");
        ensuref((int)grid[i].size() == c, "row %d length is %d, expected %d",
                i + 1, (int)grid[i].size(), c);
        inf.readEoln();
    }
    inf.readEof();

    vector<Name> names;
    vector<pair<int, int>> towns;
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c;) {
            if (grid[i][j] == 'x') {
                towns.push_back({i, j});
                ++j;
                continue;
            }
            if (!isupper((unsigned char)grid[i][j])) {
                ++j;
                continue;
            }

            int start = j;
            string text;
            while (j < c && isupper((unsigned char)grid[i][j])) {
                text.push_back(grid[i][j]);
                ++j;
            }
            names.push_back({i, start, j - 1, text});
        }
    }

    // CHECK: The statement describes towns and their names. Empty maps make that
    // object absent, so require at least one town/name pair.
    ensuref(!towns.empty(), "map must contain at least one town");
    ensuref(towns.size() == names.size(),
            "number of towns (%d) must equal number of names (%d)",
            (int)towns.size(), (int)names.size());

    vector<string> sortedNames;
    sortedNames.reserve(names.size());
    for (const Name& name : names) sortedNames.push_back(name.text);
    sort(sortedNames.begin(), sortedNames.end());
    for (int i = 1; i < (int)sortedNames.size(); ++i) {
        ensuref(sortedNames[i - 1] != sortedNames[i],
                "duplicate town name: %s", sortedNames[i].c_str());
    }

    int n = (int)names.size();
    vector<vector<int>> adj(n);
    for (int i = 0; i < n; ++i) {
        const Name& name = names[i];
        for (int j = 0; j < (int)towns.size(); ++j) {
            int tr = towns[j].first;
            int tc = towns[j].second;
            bool nearRow = abs(tr - name.row) <= 1;
            bool nearCol = name.left - 1 <= tc && tc <= name.right + 1;
            if (nearRow && nearCol) adj[i].push_back(j);
        }
        ensuref(!adj[i].empty(), "name %s is not adjacent to any town",
                name.text.c_str());
    }

    vector<int> matchTown(n, -1), matchName(n, -1);
    function<bool(int, vector<char>&)> dfs = [&](int name, vector<char>& seen) {
        for (int town : adj[name]) {
            if (seen[town]) continue;
            seen[town] = true;
            if (matchTown[town] == -1 || dfs(matchTown[town], seen)) {
                matchTown[town] = name;
                matchName[name] = town;
                return true;
            }
        }
        return false;
    };

    int matched = 0;
    for (int i = 0; i < n; ++i) {
        vector<char> seen(n, false);
        if (dfs(i, seen)) ++matched;
    }
    ensuref(matched == n, "town/name assignment is not complete");

    vector<vector<int>> alternating(n);
    for (int name = 0; name < n; ++name) {
        for (int town : adj[name]) {
            if (matchName[name] == town) continue;
            int otherName = matchTown[town];
            ensuref(otherName != -1, "matched town lookup failed");
            alternating[name].push_back(otherName);
        }
    }

    vector<int> color(n, 0);
    function<bool(int)> hasCycle = [&](int v) {
        color[v] = 1;
        for (int to : alternating[v]) {
            if (color[to] == 1) return true;
            if (color[to] == 0 && hasCycle(to)) return true;
        }
        color[v] = 2;
        return false;
    };
    for (int i = 0; i < n; ++i) {
        ensuref(color[i] != 0 || !hasCycle(i),
                "town/name assignment is not unique");
    }
}
