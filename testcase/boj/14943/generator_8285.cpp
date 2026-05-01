#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Choose size
    int N = rnd.next(2, 12);
    // Decide number of sellers and buyers
    int count_pos = rnd.next(1, N-1);
    int count_neg = rnd.next(1, N - count_pos);
    // Total fleas to transfer
    int S = rnd.next(count_pos, count_pos * 50);
    // Generate positive parts summing to S
    vector<int> pos;
    if (count_pos == 1) {
        pos = {S};
    } else {
        vector<int> cand(S-1);
        iota(cand.begin(), cand.end(), 1);
        shuffle(cand.begin(), cand.end());
        cand.resize(count_pos-1);
        cand.push_back(0);
        cand.push_back(S);
        sort(cand.begin(), cand.end());
        pos.resize(count_pos);
        for (int i = 0; i < count_pos; i++) {
            pos[i] = cand[i+1] - cand[i];
        }
    }
    // Generate negative parts summing to S
    vector<int> neg;
    if (count_neg == 1) {
        neg = {S};
    } else {
        vector<int> cand(S-1);
        iota(cand.begin(), cand.end(), 1);
        shuffle(cand.begin(), cand.end());
        cand.resize(count_neg-1);
        cand.push_back(0);
        cand.push_back(S);
        sort(cand.begin(), cand.end());
        neg.resize(count_neg);
        for (int i = 0; i < count_neg; i++) {
            neg[i] = cand[i+1] - cand[i];
        }
    }
    // Prepare result array
    vector<int> L(N, 0);
    bool block = rnd.next(0, 1);
    if (block) {
        // Block assignment: pos, then neg, then zeros
        for (int i = 0; i < count_pos; i++) L[i] = pos[i];
        for (int i = 0; i < count_neg; i++) L[count_pos + i] = -neg[i];
        // zeros already in place
    } else {
        // Random assignment
        vector<int> idx(N);
        iota(idx.begin(), idx.end(), 0);
        shuffle(idx.begin(), idx.end());
        for (int i = 0; i < count_pos; i++) {
            L[idx[i]] = pos[i];
        }
        for (int i = 0; i < count_neg; i++) {
            L[idx[count_pos + i]] = -neg[i];
        }
    }
    // Output
    println(N);
    println(L);
    return 0;
}
