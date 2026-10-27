#include <iostream>


auto sinndeslebens() {
    return 42;
}

template<typename T, typename V>
auto add(T a, V b) -> decltype(a + b)   {
    return a + b;
}


int main() {

    double a;
    int b;

    auto c = add(a, b);
    c;
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
