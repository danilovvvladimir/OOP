#include "CTVSet.h"

CTVSet::CTVSet()
	: m_isWorking(false)
	, m_currentChannel(TURNED_OFF_CHANNEL)
	, m_previousChannel(INIT_PREVIOUS_CHANNEL)
{
}

bool CTVSet::TurnOn()
{
	if (!m_isWorking)
	{
		m_isWorking = true;
		if (m_previousChannel == INIT_PREVIOUS_CHANNEL)
		{
			m_currentChannel = INIT_STARTED_CHANNEL;
		}
		else
		{
			m_currentChannel = m_previousChannel;
		}
		return true;
	}
	return false;
}

bool CTVSet::TurnOff()
{
	if (m_isWorking)
	{
		m_isWorking = false;
		m_previousChannel = m_currentChannel;
		m_currentChannel = TURNED_OFF_CHANNEL;
		return true;
	}
	return false;
}

bool CTVSet::IsTurnedOn() const
{
	return (m_isWorking)
		? true
		: false;
}

bool CTVSet::SelectChannel(int channel)
{
	if (!m_isWorking)
	{
		return false;
	}

	if (channel < MIN_CHANNEL || channel > MAX_CHANNEL)
	{
		return false;
	}

	m_previousChannel = m_currentChannel;
	m_currentChannel = channel;
	return true;
}

bool CTVSet::SelectChannel(std::string channelName)
{
	if (!m_isWorking)
	{
		return false;
	}

	auto it = channelsMap.find(channelName);
	if (it == channelsMap.end())
	{
		return false;
	}

	m_previousChannel = m_currentChannel;
	m_currentChannel = it->second;
	return true;
}

bool CTVSet::SelectPreviousChannel()
{
	if (!m_isWorking)
	{
		return false;
	}
	if (m_previousChannel != INIT_PREVIOUS_CHANNEL)
	{
		m_currentChannel = m_previousChannel;
		return true;
	}
	return false;
}

int CTVSet::GetChannel() const
{
	return m_currentChannel;
}

bool CTVSet::SetChannelName(std::string channelName, int channel)
{
	if (!m_isWorking)
	{
		return false;
	}

	if (channel < MIN_CHANNEL || channel > MAX_CHANNEL)
	{
		return false;
	}

	bool isChannelOccupied = false;
	std::string OccupiedChannelName;

	for (auto el : channelsMap)
	{
		if (el.second == channel)
		{
			isChannelOccupied = true;
			OccupiedChannelName = el.first;
		}
	}

	if (isChannelOccupied)
	{
		channelsMap.erase(OccupiedChannelName);
	}

	auto it = channelsMap.find(channelName);
	if (it != channelsMap.end())
	{
		channelsMap.erase(channelName);
	}

	channelsMap.emplace(channelName, channel);
	return true;
}

bool CTVSet::DeleteChannelName(std::string channelName)
{
	if (!m_isWorking)
	{
		return false;
	}

	auto it = channelsMap.find(channelName);
	if (it == channelsMap.end())
	{
		return false;
	}
	channelsMap.erase(channelName);
	return true;
}

std::string CTVSet::GetChannelName(int channel) const
{
	if (!m_isWorking)
	{
		return false;
	}

	if (channel < MIN_CHANNEL || channel > MAX_CHANNEL)
	{
		return false;
	}

	for (auto el : channelsMap)
	{
		if (el.second == channel)
		{
			return el.first;
		}
	}

	return std::string();
}

int CTVSet::GetChannelByName(std::string channelName) const
{
	if (!m_isWorking)
	{
		return false;
	}

	auto it = channelsMap.find(channelName);
	if (it != channelsMap.end())
	{
		return it->second;
	}

	return 0;
}

void CTVSet::ShowInfo()
{
	std::cout << "TV status: " << m_isWorking << std::endl;
	std::cout << "Current Channel: " << m_currentChannel << std::endl;
	std::cout << "Previous Channel: " << m_previousChannel << std::endl
			  << std::endl;
	std::cout << "Channels map: " << std::endl;

	std::map<int, std::string> reversedMap;
	for (auto el : channelsMap)
	{
		reversedMap.emplace(el.second, el.first);
	}

	for (auto el : reversedMap)
	{
		std::cout << el.first << " - " << el.second << std::endl;
	}
}
