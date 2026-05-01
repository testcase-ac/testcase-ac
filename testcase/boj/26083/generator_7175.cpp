#include "testlib.h"
#include <vector>
#include <array>
#include <algorithm>
using namespace std;

bool isLeap(int y) {
    return (y % 400 == 0) || (y % 4 == 0 && y % 100 != 0);
}

int daysInMonth(int y, int m) {
    static int dm[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
    if (m == 2 && isLeap(y)) return 29;
    return dm[m];
}

// days since 2000-01-01
int conv(int y, int m, int d) {
    int days = 0;
    for (int yy = 2000; yy < y; yy++)
        days += 365 + isLeap(yy);
    for (int mm = 1; mm < m; mm++)
        days += daysInMonth(y, mm);
    days += d - 1;
    return days;
}

bool validYMD(int A, int B, int C) {
    if (A < 0 || A > 99) return false;
    int y = 2000 + A;
    if (B < 1 || B > 12) return false;
    if (C < 1 || C > daysInMonth(y, B)) return false;
    return true;
}
bool validDMY(int A, int B, int C) {
    if (C < 0 || C > 99) return false;
    int y = 2000 + C;
    if (B < 1 || B > 12) return false;
    if (A < 1 || A > daysInMonth(y, B)) return false;
    return true;
}
bool validMDY(int A, int B, int C) {
    if (C < 0 || C > 99) return false;
    int y = 2000 + C;
    if (A < 1 || A > 12) return false;
    if (B < 1 || B > daysInMonth(y, A)) return false;
    return true;
}

int expYMD(int A, int B, int C) {
    return conv(2000 + A, B, C);
}
int expDMY(int A, int B, int C) {
    return conv(2000 + C, B, A);
}
int expMDY(int A, int B, int C) {
    return conv(2000 + C, A, B);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // 1) pick today's date, avoid the very first day to allow unsafe
    int Y, M, D, t0;
    while (true) {
        Y = rnd.next(0, 99);
        M = rnd.next(1, 12);
        if (!validYMD(Y, M, 1)) continue;
        D = rnd.next(1, daysInMonth(2000+Y, M));
        t0 = conv(2000+Y, M, D);
        if (t0 > 0) break;
    }

    vector<array<int,3>> triples;

    // Category 1: invalid
    {
        int A,B,C;
        for (int it = 0; it < 10000; it++) {
            A = rnd.next(0, 99);
            B = rnd.next(0, 99);
            C = rnd.next(0, 99);
            if (!validYMD(A,B,C) && !validDMY(A,B,C) && !validMDY(A,B,C)) {
                triples.push_back({A,B,C});
                break;
            }
        }
    }

    // Category 2 and 3: one valid safe, one valid unsafe
    for (int cat = 0; cat < 2; cat++) {
        bool wantSafe = (cat == 0);
        int f = rnd.next(0,2);
        int A,B,C;
        for (int it = 0; it < 10000; it++) {
            if (f == 0) {
                A = rnd.next(0,99);
                B = rnd.next(1,12);
                C = rnd.next(1, daysInMonth(2000+A, B));
            } else if (f == 1) {
                C = rnd.next(0,99);
                B = rnd.next(1,12);
                A = rnd.next(1, daysInMonth(2000+C, B));
            } else {
                C = rnd.next(0,99);
                A = rnd.next(1,12);
                B = rnd.next(1, daysInMonth(2000+C, A));
            }
            int e = (f==0 ? expYMD(A,B,C) : f==1 ? expDMY(A,B,C) : expMDY(A,B,C));
            bool cond = wantSafe ? (e >= t0) : (e < t0);
            if (!cond) continue;
            // other formats invalid
            if ( (f!=0 && validYMD(A,B,C)) ||
                 (f!=1 && validDMY(A,B,C)) ||
                 (f!=2 && validMDY(A,B,C)) ) continue;
            triples.push_back({A,B,C});
            break;
        }
    }

    // Category 4 and 5: two valid safe, two valid unsafe
    for (int cat = 0; cat < 2; cat++) {
        bool wantSafe = (cat == 0);
        int f1, f2;
        if (rnd.next(0,1) == 0) { f1 = 0; f2 = 1; }
        else if (rnd.next(0,1) == 0) { f1 = 0; f2 = 2; }
        else { f1 = 1; f2 = 2; }
        int A,B,C;
        for (int it = 0; it < 20000; it++) {
            if (f1==0 && f2==1) {
                A = rnd.next(1,28);
                B = rnd.next(1,12);
                C = rnd.next(1,28);
            } else if (f1==0 && f2==2) {
                A = rnd.next(1,12);
                B = rnd.next(1,28);
                C = rnd.next(1,28);
            } else {
                A = rnd.next(1,12);
                B = rnd.next(1,12);
                C = rnd.next(0,99);
            }
            bool v1 = (f1==0?validYMD(A,B,C):f1==1?validDMY(A,B,C):validMDY(A,B,C));
            bool v2 = (f2==0?validYMD(A,B,C):f2==1?validDMY(A,B,C):validMDY(A,B,C));
            if (!v1 || !v2) continue;
            // third invalid
            int f3 = 3 - (f1 + f2);
            bool v3 = (f3==0?validYMD(A,B,C):f3==1?validDMY(A,B,C):validMDY(A,B,C));
            if (v3) continue;
            int e1 = (f1==0?expYMD(A,B,C):f1==1?expDMY(A,B,C):expMDY(A,B,C));
            int e2 = (f2==0?expYMD(A,B,C):f2==1?expDMY(A,B,C):expMDY(A,B,C));
            int mn = min(e1,e2);
            bool cond = wantSafe ? (mn >= t0) : (mn < t0);
            if (!cond) continue;
            triples.push_back({A,B,C});
            break;
        }
    }

    // Category 6 and 7: three valid safe / unsafe
    for (int cat = 0; cat < 2; cat++) {
        bool wantSafe = (cat == 0);
        int A,B,C;
        for (int it = 0; it < 20000; it++) {
            A = rnd.next(1,12);
            B = rnd.next(1,12);
            C = rnd.next(1,28);
            if (!validYMD(A,B,C) || !validDMY(A,B,C) || !validMDY(A,B,C)) continue;
            int e0 = expYMD(A,B,C), e1 = expDMY(A,B,C), e2 = expMDY(A,B,C);
            int mn = min(e0, min(e1,e2));
            bool cond = wantSafe ? (mn >= t0) : (mn < t0);
            if (!cond) continue;
            triples.push_back({A,B,C});
            break;
        }
    }

    // shuffle for variety
    shuffle(triples.begin(), triples.end());

    // output
    println(Y, M, D);
    println((int)triples.size());
    for (auto &t : triples)
        println(t[0], t[1], t[2]);

    return 0;
}
