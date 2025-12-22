#include "../../include/mvc/View.hpp"

void View::showWelcome() const {
    std::cout << "================================\n";
    std::cout << "    Welcome to SlideEditor\n";
    std::cout << "================================\n";
    std::cout << "Slide Commands:\n";
    std::cout << "  create              - Create a new slide\n";
    std::cout << "  delete <idx>        - Delete a slide\n";
    std::cout << "  move <from> <to>    - Move slide from position to position\n";
    std::cout << "  list                - List all slides\n";
    std::cout << "  display <idx>       - Display slide details\n";
    std::cout << "\nShape Commands:\n";
    std::cout << "  addshape <idx> <type> <x> <y> <w> <h> - Add shape to slide\n";
    std::cout << "     Types: Rectangle, Circle, Triangle\n";
    std::cout << "  removeshape <idx> <shape#> - Remove shape from slide\n";
    std::cout << "\nText Commands:\n";
    std::cout << "  addtext <idx> <text>  - Add text to slide (must be empty)\n";
    std::cout << "  edittext <idx> <text> - Modify existing text\n";
    std::cout << "  cleartext <idx>       - Clear slide text\n";
    std::cout << "\nUndo/Redo:\n";
    std::cout << "  undo                - Undo last action\n";
    std::cout << "  redo                - Redo last undone action\n";
    std::cout << "  history             - Show action history\n";
    std::cout << "  sethistory <size>   - Set max history size\n";
    std::cout << "\nExport:\n";
    std::cout << "  export <idx> <file> - Export slide to SVG\n";
    std::cout << "  exportall <dir>     - Export all slides to directory\n";
    std::cout << "  preview <idx>       - Preview slide SVG in console\n";
    std::cout << "\nFile:\n";
    std::cout << "  save <filename>     - Save presentation to JSON\n";
    std::cout << "  load <filename>     - Load presentation from JSON\n";
    std::cout << "  exit                - Exit the application\n";
    std::cout << "================================\n\n";
}

void View::showPrompt() const {
    std::cout << "> ";
    std::cout.flush();
}

void View::showMessage(const std::string& message) const {
    std::cout << message << "\n";
}

void View::showError(const std::string& error) const {
    std::cout << "Error: " << error << "\n";
}

void View::showSlideList(const std::vector<std::string>& slides) const {
    if (slides.empty()) {
        std::cout << "No slides available.\n";
        return;
    }

    std::cout << "--- Slides ---\n";
    for (const auto& slide : slides) {
        std::cout << slide << "\n";
    }
}

void View::showSlideDetails(const std::string& details) const {
    std::cout << "\n=== " << details << " ===\n";
}

void View::showHistory(const std::vector<std::string>& undoList,
                       const std::vector<std::string>& redoList,
                       size_t maxSize) const {
    std::cout << "--- Action History ---\n";
    std::cout << "Undo stack (" << undoList.size() << "):\n";
    for (size_t i = 0; i < undoList.size(); ++i) {
        std::cout << "  " << (i + 1) << ". " << undoList[i] << "\n";
    }

    std::cout << "Redo stack (" << redoList.size() << "):\n";
    for (size_t i = 0; i < redoList.size(); ++i) {
        std::cout << "  " << (i + 1) << ". " << redoList[i] << "\n";
    }

    std::cout << "Max history size: " << maxSize << "\n";
}

void View::showSVGPreview(int slideNumber, const std::string& svg) const {
    std::cout << "\n=== SVG Preview for Slide " << slideNumber << " ===\n";
    std::cout << svg;
    std::cout << "=== End of Preview ===\n\n";
}

void View::showGoodbye() const {
    std::cout << "Exiting SlideEditor.\n";
}

std::string View::getInput() const {
    std::string line;
    std::getline(std::cin, line);
    return line;
}

bool View::hasInput() const {
    return !std::cin.eof() && std::cin.good();
}
