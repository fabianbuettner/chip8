#pragma once

#include "Memory.h"

#include <cstdint>
#include <filesystem>

const std::uint16_t max_memory_size = 0x1000;
const std::uint16_t sprite_address = 0x010;

class MemoryChip8 : public Memory<std::uint8_t> {
public:
    MemoryChip8(const std::filesystem::path& path, std::uint16_t memory_size = max_memory_size, std::uint16_t pc = 0x200);
    std::uint8_t& operator[](int) final;
    std::size_t size() const final;
};
