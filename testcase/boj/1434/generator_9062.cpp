#include "testlib.h"
using namespace std;

long long sumVec(const vector<int>& v) {
    long long s = 0;
    for (int x : v) s += x;
    return s;
}

bool checkValid(const vector<int>& A, const vector<int>& B) {
    int N = (int)A.size();
    int M = (int)B.size();
    int i = 0; // box index
    int j = 0; // book index
    while (j < M && i < N) {
        long long remaining = A[i];
        while (j < M && remaining >= B[j]) {
            remaining -= B[j];
            j++;
        }
        if (j == M) return true; // all books placed
        // current book doesn't fit, move to next box
        i++;
    }
    return (j == M);
}

void genModeBigBox(vector<int>& A, vector<int>& B, int& N, int& M) {
    M = rnd.next(1, 15);
    B.assign(M, 0);

    int hiBChoices[4] = {3, 5, 9, 12};
    int hiB = hiBChoices[rnd.next(0, 3)];
    for (int j = 0; j < M; ++j) {
        B[j] = rnd.next(1, hiB);
    }

    N = rnd.next(1, 15);
    A.assign(N, 0);

    long long sumB = sumVec(B);
    int bigBox = rnd.next(1, N); // 1-based index

    for (int i = 1; i <= N; ++i) {
        if (i == bigBox) {
            long long extraMax = min(10LL, 1000LL - sumB);
            long long extra = extraMax > 0 ? rnd.next(0, (int)extraMax) : 0;
            A[i - 1] = (int)(sumB + extra);
        } else {
            if (sumB >= 2) {
                int hi = (int)min(sumB - 1, 20LL);
                A[i - 1] = rnd.next(1, hi);
            } else { // sumB == 1
                A[i - 1] = 1;
            }
        }
    }
}

void genModePartitionNoEmpties(vector<int>& A, vector<int>& B, int& N, int& M) {
    M = rnd.next(2, 15);
    B.assign(M, 0);

    int hiBChoices[4] = {3, 5, 9, 12};
    int hiB = hiBChoices[rnd.next(0, 3)];
    for (int j = 0; j < M; ++j) {
        B[j] = rnd.next(1, hiB);
    }

    long long totalB = sumVec(B);

    int maxK = M;
    int K = rnd.next(2, min(maxK, 5)); // number of non-empty used boxes

    vector<int> positions;
    for (int i = 1; i <= M - 1; ++i) positions.push_back(i);
    shuffle(positions.begin(), positions.end());
    positions.resize(K - 1);
    sort(positions.begin(), positions.end());

    vector<pair<int, int>> segments;
    int prev = 1;
    for (int idx = 0; idx < (int)positions.size(); ++idx) {
        int c = positions[idx];
        segments.push_back(make_pair(prev, c));
        prev = c + 1;
    }
    segments.push_back(make_pair(prev, M)); // K segments total

    int maxEAfter = 15 - K;
    if (maxEAfter < 0) maxEAfter = 0;
    int E_after = rnd.next(0, maxEAfter);
    N = K + E_after;

    A.assign(N, 0);

    // capacities for boxes that hold books
    for (int g = 0; g < K; ++g) {
        int l = segments[g].first;
        int r = segments[g].second;

        long long S = 0;
        for (int idx = l - 1; idx <= r - 1; ++idx)
            S += B[idx];

        if (g < K - 1) {
            int nextIndex = r; // zero-based index of B[r+1]
            int T = B[nextIndex];
            long long hiLL = S + T - 1;
            long long hiCap = min(hiLL, 1000LL);
            int lo = (int)S;
            int hi = (int)hiCap;
            if (lo > hi) lo = hi;
            A[g] = rnd.next(lo, hi);
        } else {
            // last group: ensure capacity < totalB for variety
            int lo = (int)S;
            int hi = (int)min(totalB - 1, 1000LL);
            if (lo > hi) hi = lo;
            A[g] = rnd.next(lo, hi);
        }
    }

    // capacities for unopened boxes after all books
    for (int i = K; i < N; ++i) {
        int hiSmall = (int)min(totalB - 1, 20LL);
        if (hiSmall < 1) hiSmall = 1;
        A[i] = rnd.next(1, hiSmall);
    }
}

