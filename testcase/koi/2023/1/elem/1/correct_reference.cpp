#include <iostream>
#include <string>
 
using namespace std;
 
const int MAXN = 1e4+10;
 
int A[MAXN];
 
int main()
{
    int n, k, p;
 
    ios_base::sync_with_stdio(false);
    cin.tie(0);
 
    cin>>n>>k>>p;
 
    for(int i = 0; i < n*k; i++) {
        cin>>A[i];
    }
 
    int res = 0;
 
    for(int i = 0; i < n; i++) {
        int cnt = 0;
 
        for(int j = 0; j < k; j++) {
            if(A[i*k+j]==0)cnt++;
        }
 
        if(cnt<p)res++;
    }
 
    cout<<res<<"\n";
 
    return 0;
}
 
