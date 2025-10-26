# SlideEditor - C++ Slide Presentation Application

A command-driven slide editing application written in modern C++ (C++17) that supports creating, managing, and serializing slide presentations.

## Features

- **Create Slides**: Dynamically create new slides
- **Manage Slides**: Move slides between positions with automatic renumbering
- **Add Shapes**: Support for Rectangle, Circle, and Triangle shapes
- **Add Text**: Add text content to slides
- **List & Display**: View all slides or display detailed information about specific slides
- **Serialization**: Save and load presentations to/from JSON format
- **Robust Parsing**: DFA-based command parser with comprehensive token classification

## Architecture

The project follows SOLID principles and implements several design patterns:

### Design Patterns

- **Command Pattern**: All operations encapsulated as ICommand implementations
- **Factory Pattern**: SlideFactory, ShapeFactory, and CommandFactory for object creation
- **Repository Pattern**: ISlideRepository interface with SlideRepository implementation
- **Strategy Pattern**: ISerializer interface with JsonSerializer implementation
- **Parser Pattern**: DFA-based state machine for command parsing

### Project Structure

```
SlideEditor/
├── include/
│   ├── interfaces/
│   │   ├── IShape.hpp
│   │   ├── ISlideRepository.hpp
│   │   ├── ISerializer.hpp
│   │   └── ICommand.hpp
│   ├── core/
│   │   ├── Shape.hpp
│   │   ├── Slide.hpp
│   │   ├── SlideFactory.hpp
│   │   └── SlideRepository.hpp
│   ├── commands/
│   │   └── Commands.hpp
│   ├── serialization/
│   │   └── JsonSerializer.hpp
│   ├── parser/
│   │   ├── Lexer.hpp
│   │   ├── Tokenizer.hpp
│   │   └── Parser.hpp
│   └── CommandFactory.hpp
├── src/
│   ├── core/
│   │   ├── Shape.cpp
│   │   ├── Slide.cpp
│   │   ├── SlideFactory.cpp
│   │   └── SlideRepository.cpp
│   ├── commands/
│   │   └── Commands.cpp
│   ├── serialization/
│   │   └── JsonSerializer.cpp
│   ├── parser/
│   │   ├── Lexer.cpp
│   │   ├── Tokenizer.cpp
│   │   └── Parser.cpp
│   ├── CommandFactory.cpp
│   └── main.cpp
├── external/
│   └── nlohmann/
│       └── json.hpp
├── Makefile
└── README.md
```

## Building

### Requirements

- C++17 compatible compiler (g++, clang, etc.)
- nlohmann/json library (included in external/)

### Build Instructions

Using Make:
```bash
make all
```

Or manually with g++:
```bash
g++ -std=c++17 -Iinclude -Iexternal src/core/*.cpp src/commands/*.cpp \
    src/serialization/*.cpp src/parser/*.cpp src/CommandFactory.cpp \
    src/main.cpp -o SlideEditor
```

### Running

```bash
./SlideEditor
```

Or with make:
```bash
make run
```

## Usage

### Command Reference

#### Create a Slide
```
> create
Slide 1 created.
```

#### Add a Shape to a Slide
Supported shapes: Rectangle, Circle, Triangle
```
> addshape 1 Rectangle
Shape Rectangle added to slide 1.

> addshape 1 Circle
Shape Circle added to slide 1.
```

#### Add Text to a Slide
```
> addtext 1 This is my presentation
Text added to slide 1.
```

#### List All Slides
```
> list
--- Slides ---
Slide 1: Text[This is my presentation] Shapes: Rectangle Circle
```

#### Display Slide Details
```
> display 1

=== Slide 1: Text[This is my presentation] Shapes: Rectangle Circle === 
Text: This is my presentation
Shapes: Rectangle Circle
```

#### Move Slides
Move a slide from one position to another (positions are 1-indexed):
```
> create
Slide 1 created.

> create
Slide 2 created.

> create
Slide 3 created.

> move 1 3
Slide moved from position 1 to 3.
```

#### Save Presentation
```
> save presentation.json
Presentation saved to presentation.json.
```

#### Load Presentation
```
> load presentation.json
Presentation loaded from presentation.json.
```

#### Exit
```
> exit
Exiting SlideEditor.
```

### Example Session

```
> create
Slide 1 created.

> addtext 1 Title Slide
Text added to slide 1.

> addshape 1 Rectangle
Shape Rectangle added to slide 1.

> create
Slide 2 created.

> addtext 2 Content Slide
Text added to slide 2.

> addshape 2 Circle
Shape Circle added to slide 2.

> addshape 2 Triangle
Shape Triangle added to slide 2.

> list
--- Slides ---
Slide 1: Text[Title Slide] Shapes: Rectangle 
Slide 2: Text[Content Slide] Shapes: Circle Triangle

> save my_presentation.json
Presentation saved to my_presentation.json.

> exit
Exiting SlideEditor.
```

### JSON Output Format

Presentations are saved in JSON format:

```json
{
  "version": "1.0",
  "slides": [
    {
      "number": 1,
      "text": "Title Slide",
      "shapes": [
        "Rectangle"
      ]
    },
    {
      "number": 2,
      "text": "Content Slide",
      "shapes": [
        "Circle",
        "Triangle"
      ]
    }
  ]
}
```

## Implementation Details

### Parser

The parser uses a tokenizer and lexer to classify tokens, then applies a DFA state machine to validate commands:

- **Tokenizer**: Splits input into whitespace-separated tokens
- **Lexer**: Classifies tokens as Number, Float, Word, or Flag
- **Parser**: Applies state machine rules to validate command structure

### Commands

All commands implement the ICommand interface with an `execute()` method:

- `CreateSlideCommand`: Creates a new slide
- `MoveSlideCommand`: Moves a slide to a new position
- `AddShapeCommand`: Adds a shape to a slide
- `AddTextCommand`: Adds text to a slide
- `ListSlidesCommand`: Lists all slides
- `DisplaySlideCommand`: Shows details of a specific slide
- `SaveCommand`: Saves presentation to JSON
- `LoadCommand`: Loads presentation from JSON
- `ExitCommand`: Exits the application

### Repository Pattern

The SlideRepository manages slides and provides operations like:
- Adding slides
- Retrieving slides by index
- Moving slides with automatic renumbering
- Accessing the complete slide collection

## Future Enhancements

- Undo/redo functionality using command history
- Additional serialization formats (XML, CSV)
- Slide templates and themes
- Presentation playback/slideshow mode
- Image support
- Custom shape support
- Styling options (colors, fonts)

## License

This project is provided as-is for educational purposes.

## Contact & Contributing

This is a demonstration project showcasing modern C++ design patterns and practices.
