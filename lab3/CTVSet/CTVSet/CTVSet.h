#pragma once
#include <iostream>
#include <string>
#include <map>

const int MIN_CHANNEL = 1;
const int MAX_CHANNEL = 99;
const int INIT_PREVIOUS_CHANNEL = -1;
const int INIT_STARTED_CHANNEL = 1;
const int TURNED_OFF_CHANNEL = 0;

class CTVSet
{
public:
	CTVSet();
	bool TurnOn();
	bool TurnOff();
	bool IsTurnedOn() const;
	bool SelectChannel(int channel);
	bool SelectChannel(std::string str);
	bool SelectPreviousChannel();
	int GetChannel() const;

	bool SetChannelName(std::string str, int channel);
	bool DeleteChannelName(std::string str);
	std::string GetChannelName(int channel) const;
	int GetChannelByName(std::string str) const;

	void ShowInfo();

private:
	int m_currentChannel;
	int m_previousChannel;
	bool m_isWorking;
	std::map<std::string, int> channelsMap;
};
