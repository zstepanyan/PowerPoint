#pragma once
#include "ISlideRepository.hpp"
#include <string>
// class ISlideRepository;

class ICommand {
public:
    virtual ~ICommand() = default;
    virtual void execute(ISlideRepository* repository) = 0;
    virtual std::string getName() const = 0;
};