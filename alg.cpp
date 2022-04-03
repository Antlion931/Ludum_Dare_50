#include <iostream>

int main(int argc, char **argv)
{
    int from = std::stoi(argv[1]), to = std::stoi(argv[2]), by = std::stoi(argv[3]);
    for(int i = from; i<= to; i++)
    {
        std::cout << "mv " + std::to_string(i) + ".png " + std::to_string(i + by) + ".png &&";
    }
    std::cout << std::endl;
}