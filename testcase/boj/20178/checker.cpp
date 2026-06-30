#include "testlib.h"
#include <algorithm>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

int n;
vector<vector<int>> a;

string stripped(const string& s) {
    int l = 0, r = (int)s.size();
    while (l < r && isspace((unsigned char)s[l])) {
        ++l;
    }
    while (r > l && isspace((unsigned char)s[r - 1])) {
        --r;
    }
    return s.substr(l, r - l);
}

vector<string> readRemainingLines(InStream& stream) {
    vector<string> lines;
    while (!stream.seekEof()) {
        lines.push_back(stream.readLine());
    }
    return lines;
}

struct Answer {
    bool impossible;
};

Answer readAnswer(InStream& stream) {
    vector<string> lines = readRemainingLines(stream);

    int first = -1;
    while (first + 1 < (int)lines.size() && stripped(lines[first + 1]).empty()) {
        ++first;
    }
    ++first;

    if (first == (int)lines.size()) {
        stream.quitf(_wa, "missing output");
    }

    string firstLine = stripped(lines[first]);
    if (firstLine == "-1") {
        for (int i = first + 1; i < (int)lines.size(); ++i) {
            if (!stripped(lines[i]).empty()) {
                stream.quitf(_wa, "extra output after -1");
            }
        }
        return {true};
    }

    if ((int)lines.size() - first < n) {
        stream.quitf(_wa, "expected %d witness lines, found %d", n, (int)lines.size() - first);
    }

    for (int target = 0; target < n; ++target) {
        string line = stripped(lines[first + target]);
        istringstream iss(line);
        vector<int> lights(n, 0);
        int previous = 0;
        int sw;
        while (iss >> sw) {
            if (sw < 1 || sw > n) {
                stream.quitf(_wa, "switch number %d on line %d is outside [1, %d]", sw, target + 1, n);
            }
            if (sw <= previous) {
                stream.quitf(_wa, "switch numbers on line %d are not strictly increasing", target + 1);
            }
            previous = sw;
            for (int light = 0; light < n; ++light) {
                lights[light] ^= a[sw - 1][light];
            }
        }
        if (!iss.eof()) {
            stream.quitf(_wa, "invalid token on line %d", target + 1);
        }
        for (int light = 0; light < n; ++light) {
            int expected = (light == target);
            if (lights[light] != expected) {
                stream.quitf(_wa,
                             "line %d does not isolate light %d: light %d has state %d",
                             target + 1,
                             target + 1,
                             light + 1,
                             lights[light]);
            }
        }
    }

    for (int i = first + n; i < (int)lines.size(); ++i) {
        if (!stripped(lines[i]).empty()) {
            stream.quitf(_wa, "extra output after %d witness lines", n);
        }
    }

    return {false};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    a.assign(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            a[i][j] = inf.readInt();
        }
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (jury.impossible) {
        if (participant.impossible) {
            quitf(_ok, "both outputs report impossible");
        }
        quitf(_fail, "participant found a valid witness while jury reports impossible");
    }

    if (participant.impossible) {
        quitf(_wa, "participant reports impossible while jury provides witnesses");
    }

    quitf(_ok, "valid witness set");
}
