#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string randomBinaryString(int n, int ones) {
    string s(n, '0');
    vector<int> positions(n);
    for (int i = 0; i < n; ++i) positions[i] = i;
    shuffle(positions.begin(), positions.end());
    for (int i = 0; i < ones; ++i) s[positions[i]] = '1';
    return s;
}

string groupedString(int groups, int onesPerGroup, int maxGap) {
    string s;
    s.append(rnd.next(0, maxGap), '0');
    for (int g = 0; g < groups; ++g) {
        int leftGap = rnd.next(0, maxGap);
        int rightGap = rnd.next(0, maxGap);
        s.append(leftGap, '0');
        s.append(onesPerGroup, '1');
        if (g + 1 < groups) s.append(rightGap + 1, '0');
    }
    s.append(rnd.next(0, maxGap), '0');
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(1, 10);
    println(T);

    for (int tc = 0; tc < T; ++tc) {
        int mode = rnd.next(0, 6);
        int n;
        int k;
        string a;

        if (mode == 0) {
            n = rnd.next(1, 35);
            k = rnd.next(1, n);
            a.assign(n, '0');
        } else if (mode == 1) {
            n = rnd.next(1, 60);
            k = 1;
            int ones = rnd.next(0, n);
            a = randomBinaryString(n, ones);
        } else if (mode == 2) {
            n = rnd.next(1, 40);
            k = n;
            int ones = rnd.next(0, n);
            a = randomBinaryString(n, ones);
        } else if (mode == 3) {
            k = rnd.next(2, 8);
            int onesPerGroup = rnd.next(1, 4);
            a = groupedString(k, onesPerGroup, 4);
            n = static_cast<int>(a.size());
        } else if (mode == 4) {
            n = rnd.next(2, 70);
            k = rnd.next(2, n);
            int maxOnes = min(n, 30);
            int ones = rnd.next(1, maxOnes);
            if (ones % k == 0 && ones < maxOnes) ++ones;
            a = randomBinaryString(n, ones);
        } else if (mode == 5) {
            n = rnd.next(8, 90);
            k = rnd.next(2, min(n, 10));
            int ones = rnd.next(1, min(n, 35));
            a = randomBinaryString(n, ones);
            int zeroRunStart = rnd.next(0, n - 1);
            int zeroRunLen = rnd.next(1, min(12, n - zeroRunStart));
            fill(a.begin() + zeroRunStart, a.begin() + zeroRunStart + zeroRunLen, '0');
        } else {
            k = rnd.next(2, 10);
            int onesPerGroup = rnd.next(1, 3);
            a = groupedString(k, onesPerGroup, 10);
            n = static_cast<int>(a.size());
        }

        println(n, k);
        println(a);
    }

    return 0;
}
