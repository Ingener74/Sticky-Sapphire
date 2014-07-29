/*
 * RgbImageViewer.cpp
 *
 *  Created on: Jul 29, 2014
 *      Author: pavel
 */

#include <RgbImageViewer.h>

using namespace std;

RgbImageViewer::RgbImageViewer( JNIEnv* jniEnv, jobject object_self )
{
	string methodName = "";

	JavaVM *jvm = nullptr;
	jint res = jniEnv->GetJavaVM( &jvm );
	if ( !jvm ) throw runtime_error( "can't get java vm" );

	jclass class_self = jniEnv->GetObjectClass( object_self );
	if ( !class_self ) runtime_error( "can't get self class" );

	_object_self = jniEnv->NewGlobalRef( object_self );
	if ( !_object_self ) runtime_error( "can't create global ref self class" );

	_method_drawBitmap = jniEnv->GetMethodID( class_self, methodName.c_str(), "(Landroid/graphics/Bitmap;)V" );
	if ( !_method_drawBitmap ) runtime_error( "can't get drawBigmap method" );

	jniEnv->DeleteLocalRef( class_self );
}

RgbImageViewer::~RgbImageViewer()
{
}

void RgbImageViewer::drawRgbImage( RgbImage rgbImage )
{
}
