#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
vector<string> split(string s, char c) {
    vector<string> v;
    for(int i=0, j=0; i<s.size(); i=j) {
        while(j<s.size() && s[j]!=c) j++;
        v.push_back(s.substr(i, j-i));
        j++;
    }
    return v;
}
int rnd(double x) {
    return (int)(x+0.5);
}
int avg1(vector<int> A, int K) {
    int sum = 0;
    for(int i=K; i<A.size()-K; i++) {
        sum += A[i];
    }
    return rnd((double)sum / (A.size()-2*K));
}
int avg2(vector<int> A, int K) {
    int sum = 0;
    for(int i=K; i<A.size()-K; i++) {
        sum += A[i];
    }
    for(int i=0; i<K; i++) {
        sum += A[K];
    }
    for(int i=A.size()-K; i<A.size(); i++) {
        sum += A[A.size()-K-1];
    }
    return rnd((double)sum / A.size());
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int N, K;
    cin >> N >> K;
    vector<int> A(N);
    for(int i=0; i<N; i++) {
        string s;
        cin >> s;
        vector<string> v = split(s, '.');
        A[i] = stoi(v[0]) * 100 + stoi(v[1]) * 10;
    }
    sort(A.begin(), A.end());
    int a1 = avg1(A, K);
    int a2 = avg2(A, K);
    printf("%d.%02d\n", a1/100, a1%100);
    printf("%d.%02d\n", a2/100, a2%100);
}
