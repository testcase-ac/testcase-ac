#include <bits/stdc++.h>
using namespace std;
int main()
{	
    ios_base::sync_with_stdio(0),cin.tie(0);
    int N,K;
    cin >> N >> K;
    string S;
    cin >> S;
    int j=0,ans=0;
    for(int i=0; i<N; i++){
    	if(S[i]=='H') continue;
    	for(j=max(j,i-K); j<=min(N-1,i+K); j++){
    		if(S[j]=='P') continue;
    		ans++;
    		j++;
    		break;
    	}
    }
    cout << ans;
}