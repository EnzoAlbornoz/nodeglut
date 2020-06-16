#include <napi.h>
#include <GL/freeglut.h>
#include <GL/freeglut_ucall.h>

// FreeGLUT 3.2 Function Bindings ==============================================

void _glutInit(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	int argsc = info[0].As<Napi::Number>().Int32Value();
	Napi::Array wargsv = info[1].As<Napi::Array>();
	// Allocate Structure
	char*  *argsv = new char*[argsc];
	for (size_t i = 0; i < argsc; i++) {
		std::string wargv =  wargsv.Get(i).As<Napi::String>().Utf8Value();
		char* argv = strdup(wargv.c_str());
		argsv[i] = argv;
	}
	// Exec Function
	glutInit(&argsc, argsv);
	// Clear Memory - Avoid Memory Leaking
	for (size_t i = 0; i < argsc; i++) {
		free(argsv[i]);
	}
	free(argsv);
	// Return Values
	return;
}

void _glutInitWindowSize(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	int width = info[0].As<Napi::Number>().Int32Value();
	int height = info[1].As<Napi::Number>().Int32Value();
	// Exec Function
	glutInitWindowSize(width, height);
	// Return Values
	return;
}

void _glutInitWindowPosition(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	int x = info[0].As<Napi::Number>().Int32Value();
	int y = info[1].As<Napi::Number>().Int32Value();
	// Exec Function
	glutInitWindowPosition(x, y);
	// Return Values
	return;
}

void _glutInitDisplayMode(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	unsigned int mode = info[0].As<Napi::Number>().Uint32Value();
	// Exec Function
	glutInitDisplayMode(mode);
	// Return Values
	return;
}


void _glutInitDisplayString(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	std::string displayMode = info[0].As<Napi::String>().Utf8Value();
	// Exec Function
	glutInitDisplayString(displayMode.c_str());
	// Return Values
	return;
}

void _glutInitErrorFunc(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Get Params
	const Napi::FunctionReference& callbackJS = Napi::Persistent(info[0].As<Napi::Function>());
	// Define Native Callback
	auto callback = [](const char *fmt, va_list ap, void *user_data) {
		// Define JS Callback
		Napi::FunctionReference *callbackJS = (Napi::FunctionReference *) user_data;
		Napi::Env env = callbackJS->Env();
		Napi::HandleScope scope(env);
		// Get Params
		va_list vaCp;
		va_copy(vaCp, ap);
		// Format String
		size_t strSize = 1 + snprintf(nullptr, 0, fmt, vaCp);
		char strMessage[strSize];
		snprintf(strMessage, strSize, fmt, ap);
		// Send Message
		napi_value args[] = { Napi::String::New(env, strMessage) };
		callbackJS->MakeCallback(env.Undefined(), 1, args);
		callbackJS->Unref();
	};
	// Exec Function
	glutInitErrorFuncUcall(callback, callbackJS);
	// Return Values
	return;
}

void _glutInitWarningFunc(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Get Params
	const Napi::FunctionReference& callbackJS = Napi::Persistent(info[0].As<Napi::Function>());
	// Define Native Callback
	auto callback = [](const char *fmt, va_list ap, void *user_data) {
		// Define JS Callback
		Napi::FunctionReference *callbackJS = (Napi::FunctionReference *) user_data;
		Napi::Env env = callbackJS->Env();
		Napi::HandleScope scope(env);
		// Get Params
		va_list vaCp;
		va_copy(vaCp, ap);
		// Format String
		size_t strSize = 1 + snprintf(nullptr, 0, fmt, vaCp);
		char strMessage[strSize];
		snprintf(strMessage, strSize, fmt, ap);
		// Send Message
		napi_value args[] = { Napi::String::New(env, strMessage) };
		callbackJS->MakeCallback(env.Undefined(), 1, args);
		callbackJS->Unref();
	};
	// Exec Function
	glutInitWarningFuncUcall(callback, callbackJS);
	// Return Values
	return;
}

void _glutMainLoop(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	// Exec Function
	glutMainLoop();
	// Return Values
	return;
}

void _glutMainLoopEvent(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	// Exec Function
	glutMainLoopEvent();
	// Return Values
	return;
}

void _glutLeaveMainLoop(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	// Exec Function
	glutLeaveMainLoop();
	// Return Values
	return;
}

Napi::Number _glutCreateWindow(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	const char* title = info[0].As<Napi::String>().Utf8Value().c_str();
	// Exec Function
	int windowId = glutCreateWindow(title);
	// Return Values
	return Napi::Number::New(env, windowId);
}

Napi::Number _glutCreateSubWindow(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	int window = info[0].As<Napi::Number>().Int32Value();
	int x = info[1].As<Napi::Number>().Int32Value();
	int y = info[2].As<Napi::Number>().Int32Value();
	int width = info[3].As<Napi::Number>().Int32Value();
	int height = info[4].As<Napi::Number>().Int32Value();
	// Exec Function
	int subWindowId = glutCreateSubWindow(window, x, y, width, height);
	// Return Values
	return Napi::Number::New(env, subWindowId);
}

void _glutDestroyWindow(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	int window = info[0].As<Napi::Number>().Int32Value();
	// Exec Function
	glutDestroyWindow(window);
	// Return Values
	return;
}

void _glutSetWindow(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	int window = info[0].As<Napi::Number>().Int32Value();
	// Exec Function
	glutSetWindow(window);
	// Return Values
	return;
}

Napi::Number _glutGetWindow(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	// Exec Function
	int window = glutGetWindow();
	// Return Values
	return Napi::Number::New(env, window);
}

void _glutSetWindowTitle(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	const char *title = info[0].As<Napi::String>().Utf8Value().c_str();
	// Exec Function
	glutSetWindowTitle(title);
	// Return Values
	return;
}

void _glutSetIconTitle(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	const char *title = info[0].As<Napi::String>().Utf8Value().c_str();
	// Exec Function
	glutSetIconTitle(title);
	// Return Values
	return;
}

void _glutReshapeWindow(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	int width = info[0].As<Napi::Number>().Int32Value();
	int height = info[1].As<Napi::Number>().Int32Value();
	// Exec Function
	glutReshapeWindow(width, height);
	// Return Values
	return;
}

void _glutPositionWindow(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	int x = info[0].As<Napi::Number>().Int32Value();
	int y = info[1].As<Napi::Number>().Int32Value();
	// Exec Function
	glutPositionWindow(x, y);
	// Return Values
	return;
}

void _glutShowWindow(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	// Exec Function
	glutShowWindow();
	// Return Values
	return;
}

void _glutHideWindow(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	// Exec Function
	glutHideWindow();
	// Return Values
	return;
}

void _glutIconifyWindow(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	// Exec Function
	glutIconifyWindow();
	// Return Values
	return;
}

void _glutPopWindow(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	// Exec Function
	glutPopWindow();
	// Return Values
	return;
}

void _glutPushWindow(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	// Exec Function
	glutPushWindow();
	// Return Values
	return;
}

