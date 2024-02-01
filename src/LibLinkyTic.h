#include <LibTeleinfo.h>

namespace lktic {

enum class Color
{
	UNKNOWN,
	BLUE,
	WHITE,
	RED
};

class Parser;

class State
{
friend class Parser;
	Color _color;
public:
	State();
	Color color() const { return _color; }
};
	
class Parser
{
	Serial& _serial;
	TInfo _tinfo;
	State _state;
private:
	void update(char const* name, char const* value);
	void update_ptec(char const* value)
public:
	Parser(Serial& serial_to_linky);
	void loop();
	void parse(ValueList* data)
	State const& state() { return _state; }
public:
	static void parse_callback(ValueList* data);
};

} // namespace lktic
