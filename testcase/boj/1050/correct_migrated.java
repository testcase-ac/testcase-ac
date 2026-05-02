import java.util.*;
import java.io.*;

class Node {
	int cnt;
	String ingredient;
	Node(int cnt, String ingredient){
		this.cnt = cnt;
		this.ingredient = ingredient;
	}
}

class Main {
	
	// IO field
	static BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
	static BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
	static StringTokenizer st;

	static void nextLine() throws Exception {st = new StringTokenizer(br.readLine());}
	static int nextInt() {return Integer.parseInt(st.nextToken());}
	static long nextLong() {return Long.parseLong(st.nextToken());}
	static void bwEnd() throws Exception {bw.flush();bw.close();}
	
	// Additional field
	static final int INF = 1000000001;
	
	static int N, M;
	static HashMap<String, Integer> price = new HashMap<>();
	static String[] newIngredients;
	static List<Node>[] expressions;
	static boolean[] clear;
	
	public static void main(String[] args) throws Exception {
		
		ready();
		solve();
	
		bwEnd();
	}
	
	static void ready() throws Exception{

		nextLine();
		N = nextInt();
		M = nextInt();
		for(int i=0;i<N;i++) {
			nextLine();
			price.put(st.nextToken(), nextInt());
		}
		
		newIngredients = new String[M];
		expressions = new List[M];
		clear = new boolean[M];
		for(int i=0;i<M;i++) {
			String[] temp1 = br.readLine().split("=");
			newIngredients[i] = temp1[0];
			
			String[] temp2 = temp1[1].split("\\+");
			expressions[i] = new ArrayList<>();
			for(int j=0;j<temp2.length;j++) {
				int cnt = Integer.parseInt(temp2[j].substring(0,1));
				String ingredient = temp2[j].substring(1,temp2[j].length());
				expressions[i].add(new Node(cnt, ingredient));
			}
		}
		
	}
	
	static void solve() throws Exception{

		boolean change;
		
		do {
			
			change = false;
			for(int i=0;i<M;i++) {
				boolean allIngredientExists = true;
				for(Node node : expressions[i]) {
					allIngredientExists &= price.containsKey(node.ingredient);
				}
				if(!allIngredientExists) continue;
				int res = 0;
				for(Node node : expressions[i]) {
					if(res >= INF) break;
					int value = price.get(node.ingredient);
					for(int k=0;k<node.cnt;k++) {
						if(res >= INF) {
							res = INF;
							break;
						}
						res += value;
					}
				}
				if(price.containsKey(newIngredients[i])) {
					if(res < price.get(newIngredients[i])) {
						price.put(newIngredients[i], res);
						change = true;

					}
				}
				else {
					price.put(newIngredients[i], res);
					change = true;
				}
				
				
			}
			
		}while(change);
		
		if(price.containsKey("LOVE")) bw.write(price.get("LOVE")+"\n");
		else bw.write("-1");
		
	}
	
	
}
