#include <iostream>
#include "Permutation.h"

void print(const std::vector<int>& v) {
    for (int x : v) std::cout << x << " ";
    std::cout << "\n";
}

int main() {
    int n = 10;

    // Test 1: Generate permutation
    std::vector<int> p = Permutation::generate(n);
    std::cout << "Generated permutation:\n";
    print(p);

    // Test 2: Check validity
    std::cout << "Is valid? " << (Permutation::isValid(p) ? "YES" : "NO") << "\n";

    // Test 3: Shuffle again
    Permutation::shuffle(p);
    std::cout << "After shuffle:\n";
    print(p);
    std::cout << "Is valid? " << (Permutation::isValid(p) ? "YES" : "NO") << "\n";

    // Test 4: Reverse a segment
    Permutation::reverseSegment(p, 2, 7);
    std::cout << "After reverse [2..7]:\n";
    print(p);
    std::cout << "Is valid? " << (Permutation::isValid(p) ? "YES" : "NO") << "\n";

    return 0;
}
