#include <unistd.h>
#include <unordered_map>
#include <napi.h>
#include <GL/freeglut.h>
#include <GL/freeglut_ucall.h>

// AUX Structs
typedef struct NAPI_CB_REF_S {
	napi_ref ref;
	napi_env env;
} NAPI_CB_REF;

typedef struct NAPI_CB_VAL_S {
	napi_value val;
	napi_env env;
} NAPI_CB_VAL;

struct NAPI_CB_MENUS {
	// Menu Callbacks
	std::unordered_map<int, Napi::FunctionReference> _glutCreateMenu;
	Napi::FunctionReference _glutMenuDestroyFunc;
};

struct NAPI_CB_WINDOWS {
	// Window callbacks
	std::unordered_map<int,Napi::FunctionReference> _glutDisplayFunc;
	std::unordered_map<int,Napi::FunctionReference> _glutOverlayDisplayFunc;
	std::unordered_map<int,Napi::FunctionReference> _glutReshapeFunc;
	std::unordered_map<int,Napi::FunctionReference> _glutPositionFunc;
	std::unordered_map<int,Napi::FunctionReference> _glutCloseFunc;
	std::unordered_map<int,Napi::FunctionReference> _glutKeyboardFunc;
	std::unordered_map<int,Napi::FunctionReference> _glutSpecialFunc;
	std::unordered_map<int,Napi::FunctionReference> _glutKeyboardUpFunc;
	std::unordered_map<int,Napi::FunctionReference> _glutSpecialUpFunc;
	std::unordered_map<int,Napi::FunctionReference> _glutMotionFunc;
	std::unordered_map<int,Napi::FunctionReference> _glutPassiveMotionFunc;
	std::unordered_map<int,Napi::FunctionReference> _glutMouseFunc;
	std::unordered_map<int,Napi::FunctionReference> _glutMouseWheelFunc;
	std::unordered_map<int,Napi::FunctionReference> _glutEntryFunc;
	std::unordered_map<int,Napi::FunctionReference> _glutJoystickFunc;
	std::unordered_map<int,Napi::FunctionReference> _glutSpaceballMotionFunc;
	std::unordered_map<int,Napi::FunctionReference> _glutSpaceballRotateFunc;
	std::unordered_map<int,Napi::FunctionReference> _glutSpaceballButtonFunc;
	std::unordered_map<int,Napi::FunctionReference> _glutButtonBoxFunc;
	std::unordered_map<int,Napi::FunctionReference> _glutDialsFunc;
	std::unordered_map<int,Napi::FunctionReference> _glutTabletMotionFunc;
	std::unordered_map<int,Napi::FunctionReference> _glutTabletButtonFunc;
	std::unordered_map<int,Napi::FunctionReference> _glutVisibilityFunc;
	std::unordered_map<int,Napi::FunctionReference> _glutWindowStatusFunc;
	std::unordered_map<int,Napi::FunctionReference> _glutMultiEntryFunc;
	std::unordered_map<int,Napi::FunctionReference> _glutMultiButtonFunc;
	std::unordered_map<int,Napi::FunctionReference> _glutMultiMotionFunc;
	std::unordered_map<int,Napi::FunctionReference> _glutMultiPassiveFunc;
	std::unordered_map<int,Napi::FunctionReference> _glutInitContextFunc;
	std::unordered_map<int,Napi::FunctionReference> _glutAppStatusFunc;
};

struct NAPI_CB_GLOBAL {
	// Global Callbacks
	Napi::FunctionReference _glutIdleFunc;
	Napi::FunctionReference _glutMenuStatusFunc;
	Napi::FunctionReference _glutMenuStateFunc;
};

static NAPI_CB_MENUS  menusCallbacks;
static NAPI_CB_WINDOWS windowsCallbacks;
static NAPI_CB_GLOBAL globalCallbacks;
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

Napi::FunctionReference _glutInitErrorFuncCBRef;
void _glutInitErrorFunc(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Get Params
	Napi::Function callbackJS = info[0].As<Napi::Function>();
	// Define CBRef
	_glutInitErrorFuncCBRef.Reset();
	_glutInitErrorFuncCBRef.Reset(callbackJS,1);
	// Define Native Callback
	auto callback = [](const char *fmt, va_list ap) {
		// Define JS Callback
		Napi::Function callbackJS = _glutInitErrorFuncCBRef.Value();
		Napi::Env env = callbackJS.Env();
		Napi::HandleScope scope(env);
		// Get Params
		va_list vaCp;
		va_copy(vaCp, ap);
		// Format String
		size_t strSize = 1 + vsnprintf(nullptr, 0, fmt, vaCp);
		char strMessage[strSize];
		vsnprintf(strMessage, strSize, fmt, ap);
		// Send Message
		callbackJS.Call({ Napi::String::New(env, strMessage) });
	};
	// Exec Function
	glutInitErrorFunc(callback);
	// Return Values
	return;
}

Napi::FunctionReference _glutInitWarningFuncCBRef;
void _glutInitWarningFunc(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Get Params
	Napi::Function callbackJS = info[0].As<Napi::Function>();
	// Define CBRef
	_glutInitWarningFuncCBRef.Reset();
	_glutInitWarningFuncCBRef.Reset(callbackJS,1);
	// Define Native Callback
	auto callback = [](const char *fmt, va_list ap) {
		// Define JS Callback
		Napi::Function callbackJS = _glutInitWarningFuncCBRef.Value();
		Napi::Env env = callbackJS.Env();
		Napi::HandleScope scope(env);
		// Get Params
		va_list vaCp;
		va_copy(vaCp, ap);
		// Format String
		size_t strSize = 1 + vsnprintf(nullptr, 0, fmt, vaCp);
		char strMessage[strSize];
		vsnprintf(strMessage, strSize, fmt, ap);
		// Send Message
		callbackJS.Call({ Napi::String::New(env, strMessage) });
	};
	// Exec Function
	glutInitWarningFunc(callback);
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
	Napi::Function callbackJS = info[0].As<Napi::Function>();
	// Define Native Callback
	auto callback = [](int value) {
		// Get Current Menu and Window
		int currMenu = glutGetMenu();
		// Define JS Callback
		Napi::Function callbackJS = menusCallbacks._glutCreateMenu[currMenu].Value();
		Napi::Env env = callbackJS.Env();
		Napi::HandleScope scope(env);
		// Call JS Callback
		napi_value args[] = { Napi::Number::New(env, value) };
		callbackJS.MakeCallback(Napi::Object::New(env), 1, args);
	};
	// Exec Function
	int menuId = glutCreateMenu(callback);
	// Set Current Callback for Menu
	menusCallbacks._glutCreateMenu[menuId].Reset(callbackJS, 1U);
	menusCallbacks._glutCreateMenu[menuId].SuppressDestruct();
	// Return Values
	return Napi::Number::New(env, menuId);
}

