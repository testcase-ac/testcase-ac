#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of books sold today
    int N = inf.readInt(1, 1000, "N");
    inf.readEoln();

    // Read each book title: only lowercase letters, length 1 to 50
    for (int i = 0; i < N; i++) {
        inf.readToken("[a-z]{1,50}", "title");
        inf.readEoln();
    }

    // No extra data
    inf.readEof();
    return 0;
}
