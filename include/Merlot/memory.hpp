#ifndef MEMORY_HPP_
#define MEMORY_HPP_

#include <cstdint>
#include <cstring>
#include <iostream>
#include <vector>
#include <unordered_map>

#include "types.hpp"

namespace {

    class Block {
        public:

        Block() {
            data_ = nullptr;
            offset_ = nullptr;
            memory_size_ = 0;
        }

        Block(std::size_t memory_size) {            
            data_ = operator new(memory_size);
            offset_ = data_;
            memory_size_ = memory_size;
        }

        Block(const Block& other) {            
            data_ = operator new(other.memory_size_);
            offset_ = other.offset_;
            memory_size_ = other.memory_size_;
            std::memcpy(data_, other.data_, other.memory_size_);

        }

        Block(Block&& other) {            
            data_ = other.data_;
            offset_ = other.offset_;
            memory_size_ = other.memory_size_;
            other.data_ = nullptr;
            other.offset_ = nullptr;
            other.memory_size_ = 0;

        }

        Block& operator=(const Block& other) {              
            if (this != &other) {
                data_ = operator new(other.memory_size_);
                offset_ = other.offset_;
                memory_size_ = other.memory_size_;
                std::memcpy(data_, other.data_, other.memory_size_);
            }
            return *this;
        }

        Block& operator=(Block&& other) {
            if (this != &other) {
                data_ = other.data_;
                offset_ = other.offset_;
                memory_size_ = other.memory_size_;
                other.data_ = nullptr;
                other.offset_ = nullptr;
                other.memory_size_ = 0;
            }
            return *this;
        }

        ~Block() {
            operator delete(data_);
        }

        void* allocate(std::size_t chunk_size) {
            void* offset = offset_;
            offset_ = static_cast<char*>(offset_) + chunk_size;
            return offset;
        }

        private:
        void* data_;
        void* offset_;
        std::size_t memory_size_;
    };
}

namespace ml {

    struct Memory {
        static std::unordered_map<std::string, ::Block> pool;
        static void reserve(std::size_t memory_size, std::string location = "default") {
            pool[location] = ::Block(memory_size);
        }

        using size_type = std::size_t;
        static void* allocate(size_type size, type type, std::string location = "default") {
            return pool[location].allocate(size * size_of(type));
        }
    };

    std::unordered_map<std::string, ::Block> Memory::pool;

} // namespace ml

#endif // MEMORY_HPP_