#include "../include/BitcoinExchange.hpp"

int main(int argc, char *argv[]) {
   
    BitcoinExchange data;
    (void)argc;
    (void)argv;

    if (argc != 2) {
        std::cerr << "Error: Args missing  >./btc [Input file]" << std::endl;
        return 1;
    }


    data.getAndCheckData();
    data.getInputFile(argv[1]);


    return 0;

}