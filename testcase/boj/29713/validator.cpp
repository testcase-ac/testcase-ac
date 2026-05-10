#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 1000, "N");
    inf.readEoln();

    // Read the string of length N, consisting of uppercase alphabets only
    string s = inf.readToken("[A-Z]{1,1000}", "stickers");
    ensuref((int)s.size() == N, "Length of stickers string (%d) does not match N (%d)", (int)s.size(), N);

    inf.readEoln();
    inf.readEof();
}
