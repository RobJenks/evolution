#ifdef _DEBUG
#	pragma comment(lib, "LinearMath_Debug.lib")
#	pragma comment(lib, "Bullet3Common_Debug.lib")
#	pragma comment(lib, "BulletCollision_Debug.lib")
#	pragma comment(lib, "BulletDynamics_Debug.lib")
#	pragma comment(lib, "OpenGLWindow_Debug.lib")
#	pragma comment(lib, "BulletExampleBrowserLib_Debug.lib")
#else
#	pragma comment(lib, "LinearMath.lib")
#	pragma comment(lib, "Bullet3Common.lib")
#	pragma comment(lib, "BulletCollision.lib")
#	pragma comment(lib, "BulletDynamics.lib")
#	pragma comment(lib, "OpenGLWindow.lib")
#	pragma comment(lib, "BulletExampleBrowserLib.lib")
#endif

#include <stdio.h>
#include <iostream>

#include "btBulletDynamicsCommon.h"
#include "CommonInterfaces/CommonExampleInterface.h"
#include "CommonInterfaces/CommonGraphicsAppInterface.h"
#include "CommonInterfaces/CommonGUIHelperInterface.h"
#include "OpenGLWindow/SimpleOpenGL3App.h"
#include "OpenGLWindow/GwenOpenGL3CoreRenderer.h"
#include "ExampleBrowser/OpenGLExampleBrowser.h"
#include "ExampleBrowser/OpenGLGuiHelper.h"
#include "Utils/b3Clock.h"

#include "Application.h"


CommonExampleInterface* app;

b3MouseMoveCallback prevMouseMoveCallback = 0;
static void on_mouse_move(float x, float y)
{
	bool handled = false;
	handled = app->mouseMoveCallback(x, y);
	if (!handled)
	{
		if (prevMouseMoveCallback)
			prevMouseMoveCallback(x, y);
	}
}

b3MouseButtonCallback prevMouseButtonCallback = 0;
static void on_mouse_down(int button, int state, float x, float y)
{
	bool handled = false;

	handled = app->mouseButtonCallback(button, state, x, y);
	if (!handled)
	{
		if (prevMouseButtonCallback)
			prevMouseButtonCallback(button, state, x, y);
	}
}

b3KeyboardCallback prevKeyboardCallback = 0;
static void on_keyboard_event(int keycode, int state)
{
	bool handled = false;

	handled = app->keyboardCallback(keycode, state);
	if (!handled)
	{
		if (prevKeyboardCallback)
			prevKeyboardCallback(keycode, state);
	}
}

void initialise_callbacks(CommonGraphicsApp *app)
{

	prevMouseButtonCallback = app->m_window->getMouseButtonCallback();
	prevMouseMoveCallback = app->m_window->getMouseMoveCallback();
	prevKeyboardCallback = app->m_window->getKeyboardCallback();

	app->m_window->setMouseButtonCallback((b3MouseButtonCallback)on_mouse_down);
	app->m_window->setMouseMoveCallback((b3MouseMoveCallback)on_mouse_move);
	app->m_window->setKeyboardCallback((b3KeyboardCallback)on_keyboard_event);
}

int main(int argc, char* argv[])
{
	SimpleOpenGL3App* gl_app = new SimpleOpenGL3App("Evolution", 1024, 768, true);
	initialise_callbacks(gl_app);

	OpenGLGuiHelper gui(gl_app, false);
	CommonExampleOptions options(&gui);
	
	app = new Application(options.m_guiHelper);
	app->processCommandLineArgs(argc, argv);

	app->initPhysics();
	app->resetCamera();

	b3Clock clock;

	do
	{
		gl_app->m_instancingRenderer->init();
		gl_app->m_instancingRenderer->updateCamera(gl_app->getUpAxis());

		btScalar dtSec = btScalar(clock.getTimeInSeconds());
		//if (dtSec < 0.1)
		//	dtSec = 0.1;
		
		app->stepSimulation(dtSec);
		clock.reset();

		app->renderScene();

		DrawGridData dg;
		dg.upAxis = gl_app->getUpAxis();
		gl_app->drawGrid(dg);

		gl_app->swapBuffer();
	} while (!gl_app->m_window->requestedExit());

	app->exitPhysics();

	delete app;
	delete gl_app;
	return 0;
}