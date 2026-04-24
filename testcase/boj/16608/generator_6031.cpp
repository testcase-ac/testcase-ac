#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose the drive size
    int n = rnd.next(2, 30);

    // Hyper-parameter for number of broken bits b (1 ≤ b ≤ n-1), include last bit always
    int t_b = rnd.next(-2, 2);
    int b = rnd.wnext(n - 1, t_b) + 1;
    if (b < 1) b = 1;
    if (b > n - 1) b = n - 1;

    // Maximum changes we can achieve is n - b
    int max_c = n - b;

    // Hyper-parameter for desired bit changes c (1 ≤ c ≤ max_c)
    int t_c = rnd.next(-2, 2);
    int c = rnd.wnext(max_c, t_c) + 1;
    if (c < 1) c = 1;
    if (c > max_c) c = max_c;

    // Generate broken positions: pick b-1 from [2..n-1], plus n
    vector<int> pool;
    for (int i = 2; i <= n - 1; i++) pool.push_back(i);
    shuffle(pool.begin(), pool.end());
    vector<int> z;
    for (int i = 0; i < b - 1; i++) z.push_back(pool[i]);
    z.push_back(n);
    sort(z.begin(), z.end());

    // Output the test case
    println(n, c, b);
    println(z);

    return 0;
}
