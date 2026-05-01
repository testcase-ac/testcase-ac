#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of students
    int N = rnd.next(3, 20);
    // Choose a pattern type for diversity
    int t = rnd.next(1, 5);
    vector<pair<int,int>> pts;
    switch (t) {
        // 1) Perfect chain: strictly increasing A and B
        case 1: {
            int prev = rnd.next(0, 100);
            for (int i = 0; i < N; i++) {
                int a = prev + rnd.next(1, 50);
                prev = a;
                int b = a + rnd.next(1, 50);
                pts.emplace_back(a, b);
            }
            break;
        }
        // 2) Anti-chain: A increasing, B decreasing -> no two comparable
        case 2: {
            for (int i = 0; i < N; i++) {
                int a = i * 1000000 / (N - 1);
                int b = (N - 1 - i) * 1000000 / (N - 1);
                pts.emplace_back(a, b);
            }
            break;
        }
        // 3) Correlated with noise: mostly increasing but with small inversions
        case 3: {
            int prev = rnd.next(0, 100);
            vector<int> A(N);
            for (int i = 0; i < N; i++) {
                A[i] = prev + rnd.next(1, 50);
                prev = A[i];
            }
            for (int i = 0; i < N; i++) {
                int b = A[i] + rnd.next(-20, 20);
                b = max(0, min(1000000, b));
                pts.emplace_back(A[i], b);
            }
            break;
        }
        // 4) Three clusters to force a clear possible partition
        case 4: {
            int rem = N;
            int s1 = rnd.next(1, rem - 2);
            rem -= s1;
            int s2 = rnd.next(1, rem - 1);
            int s3 = rem - s2;
            auto gen = [&](int cnt, int center) {
                for (int i = 0; i < cnt; i++) {
                    int a = center + rnd.next(-50000, 50000);
                    int b = center + rnd.next(-50000, 50000);
                    a = max(0, min(1000000, a));
                    b = max(0, min(1000000, b));
                    pts.emplace_back(a, b);
                }
            };
            gen(s1, 200000);
            gen(s2, 500000);
            gen(s3, 800000);
            break;
        }
        // 5) Sorted by A, random B -> many incomparable pairs
        case 5: {
            int prev = rnd.next(0, 100);
            vector<int> A(N);
            for (int i = 0; i < N; i++) {
                A[i] = prev + rnd.next(1, 50);
                prev = A[i];
            }
            for (int i = 0; i < N; i++) {
                int b = rnd.next(0, 1000000);
                pts.emplace_back(A[i], b);
            }
            break;
        }
    }
    // Shuffle to mix the order
    shuffle(pts.begin(), pts.end());
    // Output
    println(N);
    for (auto &p : pts) {
        println(p.first, p.second);
    }
    return 0;
}
