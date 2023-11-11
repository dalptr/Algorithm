#include<cstdio>

int main() {
    int n;
    scanf("%d", &n);
    const int size = 1 << n;
    char binary[n + 1];
    const auto last = binary + n - 1;
    binary[n] = '\0';
    for (int i = 0; i < size; i++) {
        int num = i ^ (i >> 1);
        char *pointer = last;
        while (num) {
            *pointer-- = (num & 1 ? '1' : '0');
            num >>= 1;
        }
        while (pointer >= binary) {
            *pointer-- = '0';
        }
        puts(binary);
    }
}
