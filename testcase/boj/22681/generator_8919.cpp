#include "testlib.h"
using namespace std;

void printInterval(int s, int e) {
    int sh = s / 3600;
    int sm = (s % 3600) / 60;
    int ss = s % 60;
    int eh = e / 3600;
    int em = (e % 3600) / 60;
    int es = e % 60;
    printf("%02d:%02d:%02d %02d:%02d:%02d\n", sh, sm, ss, eh, em, es);
}

void genChain(int n, vector<pair<int,int>>& v) {
    v.clear();
    int curStart = rnd.next(0, 10000);
    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            int gap;
            if (rnd.next(0, 1) == 0) gap = 0;
            else gap = rnd.next(1, 500);
            curStart = v.back().second + gap;
        }
        if (curStart >= 86399) curStart = 86398;
        int maxLen = max(1, 86399 - curStart);
        int len = rnd.next(1, min(1000, maxLen));
        int arr = curStart + len;
        if (arr > 86399) arr = 86399;
        if (arr <= curStart) arr = curStart + 1;
        v.push_back({curStart, arr});
    }
}

void genOverlapPoint(int n, vector<pair<int,int>>& v) {
    v.clear();
    int c = rnd.next(20000, 70000);
    for (int i = 0; i < n; ++i) {
        int leftSpan = rnd.next(0, 2000);
        int rightSpan = rnd.next(1, 2000);
        int s = c - leftSpan;
        int e = c + rightSpan;
        if (s < 0) s = 0;
        if (e > 86399) e = 86399;
        if (e <= c) e = min(86399, c + 1);
        if (s > c) s = max(0, c - 1);
        if (e <= s) e = min(86399, s + 1);
        v.push_back({s, e});
    }
}

void genRandom(int n, vector<pair<int,int>>& v) {
    v.clear();
    for (int i = 0; i < n; ++i) {
        int s = rnd.next(0, 86398);
        int lenMax = min(20000, 86399 - s);
        if (lenMax < 1) { s = 86398; lenMax = 1; }
        int len = rnd.next(1, lenMax);
        int e = s + len;
        if (e > 86399) e = 86399;
        if (e <= s) e = s + 1;
        v.push_back({s, e});
    }
}

void genBackToBack(int n, vector<pair<int,int>>& v) {
    v.clear();
    int curStart = rnd.next(0, 20000);
    for (int i = 0; i < n; ++i) {
        if (curStart >= 86399) curStart = 86398;
        int maxLen = max(1, 86399 - curStart);
        int len = rnd.next(1, min(1500, maxLen));
        int e = curStart + len;
        if (e > 86399) e = 86399;
        if (e <= curStart) e = curStart + 1;
        v.push_back({curStart, e});
        if (i + 1 < n) {
            int choose = rnd.next(0, 2);
            if (choose == 0) curStart = e; // back-to-back
            else curStart = e + rnd.next(1, 300);
            if (curStart > 86398) curStart = 86398;
        }
    }
}

void genLateEvening(int n, vector<pair<int,int>>& v) {
    v.clear();
    for (int i = 0; i < n; ++i) {
        int e = rnd.next(85000, 86399);
        int lenMax = min(1000, e);
        if (lenMax < 1) lenMax = 1;
        int len = rnd.next(1, lenMax);
        int s = e - len;
        if (s < 0) s = 0;
        if (e <= s) e = s + 1;
        if (e > 86399) e = 86399;
        v.push_back({s, e});
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int maxTotalN = 20;
    int D = rnd.next(2, 4);
    int totalN = 0;

    for (int d = 0; d < D; ++d) {
        int remainingDatasets = D - d;
        int remainingCapacity = maxTotalN - totalN;
        if (remainingCapacity < remainingDatasets) {
            // reduce number of datasets if capacity too small
            D = d + remainingCapacity;
            remainingDatasets = D - d;
            remainingCapacity = maxTotalN - totalN;
        }
        if (d >= D) break;
        if (remainingCapacity <= 0) break;

        int maxNHere = remainingCapacity - (remainingDatasets - 1);
        if (maxNHere < 1) maxNHere = 1;
        int nHere = (maxNHere == 1) ? 1 : rnd.next(1, min(7, maxNHere));
        totalN += nHere;

        vector<pair<int,int>> intervals;
        int type = rnd.next(0, 4);
        if (type == 0) genChain(nHere, intervals);
        else if (type == 1) genOverlapPoint(nHere, intervals);
        else if (type == 2) genRandom(nHere, intervals);
        else if (type == 3) genBackToBack(nHere, intervals);
        else genLateEvening(nHere, intervals);

        if (rnd.next(0, 1) == 1) {
            shuffle(intervals.begin(), intervals.end());
        }

        println(nHere);
        for (auto &p : intervals) {
            printInterval(p.first, p.second);
        }
    }

    println(0);
    return 0;
}
