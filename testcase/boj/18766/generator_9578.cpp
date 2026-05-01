#include "testlib.h"
using namespace std;

bool equalMulti(const vector<string>& a, const vector<string>& b) {
    if (a.size() != b.size()) return false;
    vector<string> aa = a, bb = b;
    sort(aa.begin(), aa.end());
    sort(bb.begin(), bb.end());
    return aa == bb;
}

vector<string> genRandomCards(int n, bool heavyDup, const vector<string>& all) {
    vector<string> res;
    res.reserve(n);
    int m = (int)all.size();
    for (int i = 0; i < n; ++i) {
        int idx;
        if (heavyDup) idx = rnd.wnext(m, 5);
        else idx = rnd.next(0, m - 1);
        res.push_back(all[idx]);
    }
    return res;
}

vector<string> cheatSimple(const vector<string>& before, const vector<string>& all) {
    int n = (int)before.size();
    vector<string> after = before;

    int maxChanges = max(1, n / 3);
    int k = rnd.next(1, maxChanges);

    vector<int> idx(n);
    for (int i = 0; i < n; ++i) idx[i] = i;
    shuffle(idx.begin(), idx.end());
    idx.resize(k);

    for (int pos : idx) {
        string nc;
        do {
            nc = rnd.any(all);
        } while (nc == after[pos]);
        after[pos] = nc;
    }

    // Ensure multisets differ
    while (equalMulti(before, after)) {
        int pos = rnd.next(0, n - 1);
        string nc;
        do {
            nc = rnd.any(all);
        } while (nc == before[pos] && nc == after[pos]);
        after[pos] = nc;
    }
    return after;
}

void makeIndependenceTrap(vector<string>& before, vector<string>& after) {
    vector<char> colors = {'R', 'Y', 'B'};
    int c1i = rnd.next(0, 2);
    int c2i;
    do { c2i = rnd.next(0, 2); } while (c2i == c1i);
    char c1 = colors[c1i];
    char c2 = colors[c2i];

    int d1i = rnd.next(0, 9);
    int d2i;
    do { d2i = rnd.next(0, 9); } while (d2i == d1i);
    char d1 = char('0' + d1i);
    char d2 = char('0' + d2i);

    string s1, s2, s3, s4;
    s1.push_back(c1); s1.push_back(d1);
    s2.push_back(c2); s2.push_back(d2);
    s3.push_back(c1); s3.push_back(d2);
    s4.push_back(c2); s4.push_back(d1);

    int nType = rnd.next(0, 1); // 0 -> 2 cards, 1 -> 4 cards
    if (nType == 0) {
        before = {s1, s2};
        after  = {s3, s4};
    } else {
        before = {s1, s1, s2, s2};
        after  = {s3, s3, s4, s4};
        shuffle(before.begin(), before.end());
        shuffle(after.begin(), after.end());
    }
}

void makeDuplicateTrap(vector<string>& before, vector<string>& after, const vector<string>& all) {
    // Multiset vs set trap: before [x,x,y], after [x,y,y]
    string x = rnd.any(all);
    string y;
    do { y = rnd.any(all); } while (y == x);

    before.clear(); after.clear();
    before.push_back(x); before.push_back(x); before.push_back(y);
    after.push_back(x); after.push_back(y); after.push_back(y);

    shuffle(before.begin(), before.end());
    shuffle(after.begin(), after.end());
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // All possible cards
    vector<string> all;
    for (char c : {'R', 'Y', 'B'}) {
        for (char d = '0'; d <= '9'; ++d) {
            string s;
            s.push_back(c);
            s.push_back(d);
            all.push_back(s);
        }
    }

    int T = rnd.next(4, 8);
    println(T);

    for (int tc = 0; tc < T; ++tc) {
        vector<string> before, after;

        if (tc == 0) {
            // Identical, random n
            int n = rnd.next(2, 10);
            before = genRandomCards(n, rnd.next(0, 1), all);
            after = before;
        } else if (tc == 1) {
            // Pure permutation
            int n = rnd.next(3, 10);
            before = genRandomCards(n, rnd.next(0, 1), all);
            after = before;
            shuffle(after.begin(), after.end());
        } else if (tc == 2) {
            // Simple cheat with some duplicates
            int n = rnd.next(5, 15);
            before = genRandomCards(n, true, all);
            after = cheatSimple(before, all);
        } else if (tc == 3) {
            // Independence trap: same color and digit counts, different card pairs
            makeIndependenceTrap(before, after);
        } else {
            int scen = rnd.next(0, 4);
            if (scen == 0) {
                // Identical or permutation
                bool same = rnd.next(0, 1);
                if (same) {
                    int n = rnd.next(1, 10);
                    before = genRandomCards(n, rnd.next(0, 1), all);
                    after = before;
                } else {
                    int n = rnd.next(2, 10);
                    before = genRandomCards(n, rnd.next(0, 1), all);
                    after = before;
                    shuffle(after.begin(), after.end());
                }
            } else if (scen == 1) {
                // Simple cheat, random n
                int n = rnd.next(2, 20);
                before = genRandomCards(n, rnd.next(0, 1), all);
                after = cheatSimple(before, all);
            } else if (scen == 2) {
                // Duplicate multiset vs set trap
                makeDuplicateTrap(before, after, all);
            } else if (scen == 3) {
                // Size 1 case, maybe cheat
                int n = 1;
                before = genRandomCards(n, false, all);
                after = before;
                if (rnd.next(0, 1) == 1) {
                    string nc;
                    do { nc = rnd.any(all); } while (nc == before[0]);
                    after[0] = nc;
                }
            } else { // scen == 4 (not used now, but kept for extensibility)
                int n = rnd.next(25, 60);
                before = genRandomCards(n, rnd.next(0, 1), all);
                bool cheat = rnd.next(0, 1);
                if (!cheat) {
                    after = before;
                    shuffle(after.begin(), after.end());
                } else {
                    after = cheatSimple(before, all);
                }
            }
        }

        int n = (int)before.size();
        println(n);
        println(before);
        println(after);
    }

    return 0;
}
