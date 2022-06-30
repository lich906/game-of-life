#include "Config.h"

using namespace std::string_literals;

void Config::ReadFromFile(const std::string& fileName)
try
{
	m_file.open(fileName);

	if (!m_file.is_open())
	{
		throw std::runtime_error("Failed to read config from file '" + fileName + "'. Failed to open file.");
	}

	State state = State::NewLine;

	char symbol;
	while (!m_file.eof())
	{
		m_file.get(symbol);
		state = ProcessSymbol(symbol, state);

		switch (state)
		{
		case State::ReadKey:
			m_key.push_back(symbol);
			break;
		case State::ReadValue:
			m_value.push_back(symbol);
			break;
		case State::SkipComment:
			SeekNextLine();
			break;
		case State::KeyHasBeenRead:
			state = State::ReadValue;
			break;
		case State::ValueHasBeenRead:
			ProcessKeyValuePair();
			m_key.clear();
			m_value.clear();
			state = State::NewLine;
			break;
		case State::SyntaxError:
			throw std::runtime_error("Error was occured while parsing config file. Syntax error.");
		default:
			break;
		}
	}

	m_file.close();
}
catch (const std::runtime_error& e)
{
	SetDefaultValues();

	if (m_file.is_open())
	{
		m_file.close();
	}
	
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
		case State::NewLine:
			SeekNextLine();
			break;
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
		case State::NewLine:
			return curState;
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
		case State::NewLine:
			return State::SyntaxError;
		default:
			break;
		}
	default:
		switch (curState)
		{
		case State::NewLine:
			return State::ReadKey;
		default:
			break;
		}
		break;
	}

	return curState;
}

void Config::SeekNextLine()
{
	while (m_file.get() != '\n' && !m_file.eof());
}

void Config::ProcessKeyValuePair()
{
	if (availableVariableNames.find(m_key) == availableVariableNames.end())
	{
		throw std::runtime_error("Error was occured while parsing config file. No such config variable '" + m_key + "'.");
	}

	try
	{
		switch (availableVariableNames.at(m_key))
		{
		case AvailableVariables::CellSize:
			cellSize = std::stoi(m_value);
			break;
		case AvailableVariables::DelimitersFadingCoeff:
			delimitersFadingCoeff = std::stoi(m_value);
			break;
		case AvailableVariables::FrameRefreshTime:
			frameRefreshTime = std::stoi(m_value);
			break;
		case AvailableVariables::StateRefreshTime:
			stateRefreshTime = std::stoi(m_value);
			break;
		case AvailableVariables::WindowHeight:
			windowHeight = std::stoi(m_value);
			break;
		case AvailableVariables::WindowWidth:
			windowWidth = std::stoi(m_value);
			break;
		default:
			break;
		}
	}
	catch (const std::exception&)
	{
		throw std::runtime_error("Error was occured while parsing config file. Failed parse numeric value '" + m_value + "' for '" + m_key + "' variable.");
	}

	try
	{
		switch (availableVariableNames.at(m_key))
		{
		case AvailableVariables::DelimiterColor:
			delimiterColor = sf::Color(std::stoul(m_value, nullptr, 16));
			break;
		case AvailableVariables::LiveCellColor:
			liveCellColor = sf::Color(std::stoul(m_value, nullptr, 16));
			break;
		default:
			break;
		}
	}
	catch (const std::exception&)
	{
		throw std::runtime_error("Error was occured while parsing config file. Failed to parse hexadecimal color value '" + m_value + "' for '" + m_key + "' variable.");
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
