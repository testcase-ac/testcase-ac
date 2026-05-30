#include "testlib.h"
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int case_count = 0;
    while (true) {
        string line = inf.readLine("[-]+|[{}]{1,2000}", "input_line");

        bool is_end = true;
        for (char c : line) {
            if (c != '-') {
                is_end = false;
                break;
            }
        }
        if (is_end) {
            ensuref(case_count > 0, "expected at least one data set before the terminator");
            inf.readEof();
            break;
        }

        ++case_count;
        int len = line.length();
        ensuref(len % 2 == 0, "case %d has odd length %d", case_count, len);
    }
}
