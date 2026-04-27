#include <iostream>

using namespace std;

int n, a[300300];
 
int main(){
    cin >> n;
    for(int i=1;i<=n;i++) cin >> a[i];

    int ans = 1;
    for(int i=1;i<n;i++) if(a[i]%2 != a[i+1]%2) ans += 1;
    cout << ans << '\n';
}