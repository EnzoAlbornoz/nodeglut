#include <napi.h>
#include "calls.hh"

Napi::Object Init(Napi::Env env, Napi::Object exports) {
	// Setup Calls
	// glutInit
	exports.Set(Napi::String::New(env, "glutInit"), Napi::Function::New(env, _glutInit));
	// glutInitWindowSize
	exports.Set(Napi::String::New(env, "glutInitWindowSize"), Napi::Function::New(env, _glutInitWindowSize));
	// glutInitWindowPosition
	exports.Set(Napi::String::New(env, "glutInitWindowPosition"), Napi::Function::New(env, _glutInitWindowPosition));
	// glutInitDisplayMode
	exports.Set(Napi::String::New(env, "glutInitDisplayMode"), Napi::Function::New(env, _glutInitDisplayMode));
	// glutInitDisplayString
	exports.Set(Napi::String::New(env, "glutInitDisplayString"), Napi::Function::New(env, _glutInitDisplayString));
	// glutInitErrorFunc
	exports.Set(Napi::String::New(env, "glutInitErrorFunc"), Napi::Function::New(env, _glutInitErrorFunc));
	// glutInitWarningFunc
	exports.Set(Napi::String::New(env, "glutInitWarningFunc"), Napi::Function::New(env, _glutInitWarningFunc));
	// glutMainLoop
	exports.Set(Napi::String::New(env, "glutMainLoop"), Napi::Function::New(env, _glutMainLoop));
	// glutMainLoopEvent
	exports.Set(Napi::String::New(env, "glutMainLoopEvent"), Napi::Function::New(env, _glutMainLoopEvent));
	// glutLeaveMainLoop
	exports.Set(Napi::String::New(env, "glutLeaveMainLoop"), Napi::Function::New(env, _glutLeaveMainLoop));
	// glutCreateWindow
	exports.Set(Napi::String::New(env, "glutCreateWindow"), Napi::Function::New(env, _glutCreateWindow));
	// glutCreateSubWindow
	exports.Set(Napi::String::New(env, "glutCreateSubWindow"), Napi::Function::New(env, _glutCreateSubWindow));
	// glutDestroyWindow
	exports.Set(Napi::String::New(env, "glutDestroyWindow"), Napi::Function::New(env, _glutDestroyWindow));
	// glutSetWindow
	exports.Set(Napi::String::New(env, "glutSetWindow"), Napi::Function::New(env, _glutSetWindow));
	// glutGetWindow
	exports.Set(Napi::String::New(env, "glutGetWindow"), Napi::Function::New(env, _glutGetWindow));
	// glutSetWindowTitle
	exports.Set(Napi::String::New(env, "glutSetWindowTitle"), Napi::Function::New(env, _glutSetWindowTitle));
	// glutSetIconTitle
	exports.Set(Napi::String::New(env, "glutSetIconTitle"), Napi::Function::New(env, _glutSetIconTitle));
	// glutDestroyWindow
	exports.Set(Napi::String::New(env, "glutDestroyWindow"), Napi::Function::New(env, _glutDestroyWindow));
		// glutReshapeWindow
	exports.Set(Napi::String::New(env, "glutReshapeWindow"), Napi::Function::New(env, _glutReshapeWindow));
	// glutPositionWindow
	exports.Set(Napi::String::New(env, "glutPositionWindow"), Napi::Function::New(env, _glutPositionWindow));
	// glutShowWindow
	exports.Set(Napi::String::New(env, "glutShowWindow"), Napi::Function::New(env, _glutShowWindow));
	// glutHideWindow
	exports.Set(Napi::String::New(env, "glutHideWindow"), Napi::Function::New(env, _glutHideWindow));
	// glutIconifyWindow
	exports.Set(Napi::String::New(env, "glutIconifyWindow"), Napi::Function::New(env, _glutIconifyWindow));
	// glutPopWindow
	exports.Set(Napi::String::New(env, "glutPopWindow"), Napi::Function::New(env, _glutPopWindow));
	// glutPushWindow
	exports.Set(Napi::String::New(env, "glutPushWindow"), Napi::Function::New(env, _glutPushWindow));
	// glutFullScreen
	exports.Set(Napi::String::New(env, "glutFullScreen"), Napi::Function::New(env, _glutFullScreen));
	// glutLeaveFullScreen
	exports.Set(Napi::String::New(env, "glutLeaveFullScreen"), Napi::Function::New(env, _glutLeaveFullScreen));
	// glutFullScreenToggle
	exports.Set(Napi::String::New(env, "glutFullScreenToggle"), Napi::Function::New(env, _glutFullScreenToggle));
	// glutPostRedisplay
	exports.Set(Napi::String::New(env, "glutPostRedisplay"), Napi::Function::New(env, _glutPostRedisplay));
	// glutPostWindowRedisplay
	exports.Set(Napi::String::New(env, "glutPostWindowRedisplay"), Napi::Function::New(env, _glutPostWindowRedisplay));
	// glutSwapBuffers
	exports.Set(Napi::String::New(env, "glutSwapBuffers"), Napi::Function::New(env, _glutSwapBuffers));
	// glutSetCursor
	exports.Set(Napi::String::New(env, "glutSetCursor"), Napi::Function::New(env, _glutSetCursor));
	// glutWarpPointer
	exports.Set(Napi::String::New(env, "glutWarpPointer"), Napi::Function::New(env, _glutWarpPointer));
	// glutEstablishOverlay
	exports.Set(Napi::String::New(env, "glutEstablishOverlay"), Napi::Function::New(env, _glutEstablishOverlay));
	// glutRemoveOverlay
	exports.Set(Napi::String::New(env, "glutRemoveOverlay"), Napi::Function::New(env, _glutRemoveOverlay));
	// glutUseLayer
	exports.Set(Napi::String::New(env, "glutUseLayer"), Napi::Function::New(env, _glutUseLayer));
	// glutPostOverlayRedisplay
	exports.Set(Napi::String::New(env, "glutPostOverlayRedisplay"), Napi::Function::New(env, _glutPostOverlayRedisplay));
	// glutPostWindowOverlayRedisplay
	exports.Set(Napi::String::New(env, "glutPostWindowOverlayRedisplay"), Napi::Function::New(env, _glutPostWindowOverlayRedisplay));
	// glutShowOverlay
	exports.Set(Napi::String::New(env, "glutShowOverlay"), Napi::Function::New(env, _glutShowOverlay));
	// glutHideOverlay
	exports.Set(Napi::String::New(env, "glutHideOverlay"), Napi::Function::New(env, _glutHideOverlay));
	// glutCreateMenu
	exports.Set(Napi::String::New(env, "glutCreateMenu"), Napi::Function::New(env, _glutCreateMenu));
	// glutDestroyMenu
	exports.Set(Napi::String::New(env, "glutDestroyMenu"), Napi::Function::New(env, _glutDestroyMenu));
	// glutSetMenu
	exports.Set(Napi::String::New(env, "glutSetMenu"), Napi::Function::New(env, _glutSetMenu));
	// glutGetMenu
	exports.Set(Napi::String::New(env, "glutGetMenu"), Napi::Function::New(env, _glutGetMenu));
	// glutAddMenuEntry
	exports.Set(Napi::String::New(env, "glutAddMenuEntry"), Napi::Function::New(env, _glutAddMenuEntry));
	// glutAddSubMenu
	exports.Set(Napi::String::New(env, "glutAddSubMenu"), Napi::Function::New(env, _glutAddSubMenu));
	// glutChangeToMenuEntry
	exports.Set(Napi::String::New(env, "glutChangeToMenuEntry"), Napi::Function::New(env, _glutChangeToMenuEntry));
	// glutChangeToSubMenu
	exports.Set(Napi::String::New(env, "glutChangeToSubMenu"), Napi::Function::New(env, _glutChangeToSubMenu));
	// glutSetMenuFont
	exports.Set(Napi::String::New(env, "glutSetMenuFont"), Napi::Function::New(env, _glutSetMenuFont));
	// glutRemoveMenuItem
	exports.Set(Napi::String::New(env, "glutRemoveMenuItem"), Napi::Function::New(env, _glutRemoveMenuItem));
	// glutAttachMenu
	exports.Set(Napi::String::New(env, "glutAttachMenu"), Napi::Function::New(env, _glutAttachMenu));
	// glutDetachMenu
	exports.Set(Napi::String::New(env, "glutDetachMenu"), Napi::Function::New(env, _glutDetachMenu));
	// glutMenuDestroyFunc
	exports.Set(Napi::String::New(env, "glutMenuDestroyFunc"), Napi::Function::New(env, _glutMenuDestroyFunc));
	// glutTimerFunc
	exports.Set(Napi::String::New(env, "glutTimerFunc"), Napi::Function::New(env, _glutTimerFunc));
	// glutIdleFunc
	exports.Set(Napi::String::New(env, "glutIdleFunc"), Napi::Function::New(env, _glutIdleFunc));
	// glutMenuStatusFunc
	exports.Set(Napi::String::New(env, "glutMenuStatusFunc"), Napi::Function::New(env, _glutMenuStatusFunc));
	// glutMenuStateFunc
	exports.Set(Napi::String::New(env, "glutMenuStateFunc"), Napi::Function::New(env, _glutMenuStateFunc));
	// glutDisplayFunc
	exports.Set(Napi::String::New(env, "glutDisplayFunc"), Napi::Function::New(env, _glutDisplayFunc));
	// glutOverlayDisplayFunc
	exports.Set(Napi::String::New(env, "glutOverlayDisplayFunc"), Napi::Function::New(env, _glutOverlayDisplayFunc));
	// glutReshapeFunc
	exports.Set(Napi::String::New(env, "glutReshapeFunc"), Napi::Function::New(env, _glutReshapeFunc));
	// glutPositionFunc
	exports.Set(Napi::String::New(env, "glutPositionFunc"), Napi::Function::New(env, _glutPositionFunc));
	// glutCloseFunc
	exports.Set(Napi::String::New(env, "glutCloseFunc"), Napi::Function::New(env, _glutCloseFunc));
	// glutKeyboardFunc
	exports.Set(Napi::String::New(env, "glutKeyboardFunc"), Napi::Function::New(env, _glutKeyboardFunc));
	// glutSpecialFunc
	exports.Set(Napi::String::New(env, "glutSpecialFunc"), Napi::Function::New(env, _glutSpecialFunc));
	// glutKeyboardUpFunc
	exports.Set(Napi::String::New(env, "glutKeyboardUpFunc"), Napi::Function::New(env, _glutKeyboardUpFunc));
	// glutSpecialUpFunc
	exports.Set(Napi::String::New(env, "glutSpecialUpFunc"), Napi::Function::New(env, _glutSpecialUpFunc));
	// glutMotionFunc
	exports.Set(Napi::String::New(env, "glutMotionFunc"), Napi::Function::New(env, _glutMotionFunc));
	// glutPassiveMotionFunc
	exports.Set(Napi::String::New(env, "glutPassiveMotionFunc"), Napi::Function::New(env, _glutPassiveMotionFunc));
	// glutMouseFunc
	exports.Set(Napi::String::New(env, "glutMouseFunc"), Napi::Function::New(env, _glutMouseFunc));
	// glutMouseWheelFunc
	exports.Set(Napi::String::New(env, "glutMouseWheelFunc"), Napi::Function::New(env, _glutMouseWheelFunc));
	// glutEntryFunc
	exports.Set(Napi::String::New(env, "glutEntryFunc"), Napi::Function::New(env, _glutEntryFunc));
	// glutJoystickFunc
	exports.Set(Napi::String::New(env, "glutJoystickFunc"), Napi::Function::New(env, _glutJoystickFunc));
	// glutSpaceballMotionFunc
	exports.Set(Napi::String::New(env, "glutSpaceballMotionFunc"), Napi::Function::New(env, _glutSpaceballMotionFunc));
	// glutSpaceballRotateFunc
	exports.Set(Napi::String::New(env, "glutSpaceballRotateFunc"), Napi::Function::New(env, _glutSpaceballRotateFunc));
	// glutSpaceballButtonFunc
	exports.Set(Napi::String::New(env, "glutSpaceballButtonFunc"), Napi::Function::New(env, _glutSpaceballButtonFunc));
	// glutButtonBoxFunc
	exports.Set(Napi::String::New(env, "glutButtonBoxFunc"), Napi::Function::New(env, _glutButtonBoxFunc));
	// glutDialsFunc
	exports.Set(Napi::String::New(env, "glutDialsFunc"), Napi::Function::New(env, _glutDialsFunc));
	// glutTabletMotionFunc
	exports.Set(Napi::String::New(env, "glutTabletMotionFunc"), Napi::Function::New(env, _glutTabletMotionFunc));
	// glutTabletButtonFunc
	exports.Set(Napi::String::New(env, "glutTabletButtonFunc"), Napi::Function::New(env, _glutTabletButtonFunc));
	// glutVisibilityFunc
	exports.Set(Napi::String::New(env, "glutVisibilityFunc"), Napi::Function::New(env, _glutVisibilityFunc));
	// glutWindowStatusFunc
	exports.Set(Napi::String::New(env, "glutWindowStatusFunc"), Napi::Function::New(env, _glutWindowStatusFunc));
	// glutSetOption
	exports.Set(Napi::String::New(env, "glutSetOption"), Napi::Function::New(env, _glutSetOption));
	// glutGet
	exports.Set(Napi::String::New(env, "glutGet"), Napi::Function::New(env, _glutGet));
	// glutDeviceGet
	exports.Set(Napi::String::New(env, "glutDeviceGet"), Napi::Function::New(env, _glutDeviceGet));
	// glutGetModifiers
	exports.Set(Napi::String::New(env, "glutGetModifiers"), Napi::Function::New(env, _glutGetModifiers));
	// glutLayerGet
	exports.Set(Napi::String::New(env, "glutLayerGet"), Napi::Function::New(env, _glutLayerGet));
	// glutExtensionSupported
	exports.Set(Napi::String::New(env, "glutExtensionSupported"), Napi::Function::New(env, _glutExtensionSupported));
	// glutGetProcAddress
	exports.Set(Napi::String::New(env, "glutGetProcAddress"), Napi::Function::New(env, _glutGetProcAddress));
	// glutBitmapCharacter
	exports.Set(Napi::String::New(env, "glutBitmapCharacter"), Napi::Function::New(env, _glutBitmapCharacter));
	// glutBitmapString
	exports.Set(Napi::String::New(env, "glutBitmapString"), Napi::Function::New(env, _glutBitmapString));
	// glutBitmapWidth
	exports.Set(Napi::String::New(env, "glutBitmapWidth"), Napi::Function::New(env, _glutBitmapWidth));
	// glutBitmapLength
	exports.Set(Napi::String::New(env, "glutBitmapLength"), Napi::Function::New(env, _glutBitmapLength));
	// glutBitmapHeight
	exports.Set(Napi::String::New(env, "glutBitmapHeight"), Napi::Function::New(env, _glutBitmapHeight));
	// glutStrokeCharacter
	exports.Set(Napi::String::New(env, "glutStrokeCharacter"), Napi::Function::New(env, _glutStrokeCharacter));
	// glutStrokeString
	exports.Set(Napi::String::New(env, "glutStrokeString"), Napi::Function::New(env, _glutStrokeString));
	// glutStrokeWidth
	exports.Set(Napi::String::New(env, "glutStrokeWidth"), Napi::Function::New(env, _glutStrokeWidth));
	// glutStrokeWidthf
	exports.Set(Napi::String::New(env, "glutStrokeWidthf"), Napi::Function::New(env, _glutStrokeWidthf));
	// glutStrokeLength
	exports.Set(Napi::String::New(env, "glutStrokeLength"), Napi::Function::New(env, _glutStrokeLength));
	// glutStrokeLengthf
	exports.Set(Napi::String::New(env, "glutStrokeLengthf"), Napi::Function::New(env, _glutStrokeLengthf));
	// glutStrokeHeight
	exports.Set(Napi::String::New(env, "glutStrokeHeight"), Napi::Function::New(env, _glutStrokeHeight));
	// glutWireSphere
	exports.Set(Napi::String::New(env, "glutWireSphere"), Napi::Function::New(env, _glutWireSphere));
	// glutSolidSphere
	exports.Set(Napi::String::New(env, "glutSolidSphere"), Napi::Function::New(env, _glutSolidSphere));
	// glutWireTorus
	exports.Set(Napi::String::New(env, "glutWireTorus"), Napi::Function::New(env, _glutWireTorus));
	// glutSolidTorus
	exports.Set(Napi::String::New(env, "glutSolidTorus"), Napi::Function::New(env, _glutSolidTorus));
	// glutWireCylinder
	exports.Set(Napi::String::New(env, "glutWireCylinder"), Napi::Function::New(env, _glutWireCylinder));
	// glutSolidCylinder
	exports.Set(Napi::String::New(env, "glutSolidCylinder"), Napi::Function::New(env, _glutSolidCylinder));
	// glutWireCube
	exports.Set(Napi::String::New(env, "glutWireCube"), Napi::Function::New(env, _glutWireCube));
	// glutSolidCube
	exports.Set(Napi::String::New(env, "glutSolidCube"), Napi::Function::New(env, _glutSolidCube));
	// glutWireTetrahedron
	exports.Set(Napi::String::New(env, "glutWireTetrahedron"), Napi::Function::New(env, _glutWireTetrahedron));
	// glutSolidTetrahedron
	exports.Set(Napi::String::New(env, "glutSolidTetrahedron"), Napi::Function::New(env, _glutSolidTetrahedron));
	// glutWireOctahedron
	exports.Set(Napi::String::New(env, "glutWireOctahedron"), Napi::Function::New(env, _glutWireOctahedron));
	// glutSolidOctahedron
	exports.Set(Napi::String::New(env, "glutSolidOctahedron"), Napi::Function::New(env, _glutSolidOctahedron));
	// glutWireDodecahedron
	exports.Set(Napi::String::New(env, "glutWireDodecahedron"), Napi::Function::New(env, _glutWireDodecahedron));
	// glutSolidDodecahedron
	exports.Set(Napi::String::New(env, "glutSolidDodecahedron"), Napi::Function::New(env, _glutSolidDodecahedron));
	// glutWireIcosahedron
	exports.Set(Napi::String::New(env, "glutWireIcosahedron"), Napi::Function::New(env, _glutWireIcosahedron));
	// glutSolidIcosahedron
	exports.Set(Napi::String::New(env, "glutSolidIcosahedron"), Napi::Function::New(env, _glutSolidIcosahedron));
	// glutWireRhombicDodecahedron
	exports.Set(Napi::String::New(env, "glutWireRhombicDodecahedron"), Napi::Function::New(env, _glutWireRhombicDodecahedron));
	// glutSolidRhombicDodecahedron
	exports.Set(Napi::String::New(env, "glutSolidRhombicDodecahedron"), Napi::Function::New(env, _glutSolidRhombicDodecahedron));
	// glutWireTeapot
	exports.Set(Napi::String::New(env, "glutWireTeapot"), Napi::Function::New(env, _glutWireTeapot));
	// glutSolidTeapot
	exports.Set(Napi::String::New(env, "glutSolidTeapot"), Napi::Function::New(env, _glutSolidTeapot));
	// glutWireTeacup
	exports.Set(Napi::String::New(env, "glutWireTeacup"), Napi::Function::New(env, _glutWireTeacup));
	// glutSolidTeacup
	exports.Set(Napi::String::New(env, "glutSolidTeacup"), Napi::Function::New(env, _glutSolidTeacup));
	// glutWireTeaspoon
	exports.Set(Napi::String::New(env, "glutWireTeaspoon"), Napi::Function::New(env, _glutWireTeaspoon));
	// glutSolidTeaspoon
	exports.Set(Napi::String::New(env, "glutSolidTeaspoon"), Napi::Function::New(env, _glutSolidTeaspoon));
	// glutSetVertexAttribCoord3
	exports.Set(Napi::String::New(env, "glutSetVertexAttribCoord3"), Napi::Function::New(env, _glutSetVertexAttribCoord3));
	// glutSetVertexAttribNormal
	exports.Set(Napi::String::New(env, "glutSetVertexAttribNormal"), Napi::Function::New(env, _glutSetVertexAttribNormal));
	// glutSetVertexAttribTexCoord2
	exports.Set(Napi::String::New(env, "glutSetVertexAttribTexCoord2"), Napi::Function::New(env, _glutSetVertexAttribTexCoord2));
	// glutGameModeString
	exports.Set(Napi::String::New(env, "glutGameModeString"), Napi::Function::New(env, _glutGameModeString));
	// glutEnterGameMode
	exports.Set(Napi::String::New(env, "glutEnterGameMode"), Napi::Function::New(env, _glutEnterGameMode));
	// glutLeaveGameMode
	exports.Set(Napi::String::New(env, "glutLeaveGameMode"), Napi::Function::New(env, _glutLeaveGameMode));
	// glutGameModeGet
	exports.Set(Napi::String::New(env, "glutGameModeGet"), Napi::Function::New(env, _glutGameModeGet));
	// glutVideoResizeGet
	exports.Set(Napi::String::New(env, "glutVideoResizeGet"), Napi::Function::New(env, _glutVideoResizeGet));
	// glutSetupVideoResizing
	exports.Set(Napi::String::New(env, "glutSetupVideoResizing"), Napi::Function::New(env, _glutSetupVideoResizing));
	// glutStopVideoResizing
	exports.Set(Napi::String::New(env, "glutStopVideoResizing"), Napi::Function::New(env, _glutStopVideoResizing));
	// glutVideoResize
	exports.Set(Napi::String::New(env, "glutVideoResize"), Napi::Function::New(env, _glutVideoResize));
	// glutVideoPan
	exports.Set(Napi::String::New(env, "glutVideoPan"), Napi::Function::New(env, _glutVideoPan));
	// glutSetColor
	exports.Set(Napi::String::New(env, "glutSetColor"), Napi::Function::New(env, _glutSetColor));
	// glutGetColor
	exports.Set(Napi::String::New(env, "glutGetColor"), Napi::Function::New(env, _glutGetColor));
	// glutCopyColormap
	exports.Set(Napi::String::New(env, "glutCopyColormap"), Napi::Function::New(env, _glutCopyColormap));
	// glutMultiEntryFunc
	exports.Set(Napi::String::New(env, "glutMultiEntryFunc"), Napi::Function::New(env, _glutMultiEntryFunc));
	// glutMultiButtonFunc
	exports.Set(Napi::String::New(env, "glutMultiButtonFunc"), Napi::Function::New(env, _glutMultiButtonFunc));
	// glutMultiMotionFunc
	exports.Set(Napi::String::New(env, "glutMultiMotionFunc"), Napi::Function::New(env, _glutMultiMotionFunc));
	// glutMultiPassiveFunc
	exports.Set(Napi::String::New(env, "glutMultiPassiveFunc"), Napi::Function::New(env, _glutMultiPassiveFunc));
	// glutInitContextFunc
	exports.Set(Napi::String::New(env, "glutInitContextFunc"), Napi::Function::New(env, _glutInitContextFunc));
	// glutAppStatusFunc
	exports.Set(Napi::String::New(env, "glutAppStatusFunc"), Napi::Function::New(env, _glutAppStatusFunc));
	// glutSetKeyRepeat
	exports.Set(Napi::String::New(env, "glutSetKeyRepeat"), Napi::Function::New(env, _glutSetKeyRepeat));
	// glutIgnoreKeyRepeat
	exports.Set(Napi::String::New(env, "glutIgnoreKeyRepeat"), Napi::Function::New(env, _glutIgnoreKeyRepeat));
	// glutForceJoystickFunc
	exports.Set(Napi::String::New(env, "glutForceJoystickFunc"), Napi::Function::New(env, _glutForceJoystickFunc));
	// glutReportErrors
	exports.Set(Napi::String::New(env, "glutReportErrors"), Napi::Function::New(env, _glutReportErrors));
	// Return Instantiated Module
	return exports;
}

NODE_API_MODULE(nodeglut, Init)
