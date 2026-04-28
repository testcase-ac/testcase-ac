#include <cstdio>
#include <vector>
#include <algorithm>

int main(){
	int n, m;
	scanf("%d%d", &n, &m);
	std::vector<int> v;
	for(int i = 0; i < n; i++){
		int pi, li;
		scanf("%d%d", &pi, &li);
		int t_a[pi];
		for(int j = 0; j < pi; j++){
			scanf("%d", &t_a[j]);
		}
		if(pi < li){
			v.push_back(1);
			continue;
		}
		std::sort(t_a, t_a+pi, [](int x, int y){return x > y;});
		v.push_back(t_a[li-1]);
	}
	std::sort(v.begin(), v.end());
	int subjects = 0;
	auto it = v.begin();
	while(it != v.end()){
		
		m -= (*it);
		if(m < 0) break;
		it++;
		subjects++;
	}
	printf("%d", subjects);
}