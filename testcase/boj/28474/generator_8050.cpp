#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    vector<int> ns;
    // Edge cases
    ns.push_back(1);
    ns.push_back(2);
    ns.push_back(3);
    // Small random n
    int cnt = rnd.next(1, 2);
    for (int i = 0; i < cnt; i++)
        ns.push_back(rnd.next(4, 100));
    // Medium random n
    cnt = rnd.next(1, 2);
    for (int i = 0; i < cnt; i++)
        ns.push_back(rnd.next(100, 10000));
    // Large random n
    cnt = rnd.next(2, 3);
    for (int i = 0; i < cnt; i++)
        ns.push_back(rnd.next(10000, 1000000000));
    // Predefined primes
    vector<int> primes = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,61,9973,10007,1000003,10000019,100000007};
    ns.push_back(rnd.any(primes));
    // Power of two
    if (rnd.next(0, 1)) {
        int k = rnd.next(1, 29); // ensure 2^k <= 1e9
        ns.push_back(1 << k);
    }
    // Small composite p*q
    if (rnd.next(0, 1)) {
        vector<int> sp = {2,3,5,7,11,13,17,19,23,29,31};
        int p = rnd.any(sp), q;
        do { q = rnd.any(sp); } while (q == p);
        ns.push_back(p * q);
    }
    // Large composite from medium primes
    if (rnd.next(0, 1)) {
        ns.push_back(10007 * 10009);
    }
    // Random odd n
    cnt = rnd.next(1, 2);
    for (int i = 0; i < cnt; i++) {
        int t = rnd.next(0, 499999999);
        ns.push_back(t * 2 + 1);
    }
    // Remove duplicates and shuffle
    sort(ns.begin(), ns.end());
    ns.erase(unique(ns.begin(), ns.end()), ns.end());
    shuffle(ns.begin(), ns.end());
    // Output
    println((int)ns.size());
    for (int x : ns) println(x);
    return 0;
}
