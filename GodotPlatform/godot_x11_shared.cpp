/*************************************************************************/
/*  godot_server.cpp                                                     */
/*************************************************************************/
/*                       This file is part of:                           */
/*                           GODOT ENGINE                                */
/*                      https://godotengine.org                          */
/*************************************************************************/
/* Copyright (c) 2007-2019 Juan Linietsky, Ariel Manzur.                 */
/* Copyright (c) 2014-2019 Godot Engine contributors (cf. AUTHORS.md)    */
/*                                                                       */
/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the       */
/* "Software"), to deal in the Software without restriction, including   */
/* without limitation the rights to use, copy, modify, merge, publish,   */
/* distribute, sublicense, and/or sell copies of the Software, and to    */
/* permit persons to whom the Software is furnished to do so, subject to */
/* the following conditions:                                             */
/*                                                                       */
/* The above copyright notice and this permission notice shall be        */
/* included in all copies or substantial portions of the Software.       */
/*                                                                       */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*/
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                */
/*************************************************************************/

#include "main/main.h"
#include "x11_shared.h"

#include <iostream>
int main(int argc, char *argv[]) {

	X11_shared os;

	std::cout<<"Searching for a handle"<<std::endl;
	std::string handle_argument("--handle");
	bool found = false;
	int i;
	for(i=1; i<argc; i++){
		std::string arg(argv[i]);
		std::cout<<arg<<std::endl;
		if(arg == handle_argument){
			os.set_shared_handle(argv[i+1]);
			std::cout<<"Found handle = "<<argv[i+1]<<std::endl;
			found = true;
			break;
		}
	}
	if(found){
		std::cout<<"Handle found, arguments left = "<<argc - i - 1<<std::endl;
		Error err = Main::setup(argv[0], argc - i - 1, &argv[i+2]);
		if (err != OK)
			return 255;
	}else{
		std::cout<<"Handle not found, arguments left = "<<argc - 1<<std::endl;
		Error err = Main::setup(argv[0], argc - 1, &argv[1]);
		if (err != OK)
			return 255;
	}

	std::cout<<"Starting main"<<std::endl;
	if (Main::start())
		os.run(); // it is actually the OS that decides how to run
	Main::cleanup();

	return os.get_exit_code();
}
