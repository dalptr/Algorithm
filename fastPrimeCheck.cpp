#include<bits/stdc++.h>

using namespace std;

long long mulModulo(long long a, long long b, long long c) {
    long long x = 0, y = a % c;
    while (b != 0) {
        if (b & 1) {
            x = (x + y) % c;
        }
        y = (y << 1) % c;
        b >>= 1;
    }
    return x % c;
}

long long fastPower(long long base, long long exponent, long long modulo) {
    long long result = 1;
    while (exponent != 0) {
        if (exponent & 1) {
            result = mulModulo(result, base, modulo);
        }
        base = mulModulo(base, base, modulo);
        exponent >>= 1;
    }
    return result;
}

bool isPrime(long long n) {
    if (n < 2) return false;
    long long d = n - 1;
    int s = 0;
    while (d % 2 == 0) {
        s++;
        d >>= 1;
    }
    int a[9] = {2, 3, 5, 7, 11, 13, 17, 19, 23};
    for (int i = 0; i < 9; i++) {
        bool composite = fastPower(a[i], d, n) != 1;
        if (composite)
            for (int j = 0; j < s; j++) {
                long long fp = fastPower(a[i], (1LL << (long long) j) * d, n);
                if (fp == n - 1) {
                    composite = false;
                    break;
                }
            }
        if (composite) return false;
    }
    return true;
}

int main() {
    cout << isPrime(776102473077477571);
}