void _glutDestroyMenu(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	int menu = info[0].As<Napi::Number>().Int32Value();
	// Clear Callbacks References
	menusCallbacks._glutCreateMenu[menu].Reset();
	// Clear Map Entry
	menusCallbacks._glutCreateMenu.erase(menu);
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
	Napi::Function callbackJS = info[0].As<Napi::Function>();
	// Reset Callback Reference
	menusCallbacks._glutMenuDestroyFunc.Reset(callbackJS, 1U);
	menusCallbacks._glutMenuDestroyFunc.SuppressDestruct();
	// Define Native Callback
	auto callback = []() {
		// Define JS Callback
		Napi::Function callbackJS = menusCallbacks._glutMenuDestroyFunc.Value();
		Napi::Env env = callbackJS.Env();
		Napi::HandleScope scope(env);
		// Call JS Callback
		napi_value args[] = {};
		callbackJS.MakeCallback(Napi::Object::New(env), 0, args);
	};
	// Exec Function
	glutMenuDestroyFunc(callback);
	// Return Values
	return;
}

void _glutTimerFunc(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	unsigned int msecs = info[0].As<Napi::Number>().Uint32Value();
	Napi::FunctionReference callbackJS = Napi::Persistent(info[1].As<Napi::Function>());
	int value = info[2].As<Napi::Number>().Int32Value();
	// Setup CBRef
	callbackJS.SuppressDestruct();
	NAPI_CB_REF* cbref = new NAPI_CB_REF {
		napi_ref(callbackJS),
		napi_env(callbackJS.Env())
	};
	// Define Native Callback
	auto callback = [](int value, void *user_data) {
		// Define Callback Ref
		NAPI_CB_REF* cbref = (NAPI_CB_REF*) user_data;
		// Define JS Callback
		Napi::FunctionReference callbackJS(cbref->env, cbref->ref);
		Napi::Env env = callbackJS.Env();
		Napi::HandleScope scope(env);
		// Call JS Callback
		callbackJS.Call({ Napi::Number::New(env, value) });
		callbackJS.Unref();
		// Delete CBRef
		delete cbref;
	};
	// Exec Function
	glutTimerFuncUcall(msecs, callback, value, cbref);
	// Return Values
	return;
}

//! Memory Leak On This Function !//
// TODO: FIX MEMORY LEAK -> It iterates so much that I think that V8 can't handle it without allocate heap wildly
void _glutIdleFunc(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// TODO: By now, throw an error that alert about memory leak
	if (info.Length() < 2 || !info[1].IsBoolean() || !info[1].As<Napi::Boolean>().Value()) {
		return Napi::Error::New(env, "This method, for now, may end up causing memory leak. I'm working to resolve this issue").ThrowAsJavaScriptException();
	}
	// Check Disable Function
	if (info[0].IsNull() || info[0].IsUndefined()) {
		// Reset Function
		globalCallbacks._glutIdleFunc.Reset();
		// Exec Function
		glutIdleFunc(NULL);
		// Return Values
		return;
	} else {
		// Load Params
		Napi::Function callbackJS = info[0].As<Napi::Function>();
		// Setup Reference
		globalCallbacks._glutIdleFunc.Reset();
		globalCallbacks._glutIdleFunc.Reset(callbackJS, 1U);
		// Define Native Callback
		auto callback = []() {
			// Define JS Callback
			Napi::Function callbackJS = globalCallbacks._glutIdleFunc.Value();
			// Call JS Callback
			callbackJS.Call({});
		};
		// Exec Function
		glutIdleFunc(callback);
		// Return Values
		return;
	}
}

void _glutMenuStatusFunc(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Check Disable Function
	if (info[0].IsNull() || info[0].IsUndefined()) {
		// Reset Function
		globalCallbacks._glutMenuStatusFunc.Reset();
		// Exec Function
		glutMenuStatusFunc(NULL);
		// Return Values
		return;
	} else {
		// Load Params
		Napi::Function callbackJS = info[0].As<Napi::Function>();
		// Setup Reference
		globalCallbacks._glutMenuStatusFunc.Reset(callbackJS, 1U);
		globalCallbacks._glutMenuStatusFunc.SuppressDestruct();
		// Define Native Callback
		auto callback = [](int status, int x, int y) {
			// Define JS Callback
			Napi::Function callbackJS = globalCallbacks._glutMenuStatusFunc.Value();
			Napi::Env env = callbackJS.Env();
			Napi::HandleScope scope(env);
			// Call JS Callback
			napi_value args[] = {
				Napi::Number::New(scope.Env(), status),
				Napi::Number::New(scope.Env(),x),
				Napi::Number::New(scope.Env(),y)
			};
			callbackJS.MakeCallback(Napi::Object::New(scope.Env()), 3, args);
		};
		// Exec Function
		glutMenuStatusFunc(callback);
		// Return Values
		return;
	}
}

void _glutMenuStateFunc(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Check Disable Function
	if (info[0].IsNull() || info[0].IsUndefined()) {
		// Reset Function
		globalCallbacks._glutMenuStateFunc.Reset();
		// Exec Function
		glutMenuStateFunc(NULL);
		// Return Values
		return;
	} else {
		// Load Params
		Napi::Function callbackJS = info[0].As<Napi::Function>();
		// Setup Reference
		globalCallbacks._glutMenuStateFunc.Reset(callbackJS, 1U);
		globalCallbacks._glutMenuStateFunc.SuppressDestruct();
		// Define Native Callback
		auto callback = [](int status) {
			// Define JS Callback
			Napi::Env env = globalCallbacks._glutMenuStateFunc.Env();
			Napi::HandleScope scope(env);
			// Call JS Callback
			napi_value args[] = { Napi::Number::New(env, status) };
			globalCallbacks._glutMenuStateFunc.MakeCallback(Napi::Object::New(scope.Env()), 1, args);
		};
		// Exec Function
		glutMenuStateFunc(callback);
		// Return Values
		return;
	}
}

void _glutDisplayFunc(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Get Current Window Id
	int wId = glutGetWindow();
	// Load Params
	Napi::Function callbackJS = info[0].As<Napi::Function>();
	// Reset Reference
	windowsCallbacks._glutDisplayFunc[wId].Reset(callbackJS, 1);
	// Define Native Callback
	auto callback = []() {
		// Get Current Window
		int wId = glutGetWindow();
		// Define JS Callback
		Napi::Function callbackJS = windowsCallbacks._glutDisplayFunc[wId].Value();
		Napi::Env env = callbackJS.Env();
		Napi::HandleScope scope(env);
		// Call JS Callback
		napi_value args[] = {};
		callbackJS.MakeCallback(Napi::Object::New(env), 0, args);
	};
	// Exec Function
	glutDisplayFunc(callback);
	// Return Values
	return;
}

