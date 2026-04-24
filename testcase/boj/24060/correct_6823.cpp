#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N, K;

void merge(vector<int>& A, int p, int q, int r) {
    vector<int> tmp(r - p + 1);
    int i = p, j = q + 1, t = 0;

    while (i <= q && j <= r) {
        if (A[i] <= A[j]) {
            tmp[t++] = A[i++];
        } else {
            tmp[t++] = A[j++];
        }
    }
    while (i <= q) {
        tmp[t++] = A[i++];
    }
    while (j <= r) {
        tmp[t++] = A[j++];
    }
    
    for (i = p, t = 0; i <= r; i++, t++) {
        A[i] = tmp[t];
        K--;
        if(!K) {
            cout << A[i];
            exit(0);
        }
    }
}

void mergesort(vector<int>& A, int p, int r) {
    if (p < r) {
        int q = (p + r) / 2;
        mergesort(A, p, q);
        mergesort(A, q + 1, r);
        merge(A, p, q, r);
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> K;
    vector<int> A(N);
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }
    mergesort(A, 0, N - 1);
    cout << -1;
    return 0;

}
