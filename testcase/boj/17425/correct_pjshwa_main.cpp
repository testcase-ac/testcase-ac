#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int t;
    scanf("%d", &t);

    vector<long long> fs(1000001, 1);
    vector<long long> gs(1000001);

    for (int i = 2; i <= 1000000; i++) {
        for (int j = 1; i * j <= 1000000; j++) {
            fs[i * j] += i;
        }
    }

    for (int i = 1; i <= 1000000; i++) {
        gs[i] = gs[i - 1] + fs[i];
    }

    for (int i = 0; i < t; i++) {
        int n;
        scanf("%d", &n);
        printf("%lld\n", gs[n]);
    }
    return 0;
}


// #include <bits/stdc++.h>
// using namespace std; typedef long long ll;
// void OJize(){cin.tie(NULL); ios_base::sync_with_stdio(false);}

// ll ds[1001001];

// const int MX = 1000000;
// int main(){OJize();
//     for(int i=1; i<=MX; i++) for(int j=i; j<=MX; j+=i) ds[j]+= i;
//     for(int i=1; i<=MX; i++) ds[i]+= ds[i-1];
//     int Q; cin>>Q;
//     while(Q--){
//         int n; cin>>n;
//         cout<<ds[n]<<'\n';
//     }
// }

// #include <cstdio>
// typedef long long LL;
// #define MAX 1000000
// LL g[MAX + 1];

// int main() {
// 	int tt, n;
// 	for (int i = 1 ; i <= MAX ; i++) {
// 		for (int j = i ; j <= MAX ; j += i) g[j] += i;
// 	}
// 	for (int i = 1 ; i <= MAX ; i++) g[i] += g[i - 1];
// 	for (scanf("%d", &tt) ; tt-- > 0 ; ) scanf("%d", &n), printf("%lld\n", g[n]);
// }