void _glutFullScreen(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	// Exec Function
	glutFullScreen();
	// Return Values
	return;
}

void _glutLeaveFullScreen(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	// Exec Function
	glutLeaveFullScreen();
	// Return Values
	return;
}

void _glutFullScreenToggle(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	// Exec Function
	glutFullScreenToggle();
	// Return Values
	return;
}

void _glutPostRedisplay(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	// Exec Function
	glutPostRedisplay();
	// Return Values
	return;
}

void _glutPostWindowRedisplay(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	int window = info[0].As<Napi::Number>().Int32Value();
	// Exec Function
	glutPostWindowRedisplay(window);
	// Return Values
	return;
}

void _glutSwapBuffers(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	// Exec Function
	glutSwapBuffers();
	// Return Values
	return;
}

void _glutSetCursor(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	int cursor = info[0].As<Napi::Number>().Int32Value();
	// Exec Function
	glutSetCursor(cursor);
	// Return Values
	return;
}

void _glutWarpPointer(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	int x = info[0].As<Napi::Number>().Int32Value();
	int y = info[1].As<Napi::Number>().Int32Value();
	// Exec Function
	glutWarpPointer(x, y);
	// Return Values
	return;
}

void _glutEstablishOverlay(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	// Exec Function
	glutEstablishOverlay();
	// Return Values
	return;
}

void _glutRemoveOverlay(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	// Exec Function
	glutRemoveOverlay();
	// Return Values
	return;
}

void _glutUseLayer(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	GLenum layer = info[0].As<Napi::Number>().Uint32Value();
	// Exec Function
	glutUseLayer(layer);
	// Return Values
	return;
}

void _glutPostOverlayRedisplay(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	// Exec Function
	glutPostOverlayRedisplay();
	// Return Values
	return;
}

void _glutPostWindowOverlayRedisplay(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	int layer = info[0].As<Napi::Number>().Int32Value();
	// Exec Function
	glutPostWindowOverlayRedisplay(layer);
	// Return Values
	return;
}

void _glutShowOverlay(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	// Exec Function
	glutShowOverlay();
	// Return Values
	return;
}

void _glutHideOverlay(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	// Exec Function
	glutHideOverlay();
	// Return Values
	return;
}

Napi::Number _glutCreateMenu(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Get Params
	const Napi::FunctionReference& callbackJS = Napi::Persistent(info[0].As<Napi::Function>());
	// Define Native Callback
	auto callback = [](int value, void *user_data) {
		// Define JS Callback
		Napi::FunctionReference *callbackJS = (Napi::FunctionReference *) user_data;
		Napi::Env env = callbackJS->Env();
		Napi::HandleScope scope(env);
		// Call JS Callback
		napi_value args[] = { Napi::Number::New(env, value) };
		callbackJS->MakeCallback(env.Undefined(), 1, args);
		callbackJS->Unref();
	};
	// Exec Function
	int menuId = glutCreateMenuUcall(callback, callbackJS);
	// Return Values
	return Napi::Number::New(env, menuId);
}

void _glutDestroyMenu(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	int menu = info[0].As<Napi::Number>().Int32Value();
	// Exec Function
	glutDestroyMenu(menu);
	// Return Values
	return;
}

void _glutSetMenu(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	int menu = info[0].As<Napi::Number>().Int32Value();
	// Exec Function
	glutSetMenu(menu);
	// Return Values
	return;
}

Napi::Number _glutGetMenu(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Exec Function
	int menuId = glutGetMenu();
	// Return Values
	return Napi::Number::New(env, menuId);
}

void _glutAddMenuEntry(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	const char* name = info[0].As<Napi::String>().Utf8Value().c_str();
	int value = info[1].As<Napi::Number>().Int32Value();
	// Exec Function
	glutAddMenuEntry(name, value);
	// Return Values
	return;
}

void _glutAddSubMenu(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	const char* name = info[0].As<Napi::String>().Utf8Value().c_str();
	int menu = info[1].As<Napi::Number>().Int32Value();
	// Exec Function
	glutAddSubMenu(name, menu);
	// Return Values
	return;
}

void _glutChangeToMenuEntry(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	int entry = info[0].As<Napi::Number>().Int32Value();
	const char* name = info[1].As<Napi::String>().Utf8Value().c_str();
	int value = info[2].As<Napi::Number>().Int32Value();
	// Exec Function
	glutChangeToMenuEntry(entry, name, value);
	// Return Values
	return;
}

void _glutChangeToSubMenu(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	int entry = info[0].As<Napi::Number>().Int32Value();
	const char* name = info[1].As<Napi::String>().Utf8Value().c_str();
	int value = info[2].As<Napi::Number>().Int32Value();
	// Exec Function
	glutChangeToSubMenu(entry, name, value);
	// Return Values
	return;
}

void _glutSetMenuFont(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	int menuID = info[0].As<Napi::Number>().Int32Value();
	void* fontID = info[1].As<Napi::Buffer<GLubyte>>().Data();
	// Exec Function
	glutSetMenuFont(menuID, fontID);
	// Return Values
	return;
}

void _glutRemoveMenuItem(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	int entry = info[0].As<Napi::Number>().Int32Value();
	// Exec Function
	glutRemoveMenuItem(entry);
	// Return Values
	return;
}

void _glutAttachMenu(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	int button = info[0].As<Napi::Number>().Int32Value();
	// Exec Function
	glutAttachMenu(button);
	// Return Values
	return;
}

void _glutDetachMenu(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	int button = info[0].As<Napi::Number>().Int32Value();
	// Exec Function
	glutDetachMenu(button);
	// Return Values
	return;
}

void _glutMenuDestroyFunc(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Get Params
	const Napi::FunctionReference& callbackJS = Napi::Persistent(info[0].As<Napi::Function>());
	// Define Native Callback
	auto callback = [](void *user_data) {
		// Define JS Callback
		Napi::FunctionReference *callbackJS = (Napi::FunctionReference *) user_data;
		Napi::Env env = callbackJS->Env();
		Napi::HandleScope scope(env);
		// Call JS Callback
		napi_value args[] = {};
		callbackJS->MakeCallback(env.Undefined(), 0, args);
		callbackJS->Unref();
	};
	// Exec Function
	glutMenuDestroyFuncUcall(callback, callbackJS);
	// Return Values
	return;
}

void _glutTimerFunc(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	unsigned int msecs = info[0].As<Napi::Number>().Uint32Value();
	const Napi::FunctionReference& callbackJS = Napi::Persistent(info[1].As<Napi::Function>());
	int value = info[2].As<Napi::Number>().Int32Value();
	// Define Native Callback
	auto callback = [](int value, void *user_data) {
		// Define JS Callback
		Napi::FunctionReference *callbackJS = (Napi::FunctionReference *) user_data;
		Napi::Env env = callbackJS->Env();
		Napi::HandleScope scope(env);
		// Call JS Callback
		napi_value args[] = { Napi::Number::New(env, value) };
		callbackJS->MakeCallback(env.Undefined(), 1, args);
		callbackJS->Unref();
	};
	// Exec Function
	glutTimerFuncUcall(msecs, callback, value, callbackJS);
	// Return Values
	return;
}

