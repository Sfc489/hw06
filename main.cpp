#include <cstdlib>
#include <fstream>
#include <iostream>

int main(int argc, char* argv[]) {
    std::cout << "Hello, Main!" << std::endl;
    std::ifstream data{"input.dat"};
    if (!data) {
        std::cerr << "Error opening input.dat..." << std::endl;
        return EXIT_FAILURE;
    }

    int wait;
    int event;

    while (data >> wait >> event) {
        std::cout << "Wait time: " << wait << std::endl;
        std::cout << "Event: " << event << std::endl;
    }

    data.close();
    return EXIT_SUCCESS;
}

