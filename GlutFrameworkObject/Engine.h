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
/// along with GlFrameworkBasic. If not, see <http://www.gnu.org/licenses/>.
///
/// Author: Evan Edstrom
/// Date: 11/17/2013
/// Website: http://evanedstrom.com/glstart
/// Email: contact@evanedstrom.com
///
///////////////////////////////////////////////////////////////////////////////

#pragma once
#include <sstream>
#include <GL\gl.h>
#include <GL\glut.h>
#include <vector>

#include "Element.h"
#include "Keyboard.h"

namespace glFrameworkBasic {
	/**
	* Engine is a basic game engine based around OpenGL and GLUT.
	* Responsabilities of this class are to:
	* - initialize OpenGL and set modes,
	* - setup viewport and projection matrix,
	* - and register event handlers for keyboard, mouse, and display function.
	* Display function iterates drawItems vector and calls .Draw() on each Element.
	* Vector elements are deleted in destructor.
	* CAUTION: GLUT provides no provisions for returning to main. Must have engine
	* or derived class instance as a global in main() to call destructor. Alternative
	* is to use atexit().
	*/
	class Engine
	{
	public:
		/// <summary>Engine default constructor. Sets instance pointer to self.</summary>
		Engine();

		/// <summary>
		/// Engine BackColor Constructor. Calls glClearColor which makes the background
		/// go to a different color.
		/// </summary>
		/// <param name="rBack">Red Value from 0 to 1</param>
		/// <param name="gBack">Green Value from 0 to 1</param>
		/// <param name="bBack">Blue Value from 0 to 1</param>
		/// <param name="aBack">Alpha Value from 0 to 1, where 1 is solid.</param>
		Engine(float rBack, float gBack, float bBack, float aBack);
		
		/// <summary>
		/// Destructor for Engine. Properly deletes all items in draw vector
		/// because it uses pointers to store objects polymorphically.
		/// Iterates and calls delete.
		/// </summary>
		~Engine();

		/// <summary>
		/// Set size of drawn window in pixels.
		/// Default 640x480.
		/// Must be set before calling Begin().
		/// </summary>
		void SetWindowSize(int w, int h);

		/// <summary>
		/// Set top left corner position in pixels.
		/// Default 50, 50.
		/// Must be set before calling Begin();
		/// </summary>
		void SetWindowPos(int x, int y);

		/// <summary>
		/// Enable or disable fullscreen.
		/// Must be set before calling Begin()
		/// </summary>
		void SetFullScreen(bool doFs);

		/// <summary>
		/// Set title of window.
		/// Must be set before calling Begin()
		/// </summary>
		void SetWindowTitle(std::string title);

		/// <summary>
		/// Function that initializes GLUT properties, calls initGL, creates a window,
		/// and enters the main loop. Careful, GLUT has designed the main loop to never
		/// return.
		/// </summary>
		void Begin(int argc, char **argv);

	protected:
		std::vector<Element *> drawItems;

		static const int refreshMills = 30; // refresh interval in milliseconds
		const float MatrixProjectionScale = 100.0f; // Scale used for reshape function to determine unit scale.
		int WINDOW_WIDTH = 640;		// Window width in pixels
		int WINDOW_HEIGHT = 480;	// Window height in pixels
		int WINDOW_POS_X = 50;		// Window top left position (x) in pixels
		int WINDOW_POS_Y = 50;		// Window top left position (y) in pixels
		bool DO_FULL_SCN = false;		// If the window should open in full-screen
		std::string windowTitle = "GLUT Framework Basic - By Evan Edstrom";

		// Instance pointer to self. Needed for passing event handlers to glut.
		static Engine *instance;

		// Keyboard state manager
		Keyboard keyStates;

		/// <summary>Contains initilization procedures for GLUT.</summary>
		virtual void initGL();

		/// <summary>
		/// Generic function not implemented in base class. Is called
		/// during Begin() after initGL() but before glutMainLoop().
		/// </summary>
		virtual void setup();