void _glutIdleFunc(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	const Napi::FunctionReference& callbackJS = Napi::Persistent(info[0].As<Napi::Function>());
	// Define Native Callback
	auto callback = [](void *user_data) {
		// Define JS Callback
		Napi::FunctionReference *callbackJS = (Napi::FunctionReference *) user_data;
		Napi::Env env = callbackJS->Env();
		Napi::HandleScope scope(env);
		// Call JS Callback
		napi_value args[] = {};
		callbackJS->MakeCallback(env.Undefined(), 0, args);
		callbackJS->Unref();
	};
	// Exec Function
	glutIdleFuncUcall(callback, callbackJS);
	// Return Values
	return;
}

void _glutMenuStatusFunc(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	const Napi::FunctionReference& callbackJS = Napi::Persistent(info[0].As<Napi::Function>());
	// Define Native Callback
	auto callback = [](int status, int x, int y, void *user_data) {
		// Define JS Callback
		Napi::FunctionReference *callbackJS = (Napi::FunctionReference *) user_data;
		Napi::Env env = callbackJS->Env();
		Napi::HandleScope scope(env);
		// Call JS Callback
		napi_value args[] = {
			Napi::Number::New(env, status),
			Napi::Number::New(env,x),
			Napi::Number::New(env,y)
		};
		callbackJS->MakeCallback(env.Undefined(), 3, args);
		callbackJS->Unref();
	};
	// Exec Function
	glutMenuStatusFuncUcall(callback, callbackJS);
	// Return Values
	return;
}

static Napi::FunctionReference __glutMenuStateFuncCb;
void _glutMenuStateFunc(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	const Napi::FunctionReference& callbackJS = Napi::Persistent(info[0].As<Napi::Function>());
	// Define Native Callback
	auto callback = [](int status) {
		// Define JS Callback
		Napi::Env env = __glutMenuStateFuncCb.Env();
		Napi::HandleScope scope(env);
		// Call JS Callback
		napi_value args[] = { Napi::Number::New(env, status) };
		__glutMenuStateFuncCb.MakeCallback(env.Undefined(), 1, args);
	};
	// Remove Unref Callback
	if (__glutMenuStateFuncCb != nullptr) {
		__glutMenuStateFuncCb.Unref();
		__glutMenuStateFuncCb = Napi::Persistent(callbackJS.Value().As<Napi::Function>());
	}
	// Exec Function
	glutMenuStateFunc(callback);
	// Return Values
	return;
}

void _glutDisplayFunc(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	const Napi::FunctionReference& callbackJS = Napi::Persistent(info[0].As<Napi::Function>());
	// Define Native Callback
	auto callback = [](void *user_data) {
		// Define JS Callback
		Napi::FunctionReference *callbackJS = (Napi::FunctionReference *) user_data;
		Napi::Env env = callbackJS->Env();
		Napi::HandleScope scope(env);
		// Call JS Callback
		napi_value args[] = {};
		callbackJS->MakeCallback(env.Undefined(), 0, args);
		callbackJS->Unref();
	};
	// Exec Function
	glutDisplayFuncUcall(callback, callbackJS);
	// Return Values
	return;
}

void _glutOverlayDisplayFunc(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	const Napi::FunctionReference& callbackJS = Napi::Persistent(info[0].As<Napi::Function>());
	// Define Native Callback
	auto callback = [](void *user_data) {
		// Define JS Callback
		Napi::FunctionReference *callbackJS = (Napi::FunctionReference *) user_data;
		Napi::Env env = callbackJS->Env();
		Napi::HandleScope scope(env);
		// Call JS Callback
		napi_value args[] = {};
		callbackJS->MakeCallback(env.Undefined(), 0, args);
		callbackJS->Unref();
	};
	// Exec Function
	glutOverlayDisplayFuncUcall(callback, callbackJS);
	// Return Values
	return;
}

void _glutReshapeFunc(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	const Napi::FunctionReference& callbackJS = Napi::Persistent(info[0].As<Napi::Function>());
	// Define Native Callback
	auto callback = [](int width, int height, void *user_data) {
		// Define JS Callback
		Napi::FunctionReference *callbackJS = (Napi::FunctionReference *) user_data;
		Napi::Env env = callbackJS->Env();
		Napi::HandleScope scope(env);
		// Call JS Callback
		napi_value args[] = { Napi::Number::New(env, width), Napi::Number::New(env, height) };
		callbackJS->MakeCallback(env.Undefined(), 2, args);
		callbackJS->Unref();
	};
	// Exec Function
	glutReshapeFuncUcall(callback, callbackJS);
	// Return Values
	return;
}

void _glutPositionFunc(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	const Napi::FunctionReference& callbackJS = Napi::Persistent(info[0].As<Napi::Function>());
	// Define Native Callback
	auto callback = [](int x, int y, void *user_data) {
		// Define JS Callback
		Napi::FunctionReference *callbackJS = (Napi::FunctionReference *) user_data;
		Napi::Env env = callbackJS->Env();
		Napi::HandleScope scope(env);
		// Call JS Callback
		napi_value args[] = { Napi::Number::New(env, x), Napi::Number::New(env, y) };
		callbackJS->MakeCallback(env.Undefined(), 2, args);
		callbackJS->Unref();
	};
	// Exec Function
	glutPositionFuncUcall(callback, callbackJS);
	// Return Values
	return;
}

void _glutCloseFunc(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	const Napi::FunctionReference& callbackJS = Napi::Persistent(info[0].As<Napi::Function>());
	// Define Native Callback
	auto callback = [](void *user_data) {
		// Define JS Callback
		Napi::FunctionReference *callbackJS = (Napi::FunctionReference *) user_data;
		Napi::Env env = callbackJS->Env();
		Napi::HandleScope scope(env);
		// Call JS Callback
		napi_value args[] = {};
		callbackJS->MakeCallback(env.Undefined(), 0, args);
		callbackJS->Unref();
	};
	// Exec Function
	glutCloseFuncUcall(callback, callbackJS);
	// Return Values
	return;
}

void _glutKeyboardFunc(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	const Napi::FunctionReference& callbackJS = Napi::Persistent(info[0].As<Napi::Function>());
	// Define Native Callback
	auto callback = [](unsigned char key, int x, int y, void *user_data) {
		// Define JS Callback
		Napi::FunctionReference *callbackJS = (Napi::FunctionReference *) user_data;
		Napi::Env env = callbackJS->Env();
		Napi::HandleScope scope(env);
		// Call JS Callback
		napi_value args[] = {
			Napi::Number::New(env, key),
			Napi::Number::New(env, x),
			Napi::Number::New(env, y),
		};
		callbackJS->MakeCallback(env.Undefined(), 3, args);
		callbackJS->Unref();
	};
	// Exec Function
	glutKeyboardFuncUcall(callback, callbackJS);
	// Return Values
	return;
}

