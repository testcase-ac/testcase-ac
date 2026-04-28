macro_rules! parse_line { ($($t: ty),+) => ({
  let mut line = String::new();
  std::io::stdin().read_line(&mut line).unwrap();
  let mut iter = line.split_whitespace();
  ($(iter.next().unwrap().parse::<$t>().unwrap()),+)
})}

fn main() {
  let (n1, k1, n2, k2) = parse_line!(u32, u32, u32, u32);
  println!("{}", n1 * k1 + n2 * k2);
}
