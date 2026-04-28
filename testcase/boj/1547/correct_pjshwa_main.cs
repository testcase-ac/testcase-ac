using System;
using System.Linq;

class P{
	static string r(){
		return Console.ReadLine();
	}

	static int i(string s){
		return int.Parse(s);
	}

	static void Main(){
		int n = i(r());
		int cup = 1;
		foreach(var j in Enumerable.Range(1,n)){
			var args = r().Split().Select(i).ToArray();
			if (args[0] == args[1]) continue;
			else {
				var s = args.Sum();
				if (s == 3) {
					if (cup == 1) cup =2;
					else if (cup == 2) cup = 1;
				}
				else if (s == 4) {
					if (cup == 1) cup =3;
					else if (cup == 3) cup = 1;
				}
				else if (s == 5) {
					if (cup == 2) cup =3;
					else if (cup == 3) cup = 2;
				}
			}
		}
		Console.WriteLine(cup);
	}
}