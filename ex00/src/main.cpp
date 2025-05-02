#include "../include/BitcoinExchange.hpp"

int main(int argc, char *argv[]) {
   
    BitcoinExchange data;
    (void)argc;
    (void)argv;

    if ((argc != 2) && (argc != 3 || std::string(argv[1]) != "-D"))  {
        std::cerr << "Error: Args missing " << std::endl 
        << "usage: ./btc [file ...]" << std::endl
        << "usage: ./btc [-D] [file ...]" << std::endl;
        return 1;
    }


    if (argc == 2) {
        data.getAndCheckData();
        data.getInputFile(argv[1]);
    } else {
        data.getAndCheckData(argv[1]);
        data.getInputFile(argv[2]);
    }



    return 0;

}