void _glutOverlayDisplayFunc(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Get Current Window Id
	int wId = glutGetWindow();
	// Load Params
	Napi::Function callbackJS = info[0].As<Napi::Function>();
	// Reset Reference
	windowsCallbacks._glutOverlayDisplayFunc[wId].Reset(callbackJS, 1);
	// Define Native Callback
	auto callback = []() {
		// Get Current Window
		int wId = glutGetWindow();
		// Define JS Callback
		Napi::Function callbackJS = windowsCallbacks._glutOverlayDisplayFunc[wId].Value();
		Napi::Env env = callbackJS.Env();
		Napi::HandleScope scope(env);
		// Call JS Callback
		napi_value args[] = {};
		callbackJS.MakeCallback(Napi::Object::New(env), 0, args);
	};
	// Exec Function
	glutOverlayDisplayFunc(callback);
	// Return Values
	return;
}

void _glutReshapeFunc(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	if (info[0].IsNull() || info[0].IsUndefined()) {
		// Get Current Window Id
		int wId = glutGetWindow();
		// Reset Function
		windowsCallbacks._glutReshapeFunc[wId].Reset();
		// Exec Function
		glutReshapeFunc(NULL);
		// Return Values
		return;
	} else {
		// Get Current Window Id
		int wId = glutGetWindow();
		// Load Params
		Napi::Function callbackJS = info[0].As<Napi::Function>();
		// Reset Reference
		windowsCallbacks._glutReshapeFunc[wId].Reset(callbackJS, 1);
		// Define Native Callback
		auto callback = [](int width, int height) {
			// Get Current Window
			int wId = glutGetWindow();
			// Define JS Callback
			Napi::Function callbackJS = windowsCallbacks._glutReshapeFunc[wId].Value();
			Napi::Env env = callbackJS.Env();
			Napi::HandleScope scope(env);
			// Call JS Callback
			napi_value args[] = { Napi::Number::New(scope.Env(), width), Napi::Number::New(scope.Env(), height) };
			callbackJS.MakeCallback(Napi::Object::New(scope.Env()), 2, args);
		};
		// Exec Function
		glutReshapeFunc(callback);
		// Return Values
		return;
	}
}

void _glutPositionFunc(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	if (info[0].IsNull() || info[0].IsUndefined()) {
		// Get Current Window Id
		int wId = glutGetWindow();
		// Reset Function
		windowsCallbacks._glutPositionFunc[wId].Reset();
		// Exec Function
		glutPositionFunc(NULL);
		// Return Values
		return;
	} else {
		// Get Current Window Id
		int wId = glutGetWindow();
		// Load Params
		Napi::Function callbackJS = info[0].As<Napi::Function>();
		// Reset Reference
		windowsCallbacks._glutPositionFunc[wId].Reset(callbackJS, 1);
		// Define Native Callback
		auto callback = [](int x, int y) {
			// Get Current Window
			int wId = glutGetWindow();
			// Define JS Callback
			Napi::Function callbackJS = windowsCallbacks._glutPositionFunc[wId].Value();
			Napi::Env env = callbackJS.Env();
			Napi::HandleScope scope(env);
			// Call JS Callback
			napi_value args[] = { Napi::Number::New(scope.Env(), x), Napi::Number::New(scope.Env(), y) };
			callbackJS.MakeCallback(Napi::Object::New(scope.Env()), 2, args);
		};
		// Exec Function
		glutPositionFunc(callback);
		// Return Values
		return;
	}
}

void _glutCloseFunc(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	if (info[0].IsNull() || info[0].IsUndefined()) {
		// Get Current Window Id
		int wId = glutGetWindow();
		// Reset Function
		windowsCallbacks._glutCloseFunc[wId].Reset();
		// Exec Function
		glutCloseFunc(NULL);
		// Return Values
		return;
	} else {
		// Get Current Window Id
		int wId = glutGetWindow();
		// Load Params
		Napi::Function callbackJS = info[0].As<Napi::Function>();
		// Reset Reference
		windowsCallbacks._glutCloseFunc[wId].Reset(callbackJS, 1);
		// Define Native Callback
		auto callback = []() {
			// Get Current Window
			int wId = glutGetWindow();
			// Define JS Callback
			Napi::Function callbackJS = windowsCallbacks._glutCloseFunc[wId].Value();
			Napi::Env env = callbackJS.Env();
			Napi::HandleScope scope(env);
			// Call JS Callback
			napi_value args[] = {};
			callbackJS.MakeCallback(Napi::Object::New(scope.Env()), 0, args);
		};
		// Exec Function
		glutCloseFunc(callback);
		// Return Values
		return;
	}
}

void _glutKeyboardFunc(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	if (info[0].IsNull() || info[0].IsUndefined()) {
		// Get Current Window Id
		int wId = glutGetWindow();
		// Reset Function
		windowsCallbacks._glutKeyboardFunc[wId].Reset();
		// Exec Function
		glutKeyboardFunc(NULL);
		// Return Values
		return;
	} else {
		// Get Current Window Id
		int wId = glutGetWindow();
		// Load Params
		Napi::Function callbackJS = info[0].As<Napi::Function>();
		// Reset Reference
		windowsCallbacks._glutKeyboardFunc[wId].Reset(callbackJS, 1);
		// Define Native Callback
		auto callback = [](unsigned char key, int x, int y) {
			// Get Current Window
			int wId = glutGetWindow();
			// Define JS Callback
			Napi::Function callbackJS = windowsCallbacks._glutKeyboardFunc[wId].Value();
			Napi::Env env = callbackJS.Env();
			Napi::HandleScope scope(env);
			// Call JS Callback
			napi_value args[] = {
				Napi::Number::New(env, key),
				Napi::Number::New(env, x),
				Napi::Number::New(env, y),
			};
			callbackJS.MakeCallback(Napi::Object::New(scope.Env()), 3, args);
		};
		// Exec Function
		glutKeyboardFunc(callback);
		// Return Values
		return;
	}
}

void _glutSpecialFunc(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	if (info[0].IsNull() || info[0].IsUndefined()) {
		// Get Current Window Id
		int wId = glutGetWindow();
		// Reset Function
		windowsCallbacks._glutSpecialFunc[wId].Reset();
		// Exec Function
		glutSpecialFunc(NULL);
		// Return Values
		return;
	} else {
		// Get Current Window Id
		int wId = glutGetWindow();
		// Load Params
		Napi::Function callbackJS = info[0].As<Napi::Function>();
		// Reset Reference
		windowsCallbacks._glutSpecialFunc[wId].Reset(callbackJS, 1);
		// Define Native Callback
		auto callback = [](int key, int x, int y) {
			// Get Current Window
			int wId = glutGetWindow();
			// Define JS Callback
			Napi::Function callbackJS = windowsCallbacks._glutSpecialFunc[wId].Value();
			Napi::Env env = callbackJS.Env();
			Napi::HandleScope scope(env);
			// Call JS Callback
			napi_value args[] = {
				Napi::Number::New(env, key),
				Napi::Number::New(env, x),
				Napi::Number::New(env, y),
			};
			callbackJS.MakeCallback(Napi::Object::New(scope.Env()), 3, args);
		};
		// Exec Function
		glutSpecialFunc(callback);
		// Return Values
		return;
	}
}