void _glutSpecialFunc(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	const Napi::FunctionReference& callbackJS = Napi::Persistent(info[0].As<Napi::Function>());
	// Define Native Callback
	auto callback = [](int key, int x, int y, void *user_data) {
		// Define JS Callback
		Napi::FunctionReference *callbackJS = (Napi::FunctionReference *) user_data;
		Napi::Env env = callbackJS->Env();
		Napi::HandleScope scope(env);
		// Call JS Callback
		napi_value args[] = {
			Napi::Number::New(env, key),
			Napi::Number::New(env, x),
			Napi::Number::New(env, y),
		};
		callbackJS->MakeCallback(env.Undefined(), 3, args);
		callbackJS->Unref();
	};
	// Exec Function
	glutSpecialFuncUcall(callback, callbackJS);
	// Return Values
	return;
}

void _glutKeyboardUpFunc(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	const Napi::FunctionReference& callbackJS = Napi::Persistent(info[0].As<Napi::Function>());
	// Define Native Callback
	auto callback = [](unsigned char key, int x, int y, void *user_data) {
		// Define JS Callback
		Napi::FunctionReference *callbackJS = (Napi::FunctionReference *) user_data;
		Napi::Env env = callbackJS->Env();
		Napi::HandleScope scope(env);
		// Call JS Callback
		napi_value args[] = {
			Napi::Number::New(env, key),
			Napi::Number::New(env, x),
			Napi::Number::New(env, y),
		};
		callbackJS->MakeCallback(env.Undefined(), 3, args);
		callbackJS->Unref();
	};
	// Exec Function
	glutKeyboardUpFuncUcall(callback, callbackJS);
	// Return Values
	return;
}

void _glutSpecialUpFunc(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	const Napi::FunctionReference& callbackJS = Napi::Persistent(info[0].As<Napi::Function>());
	// Define Native Callback
	auto callback = [](int key, int x, int y, void *user_data) {
		// Define JS Callback
		Napi::FunctionReference *callbackJS = (Napi::FunctionReference *) user_data;
		Napi::Env env = callbackJS->Env();
		Napi::HandleScope scope(env);
		// Call JS Callback
		napi_value args[] = {
			Napi::Number::New(env, key),
			Napi::Number::New(env, x),
			Napi::Number::New(env, y),
		};
		callbackJS->MakeCallback(env.Undefined(), 3, args);
		callbackJS->Unref();
	};
	// Exec Function
	glutSpecialUpFuncUcall(callback, callbackJS);
	// Return Values
	return;
}

void _glutMotionFunc(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	const Napi::FunctionReference& callbackJS = Napi::Persistent(info[0].As<Napi::Function>());
	// Define Native Callback
	auto callback = [](int x, int y, void *user_data) {
		// Define JS Callback
		Napi::FunctionReference *callbackJS = (Napi::FunctionReference *) user_data;
		Napi::Env env = callbackJS->Env();
		Napi::HandleScope scope(env);
		// Call JS Callback
		napi_value args[] = {
			Napi::Number::New(env, x),
			Napi::Number::New(env, y),
		};
		callbackJS->MakeCallback(env.Undefined(), 2, args);
		callbackJS->Unref();
	};
	// Exec Function
	glutMotionFuncUcall(callback, callbackJS);
	// Return Values
	return;
}

void _glutPassiveMotionFunc(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	const Napi::FunctionReference& callbackJS = Napi::Persistent(info[0].As<Napi::Function>());
	// Define Native Callback
	auto callback = [](int x, int y, void *user_data) {
		// Define JS Callback
		Napi::FunctionReference *callbackJS = (Napi::FunctionReference *) user_data;
		Napi::Env env = callbackJS->Env();
		Napi::HandleScope scope(env);
		// Call JS Callback
		napi_value args[] = {
			Napi::Number::New(env, x),
			Napi::Number::New(env, y),
		};
		callbackJS->MakeCallback(env.Undefined(), 2, args);
		callbackJS->Unref();
	};
	// Exec Function
	glutPassiveMotionFuncUcall(callback, callbackJS);
	// Return Values
	return;
}

void _glutMouseFunc(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	const Napi::FunctionReference& callbackJS = Napi::Persistent(info[0].As<Napi::Function>());
	// Define Native Callback
	auto callback = [](int button, int state, int x, int y, void *user_data) {
		// Define JS Callback
		Napi::FunctionReference *callbackJS = (Napi::FunctionReference *) user_data;
		Napi::Env env = callbackJS->Env();
		Napi::HandleScope scope(env);
		// Call JS Callback
		napi_value args[] = {
			Napi::Number::New(env, button),
			Napi::Number::New(env, state),
			Napi::Number::New(env, x),
			Napi::Number::New(env, y),
		};
		callbackJS->MakeCallback(env.Undefined(), 4, args);
		callbackJS->Unref();
	};
	// Exec Function
	glutMouseFuncUcall(callback, callbackJS);
	// Return Values
	return;
}

void _glutMouseWheelFunc(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	const Napi::FunctionReference& callbackJS = Napi::Persistent(info[0].As<Napi::Function>());
	// Define Native Callback
	auto callback = [](int wheel, int direction, int x, int y, void *user_data) {
		// Define JS Callback
		Napi::FunctionReference *callbackJS = (Napi::FunctionReference *) user_data;
		Napi::Env env = callbackJS->Env();
		Napi::HandleScope scope(env);
		// Call JS Callback
		napi_value args[] = {
			Napi::Number::New(env, wheel),
			Napi::Number::New(env, direction),
			Napi::Number::New(env, x),
			Napi::Number::New(env, y),
		};
		callbackJS->MakeCallback(env.Undefined(), 4, args);
		callbackJS->Unref();
	};
	// Exec Function
	glutMouseWheelFuncUcall(callback, callbackJS);
	// Return Values
	return;
}

void _glutEntryFunc(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	const Napi::FunctionReference& callbackJS = Napi::Persistent(info[0].As<Napi::Function>());
	// Define Native Callback
	auto callback = [](int state, void *user_data) {
		// Define JS Callback
		Napi::FunctionReference *callbackJS = (Napi::FunctionReference *) user_data;
		Napi::Env env = callbackJS->Env();
		Napi::HandleScope scope(env);
		// Call JS Callback
		napi_value args[] = {
			Napi::Number::New(env, state),
		};
		callbackJS->MakeCallback(env.Undefined(), 1, args);
		callbackJS->Unref();
	};
	// Exec Function
	glutEntryFuncUcall(callback, callbackJS);
	// Return Values
	return;
}

