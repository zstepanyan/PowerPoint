#pragma once
#include <string>
#include <vector>
#include <iostream>

class View {
public:
    View() = default;
    virtual ~View() = default;

    // Display methods
    void showWelcome() const;
    void showPrompt() const;
    void showMessage(const std::string& message) const;
    void showError(const std::string& error) const;
    void showSlideList(const std::vector<std::string>& slides) const;
    void showSlideDetails(const std::string& details) const;
    void showHistory(const std::vector<std::string>& undoList,
                     const std::vector<std::string>& redoList,
                     size_t maxSize) const;
    void showSVGPreview(int slideNumber, const std::string& svg) const;
    void showGoodbye() const;

    // Input methods
    std::string getInput() const;
    bool hasInput() const;
};
