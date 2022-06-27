#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <fstream>

namespace Default
{
constexpr unsigned CELL_SIZE = 10;

const sf::Color DELIMITER_COLOR(0xAAAAAAFF);

const sf::Color LIVE_CELL_COLOR(0xF0F8FFFF);

const sf::Color DEAD_CELL_COLOR(0x000000FF);

constexpr unsigned DELIMITERS_FADING_COEFF = 8;

constexpr size_t RENDER_FREQ = 10;

constexpr size_t STATE_REFRESH_TIME = 100;

constexpr unsigned WINDOW_WIDTH = 800;

constexpr unsigned WINDOW_HEIGHT = 600;
} // namespace Default

class Config
{
public:
	void ReadFromFile(const std::string& fileName);

	unsigned GetCellSize() const;

	sf::Color GetDelimiterColor() const;

	sf::Color GetLiveCellColor() const;

	sf::Color GetDeadCellColor() const;

	unsigned GetDelimitersFadingCoeff() const;

	size_t GetRenderFreq() const;

	size_t GetStateRefreshTime() const;

	unsigned GetWindowWidth() const;

	unsigned GetWindowHeight() const;

private:
	enum class State
	{
		ReadKey,
		KeyHasBeenRead,
		ReadValue,
		ValueHasBeenRead,
		SkipComment,
		SyntaxError
	};

	enum class AvailableVariables
	{
		CellSize,
		DelimiterColor,
		LiveCellColor,
		DelimitersFadingCoeff,
		RenderFreq,
		StateRefreshTime,
		WindowWidth,
		WindowHeight
	};
	
	const std::map<const std::string, AvailableVariables> availableVariableNames = {
		{ "CELL_SIZE", AvailableVariables::CellSize },
		{ "DELIMITER_COLOR", AvailableVariables::DelimiterColor },
		{ "LIVE_CELL_COLOR", AvailableVariables::LiveCellColor },
		{ "DELIMITERS_FADING_COEFF", AvailableVariables::DelimitersFadingCoeff },
		{ "RENDER_FREQ", AvailableVariables::RenderFreq },
		{ "STATE_REFRESH_TIME", AvailableVariables::StateRefreshTime },
		{ "WINDOW_WIDTH", AvailableVariables::WindowWidth },
		{ "WINDOW_HEIGHT", AvailableVariables::WindowHeight }
	};

	State ProcessSymbol(char symbol, State curState);

	void SeekNextLine();

	void ProcessKeyValuePair();

	std::ifstream file;

	std::string key, value;

	unsigned cellSize = Default::CELL_SIZE;

	sf::Color delimiterColor = Default::DELIMITER_COLOR;

	sf::Color liveCellColor = Default::LIVE_CELL_COLOR;

	sf::Color deadCellColor = Default::DEAD_CELL_COLOR;

	unsigned delimitersFadingCoeff = Default::DELIMITERS_FADING_COEFF;

	size_t renderFreq = Default::RENDER_FREQ;

	size_t stateRefreshTime = Default::STATE_REFRESH_TIME;

	unsigned windowWidth = Default::WINDOW_WIDTH;

	unsigned windowHeight = Default::WINDOW_HEIGHT;
};
