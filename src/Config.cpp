#include "Config.h"

using namespace std::string_literals;

void Config::ReadFromFile(const std::string& fileName)
try
{
	file.open(fileName);

	if (!file.is_open())
	{
		throw std::runtime_error("Failed to read config from file '" + fileName + "'. Failed to open file.");
	}

	State state = State::ReadKey;

	char symbol;
	while (!file.eof())
	{
		file.get(symbol);
		state = ProcessSymbol(symbol, state);

		switch (state)
		{
		case State::ReadKey:
			key.push_back(symbol);
			break;
		case State::ReadValue:
			value.push_back(symbol);
			break;
		case State::SkipComment:
			SeekNextLine();
			break;
		case State::KeyHasBeenRead:
			state = State::ReadValue;
			break;
		case State::ValueHasBeenRead:
			ProcessKeyValuePair();
			break;
		case State::SyntaxError:
			throw std::runtime_error("Error was occured while parsing config file. Syntax error.");
		default:
			break;
		}
	}

	file.close();
}
catch (const std::runtime_error& e)
{
	SetDefaultValues();
	
	throw std::runtime_error(e.what() + "\nConfig variables was set to default."s);
}

unsigned Config::GetCellSize()
{
	return cellSize;
}

sf::Color Config::GetDelimiterColor()
{
	return delimiterColor;
}

sf::Color Config::GetLiveCellColor()
{
	return liveCellColor;
}

sf::Color Config::GetDeadCellColor()
{
	return deadCellColor;
}

int Config::GetDelimitersFadingCoeff()
{
	return delimitersFadingCoeff;
}

size_t Config::GetFrameRefreshTime()
{
	return frameRefreshTime;
}

size_t Config::GetStateRefreshTime()
{
	return stateRefreshTime;
}

unsigned Config::GetWindowWidth()
{
	return windowWidth;
}

unsigned Config::GetWindowHeight()
{
	return windowHeight;
}

Config::State Config::ProcessSymbol(char symbol, State curState)
{
	switch (symbol)
	{
	case '#':
	case ' ':
		switch (curState)
		{
		case State::ReadKey:
			return State::SyntaxError;
		case State::ReadValue:
			SeekNextLine();
			return State::ValueHasBeenRead;
		default:
			break;
		}
	case '\n':
		switch (curState)
		{
		case State::ReadKey:
			return State::SyntaxError;
		case State::ReadValue:
			return State::ValueHasBeenRead;
		default:
			break;
		}
	case '=':
		switch (curState)
		{
		case State::ReadKey:
			return State::KeyHasBeenRead;
		case State::ReadValue:
			return State::SyntaxError;
		default:
			break;
		}
	default:
		break;
	}

	return curState;
}

void Config::SeekNextLine()
{
	while (file.get() != '\n' && !file.eof());
}

void Config::ProcessKeyValuePair()
{
	if (availableVariableNames.find(key) == availableVariableNames.end())
	{
		throw std::runtime_error("Error was occured while parsing config file. No such config variable '" + key + "'.");
	}

	try
	{
		switch (availableVariableNames.at(key))
		{
		case AvailableVariables::CellSize:
			cellSize = std::stoi(value);
			break;
		case AvailableVariables::DelimitersFadingCoeff:
			delimitersFadingCoeff = std::stoi(value);
			break;
		case AvailableVariables::RenderFreq:
			frameRefreshTime = std::stoi(value);
			break;
		case AvailableVariables::StateRefreshTime:
			stateRefreshTime = std::stoi(value);
			break;
		case AvailableVariables::WindowHeight:
			windowHeight = std::stoi(value);
			break;
		case AvailableVariables::WindowWidth:
			windowWidth = std::stoi(value);
			break;
		default:
			break;
		}
	}
	catch (const std::exception& e)
	{
		throw std::runtime_error("Error was occured while parsing config file. Failed parse numeric value '" + value + "' for '" + key + "' variable.");
	}

	try
	{
		switch (availableVariableNames.at(key))
		{
		case AvailableVariables::DelimiterColor:
			delimiterColor = sf::Color(std::stoi(value, nullptr, 16));
			break;
		case AvailableVariables::LiveCellColor:
			liveCellColor = sf::Color(std::stoi(value, nullptr, 16));
			break;
		default:
			break;
		}
	}
	catch (const std::exception& e)
	{
		throw std::runtime_error("Error was occured while parsing config file. Failed hexadecimal color value '" + value + "' for '" + key + "' variable.");
	}
}

void Config::SetDefaultValues()
{
	cellSize = Default::CELL_SIZE;
	delimiterColor = Default::DELIMITER_COLOR;
	liveCellColor = Default::LIVE_CELL_COLOR;
	deadCellColor = Default::DEAD_CELL_COLOR;
	delimitersFadingCoeff = Default::DELIMITERS_FADING_COEFF;
	frameRefreshTime = Default::FRAME_REFRESH_TIME;
	stateRefreshTime = Default::STATE_REFRESH_TIME;
	windowWidth = Default::WINDOW_WIDTH;
	windowHeight = Default::WINDOW_HEIGHT;
}