		/// <summary>
		/// display is called every frame and contains logic for iterating
		/// vector, calling move, checking collision, and drawing.
		/// May be overwritten by a subclass, but subclass must at least call 
		/// glClear, glMatrixMode, glLoadIdentity, and glutSwapBuffers.
		/// </summary>
		virtual void display();

		/// <summary>
		/// Generic function not implemented in base class. Is called
		/// the before looping through vector in display(). Suggested uses
		/// include bounds checking, collision checking, and gameplay logic.
		/// </summary>
		virtual void preDisplayLoop();

		/// <summary>
		/// Generic function not implemented in base class. Is called
		/// the after looping through vector in display(). Suggested uses
		/// include bounds checking, collision checking, and gameplay logic.
		/// </summary>
		virtual void postDisplayLoop();

		/// <summary>
		/// Called on start and when window is resized.
		/// Designed to preserve aspect ration on different size windows
		/// so that objects are not distorted.
		/// </summary>
		virtual void reshape(GLsizei width, GLsizei height);

		/// <summary>
		/// Post a re-paint request.
		/// Not needed when using double buffers.
		/// </summary>
		virtual void idle();

		/// <summary>
		/// Maintains a constant clock for drawing frames.
		/// Clock governed by refreshMills
		/// </summary>
		static void timer(int value);
		
		// <summary>Mouse Press event handler. Not implemented, must override.</summary>
		virtual void mousePressFunc(int button, int state, int x, int y);
		
		// <summary>Mouse Move event handler. Not implemented, must override.</summary>
		virtual void mouseMoveFunc(int x, int y);

		// <summary>Key Release event handler. Not implemented, must override.</summary>
		virtual void keyboardUp(unsigned char key, int x, int y);
		
		// <summary>Key Press event handler. Looks for escape to exit.</summary>
		virtual void keyboardDown(unsigned char key, int x, int y);
		
		// <summary>Special Key Release event handler. Not implemented, must override.</summary>
		virtual void specialKeyboardUp(int key, int x, int y);
		
		// <summary>Special Key Press event handler. Not implemented, must override.</summary>
		virtual void specialKeyboardDown(int key, int x, int y);

	private:
		/// <summary>Generate GL compatible string for use with full-screen</summary>
		std::string getWindowString();

		/// <summary>Generate window for OpenGL</summary>
		void generateWindow();

		/// <summary>
		/// Static function to point to instance function.
		/// Necessary for GLUT to pass static function to glutDisplayFunc.
		/// Uses instance pointer for call.
		/// </summary>
		static void displayWrapper();

		/// <summary>
		/// Static function to point to instance function.
		/// Necessary for GLUT to pass static function to glutReshapeFunc.
		/// Uses instance pointer for call.
		/// </summary>
		static void reshapeWrapper(GLsizei width, GLsizei height);

		/// <summary>
		/// Static function to point to instance function.
		/// Uses instance pointer for call.
		/// </summary>
		static void mousePressWrapper(int button, int state, int x, int y);

		/// <summary>
		/// Static function to point to instance function.
		/// Uses instance pointer for call.
		/// </summary>
		static void mouseMoveWrapper(int x, int y);

		/// <summary>
		/// Static function to point to instance function.
		/// Uses instance pointer for call.
		/// </summary>
		static void keyboardUpWrapper(unsigned char key, int x, int y);

		/// <summary>
		/// Static function to point to instance function.
		/// Uses instance pointer for call.
		/// </summary>
		static void keyboardDownWrapper(unsigned char key, int x, int y);

		/// <summary>
		/// Static function to point to instance function.
		/// Uses instance pointer for call.
		/// </summary>
		static void specialKeyboardUpWrapper(int key, int x, int y);

		/// <summary>
		/// Static function to point to instance function.
		/// Uses instance pointer for call.
		/// </summary>
		static void specialKeyboardDownWrapper(int key, int x, int y);

	};
}