#include <iostream>
#include <array>
#include <iomanip> // ?? std::setw ? std::hex

// ????? GF(2^8) ??????
int gf28_multiply(int a, int b) {
    int result = 0;
    for (int i = 0; i < 8; ++i) {
        if (b & 1) { // ?? b ????? 1
            result ^= a; // ?? a
        }
        b >>= 1; // ?? b
        if (a & 0x80) { // ?? a ????? 1
            a = (a << 1) ^ 0x11B; // ? x^8 + x^4 + x^3 + x + 1
        } else {
            a <<= 1; // ?? a
        }
    }
    return result;
}

// ????????
void generate_gf28_multiply_table() {
    std::array<std::array<int, 256>, 256> gf28_multiply_table;

    // ??????
    for (int i = 0; i < 256; ++i) {
        for (int j = 0; j < 256; ++j) {
            gf28_multiply_table[i][j] = gf28_multiply(i, j);
        }
    }

    // ?????
    std::cout << "GF(2^8) Multiply Table:" << std::endl;
    for (int i = 0; i < 256; ++i) {
        for (int j = 0; j < 256; ++j) {
            std::cout << "0x" << std::hex << std::setw(2) << std::setfill('0') << gf28_multiply_table[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    generate_gf28_multiply_table();
    return 0;
}