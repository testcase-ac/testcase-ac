import java.util.*;
import java.io.*;

class Main {
	
	// IO field
	static BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
	static BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
	static StringTokenizer st = new StringTokenizer("");

	static void nextLine() throws Exception {st = new StringTokenizer(br.readLine());}
	static String nextToken() throws Exception {
		while(!st.hasMoreTokens()) nextLine();
		return st.nextToken();
	}
	static int nextInt() throws Exception { return Integer.parseInt(nextToken()); }
	static long nextLong() throws Exception { return Long.parseLong(nextToken()); }
	static double nextDouble() throws Exception { return Double.parseDouble(nextToken()); }
	static void bwEnd() throws Exception {bw.flush();bw.close();}
	
	// Additional field
	
	static class Node{
		long cnt, left, right, diff;
		int val;
		Node(long cnt, int val, long left, long right, long diff){
			this.cnt = cnt;
			this.val = val;
			this.left = left;
			this.right = right;
			this.diff = diff;
		}
	}
	
	static int L, N;
	static int[] A;
	static int INF = 1010101010;
	static TreeSet<Integer> V;
	
	public static void main(String[] args) throws Exception {
		
		ready();
		solve();
	
		bwEnd();
		
	}
	
	static void ready() throws Exception{
		
		L = nextInt();
		A = new int[L];
		for(int i=0;i<L;i++) A[i] = nextInt();
		N = nextInt();
		V = new TreeSet<>();
		
	}
	
	static void solve() throws Exception{
		
		PriorityQueue<Node> PQ = new PriorityQueue<>((a,b) -> {
			if(a.right == INF) {
				if(b.right == INF) return a.val-b.val;
				return 1;
			}
			if(b.right == INF) return -1;
			if(a.cnt == b.cnt) return a.val-b.val;
			if(a.cnt < b.cnt) return -1;
			return 1;
		});
		
		Arrays.sort(A);
		List<Integer> zeros = new ArrayList<>();
		if(A[0] > 2) {
			PQ.add(new Node(cal(1,A[0]-1,1), 1, 1, A[0]-1, 1));
			PQ.add(new Node(cal(1,A[0]-1,A[0]-1), A[0]-1, 1, A[0]-1, -1));
		}
		else if(A[0] == 2) zeros.add(1);
		for(int i=0;i<L;i++) zeros.add(A[i]);
		PQ.add(new Node(Long.MAX_VALUE, A[L-1]+1, A[L-1]+1, INF, 1));
		for(int i=1;i<L;i++) {
			int l = A[i-1]+1, r = A[i]-1;
			int len = r-l;
			if(len < 0) continue;
			if(len == 0) zeros.add(l);
			else {
				PQ.add(new Node(cal(l,r,l), l, l, r, 1));
				PQ.add(new Node(cal(l,r,r), r, l, r, -1));				
			}
		}
		Collections.sort(zeros);
		for(int i:zeros) {
			bw.write(i + " ");
			if(--N == 0) break;
		}
		
		while(N>0) {
			Node now = PQ.poll();
			if(V.contains(now.val)) continue;
			V.add(now.val);
			bw.write(now.val + " ");
			N--;
			Node copy = new Node(now.cnt, now.val, now.left, now.right, now.diff);
			copy.val += copy.diff;
			if(copy.left > copy.val || copy.right < copy.val) continue;
			copy.cnt = cal(copy.left, copy.right, copy.val);
			PQ.add(copy);
		}
		
	}
	
	static long cal(long l, long r, long x) {
		return (x-l+1)*(r-x+1);
	}
	
}
