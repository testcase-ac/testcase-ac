#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int type = rnd.next(0, 2);
    int N;
    if (type == 0) {
        // Odd N
        vector<int> small, med, large;
        for (int x = 3; x <= 11; x += 2) small.push_back(x);
        for (int x = 13; x <= 99; x += 2) med.push_back(x);
        for (int x = 101; x <= 299; x += 2) large.push_back(x);
        int grp = rnd.next(0, 2);
        if (grp == 0) N = rnd.any(small);
        else if (grp == 1) N = rnd.any(med);
        else N = rnd.any(large);
    } else if (type == 1) {
        // Doubly even N (divisible by 4)
        vector<int> small, med, large;
        for (int x = 4; x <= 12; x += 4) small.push_back(x);
        for (int x = 16; x <= 100; x += 4) med.push_back(x);
        for (int x = 104; x <= 300; x += 4) large.push_back(x);
        int grp = rnd.next(0, 2);
        if (grp == 0) N = rnd.any(small);
        else if (grp == 1) N = rnd.any(med);
        else N = rnd.any(large);
    } else {
        // Singly even N (2 mod 4)
        vector<int> small, med, large;
        for (int k = 1; k <= 3; k++) small.push_back(4 * k + 2);
        for (int k = 4; k <= 24; k++) med.push_back(4 * k + 2);
        for (int k = 25; k <= 74; k++) large.push_back(4 * k + 2);
        int grp = rnd.next(0, 2);
        if (grp == 0) N = rnd.any(small);
        else if (grp == 1) N = rnd.any(med);
        else N = rnd.any(large);
    }
    println(N);
    return 0;
}