void _glutKeyboardUpFunc(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	if (info[0].IsNull() || info[0].IsUndefined()) {
		// Get Current Window Id
		int wId = glutGetWindow();
		// Reset Function
		windowsCallbacks._glutKeyboardUpFunc[wId].Reset();
		// Exec Function
		glutKeyboardUpFunc(NULL);
		// Return Values
		return;
	} else {
		// Get Current Window Id
		int wId = glutGetWindow();
		// Load Params
		Napi::Function callbackJS = info[0].As<Napi::Function>();
		// Reset Reference
		windowsCallbacks._glutKeyboardUpFunc[wId].Reset(callbackJS, 1);
		// Define Native Callback
		auto callback = [](unsigned char key, int x, int y) {
			// Get Current Window
			int wId = glutGetWindow();
			// Define JS Callback
			Napi::Function callbackJS = windowsCallbacks._glutKeyboardUpFunc[wId].Value();
			Napi::Env env = callbackJS.Env();
			Napi::HandleScope scope(env);
			// Call JS Callback
			napi_value args[] = {
				Napi::Number::New(env, key),
				Napi::Number::New(env, x),
				Napi::Number::New(env, y),
			};
			callbackJS.MakeCallback(Napi::Object::New(scope.Env()), 3, args);
		};
		// Exec Function
		glutKeyboardUpFunc(callback);
		// Return Values
		return;
	}
}

void _glutSpecialUpFunc(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	if (info[0].IsNull() || info[0].IsUndefined()) {
		// Get Current Window Id
		int wId = glutGetWindow();
		// Reset Function
		windowsCallbacks._glutSpecialUpFunc[wId].Reset();
		// Exec Function
		glutSpecialUpFunc(NULL);
		// Return Values
		return;
	} else {
		// Get Current Window Id
		int wId = glutGetWindow();
		// Load Params
		Napi::Function callbackJS = info[0].As<Napi::Function>();
		// Reset Reference
		windowsCallbacks._glutSpecialUpFunc[wId].Reset(callbackJS, 1);
		// Define Native Callback
		auto callback = [](int key, int x, int y) {
			// Get Current Window
			int wId = glutGetWindow();
			// Define JS Callback
			Napi::Function callbackJS = windowsCallbacks._glutSpecialUpFunc[wId].Value();
			Napi::Env env = callbackJS.Env();
			Napi::HandleScope scope(env);
			// Call JS Callback
			napi_value args[] = {
				Napi::Number::New(env, key),
				Napi::Number::New(env, x),
				Napi::Number::New(env, y),
			};
			callbackJS.MakeCallback(Napi::Object::New(scope.Env()), 3, args);
		};
		// Exec Function
		glutSpecialUpFunc(callback);
		// Return Values
		return;
	}
}

void _glutMotionFunc(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	if (info[0].IsNull() || info[0].IsUndefined()) {
		// Get Current Window Id
		int wId = glutGetWindow();
		// Reset Function
		windowsCallbacks._glutMotionFunc[wId].Reset();
		// Exec Function
		glutMotionFunc(NULL);
		// Return Values
		return;
	} else {
		// Get Current Window Id
		int wId = glutGetWindow();
		// Load Params
		Napi::Function callbackJS = info[0].As<Napi::Function>();
		// Reset Reference
		windowsCallbacks._glutMotionFunc[wId].Reset(callbackJS, 1);
		// Define Native Callback
		auto callback = [](int x, int y) {
			// Get Current Window
			int wId = glutGetWindow();
			// Define JS Callback
			Napi::Function callbackJS = windowsCallbacks._glutMotionFunc[wId].Value();
			Napi::Env env = callbackJS.Env();
			Napi::HandleScope scope(env);
			// Call JS Callback
			napi_value args[] = {
				Napi::Number::New(env, x),
				Napi::Number::New(env, y),
			};
			callbackJS.MakeCallback(Napi::Object::New(scope.Env()), 2, args);
		};
		// Exec Function
		glutMotionFunc(callback);
		// Return Values
		return;
	}
}

void _glutPassiveMotionFunc(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	if (info[0].IsNull() || info[0].IsUndefined()) {
		// Get Current Window Id
		int wId = glutGetWindow();
		// Reset Function
		windowsCallbacks._glutPassiveMotionFunc[wId].Reset();
		// Exec Function
		glutPassiveMotionFunc(NULL);
		// Return Values
		return;
	} else {
		// Get Current Window Id
		int wId = glutGetWindow();
		// Load Params
		Napi::Function callbackJS = info[0].As<Napi::Function>();
		// Reset Reference
		windowsCallbacks._glutPassiveMotionFunc[wId].Reset(callbackJS, 1);
		// Define Native Callback
		auto callback = [](int x, int y) {
			// Get Current Window
			int wId = glutGetWindow();
			// Define JS Callback
			Napi::Function callbackJS = windowsCallbacks._glutPassiveMotionFunc[wId].Value();
			Napi::Env env = callbackJS.Env();
			Napi::HandleScope scope(env);
			// Call JS Callback
			napi_value args[] = {
				Napi::Number::New(env, x),
				Napi::Number::New(env, y),
			};
			callbackJS.MakeCallback(Napi::Object::New(scope.Env()), 2, args);
		};
		// Exec Function
		glutPassiveMotionFunc(callback);
		// Return Values
		return;
	}
}

void _glutMouseFunc(const Napi::CallbackInfo& info) {
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	if (info[0].IsNull() || info[0].IsUndefined()) {
		// Get Current Window Id
		int wId = glutGetWindow();
		// Reset Function
		windowsCallbacks._glutMouseFunc[wId].Reset();
		// Exec Function
		glutMouseFunc(NULL);
		// Return Values
		return;
	} else {
		// Get Current Window Id
		int wId = glutGetWindow();
		// Load Params
		Napi::Function callbackJS = info[0].As<Napi::Function>();
		// Reset Reference
		windowsCallbacks._glutMouseFunc[wId].Reset(callbackJS, 1);
		// Define Native Callback
		auto callback = [](int button, int state, int x, int y) {
			// Get Current Window
			int wId = glutGetWindow();
			// Define JS Callback
			Napi::Function callbackJS = windowsCallbacks._glutMouseFunc[wId].Value();
			Napi::Env env = callbackJS.Env();
			Napi::HandleScope scope(env);
			// Call JS Callback
			napi_value args[] = {
				Napi::Number::New(env, button),
				Napi::Number::New(env, state),
				Napi::Number::New(env, x),
				Napi::Number::New(env, y),
			};
			callbackJS.MakeCallback(Napi::Object::New(scope.Env()), 4, args);
		};
		// Exec Function
		glutMouseFunc(callback);
		// Return Values
		return;
	}
}

