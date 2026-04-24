#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of students
    int N = rnd.next(1, 10);
    // Distribution type: 0 = uniform, 1 = bias large, 2 = bias small
    int distType = rnd.next(0, 2);
    vector<int> a(N + 1);
    for (int i = 1; i <= N; ++i) {
        if (i == 1) {
            a[i] = 0;
        } else {
            if (distType == 0) {
                a[i] = rnd.next(0, i - 1);
            } else if (distType == 1) {
                // bias towards larger numbers
                a[i] = rnd.wnext(i, 1);
            } else {
                // bias towards smaller numbers
                a[i] = rnd.wnext(i, -1);
            }
        }
    }
    // Output
    println(N);
    vector<int> ans(N);
    for (int i = 0; i < N; ++i) ans[i] = a[i + 1];
    println(ans);
    return 0;
}
