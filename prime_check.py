import math

maxN: int = math.pow(10, 24.52).__int__()
jp: list[int] = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41]


def isPrime(n: int) -> bool:
    if n < 2:
        return False
    assert n < maxN

    for p in jp:
        if n % p == 0:
            return n == p

    r: int = n - 1
    e: int = 0
    while ~r & 1:
        r >>= 1
        e = e + 1

    for p in jp:
        x = pow(p, r, n)
        t = 0
        while t < e and x > 1:
            y: int = x * x % n
            if y == 1 and x != n - 1:
                return False
            x = y
            t = t + 1
        if x != 1:
            return False

    return True
