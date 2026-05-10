#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the whole line as the single input string
    string s = inf.readLine("[A-Z]+", "s"); // only uppercase letters, non-empty
    // Length constraint
    ensuref((int)s.size() <= 1000000, "length of s is %d, exceeds 1_000_000", (int)s.size());

    int n = (int)s.size();

    // Global constraints from statement:
    // - Seongwoo types only uppercase letters  ('A'-'Z') -> enforced by regex.
    // - He never presses the same alphabet key more than once (originally).
    //   Due to keyboard multiplying each press by N, final string consists of
    //   blocks of identical letters, each block length exactly N, and all
    //   block letters distinct.
    //
    // We must validate that such an N exists and that:
    //   * All letters in different blocks are distinct.
    //   * All blocks have equal length.
    //   * Number of blocks <= 26 (since alphabet letters are unique originally).

    // Determine block lengths and letters
    vector<int> blockLen;
    vector<char> blockChar;

    for (int i = 0; i < n; ) {
        int j = i + 1;
        while (j < n && s[j] == s[i]) j++;
        blockLen.push_back(j - i);
        blockChar.push_back(s[i]);
        i = j;
    }

    int blocks = (int)blockLen.size();
    ensuref(blocks <= 26, "number of distinct pressed keys (blocks) is %d, exceeds 26", blocks);

    // All blocks must have the same length N
    int N = blockLen[0];
    ensuref(N >= 1, "block length N must be at least 1");
    for (int i = 1; i < blocks; i++) {
        ensuref(blockLen[i] == N,
                "inconsistent block length at block %d: got %d, expected %d",
                i, blockLen[i], N);
    }

    // All block letters must be distinct (no alphabet pressed twice)
    vector<bool> used(26, false);
    for (int i = 0; i < blocks; i++) {
        int idx = blockChar[i] - 'A';
        ensuref(!used[idx],
                "alphabet '%c' appears in more than one block (block index %d)",
                blockChar[i], i);
        used[idx] = true;
    }

    // All letters in s are uppercase checked by regex already.

    inf.readEof();
}
