#pragma once
#include <string>
using namespace std;

class IpDetector {
public:
    // I don't expect this do do anything
    IpDetector();
    // Get the first potential IP address
    // Set value of input to remainder of string.
    string GetPotentialIpString(string& input);
    bool extractIPv4(const string& str, unsigned long& outAddress, int& outPort);
private:
    bool IsValidCharacter(char c);
};