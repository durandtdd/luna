#include "utils.hpp"

#include <algorithm>
#include <iomanip>
#include <sstream>


std::vector<uint8> stringToBytes(const std::string& hex)
{
    std::vector<uint8> bytes;
    std::size_t k = 0;

    while(k < hex.size() && isspace(hex[k]))
        k++;

    while(k < hex.size())
    {
        bytes.push_back(std::stoi(hex.substr(k, 2), 0, 16));
        k += 2;

        while(k < hex.size() && isspace(hex[k]))
            k++;
    }

	return bytes;
}


std::string dump(const std::vector<uint8>& bytes, uint64 beg, uint64 end)
{
    if(end > bytes.size())
        end = bytes.size();

    std::size_t bytesPerLine = 16;

    std::ostringstream oss;
    oss << std::hex;

    std::size_t k = beg;
    while(k < end)
    {
        // Number of bytes on this line
        std::size_t nb = std::min(end-k, bytesPerLine);

        // Add offset
        oss << std::setw(8) << std::setfill('0') << k << "   ";

        // Bytes
        for(std::size_t i = 0; i<nb; i++)
            oss << std::setw(2) << std::setfill('0') << (int)bytes[k+i] << " ";

        // Spacing
        oss << std::string(3*(bytesPerLine-nb)+2, ' ');

        // Chars
        for(std::size_t i = 0; i<nb; i++)
        {
            if(bytes[k+i] >= 33 && bytes[k+i] <= 126)
                oss << bytes[k+i];
            else
                oss << ".";
        }

        // End of line
        oss << std::string(bytesPerLine-nb, ' ') << "\n";

        k += nb;
    }

    return oss.str();
}

