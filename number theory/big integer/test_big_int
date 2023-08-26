void test() {
    auto test_assign = [&]() -> void {
        INTEGER a("133");
        INTEGER b = 133;
        long long t = 133;
        INTEGER c = t;
        int q = 133;
        INTEGER d = q;
        for (auto inter: {b, c, d}) {
            assert(a == inter);
        }
        long long x = a.to_long();
        assert(x == t);
    };
    auto test_abs = [&]() -> void {
        INTEGER a = -5;
        INTEGER b = 5;
        assert(a.abs() == b);
    };
    auto test_add = [&]() {
        INTEGER a = 1;
        INTEGER b = 2;
        INTEGER c = 3;
        a += b;
        assert(a == c);
    };
    auto test_gcd_lcm = [&]()->void {
        INTEGER a = 12, b = 8;
        assert(gcd(a,b) == 4);
        assert(lcm(a,b) == 24);
    };
    auto test_read = [&]()->void {
        const INTEGER a1 = 123, a2 = -123;
        INTEGER b("0123"), c("-0123");
        assert(a1 == b);
        assert(a2 == c);
    };
    auto test_negative = [&]()->void {
        const INTEGER a1 = 123, a2 = -123;
        INTEGER c = -a2;
        assert(c == a1);
        INTEGER d = -a1;
        assert(d == a2);
    };
    auto test_is_zero = [&]()->void {
        INTEGER a = 0, b("000"), c("-00000000");
        INTEGER d = 4, e = 2, f = 2;
        INTEGER g = d - e - f;
        for(auto candidate: {b,c,g}){
            assert(a == candidate);
        }
    };
    auto test_opr = [&]()->void {
        {
            INTEGER a = 5, b = 7;
            auto tmp = b / a;
            assert(tmp == 1);
            tmp = b % a;
            assert(tmp == 2);
            a += b;
            assert(a == 12);
            a = 5, b = 7;
            a -= b;
            assert(a == -2);
            a = 5, b = 7;
            a *= b;
            assert(a == 35);
            a = 7, b = 2;
            a /= b;
            assert(a == 3);
        }
        {
            INTEGER a = 5;
            long long b = 7;
            a += b;
            assert(a == 12);
            a = 5, b = 7;
            a -= b;
            assert(a == -2);
            a = 5, b = 1e9;
            a *= b;
            assert(a == 5e9);
            a = 7, b = 2;
            a /= b;
            assert(a == 3);
        }
    };
    auto test_compare = [&]()->void {
        INTEGER a("1"), b ("-1"), c("2");
        assert(b < a);
        assert(a < c);
        assert(b < c);
    };
    test_compare();
    test_abs();
    test_assign();
    test_gcd_lcm();
    test_add();
    test_read();
    test_negative();
    test_is_zero();
    test_opr();
}
