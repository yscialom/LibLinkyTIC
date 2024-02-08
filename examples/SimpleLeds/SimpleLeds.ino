#include <LibLinkyTIC.h>

int const blueLedPin = 8;
int const whileLedPin = 9;
int const redLedPin = 10;

static lktic::Parser linky_parser;

void setup()
{
  pinMode(blueLedPin, OUTPUT);
  pinMode(whileLedPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);
}

does not compile

void loop()
{
  linky_parser.loop();
  
  digitalWrite(blueLedPin, LOW);
  digitalWrite(whileLedPin, LOW);
  digitalWrite(redLedPin, LOW);
  switch (linky_parser.state().color())
  {
  case lktic::Color::BLUE: digitalWrite(blueLedPin, HIGH); break;
  case lktic::Color::WHITE: digitalWrite(whileLedPin, HIGH); break;
  case lktic::Color::RED: digitalWrite(redLedPin, HIGH); break;
  default: break;
  }
}
