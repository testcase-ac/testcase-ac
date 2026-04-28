using System; using System.Linq;
class P{

	P(){}

	void Run(){
		Console.ReadLine();
		var args = Console.ReadLine().Split();
		int condition = int.Parse(Console.ReadLine());
		int count = args.Select(int.Parse).Where(x => x == condition).Count();

		Console.WriteLine(count);
	}

	static void Main(){
		(new P()).Run();

	}
}