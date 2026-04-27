#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int n; ll s;
ll A[200002];

int main(){
    scanf("%d %lld", &n, &s);
    for(int i=1; i<=n; i++) scanf("%lld", &A[i]);

    int L = 1, R = n, turn=n%2;
    while(L<=R){
        if(turn == 1) s = 2 * A[R--] - s;
        else s = 2 * A[L++] - s;
        turn = !turn;
    }
    printf("%lld", s);
}
