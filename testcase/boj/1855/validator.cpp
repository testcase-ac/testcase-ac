#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read K
    int K = inf.readInt(1, 20, "K");
    inf.readEoln();

    // Read encrypted string (all lowercase letters, length <= 200, length % K == 0)
    string s = inf.readToken("[a-z]{1,200}", "encrypted_string");
    inf.readEoln();

    int L = int(s.size());
    ensuref(L % K == 0, "Length of encrypted string (%d) is not a multiple of K (%d)", L, K);

    inf.readEof();
}
