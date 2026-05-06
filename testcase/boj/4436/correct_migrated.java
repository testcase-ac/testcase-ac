import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.HashSet;

public class Main {

	public static void main(String[] args) throws IOException{
		// TODO Auto-generated method stub
		
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringBuilder sb = new StringBuilder();
		
		String input = null;
		
		while((input=br.readLine()) != (null)) {
			long n = Long.parseLong(input);
			
			HashSet<Character> hs = new HashSet<Character>();
			for(int i=0; i<10; i++) hs.add((char)(i+'0'));
			
			long k = 0;
			while(true) {
				k++;
				String str = Long.toString(k*n);
				for(int i=0; i<str.length(); i++) hs.remove(str.charAt(i));
				if(hs.isEmpty()) break;
			}
			
			System.out.println(k);
		}
		
	}

}
