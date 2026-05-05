#include<iostream>
using namespace std;

int n, dp[3005], arr[3005];

int main(){
    ios::sync_with_stdio(0); cin.tie(0);
	cin >> n;
	for(int i = 1; i <= n; i++){
		cin >> arr[i];
		dp[i] = 1e9;
	}
	dp[0] = 0;
	for(int i = 1;  i <= n; i++){
        dp[i] = min(dp[i-1]+1, dp[i]);
		for(int j = 1; j < arr[i]; j++){
            if(i+j > n) continue;
			dp[i+j] = min(dp[i+j], dp[i-1]+1);
		}
	}
	cout << dp[n]; 
}
