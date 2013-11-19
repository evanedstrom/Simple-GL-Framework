#pragma once

#include "Element.h"
#include <iostream>

namespace glFrameworkBasic {
	class Circle : public Element {
	public:
		Circle()
		{
		}

		void Move(){
			// Increment Positions
			// Xf = Xi + V*T (Time regulated by clock)
			xPos += xVel;
			yPos += yVel;
			zPos += zVel;

			// Hard coded for test. Should get screen width and calculate extremes.
			// See here: http://www.opengl.org/documentation/specs/glut/spec3/node70.html
			if (xPos >= 90) xVel = xVel * -1;
			else if (xPos <= -90) xVel = xVel * -1;
			if (yPos >= 90) yVel = yVel * -1;
			else if (yPos <= -90) yVel = yVel * -1;
		}

		void Draw()
		{
			if (!show) return;

			glPushMatrix();                     // Save model-view matrix setting
			glTranslatef(xPos, yPos, zPos);    // Translate
			glScalef(xScale, yScale, zScale);

			// Draw a Circle:
			glBegin(GL_TRIANGLE_FAN);
			glColor3f(0.0f, 0.0f, 1.0f);  // Blue
			glVertex2f(0.0f, 0.0f);       // Center of circle
			int numSegments = 100;
			GLfloat angle;
			for (int i = 0; i <= numSegments; i++) { // Last vertex same as first vertex
				angle = i * 2.0f * 3.14159 / numSegments;  // 360 deg for all segments
				glVertex2f(cos(angle) * 0.5f, sin(angle) * 0.5f);
			}
			glEnd();

			glPopMatrix();                      // Restore the model-view matrix
		}
	};
}