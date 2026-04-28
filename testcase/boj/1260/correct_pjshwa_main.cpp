#include <cstdio>
#include <vector>
#include <queue>


class Program {
	std::vector<int> visit_v;
	std::queue<int> search_queue;
	int adj_matrix[1000][1000];
	int n, m, v;
public:
	Program(int n, int m, int v){
		this->n = n;
		this->m = m;
		this->v = v;
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){
				adj_matrix[i][j] = 0;
			}
		}
	}

	bool not_is_in_visit_vector(int v){
		for(auto &x : visit_v){
			if(x == v){
				return false;
			}
		}
		return true;
	}

	void dfs(int v){

		visit_v.push_back(v);

		for(int i = 0; i < n; i++){
			if(adj_matrix[v-1][i] == 1 && not_is_in_visit_vector(i+1)){
				dfs(i+1);
			}
		}
	}

	void bfs(int v){

		visit_v.push_back(v);
		search_queue.push(v);
		while(!search_queue.empty()){
			auto cur_v = search_queue.front();
			for(int i = 0; i < n; i++){
				if(adj_matrix[cur_v-1][i] == 1 && not_is_in_visit_vector(i+1)){
					visit_v.push_back(i+1);
					search_queue.push(i+1);
				}
			}
			search_queue.pop();
		}
		
	}

	void run(){
		
		for(int i = 0; i < m; i++){
			int vertex_1, vertex_2;
			scanf("%d%d", &vertex_1, &vertex_2);
			adj_matrix[vertex_1-1][vertex_2-1] = 1;
			adj_matrix[vertex_2-1][vertex_1-1] = 1;
		}
		
		dfs(v);

		for(auto &x : visit_v)
		{
			printf("%d ", x);
		}

		printf("\n");

		visit_v.clear();

		bfs(v);

		for(auto &x : visit_v)
		{
			printf("%d ", x);
		}


	}
};

int main(){
	int n, m, v;
	scanf("%d%d%d", &n, &m, &v);
	(new Program(n, m, v))->run();
}