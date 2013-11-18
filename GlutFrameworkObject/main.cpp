#include <iostream>
#include "OscillateEngine.h"

glFrameworkBasic::OscillateEngine engineObject;

int main(int argc, char **argv)
{	

	engineObject.SetFullScreen(false);
	engineObject.Begin(argc, argv);
}