#include <cstdlib>
#include <iostream>
#include <thread>

int main() {
    using std::cout;
    using std::endl;
    const unsigned int numberOfCores = std::thread::hardware_concurrency();
    cout << "This system can run " << numberOfCores << " concurrent tasks." << endl;
    return EXIT_SUCCESS;
}