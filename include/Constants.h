#pragma once
#include <SFML/Graphics.hpp>

constexpr unsigned CELL_SIZE = 10;

const sf::Color DELIMITER_COLOR(0xAAAAAAFF);

const sf::Color LIVE_CELL_COLOR(0xF0F8FFFF);

const sf::Color DEAD_CELL_COLOR(0x000000FF);

constexpr int DELIMITERS_FADING_COEFF = 8;

constexpr size_t RENDER_FREQ = 10;

constexpr size_t STATE_REFRESH_FREQ = 100;

constexpr unsigned WINDOW_WIDTH = 800;

constexpr unsigned WINDOW_HEIGHT = 600;
