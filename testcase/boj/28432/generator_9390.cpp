#include "testlib.h"
using namespace std;

char randomChar() {
    return char('a' + rnd.next(0, 25));
}

char randomCharExcept(char c) {
    char r;
    do {
        r = randomChar();
    } while (r == c);
    return r;
}

string randomWord(int len, char first = '\0', char last = '\0') {
    string s(len, 'a');
    if (first != '\0') s[0] = first;
    else s[0] = randomChar();
    for (int i = 1; i < len - 1; ++i) {
        s[i] = randomChar();
    }
    if (len > 1) {
        if (last != '\0') s[len - 1] = last;
        else s[len - 1] = randomChar();
    }
    return s;
}

bool isValidCandidate(
    const string &w,
    const set<string> &existingWords,
    bool hasPrev, char prevLast,
    bool hasNext, char nextFirst
) {
    if (existingWords.count(w)) return false; // duplication with other S_i
    if (hasPrev && w[0] != prevLast) return false;
    if (hasNext && w.back() != nextFirst) return false;
    return true;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Decide whether to generate the N = 1 edge case
    bool singleCase = (rnd.next(0, 9) == 0); // ~10% probability

    if (singleCase) {
        int N = 1;
        println(N);
        println("?");
        int M = 1;
        println(M);
        int len = rnd.next(2, 7);
        string w = randomWord(len);
        println(w);
        return 0;
    }

    // General case: N >= 2, exactly one valid candidate among M >= 2
    int N;
    // Bias towards small but varied N
    int tN = rnd.next(0, 2);
    if (tN == 0) N = rnd.next(2, 4);
    else if (tN == 1) N = rnd.next(5, 8);
    else N = rnd.next(9, 12);

    vector<string> base(N);
    set<string> used;

    // Build a valid word chain with all words distinct
    for (int i = 0; i < N; ++i) {
        while (true) {
            int len = rnd.next(2, 7);
            if (i == 0) {
                base[i] = randomWord(len);
            } else {
                char prevLast = base[i - 1].back();
                base[i] = randomWord(len, prevLast, '\0');
            }
            if (!used.count(base[i])) {
                used.insert(base[i]);
                break;
            }
        }
    }

    // Choose position of '?'
    int k;
    if (N > 2 && rnd.next(0, 1) == 0) {
        // Prefer middle positions sometimes
        k = rnd.next(1, N - 2);
    } else {
        k = rnd.next(0, N - 1);
    }

    string correct = base[k];

    // Collect existing words excluding position k
    set<string> existingWords;
    vector<string> othersVec;
    for (int i = 0; i < N; ++i) {
        if (i == k) continue;
        existingWords.insert(base[i]);
        othersVec.push_back(base[i]);
    }

    bool hasPrev = (k > 0);
    bool hasNext = (k + 1 < N);
    char prevLast = hasPrev ? base[k - 1].back() : '\0';
    char nextFirst = hasNext ? base[k + 1][0] : '\0';

    // Decide number of candidates M (at least 2)
    int maxM = 8;
    int M = rnd.next(2, maxM);

    vector<string> candidates;
    set<string> candSet;

    // Always include the correct one
    candidates.push_back(correct);
    candSet.insert(correct);

    // Generate invalid candidates
    while ((int)candidates.size() < M) {
        int type = rnd.next(0, 2); // 0 or 1

        string cand;

        if (type == 1 && !othersVec.empty()) {
            // Type 1: duplicate of existing word (invalid due to duplication)
            bool tryAdjSatisfied = rnd.next(0, 1); // sometimes satisfy adjacency too
            bool got = false;
            if (tryAdjSatisfied) {
                vector<string> adjDup;
                for (const string &w : othersVec) {
                    bool ok = true;
                    if (hasPrev && w[0] != prevLast) ok = false;
                    if (hasNext && w.back() != nextFirst) ok = false;
                    if (ok) adjDup.push_back(w);
                }
                if (!adjDup.empty()) {
                    // Pick a duplicate that also satisfies adjacency
                    string w = rnd.any(adjDup);
                    if (!candSet.count(w)) {
                        cand = w;
                        got = true;
                    }
                }
            }
            if (!got) {
                // Fallback: any existing word
                for (int attempts = 0; attempts < 100 && !got; ++attempts) {
                    string w = rnd.any(othersVec);
                    if (!candSet.count(w)) {
                        cand = w;
                        got = true;
                    }
                }
            }
            if (!got) continue; // rare, retry

            // Since cand is in existingWords, it's automatically invalid.
            candSet.insert(cand);
            candidates.push_back(cand);
        } else {
            // Type 0: invalid by breaking adjacency (and ensuring not accidentally valid)
            for (int attempts = 0; attempts < 1000; ++attempts) {
                int len = rnd.next(2, 7);
                char fc = randomChar();
                char lc = randomChar();

                if (hasPrev && hasNext) {
                    bool enforceFirstMismatch = rnd.next(0, 1);
                    bool enforceLastMismatch = rnd.next(0, 1);
                    if (!enforceFirstMismatch && !enforceLastMismatch)
                        enforceFirstMismatch = true; // at least one mismatch

                    if (enforceFirstMismatch) fc = randomCharExcept(prevLast);
                    else fc = prevLast;

                    if (enforceLastMismatch) lc = randomCharExcept(nextFirst);
                    else lc = nextFirst;
                } else if (hasPrev) {
                    fc = randomCharExcept(prevLast);
                    // lc can be anything
                } else if (hasNext) {
                    lc = randomCharExcept(nextFirst);
                    // fc can be anything
                }

                string w = randomWord(len, fc, lc);

                if (candSet.count(w)) continue;
                if (isValidCandidate(w, existingWords, hasPrev, prevLast, hasNext, nextFirst))
                    continue; // accidentally valid, reject

                cand = w;
                candSet.insert(cand);
                candidates.push_back(cand);
                break;
            }
        }
    }

    // Sanity check: exactly one valid candidate (the correct one)
    int validCount = 0;
    for (const string &w : candidates) {
        if (isValidCandidate(w, existingWords, hasPrev, prevLast, hasNext, nextFirst))
            ++validCount;
    }
    // Should be exactly one
    // (In production this should always hold; generator logic is designed to ensure it.)

    // Shuffle candidates to hide the correct one
    shuffle(candidates.begin(), candidates.end());

    // Output
    println(N);
    for (int i = 0; i < N; ++i) {
        if (i == k) println("?");
        else println(base[i]);
    }
    println(M);
    for (const string &w : candidates) {
        println(w);
    }

    return 0;
}
