#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N
    int N = inf.readInt(1, 5000, "N");
    inf.readEoln();

    // 2. Read S as string of length N, all digits
    string S = inf.readToken("[0-9]{1,5000}", "S");
    ensuref((int)S.size() == N, "Length of S (%d) does not match N (%d)", (int)S.size(), N);

    // 3. S must not have leading zero
    ensuref(S[0] != '0', "S has leading zero");

    // 4. S must not have any unnecessary leading zeros in any number
    //    Each number is in [1,641], and no number has leading zeros.
    //    Since the problem says "주어진 수 S가 전역일 페이퍼에 적힌 수가 될 수 있음이 보장된다.",
    //    we do not need to check if S can be split into numbers in [1,641] with no leading zeros.
    //    But we must check that S itself does not have unnecessary leading zeros at the start.

    inf.readEoln();
    inf.readEof();
}
