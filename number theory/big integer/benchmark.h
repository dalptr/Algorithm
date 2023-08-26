template<typename F>
void benchmark(F func, const std::string& name) {
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    auto t1 = high_resolution_clock::now();
    func();
    auto t2 = high_resolution_clock::now();
    duration<double, std::milli> ms_double = t2 - t1;
    std::cout << name << "\t\t: " << ms_double.count() << std::endl;
}
