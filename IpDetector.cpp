#include "IpDetector.hpp"
#include "IpAddress.hpp"
#include <string>
#include <iostream>
using namespace std;

// I don't expect this do do anything
// This format was a product of CLion suggestions, not AI.
IpDetector::IpDetector() = default;
// Get the first potential IP address
// This does not guarantee it is valid, but does guarantee it only consists of characters
// That the IpAddress class should parse.
// I guess my real goal here was to get a function to derive substrings to test.
string IpDetector::GetPotentialIpString(string& input) {
    // Automatically defined to empty string
    string toReturn;
    // Iterate through the string until we reach an invalid character.
    unsigned int i = 0;
    // This should not throw an error assuming the string is terminated with any reasonable character.
    for (; i < input.length() && this->IsValidCharacter(input[i]); i++) {
        toReturn += input[i];
    }
    // Ensure no bugs relating to hitting the end of the string
    if (i >= input.length()) {
        input = "";
    } else {
        input = input.substr(i + 1);
    }
    return toReturn;
}
bool IpDetector::extractIPv4(const std::string& str,
                             unsigned long& outAddress,
                             int& outPort)
{
    /* ------------------------------------------------------------------
     *  1. Initialise outputs – if nothing is found we return false and
     *     leave the arguments unchanged (they’ll be set to 0 / -1 in the
     *     calling code if needed).
     * ------------------------------------------------------------------ */
    outAddress = 0;
    outPort   = -1;

    /* ------------------------------------------------------------------
     *  2. Work on a mutable copy of the input – GetPotentialIpString()
     *     consumes characters from the front, so we can keep looping
     *     until the string is exhausted or a valid IP is found.
     * ------------------------------------------------------------------ */
    std::string remaining = str;

    /* ------------------------------------------------------------------
     *  3. Keep pulling potential‑IP substrings until we either succeed
     *     or run out of data.
     * ------------------------------------------------------------------ */
    while (!remaining.empty())
    {
        // Grab the next chunk that could be an IP address
        std::string candidate = GetPotentialIpString(remaining);

        /* If nothing was extracted (e.g. leading non‑valid char) we break –
         * the loop will exit because remaining has been advanced to the
         * first invalid character, which is still part of 'remaining'.
         */

        // Modification: Remove this line, as ip address could be after an empty candidate.
        /*
        if (candidate.empty())
            break;
        */

        try
        {
            // Try to parse it with IpAddress – this may throw
            IpAddress ip(candidate);

            /* ------------------------------------------------------------------
             *  4. If we get here the constructor succeeded – pull the
             *     integer representation and port out.
             * ------------------------------------------------------------------ */
            // Change here: Convert to int first as a middleman type.
            unsigned int addrInt = static_cast<unsigned int>(ip);
            outAddress = static_cast<unsigned long>(addrInt);
            outPort    = ip.IsPortDefined() ? ip.GetPort() : -1;
            return true;          // success!
        }
        catch (const std::exception&)
        {
            /* The candidate was not a valid IPv4 address – continue
             * searching with the remainder of the string.
             */
            continue;
        }
    }

    /* ------------------------------------------------------------------
     *  5. No valid IP found – return false and leave outputs at their
     *     default (0 / -1).
     * ------------------------------------------------------------------ */
    return false;
}

bool IpDetector::IsValidCharacter(char c) {
    return (c >= '0' && c <= '9') || (c == '.') || (c == ':');
}
