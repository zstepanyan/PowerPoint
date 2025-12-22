#include "../../include/commands/Commands.hpp"
#include "../../include/core/Slide.hpp"
#include "../../include/core/SlideFactory.hpp"
#include "../../include/core/Shape.hpp"
#include "../../include/serialization/JsonSerializer.hpp"
#include "../../include/actions/Actions.hpp"
#include "../../include/history/ActionHistory.hpp"
#include "../../include/rendering/SVGExporter.hpp"
#include <iostream>
#include <fstream>

void CreateSlideCommand::execute(ISlideRepository* repository) {
    try {
        auto action = std::make_unique<CreateSlideAction>();
        action->execute(repository);
        ActionHistory::getInstance().recordAction(std::move(action));
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
    }
}

void MoveSlideCommand::execute(ISlideRepository* repository) {
    try {
        auto action = std::make_unique<MoveSlideAction>(fromIndex - 1, toIndex - 1);
        action->execute(repository);
        ActionHistory::getInstance().recordAction(std::move(action));
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
    }
}

void AddShapeCommand::execute(ISlideRepository* repository) {
    try {
        auto action = std::make_unique<AddShapeAction>(slideIndex - 1, shapeType, x, y, width, height);
        action->execute(repository);
        ActionHistory::getInstance().recordAction(std::move(action));
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
    }
}

void AddTextCommand::execute(ISlideRepository* repository) {
    try {
        auto action = std::make_unique<AddTextAction>(slideIndex - 1, text);
        action->execute(repository);
        ActionHistory::getInstance().recordAction(std::move(action));
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
    }
}

void ListSlidesCommand::execute(ISlideRepository* repository) {
    if (repository->getSlideCount() == 0) {
        std::cout << "No slides available.\n";
        return;
    }

    std::cout << "--- Slides ---\n";
    for (int i = 0; i < repository->getSlideCount(); ++i) {
        Slide* slide = repository->getSlide(i);
        std::cout << slide->serialize() << "\n";
    }
}

void DisplaySlideCommand::execute(ISlideRepository* repository) {
    try {
        Slide* slide = repository->getSlide(slideIndex - 1);
        std::cout << "\n=== " << slide->serialize() << " ===\n";
        if (!slide->getText().empty()) {
            std::cout << "Text: " << slide->getText() << "\n";
        }
        std::cout << "Shapes:\n";
        const auto& shapes = slide->getShapes();
        for (size_t i = 0; i < shapes.size(); ++i) {
            std::cout << "  " << (i + 1) << ". " << shapes[i]->serialize() << "\n";
        }
        std::cout << "\n";
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
    }
}

void SaveCommand::execute(ISlideRepository* repository) {
    try {
        JsonSerializer serializer;
        std::string data = serializer.serialize(repository);

        std::ofstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Cannot open file: " + filename);
        }
        file << data;
        file.close();
        std::cout << "Presentation saved to " << filename << ".\n";
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
    }
}

void LoadCommand::execute(ISlideRepository* repository) {
    try {
        std::ifstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Cannot open file: " + filename);
        }

        std::string data((std::istreambuf_iterator<char>(file)),
                         std::istreambuf_iterator<char>());
        file.close();

        JsonSerializer serializer;
        serializer.deserialize(data, repository);
        // Clear history after loading a new presentation
        ActionHistory::getInstance().clear();
        std::cout << "Presentation loaded from " << filename << ".\n";
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
    }
}

void ExitCommand::execute(ISlideRepository* repository) {
    (void)repository;
    std::cout << "Exiting SlideEditor.\n";
}

// New command implementations

void DeleteSlideCommand::execute(ISlideRepository* repository) {
    try {
        auto action = std::make_unique<DeleteSlideAction>(slideIndex - 1);
        action->execute(repository);
        ActionHistory::getInstance().recordAction(std::move(action));
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
    }
}

void RemoveShapeCommand::execute(ISlideRepository* repository) {
    try {
        auto action = std::make_unique<RemoveShapeAction>(slideIndex - 1, shapeIndex - 1);
        action->execute(repository);
        ActionHistory::getInstance().recordAction(std::move(action));
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
    }
}

void EditTextCommand::execute(ISlideRepository* repository) {
    try {
        auto action = std::make_unique<EditTextAction>(slideIndex - 1, text);
        action->execute(repository);
        ActionHistory::getInstance().recordAction(std::move(action));
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
    }
}

void ClearTextCommand::execute(ISlideRepository* repository) {
    try {
        auto action = std::make_unique<ClearTextAction>(slideIndex - 1);
        action->execute(repository);
        ActionHistory::getInstance().recordAction(std::move(action));
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
    }
}

void UndoCommand::execute(ISlideRepository* repository) {
    ActionHistory::getInstance().undo(repository);
}

void RedoCommand::execute(ISlideRepository* repository) {
    ActionHistory::getInstance().redo(repository);
}

void HistoryCommand::execute(ISlideRepository* repository) {
    (void)repository;
    auto& history = ActionHistory::getInstance();

    auto undoList = history.getUndoHistory();
    auto redoList = history.getRedoHistory();

    std::cout << "--- Action History ---\n";
    std::cout << "Undo stack (" << undoList.size() << "):\n";
    for (size_t i = 0; i < undoList.size(); ++i) {
        std::cout << "  " << (i + 1) << ". " << undoList[i] << "\n";
    }

    std::cout << "Redo stack (" << redoList.size() << "):\n";
    for (size_t i = 0; i < redoList.size(); ++i) {
        std::cout << "  " << (i + 1) << ". " << redoList[i] << "\n";
    }

    std::cout << "Max history size: " << history.getMaxHistorySize() << "\n";
}

void SetHistoryCommand::execute(ISlideRepository* repository) {
    (void)repository;
    ActionHistory::getInstance().setMaxHistorySize(historySize);
    std::cout << "History size set to " << historySize << ".\n";
}

// SVG Export command implementations

void ExportCommand::execute(ISlideRepository* repository) {
    try {
        Slide* slide = repository->getSlide(slideIndex - 1);
        if (SVGExporter::exportSlide(slide, filename)) {
            std::cout << "Slide " << slideIndex << " exported to " << filename << ".\n";
        } else {
            std::cout << "Error: Could not export slide to " << filename << ".\n";
        }
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
    }
}

void ExportAllCommand::execute(ISlideRepository* repository) {
    try {
        if (repository->getSlideCount() == 0) {
            std::cout << "No slides to export.\n";
            return;
        }

        if (SVGExporter::exportAllSlides(repository, directory)) {
            std::cout << "Exported " << repository->getSlideCount()
                      << " slides to " << directory << "/.\n";
        } else {
            std::cout << "Error: Some slides could not be exported.\n";
        }
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
    }
}

void PreviewCommand::execute(ISlideRepository* repository) {
    try {
        Slide* slide = repository->getSlide(slideIndex - 1);
        std::string svg = SVGExporter::renderToString(slide);
        std::cout << "\n=== SVG Preview for Slide " << slideIndex << " ===\n";
        std::cout << svg;
        std::cout << "=== End of Preview ===\n\n";
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
    }
}
