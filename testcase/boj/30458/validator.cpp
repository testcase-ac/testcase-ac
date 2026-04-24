#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and ensure it's within [3, 200000]
    int N = inf.readInt(3, 200000, "N");
    inf.readEoln();

    // Read the string S: must be only lowercase letters
    string S = inf.readLine("[a-z]+", "S");
    // Check S length matches N
    ensuref((int)S.size() == N,
            "Length of S is %d but expected %d", (int)S.size(), N);

    // No extra data after the string
    inf.readEof();
    return 0;
}
