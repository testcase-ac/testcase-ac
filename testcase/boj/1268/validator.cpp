#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of students
    int n = inf.readInt(3, 1000, "n");
    inf.readEoln();

    // For each student, read 5 class numbers (one per grade year)
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= 5; j++) {
            string name = "class[" + to_string(i) + "][" + to_string(j) + "]";
            inf.readInt(1, 9, name.c_str());
            if (j < 5) {
                inf.readSpace();
            } else {
                inf.readEoln();
            }
        }
    }

    // No extra content
    inf.readEof();
}
