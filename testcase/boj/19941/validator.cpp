#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and K
    int N = inf.readInt(1, 20000, "N");
    inf.readSpace();
    int K = inf.readInt(1, 10, "K");
    inf.readEoln();

    // Read the string of length N, only 'P' and 'H' allowed
    string S = inf.readLine("[PH]{1,20000}", "S");
    ensuref((int)S.length() == N, "Length of S (%d) does not match N (%d)", (int)S.length(), N);

    inf.readEof();
}
