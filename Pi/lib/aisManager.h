//This class handles all the AIS parsing and message dealing.
//It will get AIS messages from the sensor, turn them into AIS message objects,
//and do the necessary steps with them - either creating Ship objects or whatever.
#include <list>
#include <string>
#include <termios.h>
#include "serial.h"
#include "ship.h"
#include "utilities.h"
#include "logging.h"
#include "aisMessage.h"
class AISManager : public Serial {
	public:
		AISManager(const std::string &path);
		int update();
		void calculateNavScore(Score* scores, int num);

	private:
		std::list<Ship*> ships;

		int readSentence(std::string &payload);
		bool validChecksum(const std::string &line);
		unsigned char hexToDecimal(char hex);
		bool parse();
		void parseType1(AISMessage*);
		void parseType4(AISMessage*);
};