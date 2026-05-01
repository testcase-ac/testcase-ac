use std::io::{BufRead, stdin};

fn main() {
    let mut lines = stdin().lock().lines();

    let n: usize = lines.next().unwrap().unwrap().trim().parse().unwrap();

    let mut board = [[0; 20]; 20];
    let mut max = 0;

    for i in 0..n {
        for (j, s) in lines.next().unwrap().unwrap().trim().split_whitespace().enumerate() {
            board[i][j] = s.parse().unwrap();
            max = max.max(board[i][j]);
        }
    }

    print!("{}", bt(n, &mut board, max, &mut max, 10));
}

fn bt(n: usize, board: &mut [[u32; 20]; 20], best: u32, max: &mut u32, depth: u32,) -> u32 {
    if depth == 0 {
        *max = best.max(*max);
        return best;
    }

    if best << depth <= *max {
        return best;
    }

    let backup = *board;
    let mut ret = best;

    let (moved, nb) = up(n, board, best);
    if moved {
        ret = ret.max(bt(n, board, nb, max, depth - 1));
    }
    *board = backup;

    let (moved, nb) = down(n, board, best);
    if moved {
        ret = ret.max(bt(n, board, nb, max, depth - 1));
    }
    *board = backup;

    let (moved, nb) = right(n, board, best);
    if moved {
        ret = ret.max(bt(n, board, nb, max, depth - 1));
    }
    *board = backup;

    let (moved, nb) = left(n, board, best);
    if moved {
        ret = ret.max(bt(n, board, nb, max, depth - 1));
    }

    ret
}

fn slide_line(line: &mut [u32], best: &mut u32) -> bool {
    let n = line.len();

    let mut tmp = [0; 20];
    let mut k = 0;
    for i in 0..n {
        if line[i] != 0 {
            tmp[k] = line[i];
            k += 1;
        }
    }

    let mut merged = [0; 20];
    let mut m = 0;
    let mut i = 0;
    while i < k {
        if i + 1 < k && tmp[i] == tmp[i + 1] {
            let v = tmp[i] * 2;
            merged[m] = v;
            if v > *best {
                *best = v;
            }
            m += 1;
            i += 2;
        } else {
            merged[m] = tmp[i];
            m += 1;
            i += 1;
        }
    }

    while m < n {
        merged[m] = 0;
        m += 1;
    }

    let mut changed = false;
    for i in 0..n {
        if line[i] != merged[i] {
            changed = true;
            line[i] = merged[i];
        }
    }

    changed
}

fn up(n: usize, board: &mut [[u32; 20]; 20], mut best: u32) -> (bool, u32) {
    let mut moved = false;

    for j in 0..n {
        let mut line = [0; 20];
        for i in 0..n {
            line[i] = board[i][j];
        }

        if slide_line(&mut line[..n], &mut best) {
            moved = true;
            for i in 0..n {
                board[i][j] = line[i];
            }
        }
    }

    (moved, best)
}

fn down(n: usize, board: &mut [[u32; 20]; 20], mut best: u32) -> (bool, u32) {
    let mut moved = false;

    for j in 0..n {
        let mut line = [0; 20];
        for i in 0..n {
            line[i] = board[n - 1 - i][j];
        }

        if slide_line(&mut line[..n], &mut best) {
            moved = true;
            for i in 0..n {
                board[n - 1 - i][j] = line[i];
            }
        }
    }

    (moved, best)
}

fn right(n: usize, board: &mut [[u32; 20]; 20], mut best: u32) -> (bool, u32) {
    let mut moved = false;

    for i in 0..n {
        let mut line = [0; 20];
        for j in 0..n {
            line[j] = board[i][n - 1 - j];
        }

        if slide_line(&mut line[..n], &mut best) {
            moved = true;
            for j in 0..n {
                board[i][n - 1 - j] = line[j];
            }
        }
    }

    (moved, best)
}

fn left(n: usize, board: &mut [[u32; 20]; 20], mut best: u32) -> (bool, u32) {
    let mut moved = false;

    for i in 0..n {
        let mut line = [0; 20];
        for j in 0..n {
            line[j] = board[i][j];
        }

        if slide_line(&mut line[..n], &mut best) {
            moved = true;
            for j in 0..n {
                board[i][j] = line[j];
            }
        }
    }

    (moved, best)
}