void _glutJoystickFunc(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	const Napi::FunctionReference& callbackJS = Napi::Persistent(info[0].As<Napi::Function>());
	int pollInterval = info[1].As<Napi::Number>().Int32Value();
	// Define Native Callback
	auto callback = [](unsigned int buttonMask, int x, int y, int z, void *user_data) {
		// Define JS Callback
		Napi::FunctionReference *callbackJS = (Napi::FunctionReference *) user_data;
		Napi::Env env = callbackJS->Env();
		Napi::HandleScope scope(env);
		// Call JS Callback
		napi_value args[] = {
			Napi::Number::New(env, buttonMask),
			Napi::Number::New(env, x),
			Napi::Number::New(env, y),
			Napi::Number::New(env, z),
		};
		callbackJS->MakeCallback(env.Undefined(), 4, args);
		callbackJS->Unref();
	};
	// Exec Function
	glutJoystickFuncUcall(callback, pollInterval, callbackJS);
	// Return Values
	return;
}

void _glutSpaceballMotionFunc(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	const Napi::FunctionReference& callbackJS = Napi::Persistent(info[0].As<Napi::Function>());
	// Define Native Callback
	auto callback = [](int x, int y, int z, void *user_data) {
		// Define JS Callback
		Napi::FunctionReference *callbackJS = (Napi::FunctionReference *) user_data;
		Napi::Env env = callbackJS->Env();
		Napi::HandleScope scope(env);
		// Call JS Callback
		napi_value args[] = {
			Napi::Number::New(env, x),
			Napi::Number::New(env, y),
			Napi::Number::New(env, z),
		};
		callbackJS->MakeCallback(env.Undefined(), 3, args);
		callbackJS->Unref();
	};
	// Exec Function
	glutSpaceballMotionFuncUcall(callback, callbackJS);
	// Return Values
	return;
}

void _glutSpaceballRotateFunc(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	const Napi::FunctionReference& callbackJS = Napi::Persistent(info[0].As<Napi::Function>());
	// Define Native Callback
	auto callback = [](int rx, int ry, int rz, void *user_data) {
		// Define JS Callback
		Napi::FunctionReference *callbackJS = (Napi::FunctionReference *) user_data;
		Napi::Env env = callbackJS->Env();
		Napi::HandleScope scope(env);
		// Call JS Callback
		napi_value args[] = {
			Napi::Number::New(env, rx),
			Napi::Number::New(env, ry),
			Napi::Number::New(env, rz),
		};
		callbackJS->MakeCallback(env.Undefined(), 3, args);
		callbackJS->Unref();
	};
	// Exec Function
	glutSpaceballRotateFuncUcall(callback, callbackJS);
	// Return Values
	return;
}

void _glutSpaceballButtonFunc(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	const Napi::FunctionReference& callbackJS = Napi::Persistent(info[0].As<Napi::Function>());
	// Define Native Callback
	auto callback = [](int button, int updown, void *user_data) {
		// Define JS Callback
		Napi::FunctionReference *callbackJS = (Napi::FunctionReference *) user_data;
		Napi::Env env = callbackJS->Env();
		Napi::HandleScope scope(env);
		// Call JS Callback
		napi_value args[] = {
			Napi::Number::New(env, button),
			Napi::Number::New(env, updown),
		};
		callbackJS->MakeCallback(env.Undefined(), 2, args);
		callbackJS->Unref();
	};
	// Exec Function
	glutSpaceballButtonFuncUcall(callback, callbackJS);
	// Return Values
	return;
}

void _glutButtonBoxFunc(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	const Napi::FunctionReference& callbackJS = Napi::Persistent(info[0].As<Napi::Function>());
	// Define Native Callback
	auto callback = [](int button, int updown, void *user_data) {
		// Define JS Callback
		Napi::FunctionReference *callbackJS = (Napi::FunctionReference *) user_data;
		Napi::Env env = callbackJS->Env();
		Napi::HandleScope scope(env);
		// Call JS Callback
		napi_value args[] = {
			Napi::Number::New(env, button),
			Napi::Number::New(env, updown),
		};
		callbackJS->MakeCallback(env.Undefined(), 2, args);
		callbackJS->Unref();
	};
	// Exec Function
	glutButtonBoxFuncUcall(callback, callbackJS);
	// Return Values
	return;
}

void _glutDialsFunc(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	const Napi::FunctionReference& callbackJS = Napi::Persistent(info[0].As<Napi::Function>());
	// Define Native Callback
	auto callback = [](int dial, int value, void *user_data) {
		// Define JS Callback
		Napi::FunctionReference *callbackJS = (Napi::FunctionReference *) user_data;
		Napi::Env env = callbackJS->Env();
		Napi::HandleScope scope(env);
		// Call JS Callback
		napi_value args[] = {
			Napi::Number::New(env, dial),
			Napi::Number::New(env, value),
		};
		callbackJS->MakeCallback(env.Undefined(), 2, args);
		callbackJS->Unref();
	};
	// Exec Function
	glutDialsFuncUcall(callback, callbackJS);
	// Return Values
	return;
}

void _glutTabletMotionFunc(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	const Napi::FunctionReference& callbackJS = Napi::Persistent(info[0].As<Napi::Function>());
	// Define Native Callback
	auto callback = [](int x, int y, void *user_data) {
		// Define JS Callback
		Napi::FunctionReference *callbackJS = (Napi::FunctionReference *) user_data;
		Napi::Env env = callbackJS->Env();
		Napi::HandleScope scope(env);
		// Call JS Callback
		napi_value args[] = {
			Napi::Number::New(env, x),
			Napi::Number::New(env, y),
		};
		callbackJS->MakeCallback(env.Undefined(), 2, args);
		callbackJS->Unref();
	};
	// Exec Function
	glutTabletMotionFuncUcall(callback, callbackJS);
	// Return Values
	return;
}

void _glutTabletButtonFunc(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	const Napi::FunctionReference& callbackJS = Napi::Persistent(info[0].As<Napi::Function>());
	// Define Native Callback
	auto callback = [](int button, int updown, int x, int y, void *user_data) {
		// Define JS Callback
		Napi::FunctionReference *callbackJS = (Napi::FunctionReference *) user_data;
		Napi::Env env = callbackJS->Env();
		Napi::HandleScope scope(env);
		// Call JS Callback
		napi_value args[] = {
			Napi::Number::New(env, button),
			Napi::Number::New(env, updown),
			Napi::Number::New(env, x),
			Napi::Number::New(env, y),
		};
		callbackJS->MakeCallback(env.Undefined(), 4, args);
		callbackJS->Unref();
	};
	// Exec Function
	glutTabletButtonFuncUcall(callback, callbackJS);
	// Return Values
	return;
}

void _glutVisibilityFunc(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	const Napi::FunctionReference& callbackJS = Napi::Persistent(info[0].As<Napi::Function>());
	// Define Native Callback
	auto callback = [](int state,void *user_data) {
		// Define JS Callback
		Napi::FunctionReference *callbackJS = (Napi::FunctionReference *) user_data;
		Napi::Env env = callbackJS->Env();
		Napi::HandleScope scope(env);
		// Call JS Callback
		napi_value args[] = {
			Napi::Number::New(env, state)
		};
		callbackJS->MakeCallback(env.Undefined(), 1, args);
		callbackJS->Unref();
	};
	// Exec Function
	glutVisibilityFuncUcall(callback, callbackJS);
	// Return Values
	return;
}

