#include <iostream>
#include <string>
#include "IpDetector.hpp"
using namespace std;

int main() {
    IpDetector detector;
    string input;
    while (true) {
        cout << "Enter an input text:\t";
        getline(cin, input);
        if (input == "END") {
            break;
        }
        unsigned long outputAddress;
        int outputPort;
        bool foundIp = detector.extractIPv4(input, outputAddress, outputPort);
        if (foundIp) {
            // AI was used to write code to form the output string.
            // As defined in prompt1.txt

            // Form the output string
            // ------------------------------------------------------------
            // Build a dotted‑decimal string with an optional port using sprintf
            char ipBuf[50];                      // 4×3 digits + 3 dots + possible ":xxxx" + '\0'
            if (outputPort >= 0) {
                /* Port present – format "a.b.c.d:port" */
                sprintf(ipBuf, "%lu.%lu.%lu.%lu:%d",
                             (outputAddress >> 24) & 0xFF,
                             (outputAddress >> 16) & 0xFF,
                             (outputAddress >> 8 ) & 0xFF,
                             outputAddress        & 0xFF,
                             outputPort);
            } else {
                /* No port – format "a.b.c.d" */
                sprintf(ipBuf, "%lu.%lu.%lu.%lu",
                             (outputAddress >> 24) & 0xFF,
                             (outputAddress >> 16) & 0xFF,
                             (outputAddress >> 8 ) & 0xFF,
                             outputAddress        & 0xFF);
            }

            string ipString(ipBuf);          // optional: convert to std::string for printing
            // ------------------------------------------------------------
            cout << "Extracted IPv4 Address: " << ipString << " ";

            cout << "(decimal value: " << outputAddress << ", port: " << ((outputPort >= 0) ? to_string(outputPort) : "none") << ")" << endl;
        } else {
            cout << "No IPv4 Address found." << endl;
        }

    }
    cout << "Program Terminated." << endl;
    return 0;
}