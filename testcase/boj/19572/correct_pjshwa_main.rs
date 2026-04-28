// IMPL:parse_line
macro_rules! parse_line { ($($t: ty),+) => ({
  let mut line = String::new();
  std::io::stdin().read_line(&mut line).unwrap();
  let mut iter = line.split_whitespace();
  ($(iter.next().unwrap().parse::<$t>().unwrap()),+)
})}

fn main() {
  let (d1, d2, d3) = parse_line!(i32, i32, i32);
  let a2 = d1 + d2 - d3;
  let b2 = d1 + d3 - d2;
  let c2 = d3 + d2 - d1;

  if a2 > 0 && b2 > 0 && c2 > 0 {
    println!(
      "1\n{}.{} {}.{} {}.{}",
      a2 / 2, if a2 % 2 == 0 {0} else {5},
      b2 / 2, if b2 % 2 == 0 {0} else {5},
      c2 / 2, if c2 % 2 == 0 {0} else {5}
    )
  }
  else {println!("-1");}
}
