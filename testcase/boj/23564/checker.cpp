#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

string target;

struct Answer {
    string s;
    vector<int> a;
};

Answer readAnswer(InStream& stream) {
    string s = stream.readToken("[a-z]{1,1048575}", "S");
    stream.readEoln();

    if (s.size() > target.size()) {
        stream.quitf(_wa, "S length is %d, greater than |T|=%d", (int)s.size(), (int)target.size());
    }

    vector<int> a(s.size());
    for (int i = 0; i < (int)s.size(); ++i) {
        if (i > 0) {
            stream.readSpace();
        }
        a[i] = stream.readInt(1, (int)target.size(), format("A[%d]", i + 1).c_str());
    }
    stream.readEoln();
    stream.readEof();

    string current;
    for (int i = 0; i < (int)s.size(); ++i) {
        long long nextLength = (long long)(a[i] + 1) * current.size() + a[i];
        if (nextLength > (long long)target.size()) {
            stream.quitf(_wa,
                         "prefix after step %d has length %lld, greater than |T|=%d",
                         i + 1,
                         nextLength,
                         (int)target.size());
        }

        string next;
        next.reserve((size_t)nextLength);
        for (int j = 0; j < a[i]; ++j) {
            next += current;
            next += s[i];
        }
        next += current;
        current = next;
    }

    if (current != target) {
        stream.quitf(_wa, "constructed T differs from input T");
    }

    return {s, a};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    target = inf.readToken("[a-z]{1,1048575}", "T");

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    quitf(_ok,
          "valid recursive representation: jury |S|=%d, participant |S|=%d",
          (int)jury.s.size(),
          (int)participant.s.size());
}
