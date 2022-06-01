#include <iostream>
#include <cstdlib>
#include <rd_route/rd_route.h>
#include <unistd.h>

#define RED "\e[31m"
#define GREEN "\e[32m"
#define YELLOW "\e[33m"
#define RESET "\e[0m"

#define CYAN "\e[36m"
#define BLUE "\e[34m"
#define PURPLE "\e[35m"

void*(*MALLOC)(size_t);

//

static void* my_malloc(size_t size)
{
    char buffer[256];
    ssize_t r;

    std::cout <<
        YELLOW "> Memory allocating..."
        GREEN " from " << __builtin_return_address(0) <<
        YELLOW " (" << size << " bytes) ";

    void* retAddress = NULL;

    do
    {
        std::cout << RED " Accept?[y/n]: " RESET;
        std::cout.flush();
        r = read(STDIN_FILENO, buffer, 256);
        if (r > 2 || buffer[1] != '\n')
            continue;
        break;
    }
    while (buffer[0] != 'y' && buffer[0] != 'n');

    if (buffer[0] == 'y')
        retAddress = MALLOC(size);

    std::cout << BLUE " Address : " << retAddress << RESET << std::endl;

    return retAddress;
}

// First entry point of dylib

__attribute__((constructor))
static void load_dylib()
{
    std::cout << PURPLE " ******** WELCOME TO " CYAN "MALLOC " RED "BOMBER " PURPLE "********" RESET << std::endl;
    std::cout << std::endl;

    rd_route(
        reinterpret_cast<void*>(malloc),
        reinterpret_cast<void*>(my_malloc),
        reinterpret_cast<void**>(&MALLOC)
    );
}
