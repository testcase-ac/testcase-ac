#include <bits/stdc++.h>
using namespace std;

#define ll long long
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int k, n;
	cin >> k >> n;
	vector<int> prime(k);
	for(int i=0; i<k; i++) {
		cin >> prime[i];
	}
	priority_queue<ll, vector<ll>, greater<ll>> pq;
	for(int p: prime)
		pq.push(p);
	n--;
	while(n--) {
		ll p = pq.top();
		pq.pop();
		int i = 0;
		for(i=k-1; i>=0; i--)
			if(p % prime[i] == 0) break;
		for(;i<k;i++)
			pq.push(p*prime[i]);
	}
	cout << pq.top();
}
