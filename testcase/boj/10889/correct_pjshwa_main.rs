// IMPL:parse_line
macro_rules! parse_line { ($($t: ty),+) => ({
  let mut line = String::new();
  std::io::stdin().read_line(&mut line).unwrap();
  let mut iter = line.split_whitespace();
  ($(iter.next().unwrap().parse::<$t>().unwrap()),+)
})}

fn main() {
  let x = parse_line!(i32);
  println!("{}", 111 * x * x + 11 * x + 1);
}
