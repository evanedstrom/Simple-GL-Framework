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

#pragma once
#include <GL\glut.h>

namespace glFrameworkBasic {
	/**
	* Gameplay Element keeps information about an object's position and velocity
	* so it can be drawn in 3D space. Contains the logic to update an element's
	* position in space and logic to draw the particular type of object.
	* If not overwritten, the Draw() function will draw a blue/red square.
	*/
	class Element
	{
	protected:
		float xPos, yPos, zPos;
		float xVel, yVel, zVel;
		float xScale, yScale, zScale;
		float rotAngle; 
		bool show = true;

	public:
		/// Initializes positions and velocities to 0.
		/// Initializes scales to 1
		/// Initializes show to true.
		Element();

		/// Destructor. No dynamic memory in this class.
		~Element();

		/// <summary>
		/// Draws element on screen.
		/// Must call glPushMatrix and glPopMatrix before and after drawing.
		/// Generic function draws a red/blue square on screen.
		/// Overwite with function if different shape or behavior is required.
		/// </summary>
		virtual void Draw();

		/// <summary>
		/// Updates position of element. Adds velocity to position.
		/// Does not handle rotational velocity.
		/// </summary>
		virtual void Move();

		/// <summary>Set the position values.</summary>
		void SetPosition(float x, float y);
		/// <summary>Set the position values.</summary>
		void SetPosition(float x, float y, float z);
		
		/// <summary>Set the velocity values.</summary>
		void SetVelocity(float x, float y);
		/// <summary>Set the velocity values.</summary>
		void SetVelocity(float x, float y, float z);

		/// <summary>Set scale. Draw() is responsable for using this.</summary>
		void SetScale(float scale);
		/// <summary>Set scale. Draw() is responsable for using this.</summary>
		void SetScale(float x, float y);
		/// <summary>Set scale. Draw() is responsable for using this.</summary>
		void SetScale(float x, float y, float z);

		/// <summary>Set rotation angle</summary>
		void SetAngle(float angle);

		/// <summary>Enable / Disable whether object should be shown.</summary>
		void ShowObject(bool doShow);
	};

}