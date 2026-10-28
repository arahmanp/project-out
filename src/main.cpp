#include <cstdlib>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

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

int main(int argc, char *argv[]) {
    if(argc == 1) {
        std::cout << fg["red"] << "error: " << fg["default"]
                  << "You must pass a string!\n";
    } else {
        int nArgs = argc - 1;
        std::vector<std::string> args;

        args.reserve(nArgs);

        for(int i = 1; i < argc; i++) {
            args.push_back(argv[i]);
        }

        std::string fgColor = fg["default"];
        std::string bgColor = bg["default"];
        std::string str;

        int idx = 0;
        while(idx < nArgs) {
            if(args[idx] == "--fg-color") {
                if(idx == nArgs - 1) {
                    std::cout << bg["red"] << fg["white"] << "ERR"
                              << bg["default"] << fg["default"];
                    std::cout << " Can't find the color!\n";

                    exit(1);
                } else if(!fg.contains(args[idx + 1])) {
                    std::cout << bg["red"] << fg["white"] << "ERR"
                              << bg["default"] << fg["default"];
                    std::cout << " Can't find color \'" << args[idx + 1]
                              << "\'!\n";

                    exit(1);
                } else {
                    fgColor = fg[args[idx + 1]];
                    idx += 2;
                }
            } else if(args[idx] == "--bg-color") {
                if(idx == nArgs - 1) {
                    std::cout << bg["red"] << fg["white"] << "ERR"
                              << bg["default"] << fg["default"];
                    std::cout << " Can't find the color!\n";

                    exit(1);
                } else if(!bg.contains(args[idx + 1])) {
                    std::cout << bg["red"] << fg["white"] << "ERR"
                              << bg["default"] << fg["default"];
                    std::cout << " Can't find color \'" << args[idx + 1]
                              << "\'!\n";

                    exit(1);
                } else {
                    bgColor = bg[args[idx + 1]];
                    idx += 2;
                }
            } else {
                str = args[idx];
                idx++;
            }
        }

        std::cout << fgColor << bgColor << str << '\n';
        std::cout << fg["default"] << bg["default"];
    }
}