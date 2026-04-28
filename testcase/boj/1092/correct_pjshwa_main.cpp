#include <cstdio>
#include <algorithm>

long long min_req(long long n, int m){
	if(n % m == 0) return n / m;
	else return (n / m) + 1;
}

int main(){
	int n;
	scanf("%d", &n);

	int cranes[n];
	for(auto &x : cranes){
		scanf("%d", &x);
	}

	std::sort(cranes, cranes + n, [](int x, int y){return x > y;});

	long long viable[n];

	for(auto &x : viable){
		x = 0;
	}

	int m;
	scanf("%d", &m);

	int boxes[m];
	for(auto &x : boxes){
		scanf("%d", &x);
	}

	std::sort(boxes, boxes + m, [](int x, int y){return x > y;});

	if(cranes[0] < boxes[0]) printf("-1\n"); // impossible
	else {
		for(auto &x : boxes){
			int order = 0;
			while(x <= cranes[order + 1]){
				order++;
				if(order == n - 1) break;
			}
			viable[order]++;
		}
		long long min_cranes = 0;

		for(int i = 0; i < n - 1; i++){
			viable[i+1] += viable[i];
		}

		for(int i = 1; i <= n; i++){
			long long temp = min_req(viable[i-1], i);
			if (temp > min_cranes) min_cranes = temp;
		}

		printf("%lld\n", min_cranes);
	}
}