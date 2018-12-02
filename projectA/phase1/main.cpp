#include <boost/filesystem.hpp>

#include <cstdlib>
#include <iostream>
using namespace std;
using namespace boost::filesystem;

int main() {
    std::cout << file_size("/home/nthomos/Desktop/NH-Barcode-Reader-Commands.txt") << std::endl;
    return EXIT_SUCCESS;
}
