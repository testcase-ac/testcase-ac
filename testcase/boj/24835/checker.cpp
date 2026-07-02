#include "testlib.h"

#include <string>
#include <vector>
using namespace std;

vector<bool> readClaims(InStream& stream, int q) {
    vector<bool> claims;
    claims.reserve(q);

    for (int i = 1; i <= q; ++i) {
        string token = stream.readToken("[Yy][Ee][Ss]|[Nn][Oo]", format("answer[%d]", i).c_str());
        claims.push_back(token[0] == 'Y' || token[0] == 'y');
    }

    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after %d answers", q);
    }
    return claims;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    for (int i = 0; i < n - 1; ++i) {
        inf.readInt();
        inf.readInt();
    }
    int q = inf.readInt();

    vector<bool> jury = readClaims(ans, q);
    vector<bool> participant = readClaims(ouf, q);

    for (int i = 0; i < q; ++i) {
        if (participant[i] != jury[i]) {
            quitf(_wa, "query %d: expected %s, found %s",
                  i + 1,
                  jury[i] ? "YES" : "NO",
                  participant[i] ? "YES" : "NO");
        }
    }

    quitf(_ok, "%d answers match jury output", q);
}
