#include <iostream>
#include <algorithm>
 
using namespace std;
 
const int MAXN = 5'000;
 
int A[MAXN*2+10];
 
int main()
{
    int n;
 
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
 
    cin>>n;
 
    for(int i = 0; i < (n<<1); i++) {
        cin>>A[i];
    }
 
    int ans = 0;
 
    for(int i = 0; i < (n<<1); i++) {
        for(int j = i+1; j < (n<<1); j++) {
            if(A[i] == A[j]) {
                ans = max(ans, j-i);
                break;
            }
        }
    }
 
    cout << ans-1 << "\n";
 
    return 0;
}