void _glutWindowStatusFunc(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	const Napi::FunctionReference& callbackJS = Napi::Persistent(info[0].As<Napi::Function>());
	// Define Native Callback
	auto callback = [](int state,void *user_data) {
		// Define JS Callback
		Napi::FunctionReference *callbackJS = (Napi::FunctionReference *) user_data;
		Napi::Env env = callbackJS->Env();
		Napi::HandleScope scope(env);
		// Call JS Callback
		napi_value args[] = {
			Napi::Number::New(env, state)
		};
		callbackJS->MakeCallback(env.Undefined(), 1, args);
		callbackJS->Unref();
	};
	// Exec Function
	glutWindowStatusFuncUcall(callback, callbackJS);
	// Return Values
	return;
}

void _glutSetOption(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	GLenum eWhat = info[0].As<Napi::Number>().Uint32Value();
	int value = info[1].As<Napi::Number>().Int32Value();
	// Exec Function
	glutSetOption(eWhat, value);
	// Return Values
	return;
}

Napi::Number _glutGet(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	GLenum state = info[0].As<Napi::Number>().Uint32Value();
	// Exec Function
	int stateValue = glutGet(state);
	// Return Values
	return Napi::Number::New(env, stateValue);
}

Napi::Number _glutDeviceGet(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	GLenum devInfo = info[0].As<Napi::Number>().Uint32Value();
	// Exec Function
	int devInfoValue = glutDeviceGet(devInfo);
	// Return Values
	return Napi::Number::New(env, devInfoValue);
}

Napi::Number _glutGetModifiers(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	// Exec Function
	int modKeyState = glutGetModifiers();
	// Return Values
	return Napi::Number::New(env, modKeyState);
}

Napi::Number _glutLayerGet(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	GLenum query = info[0].As<Napi::Number>().Uint32Value();
	// Exec Function
	int queryReturn = glutLayerGet(query);
	// Return Values
	return Napi::Number::New(env, queryReturn);
}

Napi::Number _glutExtensionSupported(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	const char* extension = info[0].As<Napi::String>().Utf8Value().c_str();
	// Exec Function
	int extSupported = glutExtensionSupported(extension);
	// Return Values
	return Napi::Number::New(env, extSupported);
}

Napi::External<GLUTproc> _glutGetProcAddress(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	const char* procName = info[0].As<Napi::String>().Utf8Value().c_str();
	// Exec Function
	GLUTproc procAddr = glutGetProcAddress(procName);
	// Return Values
	return Napi::External<GLUTproc>::New(env, &procAddr);
}

void _glutBitmapCharacter(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	void* font = info[0].As<Napi::Buffer<unsigned char>>().Data();
	int character = info[1].As<Napi::Number>().Int32Value();
	// Exec Function
	glutBitmapCharacter(font, character);
	// Return Values
	return;
}

void _glutBitmapString(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	void* font = info[0].As<Napi::Buffer<unsigned char>>().Data();
	const unsigned char* string = reinterpret_cast<const unsigned char*>(
		info[1].As<Napi::String>().Utf8Value().c_str()
	);
	// Exec Function
	glutBitmapString(font, string);
	// Return Values
	return;
}

Napi::Number _glutBitmapWidth(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	void* font = info[0].As<Napi::Buffer<unsigned char>>().Data();
	int character = info[1].As<Napi::Number>().Int32Value();
	// Exec Function
	int width = glutBitmapWidth(font, character);
	// Return Values
	return Napi::Number::New(env, width);
}

Napi::Number _glutBitmapLength(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	void* font = info[0].As<Napi::Buffer<unsigned char>>().Data();
	const unsigned char* string = reinterpret_cast<const unsigned char*>(
		info[1].As<Napi::String>().Utf8Value().c_str()
	);
	// Exec Function
	int length = glutBitmapLength(font, string);
	// Return Values
	return Napi::Number::New(env, length);
}

Napi::Number _glutBitmapHeight(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	void* font = info[0].As<Napi::Buffer<unsigned char>>().Data();
	// Exec Function
	int height = glutBitmapHeight(font);
	// Return Values
	return Napi::Number::New(env, height);
}

void _glutStrokeCharacter(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	void* font = info[0].As<Napi::Buffer<unsigned char>>().Data();
	int character = info[1].As<Napi::Number>().Int32Value();
	// Exec Function
	glutStrokeCharacter(font, character);
	// Return Values
	return;
}

void _glutStrokeString(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	void* font = info[0].As<Napi::Buffer<unsigned char>>().Data();
	const unsigned char* string = reinterpret_cast<const unsigned char*>(
		info[1].As<Napi::String>().Utf8Value().c_str()
	);
	// Exec Function
	glutStrokeString(font, string);
	// Return Values
	return;
}

Napi::Number _glutStrokeWidth(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	void* font = info[0].As<Napi::Buffer<unsigned char>>().Data();
	int character = info[1].As<Napi::Number>().Int32Value();
	// Exec Function
	int width = glutStrokeWidth(font, character);
	// Return Values
	return Napi::Number::New(env, width);
}

Napi::Number _glutStrokeWidthf(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	void* font = info[0].As<Napi::Buffer<unsigned char>>().Data();
	int character = info[1].As<Napi::Number>().Int32Value();
	// Exec Function
	GLfloat width = glutStrokeWidthf(font, character);
	// Return Values
	return Napi::Number::New(env, width);
}

Napi::Number _glutStrokeLength(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	void* font = info[0].As<Napi::Buffer<unsigned char>>().Data();
	const unsigned char* string = reinterpret_cast<const unsigned char*>(
		info[1].As<Napi::String>().Utf8Value().c_str()
	);
	// Exec Function
	int length = glutStrokeLength(font, string);
	// Return Values
	return Napi::Number::New(env, length);
}

Napi::Number _glutStrokeLengthf(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	void* font = info[0].As<Napi::Buffer<unsigned char>>().Data();
	const unsigned char* string = reinterpret_cast<const unsigned char*>(
		info[1].As<Napi::String>().Utf8Value().c_str()
	);
	// Exec Function
	int length = glutStrokeLengthf(font, string);
	// Return Values
	return Napi::Number::New(env, length);
}

Napi::Number _glutStrokeHeight(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	void* font = info[0].As<Napi::Buffer<unsigned char>>().Data();
	// Exec Function
	GLfloat height = glutStrokeHeight(font);
	// Return Values
	return Napi::Number::New(env, height);
}

void _glutWireSphere(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	double dRadius = info[0].As<Napi::Number>().DoubleValue();
	GLint slices = info[1].As<Napi::Number>().Int32Value();
	GLint stacks = info[2].As<Napi::Number>().Int32Value();
	// Exec Function
	glutWireSphere(dRadius, slices, stacks);
	// Return Values
	return;
}

