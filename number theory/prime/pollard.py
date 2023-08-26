import math
import random


class PollardRho:
    ans: dict[int, int] = {}
    candidates: list[int] = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41]

    @staticmethod
    def mul(a: int, b: int, p: int) -> int:
        a %= p
        b %= p
        q = a * b // p
        r: int = (a * b) - (q * p)
        while r < 0:
            r += p
        while r >= p:
            r -= p
        return r

    def f(self, a: int, num: int) -> int:
        return (self.mul(a, a, num) + 1) % num

    def print_factor(self) -> None:
        for key in self.ans:
            print("%d^%d " % (key, self.ans[key]), end='')

        self.ans.clear()

    def is_prime(self, a: int) -> bool:
        if a < 2:
            return False

        for prime in self.candidates:
            if a % prime == 0:
                return a == prime

        r: int = a - 1
        e: int = 0
        while not r & 1:
            r >>= 1
            e += 1

        for prime in self.candidates:
            x: int = pow(prime, r, a)
            for t in range(e):
                if x < 2:
                    break
                y: int = x * x % a
                if y == 1 and x != a - 1:
                    return False
                x = y
            if x != 1:
                return False

        return True

    def find_factor(self, num: int) -> int:
        x: int = random.randint(0, num - 1) + 2
        y = x
        p = 1
        while p == 1:
            x = self.f(x, num)
            y = self.f(self.f(y, num), num)
            p = math.gcd(abs(x - y), num)
        return p

    def increase(self, val: int) -> None:
        if val in self.ans:
            self.ans[val] += 1
        else:
            self.ans[val] = 1

    def native_factorize(self, num: int) -> None:
        i: int = 2
        while i * i <= num:
            while num % i == 0:
                self.increase(i)
                num //= i
            i += 1

        if num > 1:
            self.increase(num)

    def factorize(self, num: int) -> None:
        if num <= 1000000:
            self.native_factorize(num)
            return

        if self.is_prime(num):
            self.increase(num)
            return

        p = 0
        while p == 0 or p == num:
            p = self.find_factor(num)

        self.factorize(num // p)
        self.factorize(p)
