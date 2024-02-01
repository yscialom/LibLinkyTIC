#ifndef LIB_LINKY_TIC_H
#define LIB_LINKY_TIC_H
#include <Arduino.h>
#include "LibTeleinfo.h"

namespace lktic {

enum class Color
{
	UNKNOWN,
	BLUE,
	WHITE,
	RED
};

//class Parser;

class State
{
friend class Parser;

public: // special functions
	State();

public: // members functions
	Color color() const { return _color; }

private: // data members
	Color _color;
};
	
class Parser
{
public: // special functions
	Parser(Serial& serial_to_linky);

public: // member functions
	void loop();
	State const& state() { return _state; }

private: // data members
	Serial& _serial;
	TInfo _tinfo;
	State _state;

private: // private member functions
	void parse(ValueList* data);
	void update(char const* name, char const* value);
	void update_ptec(char const* value);
};

} // namespace lktic
#endif // LIB_LINKY_TIC_H
