#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Pool of small primes ensuring p^N stays below 2^31 for N up to 8
    vector<int> pool = {2, 3, 5, 7, 11};

    // Hyper-parameter to bias K (number of primes) between 1 and pool.size()
    int tK = rnd.next(-1, 1);
    int K = rnd.wnext((int)pool.size(), tK) + 1;

    // Hyper-parameter to bias N (position) between 1 and 8
    int tN = rnd.next(-1, 1);
    int N = rnd.wnext(8, tN) + 1;

    // Select K distinct primes
    shuffle(pool.begin(), pool.end());
    vector<int> primes(pool.begin(), pool.begin() + K);
    sort(primes.begin(), primes.end());

    // Output
    println(K, N);
    println(primes);

    return 0;
}
