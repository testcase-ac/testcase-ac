#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of words
    int N = inf.readInt(1, 100, "N");
    inf.readEoln();

    // Read each word: lowercase only, length 1 to 10, no extra spaces
    for (int i = 0; i < N; i++) {
        inf.readToken("[a-z]{1,10}", "word");
        inf.readEoln();
    }

    // No extra data
    inf.readEof();
    return 0;
}
