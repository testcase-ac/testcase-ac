#include "testlib.h"
using namespace std;

string codeString(int x) {
    char buf[5];
    sprintf(buf, "%04d", x);
    return string(buf);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(1, 2); // number of test cases in this input (1 or 2)

    for (int tc = 0; tc < T; ++tc) {
        // Choose k (number of selected courses) and m (number of categories)
        int k;
        if (rnd.next(0, 3) == 0) k = rnd.next(1, 4); // smaller more often
        else k = rnd.next(4, 8);                     // up to 8

        int m;
        if (rnd.next(0, 3) == 0) m = 0;              // sometimes no categories
        else m = rnd.next(1, 4);                     // up to 4 categories

        bool willPass = true;
        if (m > 0) willPass = (rnd.next(0, 1) == 0); // roughly half pass/fail

        // Generate Freddie's selected courses (distinct)
        vector<int> sel;
        set<int> selSet;
        while ((int)sel.size() < k) {
            int x = rnd.next(0, 9999);
            if (!selSet.count(x)) {
                selSet.insert(x);
                sel.push_back(x);
            }
        }

        // Print k and m
        println(k, m);

        // Print k course numbers over 1–3 lines
        int maxLines = min(3, k);
        int L = rnd.next(1, maxLines);
        int remaining = k;
        int linesLeft = L;
        int idx = 0;
        for (int line = 0; line < L; ++line) {
            int len;
            if (linesLeft == 1) len = remaining;
            else len = rnd.next(1, remaining - (linesLeft - 1));

            vector<string> tokens;
            for (int i = 0; i < len; ++i) {
                tokens.push_back(codeString(sel[idx++]));
            }
            println(tokens);

            remaining -= len;
            --linesLeft;
        }

        if (m == 0) continue;

        bool unsatMade = false;

        for (int ci = 0; ci < m; ++ci) {
            bool makeUnsat = false;
            if (!willPass) {
                if (!unsatMade) {
                    makeUnsat = true;
                    unsatMade = true;
                }
            }

            int Cmax = min(6, k + 2); // keep categories small
            if (Cmax < 1) Cmax = 1;
            int c = rnd.next(1, Cmax);

            vector<int> catCourses;
            set<int> catSet;
            int r = 0;

            if (makeUnsat) {
                // Create an unsatisfied category
                bool allowOverlap = (k > 0 && c > 1 && rnd.next(0, 1) == 0);
                if (!allowOverlap) {
                    // Zero-overlap with r > 0
                    r = rnd.next(1, c);
                    while ((int)catCourses.size() < c) {
                        int x = rnd.next(0, 9999);
                        if (!selSet.count(x) && !catSet.count(x)) {
                            catSet.insert(x);
                            catCourses.push_back(x);
                        }
                    }
                } else {
                    // Partial overlap but not enough to meet r
                    int maxOverlap = min(k, c - 1);
                    if (maxOverlap <= 0) {
                        // Fallback to zero-overlap
                        r = rnd.next(1, c);
                        while ((int)catCourses.size() < c) {
                            int x = rnd.next(0, 9999);
                            if (!selSet.count(x) && !catSet.count(x)) {
                                catSet.insert(x);
                                catCourses.push_back(x);
                            }
                        }
                    } else {
                        int s = rnd.next(1, maxOverlap); // number of overlapping courses
                        r = rnd.next(s + 1, c);          // require more than overlap

                        // pick s from selection
                        vector<int> idxs(k);
                        for (int i = 0; i < k; ++i) idxs[i] = i;
                        shuffle(idxs.begin(), idxs.end());
                        for (int i = 0; i < s; ++i) {
                            int val = sel[idxs[i]];
                            catCourses.push_back(val);
                            catSet.insert(val);
                        }
                        // fill remaining with non-selected courses
                        while ((int)catCourses.size() < c) {
                            int x = rnd.next(0, 9999);
                            if (!selSet.count(x) && !catSet.count(x)) {
                                catSet.insert(x);
                                catCourses.push_back(x);
                            }
                        }
                    }
                }
            } else {
                // Create a satisfied category
                int maxOverlap = min(k, c);
                int s = 0;
                if (maxOverlap > 0) {
                    if (rnd.next(0, 3) == 0) s = 0;   // sometimes no overlap
                    else s = rnd.next(1, maxOverlap); // often some overlap
                }

                // pick s from selection
                if (s > 0) {
                    vector<int> idxs(k);
                    for (int i = 0; i < k; ++i) idxs[i] = i;
                    shuffle(idxs.begin(), idxs.end());
                    for (int i = 0; i < s; ++i) {
                        int val = sel[idxs[i]];
                        catCourses.push_back(val);
                        catSet.insert(val);
                    }
                }

                // fill remaining with non-selected courses
                while ((int)catCourses.size() < c) {
                    int x = rnd.next(0, 9999);
                    if (!selSet.count(x) && !catSet.count(x)) {
                        catSet.insert(x);
                        catCourses.push_back(x);
                    }
                }

                // choose r so that requirement is satisfied
                if (s == 0) {
                    r = 0; // only way to satisfy with no overlap
                } else {
                    r = rnd.next(0, s);
                }
            }

            vector<string> parts;
            parts.push_back(to_string(c));
            parts.push_back(to_string(r));
            for (int x : catCourses) {
                parts.push_back(codeString(x));
            }
            println(parts);
        }
    }

    println(0);
    return 0;
}
