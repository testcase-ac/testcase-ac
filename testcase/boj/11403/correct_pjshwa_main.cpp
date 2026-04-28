#include <cstdio>


class Program {
	int visit[100] = {0};
	int adj_matrix[100][100];
	int n;
public:
	Program(int n){
		this->n = n;
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){
				adj_matrix[i][j] = 0;
			}
		}
	}
	void dfs(int v){

		visit[v]++;

		for(int i = 0; i < n; i++){
			if(adj_matrix[v][i] == 1 && visit[i] < 2){
				dfs(i);
			}
		}
	}

	void run(){
		
		int path_matrix[100][100] = {0};

		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){
				scanf("%d", &this->adj_matrix[i][j]);
			}	
		}

		for(int i = 0; i < n; i++){
			dfs(i);
			for(int j = 0; j < n; j++){
				if(i == j){
					if(visit[j] >= 2) path_matrix[i][j] = 1;
				}
				else{
					if(visit[j] >= 1) path_matrix[i][j] = 1;
				}
				visit[j] = 0;
			}
		}
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){
				printf("%d ", path_matrix[i][j]);
			}	
			printf("\n");
		}
	}
};

int main(){
	int n;
	scanf("%d", &n);
	(new Program(n))->run();
}