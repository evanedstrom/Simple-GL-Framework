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
/// Email: contact@evanedstrom.com
///
///////////////////////////////////////////////////////////////////////////////

#include "Element.h"

namespace glFrameworkBasic {
	Element::Element()
	{
		xPos = 0; yPos = 0; zPos = 0;
		xVel = 0; yVel = 0; zVel = 0;
		xScale = 1.0f; yScale = 1.0f; zScale = 1.0f;
		rotAngle = 0.0f;
	}

	Element::~Element()
	{
	}

	void Element::Draw(){
		// Sample draw function.

		if (!show) return;
		glPushMatrix();						// Save model-view matrix setting
		glTranslatef(xPos, yPos, zPos);		// Translate
		glScalef(xScale, yScale, zScale);	// Scale by given values.
		glRotatef(rotAngle, 0, 0, 1.0f);	// Rotate (assuming about z)

		// Draw a Square:
		glBegin(GL_QUADS);				// Each set of 4 vertices form a quad
		glColor3f(1.0f, 0.0f, 0.0f);	// Red
		glVertex2f(-0.3f, -0.3f);		// Bottom Left
		glVertex2f(-0.3f, 0.3f);		// Top Left
		glColor3f(0.0f, 0.0f, 1.0f);	// Blue
		glVertex2f(0.3f, 0.3f);			// Top Right
		glVertex2f(0.3f, -0.3f);		// Bottom Right
		glEnd();						// Done drawing quads.

		glPopMatrix();		// Restore the model-view matrix
	}

	void Element::Move(){
		// Increment Positions
		// Xf = Xi + V*T (Time regulated by clock)
		xPos += xVel;
		yPos += yVel;
		zPos += zVel;
	}

	void Element::BeforeDraw() {
		// Implement in derived class.
	}
	void Element::AfterDraw() {
		// Implement in derived class.
	}

	// Mutators:
	void Element::SetPosition(float x, float y){
		xPos = x;
		yPos = y;
	}
	void Element::SetPosition(float x, float y, float z){
		xPos = x;
		yPos = y;
		zPos = z;
	}
	void Element::SetVelocity(float x, float y){
		xVel = x;
		yVel = y;
	}
	void Element::SetVelocity(float x, float y, float z){
		xVel = x;
		yVel = y;
		zVel = z;
	}
	void Element::SetScale(float scale){
		xScale = scale;
		yScale = scale;
		zScale = scale;
	}
	void Element::SetScale(float x, float y){
		xScale = x;
		yScale = y;
	}
	void Element::SetScale(float x, float y, float z){
		xScale = x;
		yScale = y;
		zScale = z;
	}
	void Element::SetAngle(float angle){
		rotAngle = angle;
	}
	void Element::ShowObject(bool doShow){
		show = doShow;
	}
}