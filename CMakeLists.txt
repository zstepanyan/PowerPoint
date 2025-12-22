cmake_minimum_required(VERSION 3.16)
project(SlideEditor VERSION 2.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/external
)

set(CORE_SOURCES
    src/core/Shape.cpp
    src/core/Slide.cpp
    src/core/SlideFactory.cpp
    src/core/SlideRepository.cpp
    src/core/SlideMemento.cpp
)

set(ACTION_SOURCES
    src/actions/Actions.cpp
)

set(HISTORY_SOURCES
    src/history/ActionHistory.cpp
)

set(RENDERING_SOURCES
    src/rendering/SVGRenderer.cpp
    src/rendering/SlideRenderer.cpp
    src/rendering/SVGExporter.cpp
)

set(COMMAND_SOURCES
    src/commands/Commands.cpp
    "src/command factory/CommandFactory.cpp"
)

set(PARSER_SOURCES
    src/parser/Lexer.cpp
    src/parser/Tokenizer.cpp
    src/parser/Parser.cpp
)

set(SERIALIZATION_SOURCES
    src/serialization/JsonSerializer.cpp
)

set(MVC_SOURCES
    src/mvc/View.cpp
    src/mvc/Controller.cpp
)

set(METACOMMAND_SOURCES
    src/metacommand/MetaCommand.cpp
    src/metacommand/CommandRegistry.cpp
)

set(MAIN_SOURCES
    src/main.cpp
)

set(ALL_SOURCES
    ${CORE_SOURCES}
    ${ACTION_SOURCES}
    ${HISTORY_SOURCES}
    ${RENDERING_SOURCES}
    ${COMMAND_SOURCES}
    ${PARSER_SOURCES}
    ${SERIALIZATION_SOURCES}
    ${MVC_SOURCES}
    ${METACOMMAND_SOURCES}
    ${MAIN_SOURCES}
)

add_executable(${PROJECT_NAME} ${ALL_SOURCES})

add_custom_target(run
    COMMAND ${PROJECT_NAME}
    DEPENDS ${PROJECT_NAME}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)

message(STATUS "Building SlideEditor v${PROJECT_VERSION}")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
