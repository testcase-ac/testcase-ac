#include "testlib.h"

#include <algorithm>
#include <cstdarg>
#include <cstdio>
#include <map>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

struct CaseData {
    int m;
    map<pair<int, int>, int> weight;
};

struct Answer {
    bool reachable;
    long long cost;
    vector<int> path;
};

vector<CaseData> cases;

void quitInvalid(InStream& stream, const char* fmt, ...) {
    char buffer[1024];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buffer, sizeof(buffer), fmt, args);
    va_end(args);
    stream.quitf(_wa, "%s", buffer);
}

bool parseIntToken(const string& token, int& value) {
    if (token.empty()) {
        return false;
    }
    size_t pos = 0;
    int sign = 1;
    if (token[pos] == '-') {
        sign = -1;
        ++pos;
    }
    if (pos == token.size()) {
        return false;
    }

    long long parsed = 0;
    for (; pos < token.size(); ++pos) {
        if (token[pos] < '0' || token[pos] > '9') {
            return false;
        }
        parsed = parsed * 10 + (token[pos] - '0');
        if (parsed > 1000000) {
            return false;
        }
    }
    value = static_cast<int>(sign * parsed);
    return true;
}

Answer readAnswer(InStream& stream, int caseNo) {
    const CaseData& cd = cases[caseNo - 1];

    string caseWord = stream.readWord();
    if (caseWord != "Case") {
        quitInvalid(stream, "case %d: expected 'Case', found '%s'", caseNo, caseWord.c_str());
    }

    string label = stream.readWord();
    string expectedLabel = format("#%d:", caseNo);
    if (label != expectedLabel) {
        quitInvalid(stream, "case %d: expected label '%s', found '%s'", caseNo, expectedLabel.c_str(), label.c_str());
    }

    string rest = stream.readLine();
    stringstream ss(rest);
    vector<int> values;
    string token;
    while (ss >> token) {
        int value;
        if (!parseIntToken(token, value)) {
            quitInvalid(stream, "case %d: invalid integer token '%s'", caseNo, token.c_str());
        }
        values.push_back(value);
    }

    if (values.empty()) {
        quitInvalid(stream, "case %d: missing path or -1", caseNo);
    }
    if (values.size() == 1 && values[0] == -1) {
        return {false, 0, {}};
    }
    if (find(values.begin(), values.end(), -1) != values.end()) {
        quitInvalid(stream, "case %d: -1 must be the only value when no path is printed", caseNo);
    }
    if (values.size() > static_cast<size_t>(cd.m)) {
        quitInvalid(stream, "case %d: path has %d vertices, more than M=%d", caseNo, int(values.size()), cd.m);
    }
    if (values.front() != 0) {
        quitInvalid(stream, "case %d: path starts at %d instead of 0", caseNo, values.front());
    }
    if (values.back() != cd.m - 1) {
        quitInvalid(stream, "case %d: path ends at %d instead of %d", caseNo, values.back(), cd.m - 1);
    }

    vector<int> used(cd.m, 0);
    for (int i = 0; i < int(values.size()); ++i) {
        int vertex = values[i];
        if (vertex < 0 || vertex >= cd.m) {
            quitInvalid(stream, "case %d: vertex %d at path position %d is outside [0, %d]",
                        caseNo, vertex, i + 1, cd.m - 1);
        }
        if (used[vertex]) {
            quitInvalid(stream, "case %d: vertex %d appears more than once", caseNo, vertex);
        }
        used[vertex] = 1;
    }

    long long cost = 0;
    for (int i = 0; i + 1 < int(values.size()); ++i) {
        pair<int, int> edge = minmax(values[i], values[i + 1]);
        auto it = cd.weight.find(edge);
        if (it == cd.weight.end()) {
            quitInvalid(stream, "case %d: edge (%d, %d) is not in the graph", caseNo, values[i], values[i + 1]);
        }
        cost += it->second;
    }

    return {true, cost, values};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int t = inf.readInt();
    cases.resize(t);
    for (int tc = 1; tc <= t; ++tc) {
        int n = inf.readInt();
        int m = inf.readInt();
        cases[tc - 1].m = m;
        for (int i = 0; i < n; ++i) {
            int x = inf.readInt();
            int y = inf.readInt();
            int z = inf.readInt();
            cases[tc - 1].weight[minmax(x, y)] = z;
        }
    }

    vector<Answer> jury(t + 1);
    for (int tc = 1; tc <= t; ++tc) {
        jury[tc] = readAnswer(ans, tc);
    }
    ans.readEof();

    for (int tc = 1; tc <= t; ++tc) {
        Answer participant = readAnswer(ouf, tc);
        const Answer& expected = jury[tc];

        if (!expected.reachable) {
            if (participant.reachable) {
                quitf(_fail, "case %d: jury says unreachable, but participant printed a valid path with cost %lld",
                      tc, participant.cost);
            }
            continue;
        }

        if (!participant.reachable) {
            quitf(_wa, "case %d: participant says unreachable, but jury has a path with cost %lld", tc, expected.cost);
        }
        if (participant.cost > expected.cost) {
            quitf(_wa, "case %d: participant path cost %lld is worse than jury cost %lld",
                  tc, participant.cost, expected.cost);
        }
        if (participant.cost < expected.cost) {
            quitf(_fail, "case %d: participant path cost %lld is better than jury cost %lld",
                  tc, participant.cost, expected.cost);
        }
    }
    ouf.readEof();

    quitf(_ok, "all %d case(s) match the jury optimum", t);
}
