#include <iostream>
#include <string>
#include <unordered_map>

// Foreground Colors
std::unordered_map<std::string, std::string> fg = {
    {"black",    "\033[30m"},
    {"red",      "\033[31m"},
    {"green",    "\033[32m"},
    {"yellow",   "\033[33m"},
    {"blue",     "\033[34m"},
    {"magenta",  "\033[35m"},
    {"cyan",     "\033[36m"},
    {"white",    "\033[37m"},
    {"default",  "\033[39m"},
};

// Background Colors
std::unordered_map<std::string, std::string> bg = {
    {"black",    "\033[40m"},
    {"red",      "\033[41m"},
    {"green",    "\033[42m"},
    {"yellow",   "\033[43m"},
    {"blue",     "\033[44m"},
    {"magenta",  "\033[45m"},
    {"cyan",     "\033[46m"},
    {"white",    "\033[47m"},
    {"default",  "\033[49m"},
};

int main() {
    std::cout << fg["magenta"] << bg["red"] << "Hello, world!\n";
}