#include <iostream>
#include <vector>
using namespace std;

#define MAX int(1e5)
#define ll long long

int main(){
  int n; cin >> n;

  vector<ll> phi(MAX + 1);
  phi[0] = 0;
  phi[1] = 1;
  for (int i = 2; i <= MAX; i++)
    phi[i] = i;

  for (int i = 2; i <= MAX; i++) {
    if (phi[i] == i) {
      for (int j = i; j <= MAX; j += i)
        phi[j] -= phi[j] / i;
    }
  }

  bool found = false;
  for(ll i = 1; i <= MAX; i++){
    if (phi[i] * i == n) {
      found = true;
      cout << i << '\n';
      break;
    }
  }

  if (!found) cout << -1 << '\n';
}

// #include<cstdio>
// #include<algorithm>
// #include<vector>
// using namespace std;
// int n;
// int main(){
//     int i;
//     scanf("%d",&n);
//     vector<int>X;
//     for(i=1;i*i<=n;i++){
//         if(n%i==0)X.push_back(i),X.push_back(n/i);
//     }
//     sort(X.begin(),X.end());
//     for(auto &t : X){
//         int u = t, ph = t;
//         for(auto &z : X){
//             if(z==1)continue;
//             if(u%z==0){
//                 ph=ph/z*(z-1);
//                 while(u%z==0)u/=z;
//             }
//         }
//         if(1ll*t*ph==n){
//             printf("%d\n",t);
//             return 0;
//         }
//     }
//     puts("-1");
// }
