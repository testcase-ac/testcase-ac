#include "testlib.h"
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 5000, "N");
    inf.readSpace();
    int m = inf.readInt(2, 5000, "M");
    inf.readEoln();

    string board = inf.readToken("[A-Z]{2,5000}", "board");
    inf.readEoln();
    string word = inf.readToken("[A-Z]{2,5000}", "word");
    inf.readEoln();

    ensuref((int)board.size() == n, "board length must be N: expected %d, got %d", n,
            (int)board.size());
    ensuref((int)word.size() == m, "word length must be M: expected %d, got %d", m,
            (int)word.size());

    inf.readEof();
}
