#include "testlib.h"

#include <bits/stdc++.h>
using namespace std;

namespace {

constexpr int kMaxPoints = 50;
constexpr int kMaxLength = 100;
constexpr int kMaxDatasets = 100000;
// CHECK: The statement says the number of routes is unlimited. This cap keeps
// validation finite while allowing far more routes than a 50-point graph needs.
constexpr int kMaxRoutesPerDataset = 100000;
constexpr int kMaxTotalRoutes = 1000000;

vector<string> splitWords(const string& line, const string& what) {
    ensuref(!line.empty(), "%s must not be empty", what.c_str());
    ensuref(line.front() != ' ' && line.back() != ' ',
            "%s must not have leading or trailing spaces", what.c_str());

    vector<string> words;
    string current;
    for (char ch : line) {
        ensuref(ch == ' ' || isdigit(static_cast<unsigned char>(ch)),
                "%s contains invalid character", what.c_str());
        if (ch == ' ') {
            ensuref(!current.empty(), "%s contains repeated spaces", what.c_str());
            words.push_back(current);
            current.clear();
        } else {
            current.push_back(ch);
        }
    }
    ensuref(!current.empty(), "%s contains repeated spaces", what.c_str());
    words.push_back(current);
    return words;
}

int parseIntToken(const string& token, int low, int high, const string& name) {
    ensuref(token.size() == 1 || token.front() != '0',
            "%s must not contain leading zeroes", name.c_str());

    long long value = 0;
    for (char ch : token) {
        value = value * 10 + (ch - '0');
        ensuref(value <= high, "%s must be at most %d", name.c_str(), high);
    }
    ensuref(value >= low, "%s must be at least %d", name.c_str(), low);
    return static_cast<int>(value);
}

void requireConnected(int p, const vector<vector<int>>& graph) {
    vector<int> seen(p + 1);
    queue<int> q;
    seen[1] = 1;
    q.push(1);

    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int to : graph[v]) {
            if (!seen[to]) {
                seen[to] = 1;
                q.push(to);
            }
        }
    }

    for (int i = 1; i <= p; ++i) {
        ensuref(seen[i], "point %d is not connected to point 1", i);
    }
}

}  // namespace

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int datasets = 0;
    int totalRoutes = 0;
    string headerLine = inf.readLine("[^\n]*", "dataset header");

    while (true) {
        vector<string> header = splitWords(headerLine, "dataset header");
        ensuref(header.size() == 1 || header.size() == 2,
                "dataset header must contain P or P R");
        int p = parseIntToken(header[0], 0, kMaxPoints, "P");
        if (p == 0) {
            ensuref(header.size() == 1, "terminating dataset must contain only P=0");
            inf.readEof();
            return 0;
        }

        ensuref(header.size() == 2, "non-terminating dataset header must contain P R");
        int r = parseIntToken(header[1], 0, kMaxRoutesPerDataset, "R");

        ++datasets;
        ensuref(datasets <= kMaxDatasets, "too many datasets: %d", datasets);
        ensuref(totalRoutes + r <= kMaxTotalRoutes,
                "too many total routes: %d", totalRoutes + r);

        vector<vector<int>> graph(p + 1);
        for (int i = 1; i <= r; ++i) {
            string routeLine = inf.readLine("[^\n]*", "route");
            vector<string> route = splitWords(routeLine, "route");
            ensuref(route.size() == 3, "route %d must contain three integers", i);

            int a = parseIntToken(route[0], 1, p, "route_start");
            int b = parseIntToken(route[1], 1, p, "route_end");
            int length = parseIntToken(route[2], 1, kMaxLength, "route_length");

            ensuref(a != b, "route %d connects point %d to itself", i, a);
            (void)length;
            graph[a].push_back(b);
            graph[b].push_back(a);
        }

        if (p >= 2) {
            requireConnected(p, graph);
        } else {
            ensuref(r == 0, "a one-point dataset cannot have routes");
        }

        totalRoutes += r;

        headerLine = inf.readLine("[^\n]*", "dataset separator or header");
        // CHECK: The input section says datasets are separated by an empty line,
        // but the official sample in the statement artifact omits those blank
        // lines. Accept either spelling and still reject extra blank lines.
        if (headerLine.empty()) {
            headerLine = inf.readLine("[^\n]*", "dataset header");
            ensuref(!headerLine.empty(), "only one empty line may separate datasets");
        }
    }
}
