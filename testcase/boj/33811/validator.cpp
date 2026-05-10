#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N
    int N = inf.readInt(1, 500000, "N");
    inf.readEoln();

    // 2. Read S
    string S = inf.readToken("[GSH]{1,500000}", "S");
    ensuref((int)S.size() == N, "Length of S (%d) does not match N (%d)", (int)S.size(), N);
    inf.readEoln();

    // 3. No further global constraints to check.
    // The problem statement says:
    // "이 문자열은 G, S, H로만 이루어져 있어 문자열의 중간에 GSHS가 부분 문자열로 포함되어 있습니다."
    // This is a description, not a constraint: it does NOT require every input to contain "GSHS" as a substring.
    // Likewise for "SSHS".
    // The only constraints are:
    // - N in [1, 500000]
    // - S of length N
    // - S consists only of G, S, H

    inf.readEof();
}
