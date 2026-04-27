#include <iostream>
#include <algorithm>
#include <numeric>

using namespace std;
using ll = long long;

ll N, A[252525], C[252525], R;

int main(){
    cin >> N;
    for(int i=1; i<=N; i++) cin >> A[i];
    if(count(A+1, A+N+1, 0) == N){ cout << N / 2; return 0; }
    rotate(A+1, max_element(A+1, A+N+1), A+N+1);
    R += accumulate(A+1, A+N+1, 0LL);
    for(int i=1, j; i<=N; i++){
        if(A[i] || C[i]) continue;
        for(j=i; j<=N && !A[j]; j++) C[j] = 1;
        R += (j - i + 1) / 2;
    }
    cout << R;
    return 0;
}