void _glutMouseWheelFunc(const Napi::CallbackInfo& info) {
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	if (info[0].IsNull() || info[0].IsUndefined()) {
		// Get Current Window Id
		int wId = glutGetWindow();
		// Reset Function
		windowsCallbacks._glutMouseWheelFunc[wId].Reset();
		// Exec Function
		glutMouseWheelFunc(NULL);
		// Return Values
		return;
	} else {
		// Get Current Window Id
		int wId = glutGetWindow();
		// Load Params
		Napi::Function callbackJS = info[0].As<Napi::Function>();
		// Reset Reference
		windowsCallbacks._glutMouseWheelFunc[wId].Reset(callbackJS, 1);
		// Define Native Callback
		auto callback = [](int wheel, int direction, int x, int y) {
			// Get Current Window
			int wId = glutGetWindow();
			// Define JS Callback
			Napi::Function callbackJS = windowsCallbacks._glutMouseWheelFunc[wId].Value();
			Napi::Env env = callbackJS.Env();
			Napi::HandleScope scope(env);
			// Call JS Callback
			napi_value args[] = {
				Napi::Number::New(env, wheel),
				Napi::Number::New(env, direction),
				Napi::Number::New(env, x),
				Napi::Number::New(env, y),
			};
			callbackJS.MakeCallback(Napi::Object::New(scope.Env()), 4, args);
		};
		// Exec Function
		glutMouseWheelFunc(callback);
		// Return Values
		return;
	}
}

void _glutEntryFunc(const Napi::CallbackInfo& info) {
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	if (info[0].IsNull() || info[0].IsUndefined()) {
		// Get Current Window Id
		int wId = glutGetWindow();
		// Reset Function
		windowsCallbacks._glutEntryFunc[wId].Reset();
		// Exec Function
		glutEntryFunc(NULL);
		// Return Values
		return;
	} else {
		// Get Current Window Id
		int wId = glutGetWindow();
		// Load Params
		Napi::Function callbackJS = info[0].As<Napi::Function>();
		// Reset Reference
		windowsCallbacks._glutEntryFunc[wId].Reset(callbackJS, 1);
		// Define Native Callback
		auto callback = [](int state) {
			// Get Current Window
			int wId = glutGetWindow();
			// Define JS Callback
			Napi::Function callbackJS = windowsCallbacks._glutEntryFunc[wId].Value();
			Napi::Env env = callbackJS.Env();
			Napi::HandleScope scope(env);
			// Call JS Callback
			napi_value args[] = {
				Napi::Number::New(env, state),
			};
			callbackJS.MakeCallback(Napi::Object::New(scope.Env()), 1, args);
		};
		// Exec Function
		glutEntryFunc(callback);
		// Return Values
		return;
	}
}

void _glutJoystickFunc(const Napi::CallbackInfo& info) {
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	if (info[0].IsNull() || info[0].IsUndefined()) {
		// Get Current Window Id
		int wId = glutGetWindow();
		// Reset Function
		windowsCallbacks._glutJoystickFunc[wId].Reset();
		// Exec Function
		glutJoystickFunc(NULL, 0);
		// Return Values
		return;
	} else {
		// Get Current Window Id
		int wId = glutGetWindow();
		// Load Params
		Napi::Function callbackJS = info[0].As<Napi::Function>();
		int pollInterval = info[1].As<Napi::Number>().Int32Value();
		// Reset Reference
		windowsCallbacks._glutJoystickFunc[wId].Reset(callbackJS, 1);
		// Define Native Callback
		auto callback = [](unsigned int buttonMask, int x, int y, int z) {
			// Get Current Window
				int wId = glutGetWindow();
				// Define JS Callback
				Napi::Function callbackJS = windowsCallbacks._glutJoystickFunc[wId].Value();
				Napi::Env env = callbackJS.Env();
				Napi::HandleScope scope(env);
			// Call JS Callback
			napi_value args[] = {
				Napi::Number::New(env, buttonMask),
				Napi::Number::New(env, x),
				Napi::Number::New(env, y),
				Napi::Number::New(env, z),
			};
			callbackJS.MakeCallback(Napi::Object::New(scope.Env()), 4, args);
		};
	// Exec Function
	glutJoystickFunc(callback, pollInterval);
	// Return Values
	return;
}
}

void _glutSpaceballMotionFunc(const Napi::CallbackInfo& info) {
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	if (info[0].IsNull() || info[0].IsUndefined()) {
		// Get Current Window Id
		int wId = glutGetWindow();
		// Reset Function
		windowsCallbacks._glutSpaceballMotionFunc[wId].Reset();
		// Exec Function
		glutSpaceballMotionFunc(NULL);
		// Return Values
		return;
	} else {
		// Get Current Window Id
		int wId = glutGetWindow();
		// Load Params
		Napi::Function callbackJS = info[0].As<Napi::Function>();
		// Reset Reference
		windowsCallbacks._glutSpaceballMotionFunc[wId].Reset(callbackJS, 1);
		// Define Native Callback
		auto callback = [](int x, int y, int z) {
			// Get Current Window
			int wId = glutGetWindow();
			// Define JS Callback
			Napi::Function callbackJS = windowsCallbacks._glutSpaceballMotionFunc[wId].Value();
			Napi::Env env = callbackJS.Env();
			Napi::HandleScope scope(env);
			// Call JS Callback
			napi_value args[] = {
				Napi::Number::New(env, x),
				Napi::Number::New(env, y),
				Napi::Number::New(env, z),
			};
			callbackJS.MakeCallback(Napi::Object::New(scope.Env()), 3, args);
		};
		// Exec Function
		glutSpaceballMotionFunc(callback);
		// Return Values
		return;
	}
}

void _glutSpaceballRotateFunc(const Napi::CallbackInfo& info) {
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	if (info[0].IsNull() || info[0].IsUndefined()) {
		// Get Current Window Id
		int wId = glutGetWindow();
		// Reset Function
		windowsCallbacks._glutSpaceballRotateFunc[wId].Reset();
		// Exec Function
		glutSpaceballRotateFunc(NULL);
		// Return Values
		return;
	} else {
		// Get Current Window Id
		int wId = glutGetWindow();
		// Load Params
		Napi::Function callbackJS = info[0].As<Napi::Function>();
		// Reset Reference
		windowsCallbacks._glutSpaceballRotateFunc[wId].Reset(callbackJS, 1);
		// Define Native Callback
		auto callback = [](int rx, int ry, int rz) {
			// Get Current Window
			int wId = glutGetWindow();
			// Define JS Callback
			Napi::Function callbackJS = windowsCallbacks._glutSpaceballRotateFunc[wId].Value();
			Napi::Env env = callbackJS.Env();
			Napi::HandleScope scope(env);
			// Call JS Callback
			napi_value args[] = {
				Napi::Number::New(env, rx),
				Napi::Number::New(env, ry),
				Napi::Number::New(env, rz),
			};
			callbackJS.MakeCallback(Napi::Object::New(scope.Env()), 3, args);
		};
		// Exec Function
		glutSpaceballRotateFunc(callback);
		// Return Values
		return;
	}
}

