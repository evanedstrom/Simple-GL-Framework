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

#include "Engine.h"

namespace glFrameworkBasic {
	Engine *Engine::instance = NULL;

	Engine::Engine()
	{
		instance = this;

		MatrixProjectionScale = 100.0;
		WINDOW_WIDTH = 640;
		WINDOW_HEIGHT = 480;
		WINDOW_POS_X = 50;
		WINDOW_POS_Y = 50;
		DO_FULL_SCN = false;
		windowTitle = "GLUT Framework Basic - By Evan Edstrom";
	}

	Engine::Engine(float projectionScale)
	{
		instance = this;

		MatrixProjectionScale = projectionScale;
		WINDOW_WIDTH = 640;
		WINDOW_HEIGHT = 480;
		WINDOW_POS_X = 50;
		WINDOW_POS_Y = 50;
		DO_FULL_SCN = false;
		windowTitle = "GLUT Framework Basic - By Evan Edstrom";
	}

	Engine::~Engine() { 
		// Iterate all items and delete them.
		for (std::vector<Element*>::iterator i = drawItems.begin(), e = drawItems.end(); i != e; ++i)
			delete (*i);
	}

	void Engine::SetWindowSize(int w, int h){
		WINDOW_WIDTH = w;
		WINDOW_HEIGHT = h;
	}
	void Engine::SetWindowPos(int x, int y){
		WINDOW_POS_X = x;
		WINDOW_POS_Y = y;
	}
	void Engine::SetFullScreen(bool doFs){
		DO_FULL_SCN = doFs;
	}
	void Engine::SetWindowTitle(std::string title){
		windowTitle = title;
	}

	void Engine::Begin(int argc, char **argv)
	{
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_DOUBLE);  // Enable double buffered mode
		
		generateWindow();	// Make OpenGL window (either full screen or window).

		// Register interaction type event handlers.
		glutMouseFunc(mousePressWrapper);
		glutMotionFunc(mouseMoveWrapper);
		glutKeyboardFunc(keyboardDownWrapper);
		glutKeyboardUpFunc(keyboardUpWrapper);
		glutSpecialFunc(specialKeyboardDownWrapper);
		glutSpecialUpFunc(specialKeyboardUpWrapper);

		glutDisplayFunc(displayWrapper);	// Register callback handler for window re-paint event
		glutReshapeFunc(reshapeWrapper);	// Register callback handler for window re-size event
		glutTimerFunc(0, timer, 0);			// First timer call immediately
		
		initGL();		// Our own OpenGL initialization
		setup();		// Any user defined setup that needs to happen.
		glutMainLoop();	// Enter the infinite event-processing loop
	}

	void Engine::initGL(){
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black and opaque
	}

	void Engine::setup(){
		// Implement in derived class.
	}

	void Engine::display(){
		glClear(GL_COLOR_BUFFER_BIT);   // Clear the color buffer
		glMatrixMode(GL_MODELVIEW);     // To operate on Model-View matrix
		glLoadIdentity();               // Reset the model-view matrix
		
		// Call the pre display loop:
		preDisplayLoop();

		// Do the loop
		for (unsigned int i = 0; i < drawItems.size(); i++)
		{
			drawItems.at(i)->Move();
			drawItems.at(i)->BeforeDraw();
			drawItems.at(i)->Draw();
			drawItems.at(i)->AfterDraw();
		}

		// Call the post display loop:
		postDisplayLoop();

		glutSwapBuffers();   // Double buffered - swap the front and back buffers
	}

	void Engine::preDisplayLoop(){
		// Implement in derived class.
	}

	void Engine::postDisplayLoop(){
		// Implement in derived class.
	}

	void Engine::reshape(GLsizei width, GLsizei height){
		// Compute aspect ratio of the new window
		if (height == 0) height = 1;	// To prevent divide by 0
		GLfloat aspect = (GLfloat)width / (GLfloat)height;

		// Set the viewport to cover the new window
		glViewport(0, 0, width, height);

		// Set the aspect ratio of the clipping area to match the viewport
		glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
		glLoadIdentity();
		if (width >= height) {
			// aspect >= 1, set the height from -1 to 1, with larger width
			gluOrtho2D(-1 * MatrixProjectionScale * aspect,
				1 * MatrixProjectionScale * aspect,
				-1 * MatrixProjectionScale,
				1 * MatrixProjectionScale);
		}
		else {
			// aspect < 1, set the width to -1 to 1, with larger height
			gluOrtho2D(-1 * MatrixProjectionScale, 
				1 * MatrixProjectionScale,
				-1 * MatrixProjectionScale / aspect,
				1 * MatrixProjectionScale / aspect);
		}
	}
	void Engine::idle(){
		glutPostRedisplay();   // Post a re-paint request to activate display()
	}

	void Engine::timer(int value){
		glutPostRedisplay();      // Post re-paint request to activate display()
		glutTimerFunc(refreshMills, timer, 0); // next Timer call milliseconds later
	}

	void Engine::mousePressFunc(int button, int state, int x, int y){
		/* Override this method in a subclass*/
	}

	void Engine::mouseMoveFunc(int x, int y){
		/* Override this method in a subclass*/
	}

	void Engine::keyboardUp(unsigned char key, int x, int y){
		/* Override this method in a subclass*/
		/* Uses ASCII integer value. Table at http://asciitable.com */
		keyStates.keyUp((int)key);
	}

	void Engine::keyboardDown(unsigned char key, int x, int y){
		/* Override this method in a subclass*/
		/* Uses ASCII integer value. Table at http://asciitable.com */
		if (key == 27) exit(0); // escape key
		keyStates.keyDown((int)key);
	}

	void Engine::specialKeyboardUp(int key, int x, int y){
		/* Override this method in a subclass*/
	}

	void Engine::specialKeyboardDown(int key, int x, int y){
		/* Override this method in a subclass*/
	}

	std::string Engine::getWindowString(){
		std::stringstream render;
		render << glutGet(GLUT_SCREEN_WIDTH) << "x" <<
			glutGet(GLUT_SCREEN_HEIGHT) << ":16@" << refreshMills;

		return render.str();
	}

	void Engine::generateWindow(){
		if (DO_FULL_SCN == true){
			glutGameModeString(getWindowString().c_str());
			glutEnterGameMode();
		}
		else {
			glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);   // Set the window's initial width & height - non-square
			glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
			glutCreateWindow(windowTitle.c_str());  // Create window with the given title
		}
	}

	void Engine::displayWrapper(){
		instance->display();
	}

	void Engine::reshapeWrapper(GLsizei width, GLsizei height){
		instance->reshape(width, height);
	}

	void Engine::mousePressWrapper(int button, int state, int x, int y){
		instance->mousePressFunc(button, state, x, y);
	}

	void Engine::mouseMoveWrapper(int x, int y){
		instance->mouseMoveFunc(x, y);
	}

	void Engine::keyboardUpWrapper(unsigned char key, int x, int y){
		instance->keyboardUp(key, x, y);
	}

	void Engine::keyboardDownWrapper(unsigned char key, int x, int y){
		instance->keyboardDown(key, x, y);
	}

	void Engine::specialKeyboardUpWrapper(int key, int x, int y){
		instance->specialKeyboardUp(key, x, y);
	}

	void Engine::specialKeyboardDownWrapper(int key, int x, int y){
		instance->specialKeyboardDown(key, x, y);
	}
}