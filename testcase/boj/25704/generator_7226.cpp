#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Diverse N segments around coupon thresholds
    vector<pair<int,int>> nRanges = {
        {0, 4},   // below first coupon
        {5, 5},   // exactly 5
        {6, 9},   // between 5 and 10
        {10,10},  // exactly 10
        {11,14},  // between 10 and 15
        {15,15},  // exactly 15
        {16,19},  // between 15 and 20
        {20,20},  // exactly 20
        {21,30}   // above all coupons
    };
    auto nr = rnd.any(nRanges);
    int N = rnd.next(nr.first, nr.second);

    // Diverse price segments to test money vs percent discounts
    // k = P/100
    vector<pair<int,int>> pKRanges = {
        {1, 4},    // 100..400
        {5, 19},   // 500..1900
        {20, 99},  // 2000..9900
        {100,500}  // 10000..50000
    };
    auto pr = rnd.any(pKRanges);
    int k = rnd.next(pr.first, pr.second);
    int P = k * 100;

    // Output
    println(N);
    println(P);

    return 0;
}
