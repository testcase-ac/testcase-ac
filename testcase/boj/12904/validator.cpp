#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read S: only 'A' or 'B', length between 1 and 999 inclusive
    string S = inf.readLine("[AB]{1,999}", "S");
    // Read T: only 'A' or 'B', length between 2 and 1000 inclusive
    string T = inf.readLine("[AB]{2,1000}", "T");

    // Ensure S is strictly shorter than T
    ensuref((int)S.size() < (int)T.size(),
            "Length constraint violated: |S| = %d, |T| = %d, but require |S| < |T|",
            (int)S.size(), (int)T.size());

    // End of file (no extra lines or spaces)
    inf.readEof();
    return 0;
}
