// this SDL window will be embedded inside a GTK+ tab
// doesn't work :(
#include <string>
#include <iostream>
#include <fstream>
#include <exception>
#include <SDL.h>
#include <SDL_video.h>
#include <SDL_timer.h>
#include <GL/gl.h>

using std::endl;
using std::string;
using std::ofstream;
using std::exception;

class SdlException : public exception {
private:
	string msg;
public:
	SdlException()
	: msg(SDL_GetError()) {}
	SdlException(const string& err)
	: msg(err) {
		string tmp(SDL_GetError());
		msg += " : " + tmp;
	}
	// why the throw() statement with destructor
	virtual ~SdlException() throw() {}
	
	virtual const char *what() const throw() override {
		return msg.c_str();
	}
};

class Sdl {
private:
	SDL_Window *sdlWindow;
	string idFileName;
	SDL_GLContext glCtx;
public:
	Sdl()
	: idFileName("appid.out"){
		if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) < 0)
			throw SdlException();
		sdlWindow = SDL_CreateWindow(nullptr,
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			400, 400,
			SDL_WINDOW_BORDERLESS|SDL_WINDOW_OPENGL
			|SDL_WINDOW_RESIZABLE
			);
		if(sdlWindow == nullptr)
			throw SdlException();
		auto windowID = SDL_GetWindowID(sdlWindow);
		ofstream idFile(idFileName);
		if(idFile) {
			idFile << windowID << endl;
			idFile.close();
		}
		glCtx = SDL_GL_CreateContext(sdlWindow);
		glClearColor(1, 0.5, 0.5, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		SDL_GL_SwapWindow(sdlWindow);
	}
	virtual ~Sdl() {
		SDL_GL_DeleteContext(glCtx);
		SDL_DestroyWindow(sdlWindow);
		SDL_Quit();
	}
};

int main(int argc, char *argv[]) {
	Sdl sdl;
	SDL_Delay(20000);
	return 0;
}
