#pragma once
#include "../interfaces/ISlideRepository.hpp"
#include "Slide.hpp"
#include <vector>
#include <memory>

class SlideRepository : public ISlideRepository {
public:
    void addSlide(std::unique_ptr<Slide> slide) override;
    Slide* getSlide(int index) override;
    int getSlideCount() const override;
    void moveSlide(int fromIndex, int toIndex) override;
    std::vector<std::unique_ptr<Slide>>& getSlides() override;

private:
    std::vector<std::unique_ptr<Slide>> slides;
};