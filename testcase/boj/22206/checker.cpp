#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int h, w;
vector<string> target;

struct Claim {
    vector<string> mines;
};

Claim readClaim(InStream& stream) {
    Claim claim;
    claim.mines.resize(h);

    for (int i = 0; i < h; ++i) {
        claim.mines[i] = stream.readToken("[X.]{" + to_string(w) + "}",
                                          format("row[%d]", i + 1).c_str());
    }

    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after %d grid rows", h);
    }

    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            int count = 0;
            for (int di = -1; di <= 1; ++di) {
                for (int dj = -1; dj <= 1; ++dj) {
                    int ni = i + di;
                    int nj = j + dj;
                    if (0 <= ni && ni < h && 0 <= nj && nj < w &&
                        claim.mines[ni][nj] == 'X') {
                        ++count;
                    }
                }
            }

            int expected = target[i][j] - '0';
            if (count != expected) {
                stream.quitf(_wa,
                             "cell (%d, %d) has %d adjacent-or-self mines, expected %d",
                             i + 1, j + 1, count, expected);
            }
        }
    }

    return claim;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    h = inf.readInt();
    w = inf.readInt();
    target.resize(h);
    for (int i = 0; i < h; ++i) {
        target[i] = inf.readToken();
    }

    readClaim(ans);
    readClaim(ouf);

    quitf(_ok, "valid mine grid");
}
