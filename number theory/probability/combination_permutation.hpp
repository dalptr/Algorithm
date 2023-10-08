int64_t factorial(int p) {
    int64_t ans = 1;
    for (int i = 2; i <= p; ++i) {
        ans *= i;
    }
    return ans;
}

int64_t combination(int A, int B) {
    if (B < 0 || B > A) return 0;
    if (B > A / 2) B = A - B;
    int64_t ans = 1;
    for (int i = 0; i < B; ++i) {
        ans *= A - i;
    }
    return ans / factorial(B);
}

int64_t permutation(int A, int B) {
    if (B < 0 || B > A) return 0;
    int64_t ans = 1;
    for (int i = 0; i < B; ++i) {
        ans *= A - i;
    }
    return ans;
}