void _glutSolidSphere(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	double dRadius = info[0].As<Napi::Number>().DoubleValue();
	GLint slices = info[1].As<Napi::Number>().Int32Value();
	GLint stacks = info[2].As<Napi::Number>().Int32Value();
	// Exec Function
	glutSolidSphere(dRadius, slices, stacks);
	// Return Values
	return;
}

void _glutWireTorus(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	double dInnerRadius = info[0].As<Napi::Number>().DoubleValue();
	double dOuterRadius = info[1].As<Napi::Number>().DoubleValue();
	GLint nSides = info[2].As<Napi::Number>().Int32Value();
	GLint nRings = info[3].As<Napi::Number>().Int32Value();
	// Exec Function
	glutWireTorus(dInnerRadius, dOuterRadius, nSides, nRings);
	// Return Values
	return;
}

void _glutSolidTorus(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	double dInnerRadius = info[0].As<Napi::Number>().DoubleValue();
	double dOuterRadius = info[1].As<Napi::Number>().DoubleValue();
	GLint nSides = info[2].As<Napi::Number>().Int32Value();
	GLint nRings = info[3].As<Napi::Number>().Int32Value();
	// Exec Function
	glutSolidTorus(dInnerRadius, dOuterRadius, nSides, nRings);
	// Return Values
	return;
}

void _glutWireCylinder(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	double base = info[0].As<Napi::Number>().DoubleValue();
	double height = info[1].As<Napi::Number>().DoubleValue();
	GLint slices = info[2].As<Napi::Number>().Int32Value();
	GLint stacks = info[3].As<Napi::Number>().Int32Value();
	// Exec Function
	glutWireCylinder(base, height, slices, stacks);
	// Return Values
	return;
}

void _glutSolidCylinder(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	double base = info[0].As<Napi::Number>().DoubleValue();
	double height = info[1].As<Napi::Number>().DoubleValue();
	GLint slices = info[2].As<Napi::Number>().Int32Value();
	GLint stacks = info[3].As<Napi::Number>().Int32Value();
	// Exec Function
	glutSolidCylinder(base, height, slices, stacks);
	// Return Values
	return;
}

void _glutWireCube(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	double dSize = info[0].As<Napi::Number>().DoubleValue();
	// Exec Function
	glutWireCube(dSize);
	// Return Values
	return;
}

void _glutSolidCube(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	double dSize = info[0].As<Napi::Number>().DoubleValue();
	// Exec Function
	glutSolidCube(dSize);
	// Return Values
	return;
}

void _glutWireTetrahedron(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	// Exec Function
	glutWireTetrahedron();
	// Return Values
	return;
}

void _glutSolidTetrahedron(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	// Exec Function
	glutSolidTetrahedron();
	// Return Values
	return;
}

void _glutWireOctahedron(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	// Exec Function
	glutWireOctahedron();
	// Return Values
	return;
}

void _glutSolidOctahedron(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	// Exec Function
	glutSolidOctahedron();
	// Return Values
	return;
}

void _glutWireDodecahedron(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	// Exec Function
	glutWireDodecahedron();
	// Return Values
	return;
}

void _glutSolidDodecahedron(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	// Exec Function
	glutSolidDodecahedron();
	// Return Values
	return;
}

void _glutWireIcosahedron(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	// Exec Function
	glutWireIcosahedron();
	// Return Values
	return;
}

void _glutSolidIcosahedron(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	// Exec Function
	glutSolidIcosahedron();
	// Return Values
	return;
}

void _glutWireRhombicDodecahedron(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	// Exec Function
	glutWireRhombicDodecahedron();
	// Return Values
	return;
}

void _glutSolidRhombicDodecahedron(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	// Exec Function
	glutSolidRhombicDodecahedron();
	// Return Values
	return;
}

void _glutWireTeapot(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	double dSize = info[0].As<Napi::Number>().DoubleValue();
	// Exec Function
	glutWireTeapot(dSize);
	// Return Values
	return;
}

void _glutSolidTeapot(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	double dSize = info[0].As<Napi::Number>().DoubleValue();
	// Exec Function
	glutSolidTeapot(dSize);
	// Return Values
	return;
}

void _glutWireTeacup(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	double dSize = info[0].As<Napi::Number>().DoubleValue();
	// Exec Function
	glutWireTeacup(dSize);
	// Return Values
	return;
}

void _glutSolidTeacup(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	double dSize = info[0].As<Napi::Number>().DoubleValue();
	// Exec Function
	glutSolidTeacup(dSize);
	// Return Values
	return;
}

void _glutWireTeaspoon(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	double dSize = info[0].As<Napi::Number>().DoubleValue();
	// Exec Function
	glutWireTeaspoon(dSize);
	// Return Values
	return;
}

void _glutSolidTeaspoon(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	double dSize = info[0].As<Napi::Number>().DoubleValue();
	// Exec Function
	glutSolidTeaspoon(dSize);
	// Return Values
	return;
}

void _glutSetVertexAttribCoord3(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	GLint attrib = info[0].As<Napi::Number>().Int32Value();
	// Exec Function
	glutSetVertexAttribCoord3(attrib);
	// Return Values
	return;
}

void _glutSetVertexAttribNormal(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	GLint attrib = info[0].As<Napi::Number>().Int32Value();
	// Exec Function
	glutSetVertexAttribNormal(attrib);
	// Return Values
	return;
}

void _glutSetVertexAttribTexCoord2(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	GLint attrib = info[0].As<Napi::Number>().Int32Value();
	// Exec Function
	glutSetVertexAttribTexCoord2(attrib);
	// Return Values
	return;
}

void _glutGameModeString(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	const char* string = info[0].As<Napi::String>().Utf8Value().c_str();
	// Exec Function
	glutGameModeString(string);
	// Return Values
	return;
}

void _glutEnterGameMode(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	// Exec Function
	glutEnterGameMode();
	// Return Values
	return;
}

void _glutLeaveGameMode(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	// Exec Function
	glutLeaveGameMode();
	// Return Values
	return;
}

Napi::Number _glutGameModeGet(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	GLenum query = info[0].As<Napi::Number>().Int32Value();
	// Exec Function
	int state = glutGameModeGet(query);
	// Return Values
	return Napi::Number::New(env, state);
}

Napi::Number _glutVideoResizeGet(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	GLenum query = info[0].As<Napi::Number>().Int32Value();
	// Exec Function
	int state = glutVideoResizeGet(query);
	// Return Values
	return Napi::Number::New(env, state);
}

void _glutSetupVideoResizing(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	// Exec Function
	glutSetupVideoResizing();
	// Return Values
	return;
}

void _glutStopVideoResizing(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	// Exec Function
	glutStopVideoResizing();
	// Return Values
	return;
}

