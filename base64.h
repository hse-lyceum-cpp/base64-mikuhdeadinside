#pragma once
#include <string>
#include <vector>
#include <cstddef>
#include <cassert>

namespace base64
{
    std::string encode(const std::vector<std::byte>&);
    template<typename Byte>
    std::string encode(const Byte* begin, std::size_t size)
    {
        static const std::string source = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
        std::size_t shrinked_size = size - (size % 3);
        std::string answer;
        answer.resize(shrinked_size / 3 * 4 + (size - shrinked_size == 0 ? 0 : 4));
        std::size_t cur_pos = 0;
        std::uint8_t x[4];
        for (std::size_t i = 0; i < shrinked_size; i += 3)
        {
            x[0] = (static_cast<std::uint8_t>(begin[i]) & static_cast<std::uint8_t>(0b11111100)) >> 2;
            x[1] = ((static_cast<std::uint8_t>(begin[i]) & static_cast<std::uint8_t>(0b00000011)) << 4) |
                   ((static_cast<std::uint8_t>(begin[i + 1]) &static_cast<std::uint8_t>(0b11110000)) >> 4);
            x[2] = ((begin[i + 1] & static_cast<std::uint8_t>(0b00001111)) << 2) |
                   ((begin[i + 2] & static_cast<std::uint8_t>(0b11000000)) >> 6);
            x[3] = static_cast<std::uint8_t>(begin[i + 2]) & static_cast<std::uint8_t>(0b00111111);
            for (std::size_t j = 0; j < 4; ++j, ++cur_pos)
                answer[cur_pos] = source[x[j]];
        }
        switch (size - shrinked_size)
        {
        case 0:
            break;
        case 1:
        {
            x[0] = (static_cast<std::uint8_t>(begin[shrinked_size]) &static_cast<std::uint8_t>(0b11111100)) >> 2;
            x[1] = (static_cast<std::uint8_t>(begin[shrinked_size]) &static_cast<std::uint8_t>(0b00000011)) << 4;
            for (std::size_t j = 0; j < 2; ++j, ++cur_pos)
                answer[cur_pos] = source[x[j]];
            answer[cur_pos++] = '=';
            answer[cur_pos] = '=';
            break;
        }
        case 2:
        {
            x[0] = (begin[shrinked_size] & static_cast<std::uint8_t>(0b11111100)) >> 2;
            x[1] = ((static_cast<std::uint8_t>(begin[shrinked_size]) & static_cast<std::uint8_t>(0b00000011)) << 4) |
                   ((static_cast<std::uint8_t>(begin[shrinked_size + 1]) & static_cast<std::uint8_t>(0b11110000)) >> 4);
            x[2] = (begin[shrinked_size + 1] & static_cast<std::uint8_t>(0b00001111)) << 2;
            for (std::size_t j = 0; j < 3; ++j, ++cur_pos)
                answer[cur_pos] = source[x[j]];
            answer[cur_pos] = '=';
            break;
        }
        default:
        {
            assert(false);
        }
        }
        return answer;
    }
    
    std::vector<std::byte> decode(const std::string&);
} // namespace base64