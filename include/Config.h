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

constexpr int DELIMITERS_FADING_COEFF = 8;

constexpr size_t FRAME_REFRESH_TIME = 10;

constexpr size_t STATE_REFRESH_TIME = 100;

constexpr unsigned WINDOW_WIDTH = 800;

constexpr unsigned WINDOW_HEIGHT = 600;
} // namespace Default

class Config
{
public:
	static void ReadFromFile(const std::string& fileName);

	static unsigned GetCellSize();

	static sf::Color GetDelimiterColor();

	static sf::Color GetLiveCellColor();

	static sf::Color GetDeadCellColor();

	static int GetDelimitersFadingCoeff();

	static size_t GetFrameRefreshTime();

	static size_t GetStateRefreshTime();

	static unsigned GetWindowWidth();

	static unsigned GetWindowHeight();

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
	
	static inline const std::map<const std::string, AvailableVariables> availableVariableNames = {
		{ "CELL_SIZE", AvailableVariables::CellSize },
		{ "DELIMITER_COLOR", AvailableVariables::DelimiterColor },
		{ "LIVE_CELL_COLOR", AvailableVariables::LiveCellColor },
		{ "DELIMITERS_FADING_COEFF", AvailableVariables::DelimitersFadingCoeff },
		{ "RENDER_FREQ", AvailableVariables::RenderFreq },
		{ "STATE_REFRESH_TIME", AvailableVariables::StateRefreshTime },
		{ "WINDOW_WIDTH", AvailableVariables::WindowWidth },
		{ "WINDOW_HEIGHT", AvailableVariables::WindowHeight }
	};

	static State ProcessSymbol(char symbol, State curState);

	static void SeekNextLine();

	static void ProcessKeyValuePair();

	static void SetDefaultValues();

	static inline std::ifstream file;

	static inline std::string key, value;

	static inline unsigned cellSize = Default::CELL_SIZE;

	static inline sf::Color delimiterColor = Default::DELIMITER_COLOR;

	static inline sf::Color liveCellColor = Default::LIVE_CELL_COLOR;

	static inline sf::Color deadCellColor = Default::DEAD_CELL_COLOR;

	static inline int delimitersFadingCoeff = Default::DELIMITERS_FADING_COEFF;

	static inline size_t frameRefreshTime = Default::FRAME_REFRESH_TIME;

	static inline size_t stateRefreshTime = Default::STATE_REFRESH_TIME;

	static inline unsigned windowWidth = Default::WINDOW_WIDTH;

	static inline unsigned windowHeight = Default::WINDOW_HEIGHT;
};
