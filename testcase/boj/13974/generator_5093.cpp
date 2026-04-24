#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(1, 5);
    println(T);
    for (int ti = 0; ti < T; ti++) {
        int type = rnd.next(0, 4);
        int K = rnd.next(3, 10);
        vector<int> a(K);
        switch (type) {
            case 0:
                // uniform random sizes
                for (int i = 0; i < K; i++)
                    a[i] = rnd.next(1, 1000);
                break;
            case 1:
                // non-decreasing sizes
                for (int i = 0; i < K; i++)
                    a[i] = rnd.next(1, 1000);
                sort(a.begin(), a.end());
                break;
            case 2:
                // non-increasing sizes
                for (int i = 0; i < K; i++)
                    a[i] = rnd.next(1, 1000);
                sort(a.begin(), a.end(), greater<int>());
                break;
            case 3:
                // mix of small and large
                for (int i = 0; i < K; i++) {
                    if (rnd.next(0, 1) == 0)
                        a[i] = rnd.next(1, 100);
                    else
                        a[i] = rnd.next(500, 1000);
                }
                break;
            case 4:
                // all equal sizes
                {
                    int c = rnd.next(1, 1000);
                    for (int i = 0; i < K; i++)
                        a[i] = c;
                }
                break;
        }
        // optionally shuffle in random case for more diversity
        if (type == 0 || type == 3) {
            shuffle(a.begin(), a.end());
        }
        println(K);
        println(a);
    }
    return 0;
}
