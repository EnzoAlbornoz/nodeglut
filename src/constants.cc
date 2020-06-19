#include <napi.h>
#include <GL/freeglut.h>
#include "constants.hh"

Napi::Object InitConstants(Napi::Env env, Napi::Object object) {
	// Set (void*) based constants
	// GLUT_STROKE_ROMAN
	object.Set(Napi::String::New(env, "GLUT_STROKE_ROMAN"),Napi::Number::New(env, (uintptr_t) GLUT_STROKE_ROMAN));
	// GLUT_STROKE_MONO_ROMAN
	object.Set(Napi::String::New(env, "GLUT_STROKE_MONO_ROMAN"),Napi::Number::New(env, (uintptr_t) GLUT_STROKE_MONO_ROMAN));
	// GLUT_BITMAP_9_BY_15
	object.Set(Napi::String::New(env, "GLUT_BITMAP_9_BY_15"),Napi::Number::New(env, (uintptr_t) GLUT_BITMAP_9_BY_15));
	// GLUT_BITMAP_8_BY_13
	object.Set(Napi::String::New(env, "GLUT_BITMAP_8_BY_13"),Napi::Number::New(env, (uintptr_t) GLUT_BITMAP_8_BY_13));
	// GLUT_BITMAP_TIMES_ROMAN_10
	object.Set(Napi::String::New(env, "GLUT_BITMAP_TIMES_ROMAN_10"),Napi::Number::New(env, (uintptr_t) GLUT_BITMAP_TIMES_ROMAN_10));
	// GLUT_BITMAP_TIMES_ROMAN_24
	object.Set(Napi::String::New(env, "GLUT_BITMAP_TIMES_ROMAN_24"),Napi::Number::New(env, (uintptr_t) GLUT_BITMAP_TIMES_ROMAN_24));
	// GLUT_BITMAP_HELVETICA_10
	object.Set(Napi::String::New(env, "GLUT_BITMAP_HELVETICA_10"),Napi::Number::New(env, (uintptr_t) GLUT_BITMAP_HELVETICA_10));
	// GLUT_BITMAP_HELVETICA_12
	object.Set(Napi::String::New(env, "GLUT_BITMAP_HELVETICA_12"),Napi::Number::New(env, (uintptr_t) GLUT_BITMAP_HELVETICA_12));
	// GLUT_BITMAP_HELVETICA_18
	object.Set(Napi::String::New(env, "GLUT_BITMAP_HELVETICA_18"),Napi::Number::New(env, (uintptr_t) GLUT_BITMAP_HELVETICA_18));
	// Return Populated Object
	return object;
}
