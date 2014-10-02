#ifndef RESTblu_h
#define RESTblu_h

#include "Arduino.h"
#include "WiFi.h"
#include "WiFiClient.h"

class RESTblu
{
	public:
		RESTblu(String UUID, String TOKEN);
		void send(String payload, String target, WiFiClient client);
	//	void recieve(String target);
	private:
		String _UUID;
		String _TOKEN;
	


};

#endif