void genModePartitionWithEmpties(vector<int>& A, vector<int>& B, int& N, int& M) {
    M = rnd.next(2, 15);
    B.assign(M, 0);

    int hiBChoices[4] = {3, 5, 9, 12};
    int hiB = hiBChoices[rnd.next(0, 3)];
    for (int j = 0; j < M; ++j) {
        B[j] = rnd.next(1, hiB);
    }

    long long totalB = sumVec(B);

    int K = rnd.next(2, min(M, 5)); // number of non-empty used boxes

    vector<int> positions;
    for (int i = 1; i <= M - 1; ++i) positions.push_back(i);
    shuffle(positions.begin(), positions.end());
    positions.resize(K - 1);
    sort(positions.begin(), positions.end());

    vector<pair<int, int>> segments;
    int prev = 1;
    for (int idx = 0; idx < (int)positions.size(); ++idx) {
        int c = positions[idx];
        segments.push_back(make_pair(prev, c));
        prev = c + 1;
    }
    segments.push_back(make_pair(prev, M)); // K segments total

    int E_before = 0;
    if (B[0] > 1) {
        int maxE_before = min(2, 15 - K);
        if (maxE_before < 0) maxE_before = 0;
        if (maxE_before > 0) {
            E_before = rnd.next(0, maxE_before);
        }
    }

    int remainingForAfter = 15 - (E_before + K);
    if (remainingForAfter < 0) remainingForAfter = 0;
    int E_after = rnd.next(0, remainingForAfter);

    N = E_before + K + E_after;
    A.assign(N, 0);

    // leading empty boxes: too small for first book
    for (int i = 0; i < E_before; ++i) {
        A[i] = rnd.next(1, B[0] - 1); // B[0] > 1 guaranteed if E_before > 0
    }

    // boxes that actually hold books
    for (int g = 0; g < K; ++g) {
        int idxBox = E_before + g;
        int l = segments[g].first;
        int r = segments[g].second;

        long long S = 0;
        for (int idx = l - 1; idx <= r - 1; ++idx)
            S += B[idx];

        if (g < K - 1) {
            int nextIndex = r; // zero-based index of B[r+1]
            int T = B[nextIndex];
            long long hiLL = S + T - 1;
            long long hiCap = min(hiLL, 1000LL);
            int lo = (int)S;
            int hi = (int)hiCap;
            if (lo > hi) lo = hi;
            A[idxBox] = rnd.next(lo, hi);
        } else {
            // last group: capacity at least S, less than totalB for variety
            int lo = (int)S;
            int hi = (int)min(totalB - 1, 1000LL);
            if (lo > hi) hi = lo;
            A[idxBox] = rnd.next(lo, hi);
        }
    }

    // unopened boxes after finishing all books
    for (int i = E_before + K; i < N; ++i) {
        int hiSmall = (int)min(totalB - 1, 20LL);
        if (hiSmall < 1) hiSmall = 1;
        A[i] = rnd.next(1, hiSmall);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> A, B;
    int N = 0, M = 0;

    int mode = rnd.next(0, 2); // 0: big box, 1: partition no empties, 2: partition with empties

    if (mode == 0) {
        genModeBigBox(A, B, N, M);
        if (!checkValid(A, B)) {
            genModeBigBox(A, B, N, M);
        }
    } else if (mode == 1) {
        genModePartitionNoEmpties(A, B, N, M);
        if (!checkValid(A, B)) {
            genModeBigBox(A, B, N, M);
        }
    } else {
        genModePartitionWithEmpties(A, B, N, M);
        if (!checkValid(A, B)) {
            genModeBigBox(A, B, N, M);
        }
    }

    // Final safety: ensure validity
    if (!checkValid(A, B)) {
        // As a last resort, regenerate with the simplest safe mode
        genModeBigBox(A, B, N, M);
    }

    println(N, M);
    println(A);
    println(B);

    return 0;
}
