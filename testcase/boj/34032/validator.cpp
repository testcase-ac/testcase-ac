#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: number of team members
    int N = inf.readInt(2, 500000, "N");
    inf.readEoln();

    // Read S: string of length N consisting only of 'O' and 'X'
    // We use readLine to consume the entire line including the trailing EOLN.
    string S = inf.readLine("[OX]{1,500000}", "S");
    ensuref((int)S.length() == N,
            "Length of S must be %d, but got %d", N, (int)S.length());

    // No extra data
    inf.readEof();
    return 0;
}
