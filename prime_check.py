candidates: list[int] = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41]


def isPrime(n: int) -> bool:
    if n < 2:
        return False

    for prime in candidates:
        if n % prime == 0:
            return n == prime

    r: int = n - 1
    e: int = 0
    while not r & 1:
        r >>= 1
        e = e + 1

    for prime in candidates:
        x: int = pow(prime, r, n)
        for t in range(e):
            if x <= 1:
                break
            y: int = x * x % n
            if y == 1 and x != n - 1:
                return False
            x = y
        if x != 1:
            return False

    return True
