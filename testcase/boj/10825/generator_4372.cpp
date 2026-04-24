#include "testlib.h"
#include <string>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyperparameters for diversity
    int N = rnd.next(1, 10);               // number of students
    int maxNameLen = rnd.next(1, 10);      // max length of names
    double pUpper = rnd.next(0.0, 1.0);     // probability of uppercase letters
    int t1 = rnd.next(-2, 2);              // skew for Korean scores
    int t2 = rnd.next(-2, 2);              // skew for English scores
    int t3 = rnd.next(-2, 2);              // skew for Math scores

    // Generate unique random names
    set<string> used;
    vector<string> names;
    while ((int)names.size() < N) {
        int len = rnd.next(1, maxNameLen);
        string s;
        s.reserve(len);
        for (int i = 0; i < len; i++) {
            if (rnd.next() < pUpper)
                s.push_back(char(rnd.next('A', 'Z')));
            else
                s.push_back(char(rnd.next('a', 'z')));
        }
        if (!used.count(s)) {
            used.insert(s);
            names.push_back(s);
        }
    }

    // Output
    println(N);
    for (int i = 0; i < N; i++) {
        int ko = rnd.wnext(100, t1) + 1;
        int en = rnd.wnext(100, t2) + 1;
        int ma = rnd.wnext(100, t3) + 1;
        println(names[i], ko, en, ma);
    }

    return 0;
}