void _glutSpaceballButtonFunc(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	if (info[0].IsNull() || info[0].IsUndefined()) {
		// Get Current Window Id
		int wId = glutGetWindow();
		// Reset Function
		windowsCallbacks._glutSpaceballButtonFunc[wId].Reset();
		// Exec Function
		glutSpaceballButtonFunc(NULL);
		// Return Values
		return;
	} else {
		// Get Current Window Id
		int wId = glutGetWindow();
		// Load Params
		Napi::Function callbackJS = info[0].As<Napi::Function>();
		// Reset Reference
		windowsCallbacks._glutSpaceballButtonFunc[wId].Reset(callbackJS, 1);
		// Define Native Callback
		auto callback = [](int button, int updown) {
			// Get Current Window
			int wId = glutGetWindow();
			// Define JS Callback
			Napi::Function callbackJS = windowsCallbacks._glutSpaceballButtonFunc[wId].Value();
			Napi::Env env = callbackJS.Env();
			Napi::HandleScope scope(env);
			// Call JS Callback
			napi_value args[] = {
				Napi::Number::New(env, button),
				Napi::Number::New(env, updown),
			};
			callbackJS.MakeCallback(Napi::Object::New(scope.Env()), 2, args);
		};
		// Exec Function
		glutSpaceballButtonFunc(callback);
		// Return Values
		return;
	}
}

void _glutButtonBoxFunc(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	if (info[0].IsNull() || info[0].IsUndefined()) {
		// Get Current Window Id
		int wId = glutGetWindow();
		// Reset Function
		windowsCallbacks._glutButtonBoxFunc[wId].Reset();
		// Exec Function
		glutButtonBoxFunc(NULL);
		// Return Values
		return;
	} else {
		// Get Current Window Id
		int wId = glutGetWindow();
		// Load Params
		Napi::Function callbackJS = info[0].As<Napi::Function>();
		// Reset Reference
		windowsCallbacks._glutButtonBoxFunc[wId].Reset(callbackJS, 1);
		// Define Native Callback
		auto callback = [](int button, int updown) {
			// Get Current Window
			int wId = glutGetWindow();
			// Define JS Callback
			Napi::Function callbackJS = windowsCallbacks._glutButtonBoxFunc[wId].Value();
			Napi::Env env = callbackJS.Env();
			Napi::HandleScope scope(env);
			// Call JS Callback
			napi_value args[] = {
				Napi::Number::New(env, button),
				Napi::Number::New(env, updown),
			};
			callbackJS.MakeCallback(Napi::Object::New(scope.Env()), 2, args);
		};
		// Exec Function
		glutButtonBoxFunc(callback);
		// Return Values
		return;
	}
}

void _glutDialsFunc(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	if (info[0].IsNull() || info[0].IsUndefined()) {
		// Get Current Window Id
		int wId = glutGetWindow();
		// Reset Function
		windowsCallbacks._glutDialsFunc[wId].Reset();
		// Exec Function
		glutDialsFunc(NULL);
		// Return Values
		return;
	} else {
		// Get Current Window Id
		int wId = glutGetWindow();
		// Load Params
		Napi::Function callbackJS = info[0].As<Napi::Function>();
		// Reset Reference
		windowsCallbacks._glutDialsFunc[wId].Reset(callbackJS, 1);
		// Define Native Callback
		auto callback = [](int dial, int value) {
			// Get Current Window
			int wId = glutGetWindow();
			// Define JS Callback
			Napi::Function callbackJS = windowsCallbacks._glutDialsFunc[wId].Value();
			Napi::Env env = callbackJS.Env();
			Napi::HandleScope scope(env);
			// Call JS Callback
			napi_value args[] = {
				Napi::Number::New(env, dial),
				Napi::Number::New(env, value),
			};
			callbackJS.MakeCallback(Napi::Object::New(scope.Env()), 2, args);
		};
		// Exec Function
		glutDialsFunc(callback);
		// Return Values
		return;
	}
}

void _glutTabletMotionFunc(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	if (info[0].IsNull() || info[0].IsUndefined()) {
		// Get Current Window Id
		int wId = glutGetWindow();
		// Reset Function
		windowsCallbacks._glutTabletMotionFunc[wId].Reset();
		// Exec Function
		glutTabletMotionFunc(NULL);
		// Return Values
		return;
	} else {
		// Get Current Window Id
		int wId = glutGetWindow();
		// Load Params
		Napi::Function callbackJS = info[0].As<Napi::Function>();
		// Reset Reference
		windowsCallbacks._glutTabletMotionFunc[wId].Reset(callbackJS, 1);
		// Define Native Callback
		auto callback = [](int x, int y) {
			// Get Current Window
			int wId = glutGetWindow();
			// Define JS Callback
			Napi::Function callbackJS = windowsCallbacks._glutTabletMotionFunc[wId].Value();
			Napi::Env env = callbackJS.Env();
			Napi::HandleScope scope(env);
			// Call JS Callback
			napi_value args[] = {
				Napi::Number::New(env, x),
				Napi::Number::New(env, y),
			};
			callbackJS.MakeCallback(Napi::Object::New(scope.Env()), 2, args);
		};
		// Exec Function
		glutTabletMotionFunc(callback);
		// Return Values
		return;
	}
}

void _glutTabletButtonFunc(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	if (info[0].IsNull() || info[0].IsUndefined()) {
		// Get Current Window Id
		int wId = glutGetWindow();
		// Reset Function
		windowsCallbacks._glutTabletButtonFunc[wId].Reset();
		// Exec Function
		glutTabletButtonFunc(NULL);
		// Return Values
		return;
	} else {
		// Get Current Window Id
		int wId = glutGetWindow();
		// Load Params
		Napi::Function callbackJS = info[0].As<Napi::Function>();
		// Reset Reference
		windowsCallbacks._glutTabletButtonFunc[wId].Reset(callbackJS, 1);
		// Define Native Callback
		auto callback = [](int button, int updown, int x, int y) {
			// Get Current Window
			int wId = glutGetWindow();
			// Define JS Callback
			Napi::Function callbackJS = windowsCallbacks._glutTabletButtonFunc[wId].Value();
			Napi::Env env = callbackJS.Env();
			Napi::HandleScope scope(env);
			// Call JS Callback
			napi_value args[] = {
				Napi::Number::New(env, button),
				Napi::Number::New(env, updown),
				Napi::Number::New(env, x),
				Napi::Number::New(env, y),
			};
			callbackJS.MakeCallback(Napi::Object::New(scope.Env()), 4, args);
		};
		// Exec Function
		glutTabletButtonFunc(callback);
		// Return Values
		return;
	}
}

