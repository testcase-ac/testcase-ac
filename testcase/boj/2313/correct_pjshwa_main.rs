use std::{io, str, collections::HashMap};

pub struct UnsafeScanner<R> {
  reader: R,
  buf_str: Vec<u8>,
  buf_iter: str::SplitAsciiWhitespace<'static>,
}

impl<R: io::BufRead> UnsafeScanner<R> {
  pub fn new(reader: R) -> Self {
    Self {
      reader,
      buf_str: vec![],
      buf_iter: "".split_ascii_whitespace(),
    }
  }
  
  pub fn token<T: str::FromStr>(&mut self) -> T {
    loop {
      if let Some(token) = self.buf_iter.next() {
        return token.parse().ok().expect("Failed parse");
      }
      self.buf_str.clear();
      self.reader
          .read_until(b'\n', &mut self.buf_str)
          .expect("Failed read");
      self.buf_iter = unsafe {
        let slice = str::from_utf8_unchecked(&self.buf_str);
        std::mem::transmute(slice.split_ascii_whitespace())
      }
    }
  }
}

fn input_integers() -> Vec<i32> {
  let mut s = String::new();

  io::stdin().read_line(&mut s).unwrap();

  let values: Vec<i32> = s
      .as_mut_str()
      .split_whitespace()
      .map(|s| s.parse().unwrap())
      .collect();

  values
}

#[derive(Clone)]
pub struct Pair {
  pub start: i32,
  pub end: i32,
}

fn main() {
  let n = input_integers()[0] as usize;
  let mut sum = 0 as i64;
  let mut ans = vec![Pair { start: 0, end: 0 }; n];

  for i in 0..n {
    let l = input_integers()[0] as usize;
    let a = input_integers();

    let mut max_so_far = i32::MIN;
    let mut max_ending_here = 0;

    for j in 0..l {
      max_ending_here = max_ending_here + a[j];
      if max_so_far < max_ending_here {
        max_so_far = max_ending_here;
      }
      if max_ending_here < 0 {
        max_ending_here = 0;
      }
    }
    sum += max_so_far as i64;

    let mut acc = 0;
    let mut map = HashMap::new();
    map.insert(0, 0);

    let mut si = -1 as i32;
    let mut ei = -1 as i32;

    for j in 0..l {
      acc += a[j];
      if map.contains_key(&(acc - max_so_far)) {
        if si == -1 || ei - si > j as i32 - map[&(acc - max_so_far)] as i32 {
          si = map[&(acc - max_so_far)] as i32;
          ei = j as i32;
        }
      }

      map.insert(acc, j + 1);
    }

    ans[i] = Pair { start: si + 1, end: ei + 1 };
  }

  println!("{}", sum);
  for i in 0..n {
    println!("{} {}", ans[i].start, ans[i].end);
  }
}
