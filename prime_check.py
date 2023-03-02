def check_prime_int64(n: int):
    if n < 2:
        return False
    assert n < 3825123056546413051  # references https://oeis.org/A014233
    jp = [2, 3, 5, 7, 11, 13, 17, 19, 23]
    for p in jp:
        if n % p == 0:
            return n == p

    r = n - 1
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


def check_prime_int32(n: int):
    if n < 2:
        return False
    assert n < 4759123141  # references https://oeis.org/A014233
    jp = [2, 7, 61]
    for p in jp:
        if n % p == 0:
            return n == p

    r = n - 1
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
