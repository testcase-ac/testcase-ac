#include "testlib.h"

#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <map>
#include <string>
#include <vector>

using namespace std;

const int MAX_VALUE = 1000000;

int n;
vector<int> x1s, y1s, x2s, y2s;

struct Answer {
    bool impossible;
};

bool parseIntToken(const string& token, int& value) {
    if (token.empty()) {
        return false;
    }
    long long parsed = 0;
    for (char ch : token) {
        if (!isdigit((unsigned char)ch)) {
            return false;
        }
        parsed = parsed * 10 + (ch - '0');
        if (parsed > MAX_VALUE) {
            return false;
        }
    }
    value = (int)parsed;
    return true;
}

bool adjacentEndpoints(int a, int b) {
    int da = a / 2;
    int db = b / 2;
    if (da == db) {
        return false;
    }

    int ax = (a % 2 == 0) ? x1s[da] : x2s[da];
    int ay = (a % 2 == 0) ? y1s[da] : y2s[da];
    int bx = (b % 2 == 0) ? x1s[db] : x2s[db];
    int by = (b % 2 == 0) ? y1s[db] : y2s[db];
    return abs(ax - bx) + abs(ay - by) == 1;
}

Answer readAnswer(InStream& stream) {
    string first = stream.readWord("impossible|[0-9]+", "first output token");
    if (first == "impossible") {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after impossible");
        }
        return {true};
    }

    vector<int> labels(2 * n);
    if (!parseIntToken(first, labels[0])) {
        stream.quitf(_wa, "label[1][1] must be an integer between 0 and %d", MAX_VALUE);
    }
    labels[1] = stream.readInt(0, MAX_VALUE, "label[1][2]");
    for (int i = 1; i < n; ++i) {
        labels[2 * i] = stream.readInt(0, MAX_VALUE, format("label[%d][1]", i + 1).c_str());
        labels[2 * i + 1] = stream.readInt(0, MAX_VALUE, format("label[%d][2]", i + 1).c_str());
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after numbering");
    }

    map<int, vector<int>> endpointsByLabel;
    for (int i = 0; i < 2 * n; ++i) {
        endpointsByLabel[labels[i]].push_back(i);
    }

    for (const auto& entry : endpointsByLabel) {
        int label = entry.first;
        const vector<int>& endpoints = entry.second;
        if ((int)endpoints.size() != 2) {
            stream.quitf(_wa,
                         "number %d is used %d times, but every used number must pair exactly two ends",
                         label,
                         (int)endpoints.size());
        }
        if (!adjacentEndpoints(endpoints[0], endpoints[1])) {
            stream.quitf(_wa,
                         "the two ends with number %d are not adjacent ends of different dominoes",
                         label);
        }
    }

    return {false};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    x1s.resize(n);
    y1s.resize(n);
    x2s.resize(n);
    y2s.resize(n);
    for (int i = 0; i < n; ++i) {
        x1s[i] = inf.readInt();
        y1s[i] = inf.readInt();
        x2s[i] = inf.readInt();
        y2s[i] = inf.readInt();
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (jury.impossible && participant.impossible) {
        quitf(_ok, "both outputs report impossible");
    }
    if (!jury.impossible && participant.impossible) {
        quitf(_wa, "jury provides a valid numbering, but participant reports impossible");
    }
    if (jury.impossible && !participant.impossible) {
        quitf(_fail, "participant provides a valid numbering while jury reports impossible");
    }

    quitf(_ok, "valid numbering");
}
