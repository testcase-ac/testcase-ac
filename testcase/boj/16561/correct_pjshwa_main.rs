// IMPL:parse_line
macro_rules! parse_line { ($($t: ty),+) => ({
  let mut line = String::new();
  std::io::stdin().read_line(&mut line).unwrap();
  let mut iter = line.split_whitespace();
  ($(iter.next().unwrap().parse::<$t>().unwrap()),+)
})}

fn main() {
  let n = parse_line!(u32);
  let borders = n / 3 - 1;

  if borders < 2 {println!("0");}
  else {println!("{}", borders * (borders - 1) / 2);}
}
