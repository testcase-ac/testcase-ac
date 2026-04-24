#include "testlib.h"
#include <vector>
#include <utility>
using namespace std;

static const int MAX_NUM = 1000000;
int N;
vector<pair<int,int>> shirts;

struct Answer {
    bool impossible;
    vector<int> v;
};

Answer readAns(InStream &stream) {
    // Read first integer: either -1 or the display number for shirt 1
    int x = stream.readInt(-1, MAX_NUM, "answer[1]");
    if (x == -1) {
        // Must be exactly "-1" and nothing else
        stream.readEof();
        return { true, vector<int>() };
    }
    // Otherwise read N numbers in total
    vector<int> v;
    v.reserve(N);
    v.push_back(x);
    for (int i = 1; i < N; i++) {
        int y = stream.readInt(1, MAX_NUM, format("answer[%d]", i+1).c_str());
        v.push_back(y);
    }
    stream.readEof();
    // Validate the solution
    vector<char> seen(MAX_NUM+1, 0);
    for (int i = 0; i < N; i++) {
        int val = v[i];
        int a = shirts[i].first;
        int b = shirts[i].second;
        if (val != a && val != b) {
            stream.quitf(_wa,
                "answer for shirt %d is %d -- invalid, expected %d or %d",
                i+1, val, a, b);
        }
        if (seen[val]) {
            stream.quitf(_wa,
                "number %d is used more than once", val);
        }
        seen[val] = 1;
    }
    return { false, v };
}

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);
    // Read input data
    N = inf.readInt();
    shirts.resize(N);
    for (int i = 0; i < N; i++) {
        shirts[i].first = inf.readInt(1, MAX_NUM);
        shirts[i].second = inf.readInt(1, MAX_NUM);
    }
    // Read jury's and participant's answers
    Answer jans = readAns(ans);
    Answer pans = readAns(ouf);

    if (jans.impossible && pans.impossible) {
        quitf(_ok, "both answers are -1 (impossible)");
    }
    if (jans.impossible && !pans.impossible) {
        quitf(_wa, "expected -1 (impossible), found a valid solution");
    }
    if (!jans.impossible && pans.impossible) {
        quitf(_wa, "expected a valid solution, found -1 (impossible)");
    }
    // Both are valid solutions; we accept any correct one
    quitf(_ok, "correct solution");
    return 0;
}
