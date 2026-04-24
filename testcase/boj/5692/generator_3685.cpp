#include "testlib.h"
#include <vector>
#include <string>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyperparameter for number of test cases (1 to 10)
    int tCase = rnd.next(-1, 1);
    int C = rnd.wnext(10, tCase) + 1;

    vector<string> cases;
    cases.reserve(C);
    for (int ci = 0; ci < C; ++ci) {
        // Hyperparameter for length (1 to 5)
        int tLen = rnd.next(-1, 1);
        int L = rnd.wnext(5, tLen) + 1;
        string s;
        s.reserve(L);
        // Leading digit: 1 to 9 (avoid zero which ends input)
        int tLead = rnd.next(-1, 1);
        int d0 = rnd.wnext(9, tLead) + 1;
        s.push_back('0' + d0);
        // Other digits: 0 to 9
        for (int i = 1; i < L; ++i) {
            int tDig = rnd.next(-1, 1);
            int d = rnd.wnext(10, tDig);
            s.push_back('0' + d);
        }
        cases.push_back(s);
    }

    // Output cases
    for (auto &str : cases) {
        printf("%s\n", str.c_str());
    }
    // Termination line
    printf("0\n");

    return 0;
}
