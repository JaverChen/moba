#pragma once
#include <boost/crc.hpp>

class DataValidator {
public:
    static uint32_t CalculateCRC(const char* data, size_t length) {
        boost::crc_32_type crc;
        crc.process_bytes(data, length);
        return crc.checksum();
    }

    static std::vector<char> AddChecksum(const std::vector<char>& data) {
        uint32_t checksum = CalculateCRC(data.data(), data.size());
        
        std::vector<char> protected_data(data.size() + sizeof(checksum));
        memcpy(protected_data.data(), &checksum, sizeof(checksum));
        memcpy(protected_data.data() + sizeof(checksum), data.data(), data.size());
        
        return protected_data;
    }

    static bool Validate(const std::vector<char>& protected_data) {
        if (protected_data.size() < sizeof(uint32_t)) return false;
        
        uint32_t received_checksum;
        memcpy(&received_checksum, protected_data.data(), sizeof(received_checksum));
        
        const char* data = protected_data.data() + sizeof(received_checksum);
        size_t data_length = protected_data.size() - sizeof(received_checksum);
        
        return received_checksum == CalculateCRC(data, data_length);
    }
};