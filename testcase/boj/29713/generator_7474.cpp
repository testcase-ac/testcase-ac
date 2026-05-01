#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Word to form
    const string req = "BRONZESILVER";
    // Unique letters in req
    vector<bool> isReq(26, false);
    for (char c : req) isReq[c - 'A'] = true;
    string uniqueReq;
    for (int i = 0; i < 26; i++)
        if (isReq[i]) uniqueReq.push_back(char('A' + i));
    // All uppercase letters
    const string uppercase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    // Choose N: small (<12), exact 12, medium (>12 up to 30)
    int groupN = rnd.next(0, 2);
    int N;
    if (groupN == 0) {
        N = rnd.next(1, 11);
    } else if (groupN == 1) {
        N = 12;
    } else {
        N = rnd.next(13, 30);
    }

    // Decide how many full patterns to reserve
    int maxPossible = N / 12;
    int t = 0;
    if (N >= 12) {
        int tGroup = rnd.next(0, 3);
        if (tGroup == 0) {
            t = 0;
        } else if (tGroup == 1) {
            t = 1;
        } else if (tGroup == 2) {
            t = rnd.next(1, maxPossible);
        } else {
            t = maxPossible;
        }
    } else {
        t = 0;
    }

    // Build the string
    vector<char> s;
    // Reserve t copies of the word
    for (int i = 0; i < t; i++) {
        for (char c : req) s.push_back(c);
    }
    int leftover = N - int(s.size());
    // Determine forbidden letters for leftover to control exact patterns
    vector<bool> forbid(26, false);
    if (t >= 1) {
        // forbid all req letters to avoid extra patterns
        for (int i = 0; i < 26; i++) if (isReq[i]) forbid[i] = true;
    } else if (N >= 12) {
        // ensure at least one letter missing
        char missing = rnd.any(uniqueReq);
        forbid[missing - 'A'] = true;
    }
    // Build allowed pool
    string pool;
    for (char c : uppercase) {
        if (!forbid[c - 'A'])
            pool.push_back(c);
    }
    if (pool.empty()) {
        // fallback to uppercase if pool is empty
        pool = uppercase;
    }
    // Fill leftover
    for (int i = 0; i < leftover; i++) {
        s.push_back(rnd.any(pool));
    }
    // Shuffle the result
    shuffle(s.begin(), s.end());

    // Output
    println(N);
    string out(s.begin(), s.end());
    println(out);
    return 0;
}
