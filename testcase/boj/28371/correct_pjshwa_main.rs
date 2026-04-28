use io::Write;
use std::{io, str, collections::VecDeque};

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

const INF: usize = 0x3f3f3f3f;

fn gcd(x: usize, y: usize) -> usize {
  if y == 0 { x } else { gcd(y, x % y) }
}

fn solve(scan: &mut UnsafeScanner<io::StdinLock>, out: &mut io::BufWriter<io::StdoutLock>) {
  let (n, m, k) = (scan.token::<usize>(), scan.token::<usize>(), scan.token::<usize>());
  let a = (0..k).map(|_| scan.token::<usize>()).collect::<Vec<_>>();
  
  let mut adj = vec![vec![]; n + 1];
  for _ in 0..m {
    let (u, v) = (scan.token::<usize>(), scan.token::<usize>());
    adj[u].push(v); adj[v].push(u);
  }

  let mut q = VecDeque::new();
  let (mut dist1, mut distn) = (vec![INF; n + 1], vec![INF; n + 1]);

  q.push_back(1); dist1[1] = 0;
  while let Some(u) = q.pop_front() {
    for &v in &adj[u] {
      if dist1[v] == INF {
        dist1[v] = dist1[u] + 1;
        q.push_back(v);
      }
    }
  }
  q.push_back(n); distn[n] = 0;
  while let Some(u) = q.pop_front() {
    for &v in &adj[u] {
      if distn[v] == INF {
        distn[v] = distn[u] + 1;
        q.push_back(v);
      }
    }
  }

  let mut rsum = 0;
  for e in &a { rsum += distn[*e]; }

  let mut unom = (k - 1) * dist1[n];
  for e in &a {
    unom = unom.min((k - 1) * dist1[*e] + (rsum - distn[*e]));
  }
  let g = gcd(unom, k - 1);
  writeln!(out, "{}/{}", unom / g, (k - 1) / g).ok();
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
