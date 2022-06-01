/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 19:23:11 by smun              #+#    #+#             */
/*   Updated: 2022/06/01 20:05:57 by smun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <unordered_map>
#include <string>
#include <filesystem>
#include <vector>

extern char **environ;

#define RED "\e[31m"
#define GREEN "\e[32m"
#define YELLOW "\e[33m"
#define RESET "\e[0m"

#define CYAN "\e[36m"
#define BLUE "\e[34m"
#define PURPLE "\e[35m"

static void set_dyld_library_path()
{
    const auto libpath = std::filesystem::current_path() / "hooklib" / "testmalloc.dylib";

    setenv("DYLD_INSERT_LIBRARIES", libpath.c_str(), 1);
}

int main(int argc, char *argv[])
{
    std::cout << std::endl;
    std::cout << CYAN "     ::: MALLOC " RED "BOMBER :::" RESET << std::endl;
    std::cout << std::endl;

    if (argc <= 1)
    {
        std::cerr << "Usage:: " << std::endl;
        std::cerr << argv[0] << " [Executable] (Arguments)" << std::endl;
        return EXIT_FAILURE;
    }

    const auto pid = fork();
    if (pid == 0)
        return 0;

    // Make arguments list
    std::vector<char*> arguments;
    for (int i = 1; i < argc; ++i)
        arguments.push_back(argv[i]);
    arguments.push_back(NULL);

    // Set DYLD_LIBRARY_PATH environment variable
    set_dyld_library_path();

    if (-1 == execv(arguments[0], &arguments[0]))
    {
        std::perror("Failed to execv: ");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}