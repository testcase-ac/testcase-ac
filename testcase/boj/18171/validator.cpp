#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: number of existing bungalows
    int N = inf.readInt(1, 400000, "N");
    inf.readEoln();

    // Read the sequence of colors S: exactly N lowercase letters
    string S = inf.readToken("[a-z]+", "S");
    ensuref((int)S.size() == N,
            "Length of string S (%d) does not match N (%d)", (int)S.size(), N);
    inf.readEoln();

    // No more data
    inf.readEof();
    return 0;
}