void _glutVideoResize(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	int x = info[0].As<Napi::Number>().Int32Value();
	int y = info[0].As<Napi::Number>().Int32Value();
	int width = info[0].As<Napi::Number>().Int32Value();
	int height = info[0].As<Napi::Number>().Int32Value();
	// Exec Function
	glutVideoResize(x, y, width, height);
	// Return Values
	return;
}

void _glutVideoPan(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	int x = info[0].As<Napi::Number>().Int32Value();
	int y = info[0].As<Napi::Number>().Int32Value();
	int width = info[0].As<Napi::Number>().Int32Value();
	int height = info[0].As<Napi::Number>().Int32Value();
	// Exec Function
	glutVideoPan(x, y, width, height);
	// Return Values
	return;
}

void _glutSetColor(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	int cell = info[0].As<Napi::Number>().Int32Value();
	GLclampf red = info[0].As<Napi::Number>().FloatValue();
	GLclampf green = info[0].As<Napi::Number>().FloatValue();
	GLclampf blue = info[0].As<Napi::Number>().FloatValue();
	// Exec Function
	glutSetColor(cell, red, green, blue);
	// Return Values
	return;
}

Napi::Number _glutGetColor(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	int cell = info[0].As<Napi::Number>().Int32Value();
	int component = info[0].As<Napi::Number>().Int32Value();
	// Exec Function
	GLclampf intensity = glutGetColor(cell, component);
	// Return Values
	return Napi::Number::New(env, intensity);
}

void _glutCopyColormap(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	int window = info[0].As<Napi::Number>().Int32Value();
	// Exec Function
	glutCopyColormap(window);
	// Return Values
	return;
}

void _glutMultiEntryFunc(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	const Napi::FunctionReference& callbackJS = Napi::Persistent(info[0].As<Napi::Function>());
	// Define Native Callback
	auto callback = [](int id, int status, void *user_data) {
		// Define JS Callback
		Napi::FunctionReference *callbackJS = (Napi::FunctionReference *) user_data;
		Napi::Env env = callbackJS->Env();
		Napi::HandleScope scope(env);
		// Call JS Callback
		napi_value args[] = {
			Napi::Number::New(env, id),
			Napi::Number::New(env, status)
		};
		callbackJS->MakeCallback(env.Undefined(), 2, args);
		callbackJS->Unref();
	};
	// Exec Function
	glutMultiEntryFuncUcall(callback, callbackJS);
	// Return Values
	return;
}

void _glutMultiButtonFunc(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	const Napi::FunctionReference& callbackJS = Napi::Persistent(info[0].As<Napi::Function>());
	// Define Native Callback
	auto callback = [](int id, int x, int y, int button, int status, void *user_data) {
		// Define JS Callback
		Napi::FunctionReference *callbackJS = (Napi::FunctionReference *) user_data;
		Napi::Env env = callbackJS->Env();
		Napi::HandleScope scope(env);
		// Call JS Callback
		napi_value args[] = {
			Napi::Number::New(env, id),
			Napi::Number::New(env, x),
			Napi::Number::New(env, y),
			Napi::Number::New(env, button),
			Napi::Number::New(env, status)
		};
		callbackJS->MakeCallback(env.Undefined(), 5, args);
		callbackJS->Unref();
	};
	// Exec Function
	glutMultiButtonFuncUcall(callback, callbackJS);
	// Return Values
	return;
}

void _glutMultiMotionFunc(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	const Napi::FunctionReference& callbackJS = Napi::Persistent(info[0].As<Napi::Function>());
	// Define Native Callback
	auto callback = [](int id, int x, int y, void *user_data) {
		// Define JS Callback
		Napi::FunctionReference *callbackJS = (Napi::FunctionReference *) user_data;
		Napi::Env env = callbackJS->Env();
		Napi::HandleScope scope(env);
		// Call JS Callback
		napi_value args[] = {
			Napi::Number::New(env, id),
			Napi::Number::New(env, x),
			Napi::Number::New(env, y),
		};
		callbackJS->MakeCallback(env.Undefined(), 3, args);
		callbackJS->Unref();
	};
	// Exec Function
	glutMultiMotionFuncUcall(callback, callbackJS);
	// Return Values
	return;
}

void _glutMultiPassiveFunc(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	const Napi::FunctionReference& callbackJS = Napi::Persistent(info[0].As<Napi::Function>());
	// Define Native Callback
	auto callback = [](int id, int x, int y, void *user_data) {
		// Define JS Callback
		Napi::FunctionReference *callbackJS = (Napi::FunctionReference *) user_data;
		Napi::Env env = callbackJS->Env();
		Napi::HandleScope scope(env);
		// Call JS Callback
		napi_value args[] = {
			Napi::Number::New(env, id),
			Napi::Number::New(env, x),
			Napi::Number::New(env, y),
		};
		callbackJS->MakeCallback(env.Undefined(), 3, args);
		callbackJS->Unref();
	};
	// Exec Function
	glutMultiPassiveFuncUcall(callback, callbackJS);
	// Return Values
	return;
}

void _glutInitContextFunc(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	const Napi::FunctionReference& callbackJS = Napi::Persistent(info[0].As<Napi::Function>());
	// Define Native Callback
	auto callback = [](void *user_data) {
		// Define JS Callback
		Napi::FunctionReference *callbackJS = (Napi::FunctionReference *) user_data;
		Napi::Env env = callbackJS->Env();
		Napi::HandleScope scope(env);
		// Call JS Callback
		napi_value args[] = {};
		callbackJS->MakeCallback(env.Undefined(), 0, args);
		callbackJS->Unref();
	};
	// Exec Function
	glutInitContextFuncUcall(callback, callbackJS);
	// Return Values
	return;
}

void _glutAppStatusFunc(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	const Napi::FunctionReference& callbackJS = Napi::Persistent(info[0].As<Napi::Function>());
	// Define Native Callback
	auto callback = [](int event, void *user_data) {
		// Define JS Callback
		Napi::FunctionReference *callbackJS = (Napi::FunctionReference *) user_data;
		Napi::Env env = callbackJS->Env();
		Napi::HandleScope scope(env);
		// Call JS Callback
		napi_value args[] = {
			Napi::Number::New(env, event),
		};
		callbackJS->MakeCallback(env.Undefined(), 1, args);
		callbackJS->Unref();
	};
	// Exec Function
	glutAppStatusFuncUcall(callback, callbackJS);
	// Return Values
	return;
}

void _glutSetKeyRepeat(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	int repeatMode = info[0].As<Napi::Number>().Int32Value();
	// Exec Function
	glutSetKeyRepeat(repeatMode);
	// Return Values
	return;
}

void _glutIgnoreKeyRepeat(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	int ignore = info[0].As<Napi::Number>().Int32Value();
	// Exec Function
	glutIgnoreKeyRepeat(ignore);
	// Return Values
	return;
}

void _glutForceJoystickFunc(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	// Exec Function
	glutForceJoystickFunc();
	// Return Values
	return;
}

void _glutReportErrors(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	// Exec Function
	glutReportErrors();
	// Return Values
	return;
}
