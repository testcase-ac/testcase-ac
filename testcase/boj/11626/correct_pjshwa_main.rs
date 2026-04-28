use io::Write;
use std::{io, str};

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

struct SegmentTree {
  tree: Vec<i64>,
  bias: usize,
}

impl SegmentTree {
  fn new(n: usize) -> Self {
    Self {
      tree: vec![0; (n + 1) * 4],
      bias: {
        let mut bias = 1;
        while bias < (n + 1) { bias *= 2; }
        bias
      },
    }
  }

  fn add(&mut self, idx: usize, val: i64) {
    let mut idx = idx + self.bias;
    self.tree[idx] += val;

    idx /= 2;

    while idx != 0 {
      self.tree[idx] = self.tree[idx * 2] + self.tree[idx * 2 + 1];
      idx /= 2;
    }
  }

  fn query(&mut self, left: usize, right: usize) -> i64 {
    let mut left = left + self.bias;
    let mut right = right + self.bias;
    let mut ret = 0;

    while left < right {
      if (left & 1) != 0 {
        ret += self.tree[left];
        left += 1;
      }
      if (!right & 1) != 0 {
        ret += self.tree[right];
        right -= 1;
      }

      left /= 2;
      right /= 2;
    }

    if left == right { ret += self.tree[left]; }
    ret
  }
}

fn solve(scan: &mut UnsafeScanner<io::StdinLock>, out: &mut io::BufWriter<io::StdoutLock>) {
  let n = scan.token::<usize>();
  let a = (0..n).map(|_| scan.token::<usize>()).collect::<Vec<_>>();

  let mut p = vec![0; n];
  for i in 0..n { p[a[i] - 1] = i; }

  let mut s = SegmentTree::new(n);
  let mut ans = vec![];
  for i in 0..n {
    if s.query(p[i], n - 1) > 0 { ans.push(i + 1); }
    s.add(p[i], 1);
  }

  writeln!(out, "{}", ans.len()).ok();
  for e in ans { writeln!(out, "{}", e).ok(); }
}

fn main() {
  let (stdin, stdout) = (io::stdin(), io::stdout());
  let mut scan = UnsafeScanner::new(stdin.lock());
  let mut out = io::BufWriter::new(stdout.lock());

  // let t = 1;
  let t = scan.token::<usize>();
  for _ in 0..t {
    solve(&mut scan, &mut out);
  }
}
