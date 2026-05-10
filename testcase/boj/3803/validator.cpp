#include "testlib.h"
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

const int MAX_P = 50;
const int MAX_LEN = 100;
const int MAX_TESTCASES = 100000;

void check_connected(int P, const vector<vector<int>>& adj) {
    // BFS from node 1
    vector<bool> vis(P + 1, false);
    vector<int> q;
    q.push_back(1);
    vis[1] = true;
    for (size_t i = 0; i < q.size(); ++i) {
        int v = q[i];
        for (int u : adj[v]) {
            if (!vis[u]) {
                vis[u] = true;
                q.push_back(u);
            }
        }
    }
    for (int i = 1; i <= P; ++i) {
        ensuref(vis[i], "Graph is not connected: node %d is unreachable", i);
    }
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int testcases = 0;
    bool first_case = true;

    while (true) {
        // Handle empty line between datasets (except before first case)
        if (!first_case) {
            // The next character must be '\n' (empty line)
            char c = inf.readChar();
            ensuref(c == '\n', "Expected empty line between datasets, but got char code %d", int(c));
        }
        first_case = false;

        // Read the header line (could be "0" or "P R")
        string header = inf.readLine("[^]+", "dataset header");
        // Remove leading/trailing spaces
        size_t start = header.find_first_not_of(' ');
        size_t end = header.find_last_not_of(' ');
        if (start == string::npos) header = "";
        else header = header.substr(start, end - start + 1);

        // Split header into tokens
        vector<string> tokens;
        stringstream ss(header);
        string token;
        while (ss >> token) tokens.push_back(token);

        ensuref(tokens.size() >= 1 && tokens.size() <= 2, "Header line must have 1 or 2 integers, got: '%s'", header.c_str());

        int P = -1, R = -1;
        // Parse P
        ensuref(!tokens[0].empty(), "First token (P) is empty in header line: '%s'", header.c_str());
        ensuref(tokens[0].find_first_not_of("0123456789") == string::npos, "P must be a non-negative integer, got '%s'", tokens[0].c_str());
        P = stoi(tokens[0]);
        ensuref(P >= 0 && P <= MAX_P, "P must be in [0, %d], got %d", MAX_P, P);

        if (P == 0) {
            // End of input
            ensuref(tokens.size() == 1, "When P=0, header line must have only one token");
            inf.readEof();
            return 0;
        }

        // Parse R
        ensuref(tokens.size() == 2, "Header line must have two integers when P != 0");
        ensuref(!tokens[1].empty(), "Second token (R) is empty in header line: '%s'", header.c_str());
        ensuref(tokens[1].find_first_not_of("0123456789") == string::npos, "R must be a non-negative integer, got '%s'", tokens[1].c_str());
        R = stoi(tokens[1]);
        ensuref(R >= 0, "R must be non-negative, got %d", R);

        testcases++;
        ensuref(testcases <= MAX_TESTCASES, "Too many testcases: %d (max %d)", testcases, MAX_TESTCASES);

        // For P == 1, R must be 0 (no routes possible)
        if (P == 1) {
            ensuref(R == 0, "If P == 1, R must be 0, got %d", R);
        }

        // Read R lines of routes
        // For each route: a b l
        // a, b in [1, P], l in [1, 100]
        // Multiple routes between same pair allowed, direction may be reversed
        vector<vector<int>> adj(P + 1); // 1-based, for connectivity check
        for (int i = 0; i < R; ++i) {
            int a = inf.readInt(1, P, "a");
            inf.readSpace();
            int b = inf.readInt(1, P, "b");
            inf.readSpace();
            int l = inf.readInt(1, MAX_LEN, "l");
            inf.readEoln();

            // Self-loops are allowed by statement

            // Store for connectivity check (undirected)
            adj[a].push_back(b);
            adj[b].push_back(a);
        }

        // For P >= 2, must check that the graph is connected (undirected)
        if (P >= 2) {
            ensuref(R > 0, "For P >= 2, R must be at least 1 to be connected");
            check_connected(P, adj);
        }
        // After each dataset, expect either EOF (if next is 0), or an empty line (checked at top of loop)
    }
}
