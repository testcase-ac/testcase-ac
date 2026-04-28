use std::collections::HashMap;

fn main() {
  let stdin = std::io::stdin();
  let mut buf = String::new();

  stdin.read_line(&mut buf).unwrap();
  let mut iter = buf.split_whitespace();

  let n = iter.next().unwrap().parse::<i64>().unwrap();
  let k = iter.next().unwrap().parse::<i64>().unwrap();
  buf.clear();

  let mut sum = 0i64;
  let mut ans = 0i64;
  let mut map = HashMap::new();

  stdin.read_line(&mut buf).unwrap();
  let mut iter = buf.split_whitespace();

  for i in 0..n {
    let m = iter.next().unwrap().parse::<i64>().unwrap();

    sum += m;
    let t: i64 = sum - k * (i + 1);

    if !map.contains_key(&t) {
      map.insert(t, 0);
    }

    ans += map[&t];
    map.insert(t, map[&t] + 1);
  }

  if !map.contains_key(&0) {
    map.insert(0, 0);
  }

  println!("{}", ans + map[&0]);
}
