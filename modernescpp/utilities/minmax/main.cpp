#include <algorithm>
#include <iostream>

int main() {

    // Predicate function to compare the absolute value of the square of an int.
    auto absSquareNumComp = [] ( int a, int b ) {
        int x = std::abs( a * a ); 
        int y = std::abs( b * b ); 
        return x < y;
    };

    // std::minmax({initializer list}, comp) => returns a std::pair with first the min and second the max.
    auto result = std::minmax({-1, 2, -3, 4, -5}, absSquareNumComp);
    std::cout << result.first << ',' << result.second << '\n';

    return EXIT_SUCCESS;
}
