#include <cstdio>
#include <vector>
#include <algorithm>


int main(void){
	int n;
	scanf("%d", &n);

	int list_a[n], list_a_dp[n];
	for(int i = 0; i < n; i++){
		scanf("%d", &list_a[i]);
		list_a_dp[i] = list_a[i];
	}

	std::sort(list_a, list_a + n);

	std::vector<std::pair<int, int>> v;
	for(int i = 0; i < n; i++){
		v.push_back(std::make_pair(list_a[i], i));
	}

	for(auto &i : list_a_dp){
		for(auto &x : v){
			if(i == x.first){
				printf("%d ", x.second);
				x.first = -1;
				break;
			}
		}
	}
}
