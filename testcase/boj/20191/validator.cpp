#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read S
    string S = inf.readLine("[a-z]{1,1000000}", "S");
    int lenS = S.length();

    // Read T
    string T = inf.readLine("[a-z]{1,100000}", "T");
    int lenT = T.length();

    // No extra lines allowed
    inf.readEof();
}
