#pragma once
#include <string>
using namespace std;

class IpAddress {
public:
    IpAddress(string form);
    ~IpAddress();
    explicit operator unsigned int() {
        unsigned int toReturn = 0;
        for(int i = 0; i < 4; i++) {
            toReturn <<= 8;
            toReturn += 0xFF & *(this->values + i);
        }
        return toReturn;
    }
    explicit operator string() {
        return this->ToString();
    }
    string ToString();
    int GetPort();
    bool IsPortDefined();
protected:
    int* values;
    int port;
};