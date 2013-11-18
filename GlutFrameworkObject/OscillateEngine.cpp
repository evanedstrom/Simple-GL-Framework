///////////////////////////////////////////////////////////////////////////////
/// GlFrameworkBasic is free software : you can redistribute it and or modify
/// it under the terms of the GNU General Public License as published by
/// the Free Software Foundation, either version 3 of the License, or
/// (at your option) any later version.
///
/// GlFrameworkBasic is distributed in the hope that it will be useful,
/// but WITHOUT ANY WARRANTY; without even the implied warranty of
/// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
/// GNU General Public License for more details.
///
/// You should have received a copy of the GNU General Public License
/// along with Foobar.If not, see <http://www.gnu.org/licenses/>.
///
/// Author: Evan Edstrom
/// Date: 11/17/2013
/// Website: http://evanedstrom.com/glstart
///
///////////////////////////////////////////////////////////////////////////////

#include "OscillateEngine.h"
#include "TestCircle.h"

namespace glFrameworkBasic {
	/**
	* A demo subclass of Engine that draws two squares and a 
	* circle and moves the circle around the screen.
	*/
	OscillateEngine::OscillateEngine()
		: Engine()	//<- Constructor must be chained.
	{
		// Make Circle
		Circle *oscillateCircle = new Circle();
		oscillateCircle->SetVelocity(2, 0.5);
		oscillateCircle->SetScale(20);
		drawItems.push_back(oscillateCircle);

		// Make Top Square
		Element *square = new Element();
		square->SetScale(10);
		square->SetPosition(0, 40);
		drawItems.push_back(square);

		// Make Bottom Square
		Element *square2 = new Element();
		square2->SetScale(10);
		square2->SetPosition(0, -40);
		square2->SetAngle(180);
		drawItems.push_back(square2);
	}

	// Destructor is already chained.
	OscillateEngine::~OscillateEngine()
	{
	}
}