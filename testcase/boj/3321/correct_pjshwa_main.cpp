#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>

class queueloader {
	std::queue<int> q;
	bool ready;
public:
	queueloader() : ready(false) {}

	void load(int index, char c){
		if(c == '0'){
			if(ready) q.push(index);
			ready = false;
		}
		else {
			ready = true;
		}
	}

	void peek_and_pop(int index){
		if(index >= q.front()) q.pop();
	}

	int top(){
		return q.front();
	}

	void finalize(int n){
		if(ready) q.push(n);
		ready = false;
	}
	void flush(){
		// debug purposes
		while(!q.empty()){
			printf("%d\n", q.front());
			q.pop();
		}
		
	}
};

int main(){
	int n, m;
	scanf("%d%d", &n, &m);
	char board[n][m+1]; // last digit for null
	std::vector<queueloader*> v;
	for(int j = 0; j < m; j++){
		v.push_back(new queueloader());
	}
	for(int i = 0; i < n; i++){
		scanf("%s", board[i]);
		for(int j = 0; j < m; j++){
			v[j]->load(i, board[i][j]);
		}
	} // read the matrix
	for(int j = 0; j < m; j++){
		v[j]->finalize(n);
	}
	int max_size = 0;

	for(int i = 0; i < n; i++){
		int sizearray[m+1];
		for(int j = 0; j < m; j++){ // search down from each row to find the highest score
			
			if(board[i][j] == '0') sizearray[j] = 0;
			else{
				v[j]->peek_and_pop(i);
				sizearray[j] = v[j]->top() - i;
			}
		}
		sizearray[m] = 0;
		std::sort(sizearray, sizearray+m+1, [](int x, int y){return x > y;});
		int size = 0;
		for(int j = 0; j < m; j++){
			if(sizearray[j] == sizearray[j+1]) continue;
			int temp_size = (j+1) * sizearray[j];
			if(temp_size > size) size = temp_size;
		}
		if(max_size < size) max_size = size;
		if(max_size > m * (n - i - 1)) break;
	}
	printf("%d", max_size);
}