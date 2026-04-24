#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of students
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    // Read each student's data
    for (int i = 0; i < N; i++) {
        // Name: 1 to 10 letters, uppercase or lowercase
        inf.readToken("[A-Za-z]{1,10}", "name");
        inf.readSpace();
        // Scores: integers between 1 and 100
        inf.readInt(1, 100, "kor");
        inf.readSpace();
        inf.readInt(1, 100, "eng");
        inf.readSpace();
        inf.readInt(1, 100, "math");
        inf.readEoln();
    }

    // No extra data
    inf.readEof();
    return 0;
}
