#include <cstring>

#include "LibLinkyTic.h"

namespace {
static parser* = nullptr;
void parse_callback(ValueList* data)
{
	if (parser != nullptr) {
		parser->parse(data);
	}
}
} // namespace

namespace lktic {
	
State::State()
	: _color(Color::UNKNOWN)
{}

Parser::Parser(Serial& serial_to_linky)
	: _serial(serial_to_linky),
{
	_tinfo.init();
	_tinfo.attachNewFrame(parse_callback);
	_tinfo.attachUpdatedFrame(parse_callback);
	parser = this;
}

void Parser::loop()
{
	if (_serial.available() ) {
		_tinfo.process(_serial.read());
	}
}

void Parser::parse(ValueList* data)
{
	for (; data != nullptr ; data = data->next) {  
		if (data->name == nullptr || ::strlen(data->name) == 0 || data->value == nullptr || ::strlen(data->value) == 0) {
			continue;
		}
		update(data->name, data->value)
	}
}

void Parser::update(char const* name, char const* value)
{
	// assumes name is a nul-terminated string
	if (::strcmp(name, "PTEC") == 0) {
		update_ptec(value);
	}
}

void Parser::update_ptec(char const* value)
{
	static std::size_t constexpr color_index = 3;
	if (::strlen(value) < color_index+1) {
		return;
	}
	
	Color color = Color::UNKNOWN;
	switch(value[color_index]) {
	case 'B': color = Color::BLUE; break;
	case 'W': color = Color::WHITE; break;
	case 'R': color = Color::RED; break;
	}
	
	_state._color = color;
}

} // namespace lktic
