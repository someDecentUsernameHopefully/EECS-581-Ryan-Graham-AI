#include <string>
#include <stdexcept>
#include "IpAddress.hpp"
using namespace std;

// This entire constructor has been AI-generated.
IpAddress::IpAddress(std::string form) {
    /* ---------- Allocate storage ------------------------------------ */
    this->values = new int[4];
    this->port   = -1;          // “no port” sentinel

    const char* s  = form.c_str();      // raw C‑style string
    size_t      len = form.size();
    size_t      i   = 0;                 // current index in the string

    /* ---------- Parse the four octets -------------------------------- */
    for (int part = 0; part < 4; ++part) {
        if (i >= len)
            throw std::invalid_argument("IP address too short");

        int value      = 0;
        int digits     = 0;
        bool leadingZero = false;

        /* read the numeric characters of this octet */
        while (i < len && s[i] >= '0' && s[i] <= '9') {
            if (digits == 0) {                // first digit
                leadingZero = (s[i] == '0');
            } else {
                /* once we have more than one digit, a leading zero is forbidden */
                if (leadingZero)
                    throw std::invalid_argument("Octet has leading zeros");
            }

            value = value * 10 + (s[i] - '0');
            if (value > 255)                     // range check
                throw std::invalid_argument("Octet out of range 0‑255");

            ++digits;
            ++i;
        }

        if (digits == 0)
            throw std::invalid_argument("Missing octet value");

        /* after the digits, we expect '.' or ':' (or end of string) */
        if (part < 3) {                        // not the last part → must be '.'
            if (i >= len || s[i] != '.')
                throw std::invalid_argument("Expected '.' between octets");
            ++i;                               // skip the dot
        } else {                               // last part
            /* we may have ':' for a port or end‑of‑string */
            if (i < len && s[i] == ':') {
                /* keep colon, parse port later */
            } else if (i != len) {
                throw std::invalid_argument("Unexpected character after IP address");
            }
        }

        this->values[part] = value;
    }

    /* ---------- Parse optional port --------------------------------- */
    if (i < len && s[i] == ':') {              // colon found → parse port
        ++i;                                   // skip ':'

        int pvalue   = 0;
        int pdigits  = 0;
        bool pLeadingZero = false;

        while (i < len && s[i] >= '0' && s[i] <= '9') {
            if (pdigits == 0) {                // first digit of the port
                pLeadingZero = (s[i] == '0');
            } else {
                if (pLeadingZero)
                    throw std::invalid_argument("Port has leading zeros");
            }

            pvalue = pvalue * 10 + (s[i] - '0');
            if (pvalue > 65535)                 // range check
                throw std::invalid_argument("Port out of range 0‑65535");

            ++pdigits;
            ++i;
        }

        if (pdigits == 0)
            throw std::invalid_argument("Missing port number");

        /* after the digits there must be nothing else */
        if (i != len)
            throw std::invalid_argument("Unexpected characters after port");

        this->port = pvalue;
    } else if (i < len) {                       // stray character
        throw std::invalid_argument("Invalid trailing data");
    }
}
IpAddress::~IpAddress() {
    delete[] this->values;
}
string IpAddress::ToString() {
    char toReturn[32];
    char temp[32];
    for(int i = 0; i < 4; i++) {
        if(i > 0) {
            sprintf(temp, "%s.", toReturn);
        } else {
            temp[0] = '\0';
        }
        sprintf(toReturn, "%s%d", temp, this->values[i]);
    }
    if(this->IsPortDefined()) {
        sprintf(temp, "%s:%d", toReturn, this->GetPort());
        sprintf(toReturn, "%s", temp);
    }
    return string(toReturn);
}
int IpAddress::GetPort() {
    return this->port & 0xFFFF;
}
bool IpAddress::IsPortDefined() {
    return this->port >= 0 && this->port <= 0xFFFF;
}