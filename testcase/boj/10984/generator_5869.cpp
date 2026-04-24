#include "testlib.h"
#include <vector>
#include <string>
#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of semesters
    int T = rnd.next(1, 5);
    println(T);

    // Possible grade values
    vector<double> grades = {0, 0.7, 1, 1.3, 1.7, 2, 2.3, 2.7, 3, 3.3, 3.7, 4, 4.3};
    for (int ti = 0; ti < T; ti++) {
        // Hyper-parameter for N: bias small or large
        int tN = rnd.next(-2, 2);
        int N = rnd.wnext(10, tN) + 1;  // 1..10
        println(N);
        for (int i = 0; i < N; i++) {
            // Credit C uniform 1..6
            int C = rnd.next(1, 6);
            // Grade selection
            double g = rnd.any(grades);
            string gstr;
            // Determine if integer grade
            if (fabs(g - round(g)) < 1e-9) {
                // Randomly choose "x" or "x.0"
                if (rnd.next(0, 1) == 0) {
                    gstr = to_string(int(round(g)));
                } else {
                    gstr = to_string(int(round(g))) + ".0";
                }
            } else {
                char buf[8];
                sprintf(buf, "%.1f", g);
                gstr = buf;
            }
            println(C, gstr);
        }
    }
    return 0;
}
