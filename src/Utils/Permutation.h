#ifndef PERMUTATION_H
#define PERMUTATION_H

#include <vector>
#include <cstdlib>   // rand()
#include <ctime>     // time()
#include <utility>   // std::swap

class Permutation {
public:

    // ------------------------------------------------------------
    // Generate a random permutation of 0..n-1
    // (manual Fisher–Yates shuffle)
    // ------------------------------------------------------------
    static std::vector<int> generate(int n) {
        std::vector<int> perm(n);

        // Fill array with 0..n-1
        for (int i = 0; i < n; i++)
            perm[i] = i;

        shuffle(perm);
        return perm;
    }

    // ------------------------------------------------------------
    // Manual shuffle using minimal STL
    // ------------------------------------------------------------
    static void shuffle(std::vector<int>& perm) {
        int n = perm.size();
        srand(time(nullptr));

        for (int i = n - 1; i > 0; i--) {
            int j = rand() % (i + 1);   // 0..i
            std::swap(perm[i], perm[j]);
        }
    }

    // ------------------------------------------------------------
    // Check if valid permutation: contains all 0..n-1 exactly once
    // ------------------------------------------------------------
    static bool isValid(const std::vector<int>& perm) {
        int n = perm.size();
        std::vector<int> seen(n, 0);

        for (int i = 0; i < n; i++) {
            int v = perm[i];
            if (v < 0 || v >= n) return false;
            if (seen[v] == 1) return false;
            seen[v] = 1;
        }
        return true;
    }

    // ------------------------------------------------------------
    // Reverse the segment [l..r]
    // ------------------------------------------------------------
    static void reverseSegment(std::vector<int>& perm, int l, int r) {
        while (l < r) {
            std::swap(perm[l], perm[r]);
            l++;
            r--;
        }
    }
};

#endif
