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

fn solve() {
  let args = input_integers();
  let n = args[0] as usize;
  let m = args[1] as usize;

  let mut board = vec![vec![' '; m + 1]; n + 1];
  for i in 1..=n {
    let mut s = String::new();
    io::stdin().read_line(&mut s).unwrap();
    s = s.trim().to_string();
    let mut chars = s.chars();

    for j in 1..=m {
      board[i][j] = chars.next().unwrap();
    }
  }

  let mut ans = n * m + 1;
  if n < m {
    let mut pf_col_W = vec![vec![0; m + 1]; n + 1];
    let mut pf_col_A = vec![vec![0; m + 1]; n + 1];
    let mut pf_col_L = vec![vec![0; m + 1]; n + 1];
    let mut pf_col_D = vec![vec![0; m + 1]; n + 1];
    let mut pf_col_O = vec![vec![0; m + 1]; n + 1];

    for j in 1..=m {
      for i in 1..=n {
        pf_col_W[i][j] = pf_col_W[i - 1][j] + if board[i][j] == 'W' { 1 } else { 0 };
        pf_col_A[i][j] = pf_col_A[i - 1][j] + if board[i][j] == 'A' { 1 } else { 0 };
        pf_col_L[i][j] = pf_col_L[i - 1][j] + if board[i][j] == 'L' { 1 } else { 0 };
        pf_col_D[i][j] = pf_col_D[i - 1][j] + if board[i][j] == 'D' { 1 } else { 0 };
        pf_col_O[i][j] = pf_col_O[i - 1][j] + if board[i][j] == 'O' { 1 } else { 0 };
      }
    }

    for i1 in 1..=n {
      for i2 in i1..=n {
        let (mut wc, mut ac, mut lc, mut dc, mut oc) = (0, 0, 0, 0, 0);

        let mut rj = 0;
        for lj in 1..=m {
          while rj < m {
            if wc > 0 && ac > 0 && lc > 0 && dc > 0 && oc > 0 { break; }

            rj += 1;
            wc += pf_col_W[i2][rj] - pf_col_W[i1 - 1][rj];
            ac += pf_col_A[i2][rj] - pf_col_A[i1 - 1][rj];
            lc += pf_col_L[i2][rj] - pf_col_L[i1 - 1][rj];
            dc += pf_col_D[i2][rj] - pf_col_D[i1 - 1][rj];
            oc += pf_col_O[i2][rj] - pf_col_O[i1 - 1][rj];
          }

          if wc > 0 && ac > 0 && lc > 0 && dc > 0 && oc > 0 {
            ans = ans.min((i2 - i1 + 1) * (rj - lj + 1));
          }

          wc -= pf_col_W[i2][lj] - pf_col_W[i1 - 1][lj];
          ac -= pf_col_A[i2][lj] - pf_col_A[i1 - 1][lj];
          lc -= pf_col_L[i2][lj] - pf_col_L[i1 - 1][lj];
          dc -= pf_col_D[i2][lj] - pf_col_D[i1 - 1][lj];
          oc -= pf_col_O[i2][lj] - pf_col_O[i1 - 1][lj];
        }
      }
    }
  }
  else {
    let mut pf_row_W = vec![vec![0; m + 1]; n + 1];
    let mut pf_row_A = vec![vec![0; m + 1]; n + 1];
    let mut pf_row_L = vec![vec![0; m + 1]; n + 1];
    let mut pf_row_D = vec![vec![0; m + 1]; n + 1];
    let mut pf_row_O = vec![vec![0; m + 1]; n + 1];

    for i in 1..=n {
      for j in 1..=m {
        pf_row_W[i][j] = pf_row_W[i][j - 1] + if board[i][j] == 'W' { 1 } else { 0 };
        pf_row_A[i][j] = pf_row_A[i][j - 1] + if board[i][j] == 'A' { 1 } else { 0 };
        pf_row_L[i][j] = pf_row_L[i][j - 1] + if board[i][j] == 'L' { 1 } else { 0 };
        pf_row_D[i][j] = pf_row_D[i][j - 1] + if board[i][j] == 'D' { 1 } else { 0 };
        pf_row_O[i][j] = pf_row_O[i][j - 1] + if board[i][j] == 'O' { 1 } else { 0 };
      }
    }

    for j1 in 1..=m {
      for j2 in j1..=m {
        let (mut wc, mut ac, mut lc, mut dc, mut oc) = (0, 0, 0, 0, 0);

        let mut ri = 0;
        for li in 1..=n {
          while ri < n {
            if wc > 0 && ac > 0 && lc > 0 && dc > 0 && oc > 0 { break; }

            ri += 1;
            wc += pf_row_W[ri][j2] - pf_row_W[ri][j1 - 1];
            ac += pf_row_A[ri][j2] - pf_row_A[ri][j1 - 1];
            lc += pf_row_L[ri][j2] - pf_row_L[ri][j1 - 1];
            dc += pf_row_D[ri][j2] - pf_row_D[ri][j1 - 1];
            oc += pf_row_O[ri][j2] - pf_row_O[ri][j1 - 1];
          }

          if wc > 0 && ac > 0 && lc > 0 && dc > 0 && oc > 0 {
            ans = ans.min((j2 - j1 + 1) * (ri - li + 1));
          }

          wc -= pf_row_W[li][j2] - pf_row_W[li][j1 - 1];
          ac -= pf_row_A[li][j2] - pf_row_A[li][j1 - 1];
          lc -= pf_row_L[li][j2] - pf_row_L[li][j1 - 1];
          dc -= pf_row_D[li][j2] - pf_row_D[li][j1 - 1];
          oc -= pf_row_O[li][j2] - pf_row_O[li][j1 - 1];
        }
      }
    }
  }

  if ans == n * m + 1 {
    println!("impossible");
  }
  else {
    println!("{}", ans);
  }

}

fn main() {
  let t = 1;
  for i in 0..t {
    solve();
  }
}