void _glutVisibilityFunc(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	if (info[0].IsNull() || info[0].IsUndefined()) {
		// Get Current Window Id
		int wId = glutGetWindow();
		// Reset Function
		windowsCallbacks._glutVisibilityFunc[wId].Reset();
		// Exec Function
		glutVisibilityFunc(NULL);
		// Return Values
		return;
	} else {
		// Get Current Window Id
		int wId = glutGetWindow();
		// Load Params
		Napi::Function callbackJS = info[0].As<Napi::Function>();
		// Reset Reference
		windowsCallbacks._glutVisibilityFunc[wId].Reset(callbackJS, 1);
		// Define Native Callback
		auto callback = [](int state) {
			// Get Current Window
			int wId = glutGetWindow();
			// Define JS Callback
			Napi::Function callbackJS = windowsCallbacks._glutVisibilityFunc[wId].Value();
			Napi::Env env = callbackJS.Env();
			Napi::HandleScope scope(env);
			// Call JS Callback
			napi_value args[] = {
				Napi::Number::New(env, state)
			};
			callbackJS.MakeCallback(Napi::Object::New(scope.Env()), 1, args);
		};
		// Exec Function
		glutVisibilityFunc(callback);
		// Return Values
		return;
	}
}

void _glutWindowStatusFunc(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	if (info[0].IsNull() || info[0].IsUndefined()) {
		// Get Current Window Id
		int wId = glutGetWindow();
		// Reset Function
		windowsCallbacks._glutWindowStatusFunc[wId].Reset();
		// Exec Function
		glutWindowStatusFunc(NULL);
		// Return Values
		return;
	} else {
		// Get Current Window Id
		int wId = glutGetWindow();
		// Load Params
		Napi::Function callbackJS = info[0].As<Napi::Function>();
		// Reset Reference
		windowsCallbacks._glutWindowStatusFunc[wId].Reset(callbackJS, 1);
		// Define Native Callback
		auto callback = [](int state) {
			// Get Current Window
			int wId = glutGetWindow();
			// Define JS Callback
			Napi::Function callbackJS = windowsCallbacks._glutWindowStatusFunc[wId].Value();
			Napi::Env env = callbackJS.Env();
			Napi::HandleScope scope(env);
			// Call JS Callback
			napi_value args[] = {
				Napi::Number::New(env, state)
			};
			callbackJS.MakeCallback(Napi::Object::New(scope.Env()), 1, args);
		};
		// Exec Function
		glutWindowStatusFunc(callback);
		// Return Values
		return;
	}
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

Napi::BigInt _glutGetProcAddress(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	const char* procName = info[0].As<Napi::String>().Utf8Value().c_str();
	// Exec Function
	GLUTproc procAddr = glutGetProcAddress(procName);
	// Return Values
	return Napi::BigInt::New(env,(uintptr_t) procAddr);
}

void _glutBitmapCharacter(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	// Load Params
	bool lossless;
	void* font = info[0].IsBigInt() ? (void*) ((uintptr_t) info[0].As<Napi::BigInt>().Uint64Value(&lossless)) : info[0].As<Napi::Buffer<unsigned char>>().Data();
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
	bool lossless;
	void* font = info[0].IsBigInt() ? (void*) ((uintptr_t) info[0].As<Napi::BigInt>().Uint64Value(&lossless)) : info[0].As<Napi::Buffer<unsigned char>>().Data();
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
	bool lossless;
	void* font = info[0].IsBigInt() ? (void*) ((uintptr_t) info[0].As<Napi::BigInt>().Uint64Value(&lossless)) : info[0].As<Napi::Buffer<unsigned char>>().Data();
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
	bool lossless;
	void* font = info[0].IsBigInt() ? (void*) ((uintptr_t) info[0].As<Napi::BigInt>().Uint64Value(&lossless)) : info[0].As<Napi::Buffer<unsigned char>>().Data();
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
	bool lossless;
	void* font = info[0].IsBigInt() ? (void*) ((uintptr_t) info[0].As<Napi::BigInt>().Uint64Value(&lossless)) : info[0].As<Napi::Buffer<unsigned char>>().Data();
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
	bool lossless;
	void* font = info[0].IsBigInt() ? (void*) ((uintptr_t) info[0].As<Napi::BigInt>().Uint64Value(&lossless)) : info[0].As<Napi::Buffer<unsigned char>>().Data();
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
	bool lossless;
	void* font = info[0].IsBigInt() ? (void*) ((uintptr_t) info[0].As<Napi::BigInt>().Uint64Value(&lossless)) : info[0].As<Napi::Buffer<unsigned char>>().Data();
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
	bool lossless;
	void* font = info[0].IsBigInt() ? (void*) ((uintptr_t) info[0].As<Napi::BigInt>().Uint64Value(&lossless)) : info[0].As<Napi::Buffer<unsigned char>>().Data();
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
	bool lossless;
	void* font = info[0].IsBigInt() ? (void*) ((uintptr_t) info[0].As<Napi::BigInt>().Uint64Value(&lossless)) : info[0].As<Napi::Buffer<unsigned char>>().Data();
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
	bool lossless;
	void* font = info[0].IsBigInt() ? (void*) ((uintptr_t) info[0].As<Napi::BigInt>().Uint64Value(&lossless)) : info[0].As<Napi::Buffer<unsigned char>>().Data();
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
	bool lossless;
	void* font = info[0].IsBigInt() ? (void*) ((uintptr_t) info[0].As<Napi::BigInt>().Uint64Value(&lossless)) : info[0].As<Napi::Buffer<unsigned char>>().Data();
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
	bool lossless;
	void* font = info[0].IsBigInt() ? (void*) ((uintptr_t) info[0].As<Napi::BigInt>().Uint64Value(&lossless)) : info[0].As<Napi::Buffer<unsigned char>>().Data();
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
	if (info[0].IsNull() || info[0].IsUndefined()) {
		// Get Current Window Id
		int wId = glutGetWindow();
		// Reset Function
		windowsCallbacks._glutMultiEntryFunc[wId].Reset();
		// Exec Function
		glutMultiEntryFunc(NULL);
		// Return Values
		return;
	} else {
		// Get Current Window Id
		int wId = glutGetWindow();
		// Load Params
		Napi::Function callbackJS = info[0].As<Napi::Function>();
		// Reset Reference
		windowsCallbacks._glutMultiEntryFunc[wId].Reset(callbackJS, 1);
		// Define Native Callback
		auto callback = [](int id, int status) {
			// Get Current Window
			int wId = glutGetWindow();
			// Define JS Callback
			Napi::Function callbackJS = windowsCallbacks._glutMultiEntryFunc[wId].Value();
			Napi::Env env = callbackJS.Env();
			Napi::HandleScope scope(env);
			// Call JS Callback
			napi_value args[] = {
				Napi::Number::New(env, id),
				Napi::Number::New(env, status)
			};
			callbackJS.MakeCallback(Napi::Object::New(scope.Env()), 2, args);
		};
		// Exec Function
		glutMultiEntryFunc(callback);
		// Return Values
		return;
	}
}

void _glutMultiButtonFunc(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	if (info[0].IsNull() || info[0].IsUndefined()) {
		// Get Current Window Id
		int wId = glutGetWindow();
		// Reset Function
		windowsCallbacks._glutMultiButtonFunc[wId].Reset();
		// Exec Function
		glutMultiButtonFunc(NULL);
		// Return Values
		return;
	} else {
		// Get Current Window Id
		int wId = glutGetWindow();
		// Load Params
		Napi::Function callbackJS = info[0].As<Napi::Function>();
		// Reset Reference
		windowsCallbacks._glutMultiButtonFunc[wId].Reset(callbackJS, 1);
		// Define Native Callback
		auto callback = [](int id, int x, int y, int button, int status) {
			// Get Current Window
			int wId = glutGetWindow();
			// Define JS Callback
			Napi::Function callbackJS = windowsCallbacks._glutMultiButtonFunc[wId].Value();
			Napi::Env env = callbackJS.Env();
			Napi::HandleScope scope(env);
			// Call JS Callback
			napi_value args[] = {
				Napi::Number::New(env, id),
				Napi::Number::New(env, x),
				Napi::Number::New(env, y),
				Napi::Number::New(env, button),
				Napi::Number::New(env, status)
			};
			callbackJS.MakeCallback(Napi::Object::New(scope.Env()), 5, args);
		};
		// Exec Function
		glutMultiButtonFunc(callback);
		// Return Values
		return;
	}
}

void _glutMultiMotionFunc(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	if (info[0].IsNull() || info[0].IsUndefined()) {
		// Get Current Window Id
		int wId = glutGetWindow();
		// Reset Function
		windowsCallbacks._glutMultiMotionFunc[wId].Reset();
		// Exec Function
		glutMultiMotionFunc(NULL);
		// Return Values
		return;
	} else {
		// Get Current Window Id
		int wId = glutGetWindow();
		// Load Params
		Napi::Function callbackJS = info[0].As<Napi::Function>();
		// Reset Reference
		windowsCallbacks._glutMultiMotionFunc[wId].Reset(callbackJS, 1);
		// Define Native Callback
		auto callback = [](int id, int x, int y) {
			// Get Current Window
			int wId = glutGetWindow();
			// Define JS Callback
			Napi::Function callbackJS = windowsCallbacks._glutMultiMotionFunc[wId].Value();
			Napi::Env env = callbackJS.Env();
			Napi::HandleScope scope(env);
			// Call JS Callback
			napi_value args[] = {
				Napi::Number::New(env, id),
				Napi::Number::New(env, x),
				Napi::Number::New(env, y),
			};
			callbackJS.MakeCallback(Napi::Object::New(scope.Env()), 3, args);
		};
		// Exec Function
		glutMultiMotionFunc(callback);
		// Return Values
		return;
	}
}

void _glutMultiPassiveFunc(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	if (info[0].IsNull() || info[0].IsUndefined()) {
		// Get Current Window Id
		int wId = glutGetWindow();
		// Reset Function
		windowsCallbacks._glutMultiPassiveFunc[wId].Reset();
		// Exec Function
		glutMultiPassiveFunc(NULL);
		// Return Values
		return;
	} else {
		// Get Current Window Id
		int wId = glutGetWindow();
		// Load Params
		Napi::Function callbackJS = info[0].As<Napi::Function>();
		// Reset Reference
		windowsCallbacks._glutMultiPassiveFunc[wId].Reset(callbackJS, 1);
		// Define Native Callback
		auto callback = [](int id, int x, int y) {
			// Get Current Window
			int wId = glutGetWindow();
			// Define JS Callback
			Napi::Function callbackJS = windowsCallbacks._glutMultiPassiveFunc[wId].Value();
			Napi::Env env = callbackJS.Env();
			Napi::HandleScope scope(env);
			// Call JS Callback
			napi_value args[] = {
				Napi::Number::New(env, id),
				Napi::Number::New(env, x),
				Napi::Number::New(env, y),
			};
			callbackJS.MakeCallback(Napi::Object::New(scope.Env()), 3, args);
		};
		// Exec Function
		glutMultiPassiveFunc(callback);
		// Return Values
		return;
	}
}

void _glutInitContextFunc(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	if (info[0].IsNull() || info[0].IsUndefined()) {
		// Get Current Window Id
		int wId = glutGetWindow();
		// Reset Function
		windowsCallbacks._glutInitContextFunc[wId].Reset();
		// Exec Function
		glutInitContextFunc(NULL);
		// Return Values
		return;
	} else {
		// Get Current Window Id
		int wId = glutGetWindow();
		// Load Params
		Napi::Function callbackJS = info[0].As<Napi::Function>();
		// Reset Reference
		windowsCallbacks._glutInitContextFunc[wId].Reset(callbackJS, 1);
		// Define Native Callback
		auto callback = []() {
			// Get Current Window
			int wId = glutGetWindow();
			// Define JS Callback
			Napi::Function callbackJS = windowsCallbacks._glutInitContextFunc[wId].Value();
			Napi::Env env = callbackJS.Env();
			Napi::HandleScope scope(env);
			// Call JS Callback
			napi_value args[] = {};
			callbackJS.MakeCallback(Napi::Object::New(scope.Env()), 0, args);
		};
		// Exec Function
		glutInitContextFunc(callback);
		// Return Values
		return;
	}
}

void _glutAppStatusFunc(const Napi::CallbackInfo& info) {
	// Handle Env
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	if (info[0].IsNull() || info[0].IsUndefined()) {
		// Get Current Window Id
		int wId = glutGetWindow();
		// Reset Function
		windowsCallbacks._glutAppStatusFunc[wId].Reset();
		// Exec Function
		glutAppStatusFunc(NULL);
		// Return Values
		return;
	} else {
		// Get Current Window Id
		int wId = glutGetWindow();
		// Load Params
		Napi::Function callbackJS = info[0].As<Napi::Function>();
		// Reset Reference
		windowsCallbacks._glutAppStatusFunc[wId].Reset(callbackJS, 1);
		// Define Native Callback
		auto callback = [](int event) {
			// Get Current Window
			int wId = glutGetWindow();
			// Define JS Callback
			Napi::Function callbackJS = windowsCallbacks._glutAppStatusFunc[wId].Value();
			Napi::Env env = callbackJS.Env();
			Napi::HandleScope scope(env);
			// Call JS Callback
			napi_value args[] = {
				Napi::Number::New(env, event),
			};
			callbackJS.MakeCallback(Napi::Object::New(scope.Env()), 1, args);
		};
		// Exec Function
		glutAppStatusFunc(callback);
		// Return Values
		return;
	}
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
