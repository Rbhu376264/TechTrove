#include <string>

using namespace std;

struct Letter {
    char c;
    string lines[8];
};

struct Banner {
    string message;
    string output[8];
};

void print_banner(Banner);
Banner make_banner(string, Letter*);
Letter* read_font(const char*);
