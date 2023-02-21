#pragma once

#include <SFML/Graphics.hpp>
#include <cstdint>
#include <array>
#include <vector>

inline sf::Color Red(255, 0, 0);
inline sf::Color Orange(255, 145, 0);
inline sf::Color Yellow(255, 255, 0);
inline sf::Color Lime(0, 255, 0);
inline sf::Color Cyan(0, 255, 255);
inline sf::Color Blue(0, 0, 255);
inline sf::Color Violet(148, 0, 211);
inline sf::Color Gray(32, 32, 32);

typedef signed int INT;
typedef unsigned int UINT;
typedef int8_t INT8;
typedef int16_t INT16;
typedef int32_t INT32;
typedef int64_t INT64;
typedef uint8_t UINT8;
typedef uint16_t UINT16;
typedef uint32_t UINT32;
typedef uint64_t UINT64;

typedef uint8_t BYTE;

constexpr BYTE CELL_SIZE = 8;
constexpr BYTE COLUMNS = 10;
constexpr BYTE ROWS = 22;
constexpr BYTE SCREEN_RESIZE = 4;

constexpr UINT16 SCREEN_WIDTH = COLUMNS * CELL_SIZE * SCREEN_RESIZE;
constexpr UINT16 SCREEN_HEIGHT = ROWS * CELL_SIZE * SCREEN_RESIZE;

