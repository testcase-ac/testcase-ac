macro_rules! parse_line { ($($t: ty),+) => ({
  let mut line = String::new();
  std::io::stdin().read_line(&mut line).unwrap();
  let mut iter = line.split_whitespace();
  ($(iter.next().unwrap().parse::<$t>().unwrap()),+)
})}

fn main() {
  let (k, q, l, b, n, p) = parse_line!(i8, i8, i8, i8, i8, i8);
  println!("{} {} {} {} {} {}", 1 - k, 1 - q, 2 - l, 2 - b, 2 - n, 8 - p);
}
