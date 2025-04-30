#include "../include/BitcoinExchange.hpp"

int main(int argc, char *argv[]) {
   
    (void)argc;
    (void)argv;

    BitcoinExchange data;

    data.getAndCheckData();

    return 0;

}