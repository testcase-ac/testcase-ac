#include <cstdio>
#include <cstring>
#include <queue>
#include <stack>
#include <utility>

std::stack<int> binary(long long integer, int max){
	std::stack<int> b;
	while(b.size() != max){
		b.push((int)(integer % 2LL));
		integer /= 2LL;
	}
	return b;
}

int main(){
	char p[61];
	scanf("%s", p);
	long long k;
	scanf("%lld", &k);
	int l = strlen(p);
	std::queue<std::pair<int, int>> pos_q; // position, type
	for(int i = 0; i < l; i++){
		if(p[i] == '1' || p[i] == '6'){
			pos_q.push(std::make_pair(i, 0));
		}
		else if(p[i] == '2' || p[i] == '7'){
			pos_q.push(std::make_pair(i, 1));
		}
	}
	int s = pos_q.size();
	if(k > (1LL << s)){
		printf("-1");
		return 0;
	}
	auto b = binary(k - 1LL, s);
	while(!b.empty()){
		auto f = pos_q.front();
		if(b.top()) f.second?p[f.first] = '7':p[f.first] = '6';
		else f.second?p[f.first] = '2':p[f.first] = '1';
		b.pop();
		pos_q.pop();
	}
	printf("%s", p);

}