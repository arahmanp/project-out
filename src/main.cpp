#include <cstdlib>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

// Available Colors
enum class Color {
    Black,
    Red,
    Green,
    Yellow,
    Blue,
    Magenta,
    Cyan,
    White,
    Default,
    Unknown,
};

// Foreground Colors
std::unordered_map<Color, std::string> fg = {
    {Color::Black,    "\033[30m"},
    {Color::Red,      "\033[31m"},
    {Color::Green,    "\033[32m"},
    {Color::Yellow,   "\033[33m"},
    {Color::Blue,     "\033[34m"},
    {Color::Magenta,  "\033[35m"},
    {Color::Cyan,     "\033[36m"},
    {Color::White,    "\033[37m"},
    {Color::Default,  "\033[39m"},
};

// Background Colors
std::unordered_map<Color, std::string> bg = {
    {Color::Black,    "\033[40m"},
    {Color::Red,      "\033[41m"},
    {Color::Green,    "\033[42m"},
    {Color::Yellow,   "\033[43m"},
    {Color::Blue,     "\033[44m"},
    {Color::Magenta,  "\033[45m"},
    {Color::Cyan,     "\033[46m"},
    {Color::White,    "\033[47m"},
    {Color::Default,  "\033[49m"},
};

// Mapping string-to-enum for color
Color stocl(const std::string &str) {
    if(str == "black") return Color::Black;
    if(str == "red") return Color::Red;
    if(str == "green") return Color::Green;
    if(str == "yellow") return Color::Yellow;
    if(str == "blue") return Color::Blue;
    if(str == "magenta") return Color::Magenta;
    if(str == "cyan") return Color::Cyan;
    if(str == "white") return Color::White;

    return Color::Unknown;
}

// Errors
int noArgsErr() {
    std::cout << bg[Color::Red] << fg[Color::White] << "ERROR"
              << bg[Color::Default] << fg[Color::Default]
              << " You must provide at least one argument!\n";

    return 1;
}
int lastFlagErr() {
    std::cout << bg[Color::Red] << fg[Color::White] << "ERROR"
              << bg[Color::Default] << fg[Color::Default]
              << " Flags that require arguments must not be placed at the end!\n";

    return 1;
}
int unknownColorErr(const std::string &color) {
    std::cout << bg[Color::Red] << fg[Color::White] << "ERROR"
              << bg[Color::Default] << fg[Color::Default]
              << " Can't find color \'" << color << "\'!\n";

    return 1;
}
int emptyStrErr() {
    std::cout << bg[Color::Red] << fg[Color::White] << "ERROR"
              << bg[Color::Default] << fg[Color::Default]
              << " You must provide a non-empty string!\n";

    return 1;
}

// Warnings
void onlyWhitespacesStrWarn() {
    std::cout << bg[Color::Yellow] << fg[Color::Black] << "WARNING"
              << bg[Color::Default] << fg[Color::Default]
              << " You have entered a string that contains only whitespace, while also setting the --fg-color flag.\n";
}

// Helpers
bool isOnlyContainsWhitespaces(const std::string &str) {
    for(auto c : str) {
        if(c != ' ') return false;
    }
    return true;
}

int main(int argc, char *argv[]) {
    if(argc == 1) {
        return noArgsErr();
    } else {
        int nArgs = argc - 1;
        std::vector<std::string> args;

        args.reserve(nArgs);

        for(int i = 1; i < argc; i++) {
            args.push_back(argv[i]);
        }

        std::string fgColor = fg[Color::Default];
        std::string bgColor = bg[Color::Default];
        std::string str = "";

        int idx = 0;
        while(idx < nArgs) {
            if(args[idx] == "--fg-color") {
                if(idx == nArgs - 1) {
                    return lastFlagErr();
                } else if(!fg.contains(stocl(args[idx + 1]))) {
                    return unknownColorErr(args[idx + 1]);
                } else {
                    fgColor = fg[stocl(args[idx + 1])];
                    idx += 2;
                }
            } else if(args[idx] == "--bg-color") {
                if(idx == nArgs - 1) {
                    return lastFlagErr();
                } else if(!bg.contains(stocl(args[idx + 1]))) {
                    return unknownColorErr(args[idx + 1]);
                } else {
                    bgColor = bg[stocl(args[idx + 1])];
                    idx += 2;
                }
            } else {
                str = args[idx];
                idx++;
            }
        }

        if(str.empty()) return emptyStrErr();

        if(isOnlyContainsWhitespaces(str) && fgColor != fg[Color::Default]) onlyWhitespacesStrWarn();

        std::cout << fgColor << bgColor << str << '\n';
        std::cout << fg[Color::Default] << bg[Color::Default];
    }
}