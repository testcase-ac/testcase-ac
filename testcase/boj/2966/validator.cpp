#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of questions
    int N = inf.readInt(1, 100, "N");
    inf.readEoln();

    // Read the answer string: must consist only of 'A','B','C'
    string answers = inf.readLine("[ABC]{1,100}", "answers");
    // Ensure the string length matches N
    ensuref((int)answers.length() == N,
            "Length of answer string (%d) does not match N (%d)",
            (int)answers.length(), N);

    // No extra content
    inf.readEof();
    return 0;
}
