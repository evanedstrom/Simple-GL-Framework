/*
* The MIT License
*
* Copyright (c) 2010 Paul Solt, PaulSolt@gmail.com
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*/

#ifndef KEYBOARD_H
#define KEYBOARD_H

namespace glFrameworkBasic {

	/**
	* A basic utility class to keep track of what keys are currently being pressed.
	* Author: Paul Solt
	*/
	class Keyboard {
	private:
		enum Key { UP, DOWN, RELEASED };
		static const int NUMBER_KEYS = 256;
		Key keys[NUMBER_KEYS];

	public:

		/**
		* Description: Initialize all keys in the up state
		*/
		Keyboard();

		/**
		* Description: Set the key to the down state
		* <param name="key">the key that is being pressed</param>
		*/
		void keyDown(int key);

		/**
		* Description: Set the key to the up state
		* <param name="key">the key that is being released</param>
		*/
		void keyUp(int key);

		/**
		* Description: Test to see if the key is being pressed
		*/
		bool isKeyDown(int key);
	};

}
#endif
