#pragma once
#include "../interfaces/ISerializer.hpp"
#include <string>

class JsonSerializer : public ISerializer {
public:
    std::string serialize(ISlideRepository* repository) const override;
    void deserialize(const std::string& data, ISlideRepository* repository) override;
};