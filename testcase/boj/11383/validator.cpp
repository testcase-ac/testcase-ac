#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read dimensions
    int N = inf.readInt(1, 10, "N");
    inf.readSpace();
    int M = inf.readInt(1, 10, "M");
    inf.readEoln();

    // Read the first image: N lines of exactly M letters
    for (int i = 0; i < N; i++) {
        // name for error messages
        string name = "row1[" + to_string(i) + "]";
        // read line consisting only of letters (at least 1, at most 10)
        string s = inf.readLine("[A-Za-z]+", name.c_str());
        // check exact length
        ensuref((int)s.size() == M,
                "Length of %s is %d but expected %d", 
                name.c_str(), (int)s.size(), M);
    }

    // Read the second image: N lines of exactly 2*M letters
    for (int i = 0; i < N; i++) {
        string name = "row2[" + to_string(i) + "]";
        string t = inf.readLine("[A-Za-z]+", name.c_str());
        ensuref((int)t.size() == 2 * M,
                "Length of %s is %d but expected %d",
                name.c_str(), (int)t.size(), 2 * M);
    }

    // No extra characters after the last newline
    inf.readEof();
    return 0;
}
