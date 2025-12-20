#pragma once
#include <string>
#include "ISlideRepository.hpp"

// class ISlideRepository;

class ISerializer {
public:
    virtual ~ISerializer() = default;
    virtual std::string serialize(ISlideRepository* repository) const = 0;
    virtual void deserialize(const std::string& data, ISlideRepository* repository) = 0;
};