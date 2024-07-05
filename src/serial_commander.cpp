// Created by GeoNicZ
// mailto:geonicz@gmail.com

#include "Arduino.h"

int digital_pins[] = {0 - 13};
int analog_pins[] = {14 - 19};
String command = "";

void print_command(String command)
{
	for (unsigned int i = 0; i < command.length(); i++)
	{
		Serial.print(i);
		Serial.print(":\t");
		Serial.print(command[i]);
		Serial.print('\t');
		Serial.println(command[i], HEX);
	}
}
bool check_command(String command)
{
	// D0-13 + A0-5 + +-?! on,off,read,toggle
	command.toLowerCase();
	if (!(command.charAt(0) == 'd' or command.charAt(0) == 'a'))
		return false;
	for (unsigned int i = 1; i < command.length(); i++)
		if (!(command[i] == '+' or command[i] == '-' or command[i] == '?' or command[i] == '!' or command[i] == 0x0d or command[i] == 0x0a or isdigit(command[i])))
			return false;
	return true;
}
void execute()
{
	command.toLowerCase();

	String port = "";
	String state = "";

	for (unsigned int i = 1; i < command.length(); i++)
		if (!isDigit(command[i]))
		{
			state = command[i];
			break;
		}
		else
			port += command[i];

	pinMode(port.toInt(), OUTPUT);

	if (state == "+")
	{
		if (command[0] == 'd')
			digitalWrite(port.toInt(), HIGH);
		if (command[0] == 'a')
			analogWrite(port.toInt(), HIGH);
		return;
	}

	if (state == "-")
	{
		if (command[0] == 'd')
			digitalWrite(port.toInt(), LOW);
		if (command[0] == 'a')
			analogWrite(port.toInt(), LOW);
		return;
	}

	if (state == "!")
	{
		if (command[0] == 'd')
		{
			if (digitalRead(port.toInt()) == HIGH)
			{
				digitalWrite(port.toInt(), LOW);
				return;
			}
			digitalWrite(port.toInt(), HIGH);
		}
		if (command[0] == 'a')
		{
			if (digitalRead(port.toInt()) == HIGH)
			{
				digitalWrite(port.toInt(), LOW);
				return;
			}
			digitalWrite(port.toInt(), HIGH);
		}
		return;
	}
	if (state == "?")
	{
		if (command[0] == 'd')
			Serial.println(digitalRead(port.toInt()));
		if (command[0] == 'a')
			Serial.println(analogRead(port.toInt()));
	}
}
void setup()
{
	Serial.begin(9600);
}
void loop()
{
	command = Serial.readString();
	if (check_command(command))
		execute();
}
