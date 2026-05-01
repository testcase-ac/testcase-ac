#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Decide whether to force at least one valid 4-part split
    bool force_solution = rnd.next(0, 2) != 0; // ~2/3 chance to force

    int N;
    vector<int> A;
    if (!force_solution) {
        // Random sequence, may or may not have a solution
        N = rnd.next(4, 50);
        A.resize(N);
        for (int i = 0; i < N; i++) {
            A[i] = rnd.next(-1000, 1000);
        }
    } else {
        // Generate a sequence that definitely has at least one valid split
        // Try until success
        while (true) {
            N = rnd.next(4, 50);
            int i = rnd.next(1, N-3);
            int j = rnd.next(i+1, N-2);
            int k = rnd.next(j+1, N-1);
            int len1 = i, len2 = j-i, len3 = k-j, len4 = N-k;
            int target = rnd.next(-10, 10);
            vector<int> tmp(N);
            bool ok = true;
            // fill a segment of given length to sum == target
            auto make_seg = [&](int start, int len) {
                int sum = 0;
                for (int t = 0; t < len-1; t++) {
                    int v = rnd.next(-5, 5);
                    tmp[start+t] = v;
                    sum += v;
                }
                int last = target - sum;
                if (last < -1000 || last > 1000) return false;
                tmp[start+len-1] = last;
                return true;
            };
            if (!make_seg(0,    len1)) continue;
            if (!make_seg(i,    len2)) continue;
            if (!make_seg(j,    len3)) continue;
            if (!make_seg(k,    len4)) continue;
            A = tmp;
            break;
        }
    }

    // Output
    println(N);
    println(A);

    return 0;
}
