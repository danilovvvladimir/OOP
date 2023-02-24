#include "CTVSet.h"

int main()
{
	CTVSet tv;
	tv.TurnOn();
	tv.SelectChannel(99);
	tv.SelectChannel(1);
	tv.SelectPreviousChannel();
	tv.SetChannelName("Discovery", 1);
	tv.SetChannelName("TNT", 2);
	tv.SetChannelName("CTC", 56);
	tv.SetChannelName("CNN", 99);
	tv.SetChannelName("NOTCNN", 99);
	tv.DeleteChannelName("NOTCNN");
	tv.SelectChannel("TNT");
	tv.SelectChannel("Discovery");
	tv.ShowInfo();
	std::cout << tv.GetChannelName(20) << std::endl;
	std::cout << tv.GetChannelByName("TNTs") << std::endl;
	return 0;
}