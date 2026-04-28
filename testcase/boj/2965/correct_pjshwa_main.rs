macro_rules! parse_line { ($($t: ty),+) => ({
  let mut line = String::new();
  std::io::stdin().read_line(&mut line).unwrap();
  let mut iter = line.split_whitespace();
  ($(iter.next().unwrap().parse::<$t>().unwrap()),+)
})}

use std::cmp;

fn main() {
  let (a, b, c) = parse_line!(u8, u8, u8);

  let cnt = cmp::max(c - b, b - a) - 1;
  println!("{}", cnt);
}
