#include "testlib.h"
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases
    int T = rnd.next(1, 5);
    println(T);

    // Prepare a pool of small odd lengths
    vector<int> M_pool;
    for (int m = 1; m <= 19; m += 2) M_pool.push_back(m);

    // Sequence generation types
    vector<string> types = {"random", "inc", "dec", "constant", "zigzag"};

    for (int tc = 0; tc < T; ++tc) {
        // Hyper-parameter for odd M: bias small or large
        int tM = rnd.next(-2, 2);
        int idx = rnd.wnext((int)M_pool.size(), tM);
        int M = M_pool[idx];
        println(M);

        // Choose a pattern for the sequence
        string typ = rnd.any(types);
        vector<int> a(M);

        if (typ == "random") {
            for (int i = 0; i < M; ++i)
                a[i] = rnd.next(-1000, 1000);
        }
        else if (typ == "inc") {
            for (int i = 0; i < M; ++i)
                a[i] = rnd.next(-1000, 1000);
            sort(a.begin(), a.end());
        }
        else if (typ == "dec") {
            for (int i = 0; i < M; ++i)
                a[i] = rnd.next(-1000, 1000);
            sort(a.begin(), a.end(), greater<int>());
        }
        else if (typ == "constant") {
            int x = rnd.next(-1000, 1000);
            for (int i = 0; i < M; ++i)
                a[i] = x;
        }
        else if (typ == "zigzag") {
            for (int i = 0; i < M; ++i)
                a[i] = rnd.next(-1000, 1000);
            sort(a.begin(), a.end());
            vector<int> b;
            int l = 0, r = M - 1;
            while (l <= r) {
                b.push_back(a[l++]);
                if (l <= r) b.push_back(a[r--]);
            }
            a = b;
        }

        // Print the sequence, 10 numbers per line
        for (int i = 0; i < M; ++i) {
            printf("%d", a[i]);
            if (i % 10 == 9 || i == M - 1) 
                printf("\n");
            else 
                printf(" ");
        }
    }

    return 0;
}
