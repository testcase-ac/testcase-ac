#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of students
    int N = inf.readInt(1, 100, "N");
    inf.readEoln();

    // Each student has exactly 10 answers, each between 1 and 5
    for (int i = 1; i <= N; i++) {
        vector<int> answers = inf.readInts(10, 1, 5, "answer");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
