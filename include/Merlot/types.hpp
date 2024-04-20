#ifndef TYPES_HPP_
#define TYPES_HPP_
#include <cstddef>

namespace ml {
    
    enum class type {
        float32,
        int32
    };


    std::size_t size_of(type type) {
        switch (type) {
            case type::float32:
                return sizeof(float);
            case type::int32:
                return sizeof(int);
            default:
                return 0;
        }
    }

} // namespace ml

#endif // TYPES_HPP_