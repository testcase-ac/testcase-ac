#include <cstdio>
#include <vector>
#include <algorithm>
int main(){
	int n;
	long long m;
	scanf("%d%lld", &n, &m);
	std::vector<std::pair<long long, long long>> v;
	long long a[n], b[n];
	for(auto &x : a){
		scanf("%lld", &x);
	}
	for(auto &x : b){
		scanf("%lld", &x);
	}
	for(int i = 0; i < n; i++){
		v.push_back(std::make_pair(a[i], b[i]));
	}
	// printf("FLAY");
	std::sort(v.begin(), v.end(), [](auto &p1, auto &p2){return p1.first < p2.first;});
	// printf("FLA2");
	for(int i = 0; i < n; i++){
		if(v[i].first > v[i].second) continue;
		else{
			if(v[i].first > m) break;
			else{
				m += (v[i].second - v[i].first);
			}
		}
	}
	printf("%lld", m);
}