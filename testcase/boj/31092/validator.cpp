#include "testlib.h"
#include <set>
#include <vector>
#include <string>
#include <cctype>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N, M, K
    int N = inf.readInt(1, 500, "N");
    inf.readSpace();
    int M = inf.readInt(1, 500, "M");
    inf.readSpace();
    int K = inf.readInt(1, N, "K");
    inf.readEoln();

    // 2. Read M sticker infos
    vector<char> s(M+1); // 1-based
    vector<int> d(M+1), a(M+1);
    for (int j = 1; j <= M; ++j) {
        string sj = inf.readToken("[a-z]", "s_j");
        inf.readSpace();
        d[j] = inf.readInt(1, 1000, "d_j");
        inf.readSpace();
        a[j] = inf.readInt(1, 1000, "a_j");
        inf.readEoln();
        s[j] = sj[0];
    }

    // 3. Read N sticker placements
    vector<int> b = inf.readInts(N, 1, M, "b_i");
    inf.readEoln();

    // 4. Read string S of length K, lowercase
    string S = inf.readToken("[a-z]{1,500}", "S");
    inf.readEoln();
    ensuref((int)S.size() == K, "Length of S (%d) does not match K (%d)", (int)S.size(), K);

    inf.readEof();
}
