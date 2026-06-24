#include "testlib.h"

#include <cctype>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int n, k, m;
vector<string> codes;
vector<int> queries;

struct Claim {
    bool reachable;
    int length;
};

string trimLine(const string& s) {
    int left = 0;
    int right = int(s.size()) - 1;
    while (left <= right && isspace(static_cast<unsigned char>(s[left]))) {
        ++left;
    }
    while (right >= left && isspace(static_cast<unsigned char>(s[right]))) {
        --right;
    }
    return s.substr(left, right - left + 1);
}

bool parseIntToken(const string& token, int& value) {
    if (token.empty()) {
        return false;
    }

    int pos = 0;
    int sign = 1;
    if (token[pos] == '-') {
        sign = -1;
        ++pos;
    }
    if (pos == int(token.size())) {
        return false;
    }

    long long parsed = 0;
    for (; pos < int(token.size()); ++pos) {
        if (!isdigit(static_cast<unsigned char>(token[pos]))) {
            return false;
        }
        parsed = parsed * 10 + (token[pos] - '0');
        if (parsed > n) {
            return false;
        }
    }

    value = int(sign * parsed);
    return true;
}

int hammingDistance(int u, int v) {
    int distance = 0;
    for (int i = 0; i < k; ++i) {
        if (codes[u - 1][i] != codes[v - 1][i]) {
            ++distance;
        }
    }
    return distance;
}

Claim readClaim(InStream& stream, int queryIndex) {
    if (stream.seekEof()) {
        stream.quitf(_wa, "query %d: missing output line", queryIndex);
    }

    string line = trimLine(stream.readLine());
    if (line.empty()) {
        stream.quitf(_wa, "query %d: empty output line", queryIndex);
    }

    stringstream ss(line);
    vector<int> path;
    string token;
    while (ss >> token) {
        int value;
        if (!parseIntToken(token, value)) {
            stream.quitf(_wa, "query %d: invalid integer token '%s'", queryIndex, token.c_str());
        }
        path.push_back(value);
    }

    if (path.size() == 1 && path[0] == -1) {
        return {false, 0};
    }
    for (int value : path) {
        if (value == -1) {
            stream.quitf(_wa, "query %d: -1 must be the only value on an impossible line", queryIndex);
        }
    }
    if (path.empty()) {
        stream.quitf(_wa, "query %d: missing path", queryIndex);
    }
    if (path.size() < 2) {
        stream.quitf(_wa, "query %d: path has fewer than 2 vertices", queryIndex);
    }
    if (path.front() != 1) {
        stream.quitf(_wa, "query %d: path starts at %d instead of 1", queryIndex, path.front());
    }

    int target = queries[queryIndex - 1];
    if (path.back() != target) {
        stream.quitf(_wa, "query %d: path ends at %d instead of %d", queryIndex, path.back(), target);
    }

    vector<int> used(n + 1, 0);
    for (int i = 0; i < int(path.size()); ++i) {
        int vertex = path[i];
        if (vertex < 1 || vertex > n) {
            stream.quitf(_wa, "query %d: vertex %d at position %d is outside [1, %d]",
                         queryIndex, vertex, i + 1, n);
        }
        if (used[vertex]) {
            stream.quitf(_wa, "query %d: vertex %d appears more than once", queryIndex, vertex);
        }
        used[vertex] = 1;
    }

    for (int i = 0; i + 1 < int(path.size()); ++i) {
        int u = path[i];
        int v = path[i + 1];
        if (hammingDistance(u, v) != 1) {
            stream.quitf(_wa, "query %d: vertices %d and %d have Hamming distance %d instead of 1",
                         queryIndex, u, v, hammingDistance(u, v));
        }
    }

    return {true, int(path.size())};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    k = inf.readInt();
    codes.resize(n);
    for (int i = 0; i < n; ++i) {
        codes[i] = inf.readToken();
    }
    m = inf.readInt();
    queries.resize(m);
    for (int i = 0; i < m; ++i) {
        queries[i] = inf.readInt();
    }

    vector<Claim> jury(m);
    for (int i = 1; i <= m; ++i) {
        jury[i - 1] = readClaim(ans, i);
    }
    ans.readEof();

    for (int i = 1; i <= m; ++i) {
        Claim participant = readClaim(ouf, i);
        const Claim& expected = jury[i - 1];

        if (!expected.reachable) {
            if (participant.reachable) {
                quitf(_fail, "query %d: jury says impossible, but participant printed a valid path of length %d",
                      i, participant.length);
            }
            continue;
        }

        if (!participant.reachable) {
            quitf(_wa, "query %d: participant says impossible, but jury has a path of length %d",
                  i, expected.length);
        }
        if (participant.length > expected.length) {
            quitf(_wa, "query %d: participant path length %d is longer than jury length %d",
                  i, participant.length, expected.length);
        }
        if (participant.length < expected.length) {
            quitf(_fail, "query %d: participant path length %d is shorter than jury length %d",
                  i, participant.length, expected.length);
        }
    }
    ouf.readEof();

    quitf(_ok, "all %d query answer(s) match the jury shortest length", m);
}
