#include <iostream>
using namespace std;

int N, X[3030], T[3030];

int main(){
    cin >> N;
    for(int i=1; i<=N; i++) cin >> X[i];
    for(int i=1; i<=N; i++) cin >> T[i];

    int L = X[N], M = 0;
    for(int i=1; i<=N; i++) M = max(M, T[i] - (2 * L - X[i]));
    cout << 2 * L + M;
}