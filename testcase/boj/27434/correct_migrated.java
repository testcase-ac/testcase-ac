import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.math.BigInteger;

public class Main {

	public static void main(String[] args) throws NumberFormatException, IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int N = Integer.parseInt(br.readLine());
		br.close();

		System.out.println(factorial(1, N));
	}

	public static BigInteger factorial(int a, int n) {
		BigInteger num = BigInteger.valueOf(a);
		if (a < n) {
			int b = (a + n) / 2;
			num = factorial(a, b).multiply(factorial(b + 1, n));
		}
		return num;
	}
}
