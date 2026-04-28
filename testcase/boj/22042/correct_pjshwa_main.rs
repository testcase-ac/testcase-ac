use io::Write;
use std::{io, str, collections::{BTreeSet, BTreeMap}};

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

fn gcd(a: i64, b: i64) -> i64 {
  if b == 0 { a }
  else { gcd(b, a % b) }
}

fn solve(scan: &mut UnsafeScanner<io::StdinLock>, out: &mut io::BufWriter<io::StdoutLock>) {
  let n = scan.token::<usize>();
  let a = (0..n).map(|_| scan.token::<i64>()).collect::<Vec<_>>();
  let sum = a.iter().sum::<i64>();

  let mut cnt = BTreeMap::new();
  for i in 0..n {
    if a[i] >= 100 { continue; }
    *cnt.entry(a[i]).or_insert(0) += 1;
  }

  let mut b = vec![];
  for (k, v) in cnt.iter() {
    let g = *k;
    for _ in 0..(*v.min(&(100 / g))) { b.push(g); }
  }

  let mut v = BTreeSet::new();
  v.insert((0, 0));
  for i in 0..b.len() {
    let mut nv = v.clone();
    for (g, e) in v {
      if e + b[i] < 100 {
        let ng = gcd(g, b[i]);
        nv.insert((ng, e + b[i]));
      }
    }
    v = nv;
  }

  let mut ans = BTreeSet::new();
  for (g, e) in v {
    if e < sum && 100 * (sum - e) % (100 - e) == 0 {
      let u = 100 * (sum - e) / (100 - e);
      if (u * g % 100) == 0 { ans.insert(u); }
    }
  }

  writeln!(out, "{}", ans.len()).ok();
  for e in ans { write!(out, "{} ", e).ok(); }
  writeln!(out).ok();
}

fn main() {
  let (stdin, stdout) = (io::stdin(), io::stdout());
  let mut scan = UnsafeScanner::new(stdin.lock());
  let mut out = io::BufWriter::new(stdout.lock());

  let t = 1;
  // let t = scan.token::<usize>();
  for _ in 0..t {
    solve(&mut scan, &mut out);
  }
}
