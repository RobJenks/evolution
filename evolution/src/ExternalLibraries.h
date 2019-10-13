#pragma once

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")

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