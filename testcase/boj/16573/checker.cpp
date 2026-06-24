#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

string s;

int editDistance(const string& a, const string& b) {
    const int n = (int)a.size();
    const int m = (int)b.size();
    vector<int> prev(m + 1), cur(m + 1);
    for (int j = 0; j <= m; ++j) {
        prev[j] = j;
    }
    for (int i = 1; i <= n; ++i) {
        cur[0] = i;
        for (int j = 1; j <= m; ++j) {
            int cost = a[i - 1] == b[j - 1] ? 0 : 1;
            cur[j] = min(min(prev[j] + 1, cur[j - 1] + 1), prev[j - 1] + cost);
        }
        prev.swap(cur);
    }
    return prev[m];
}

struct Answer {
    string t;
    int distance;
};

Answer readAnswer(InStream& stream) {
    string t = stream.readToken("[01]+", "T");
    stream.readEoln();
    stream.readEof();

    if (t.size() != s.size()) {
        stream.quitf(_wa, "T has length %d, expected %d", (int)t.size(), (int)s.size());
    }

    int distance = editDistance(s, t);
    if (2 * distance <= (int)s.size()) {
        stream.quitf(_wa, "edit(S, T) is %d, but must be more than %d/2", distance, (int)s.size());
    }

    return {t, distance};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    s = inf.readToken("[01]{1,2000}", "S");
    inf.readEoln();
    inf.readEof();

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    quitf(_ok, "valid answer with edit distance %d; jury edit distance %d",
          participant.distance, jury.distance);
}
