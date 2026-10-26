
#include "address.h"
#include <sstream>

using namespace std;

string address::address_info() {
    stringstream ss;

    ss << address_line1 << "\n";
    ss << address_line2 << "\n";
    ss << city << "\n";
    ss << state << "\n";
    ss << zip << "\n";

    return ss.str();
}
//implementation code for address struct here
