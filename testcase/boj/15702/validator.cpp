#include "testlib.h"
#include <set>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N and M
    int N = inf.readInt(1, 100, "N");
    inf.readSpace();
    int M = inf.readInt(1, 100, "M");
    inf.readEoln();

    // 2. Read scores for each problem
    vector<int> scores = inf.readInts(N, 1, 100, "score_i");
    inf.readEoln();

    // 3. Read examinee info, check for unique examinee numbers
    set<int> examinee_numbers;
    for (int i = 0; i < M; ++i) {
        // Read examinee number
        int num = inf.readInt(0, 100000, "examinee_number");
        ensuref(examinee_numbers.count(num) == 0, "Duplicate examinee number at line %d: %d", i+3, num);
        examinee_numbers.insert(num);

        // Read N tokens: 'O' or 'X'
        for (int j = 0; j < N; ++j) {
            inf.readSpace();
            string res = inf.readToken("[OX]", "result");
            ensuref(res == "O" || res == "X", "Invalid result token at examinee %d, problem %d: %s", num, j+1, res.c_str());
        }
        inf.readEoln();
    }

    inf.readEof();
}
