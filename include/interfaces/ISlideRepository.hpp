#pragma once
#include <vector>
#include <memory>

class Slide;

class ISlideRepository {
public:
    virtual ~ISlideRepository() = default;
    virtual void addSlide(std::unique_ptr<Slide> slide) = 0;
    virtual Slide* getSlide(int index) = 0;
    virtual int getSlideCount() const = 0;
    virtual void moveSlide(int fromIndex, int toIndex) = 0;
    virtual std::vector<std::unique_ptr<Slide>>& getSlides() = 0;
};