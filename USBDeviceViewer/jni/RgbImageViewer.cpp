/*
 * RgbImageViewer.cpp
 *
 *  Created on: Jul 29, 2014
 *      Author: pavel
 */

#include <Error.h>

#include <RgbImageViewer.h>

using namespace std;

RgbImageViewer::RgbImageViewer( JNIEnv* jniEnv, jobject object_self )
{
    string methodName = "drawBitmap";

    jint res = jniEnv->GetJavaVM(&jvm);
    if ( !jvm ) throw Error("can't get java vm");

    jclass class_self = jniEnv->GetObjectClass(object_self);
    if ( !class_self ) throw Error("can't get self class");

    _object_self = jniEnv->NewGlobalRef(object_self);
    if ( !_object_self ) throw Error("can't create global ref self class");

    _method_drawBitmap = jniEnv->GetMethodID(class_self, methodName.c_str(), "(Landroid/graphics/Bitmap;)V");
    if ( !_method_drawBitmap ) throw Error("can't get drawBigmap method");

    jniEnv->DeleteLocalRef(class_self);
}

RgbImageViewer::~RgbImageViewer()
{
}

void RgbImageViewer::drawRgbImage( RgbImage rgbImage )
{
    if ( !rgbImage.cols || !rgbImage.rows || !rgbImage.buffer.empty() ) throw Error("image is empty");

    JNIEnv * jniEnv = 0;
    jint res = 0;
    res = jvm->AttachCurrentThread(reinterpret_cast<JNIEnv **>(&jniEnv), nullptr);
    if ( res != JNI_OK ) throw Error("can't attach current thread");

    jclass class_Bitmap = (jclass) jniEnv->FindClass("android/graphics/Bitmap");
    jmethodID method_Bitmap_createBitmap = jniEnv->GetStaticMethodID(class_Bitmap, "createBitmap",
            "(IILandroid/graphics/Bitmap$Config;)Landroid/graphics/Bitmap;");

    jstring string_Config_Name = jniEnv->NewStringUTF("ARGB_8888");
    if ( !string_Config_Name ) throw Error("can't create config string");

    jclass class_Bitmap_Config = jniEnv->FindClass("android/graphics/Bitmap$Config");
    if ( !class_Bitmap ) throw Error("can't find bitmap config class");

    jobject object_Bitmap_Config = jniEnv->CallStaticObjectMethod(class_Bitmap_Config,
            jniEnv->GetStaticMethodID(class_Bitmap_Config, "valueOf",
                    "(Ljava/lang/String;)Landroid/graphics/Bitmap$Config;"), string_Config_Name);
    if ( !object_Bitmap_Config ) throw Error("can't create bitmap config object");

    jobject object_Bitmap = jniEnv->CallStaticObjectMethod(class_Bitmap, method_Bitmap_createBitmap, rgbImage.cols,
            rgbImage.rows, object_Bitmap_Config);

    uint8_t *data = 0;
    res = AndroidBitmap_lockPixels(jniEnv, object_Bitmap, reinterpret_cast<void **>(&data));
    if ( res != ANDROID_BITMAP_RESULT_SUCCESS ) throw Error("can't lock pixels");

    if ( data )
    {
        uint8_t * src = &rgbImage.buffer[ 0 ];
        uint8_t * dst = data;
        for ( int i = 0, imax = rgbImage.rows; i < imax; ++i )
        {
            for ( int j = 0, jmax = rgbImage.cols; j < jmax; ++j )
            {
                *dst++ = *src++;
                *dst++ = *src++;
                *dst++ = *src++;
                *dst++ = 255;
            }
        }

        res = AndroidBitmap_unlockPixels(jniEnv, object_Bitmap);
        if ( res != ANDROID_BITMAP_RESULT_SUCCESS ) throw Error("can't unlock pixels");
    }

    jniEnv->CallVoidMethod(_object_self, _method_drawBitmap, object_Bitmap);

    /* clean up */
    jniEnv->DeleteLocalRef(class_Bitmap);
    jniEnv->DeleteLocalRef(class_Bitmap_Config);
    jniEnv->DeleteLocalRef(string_Config_Name);
    jniEnv->DeleteLocalRef(object_Bitmap_Config);
    jniEnv->DeleteLocalRef(object_Bitmap);

    if ( (res = jvm->DetachCurrentThread()) != JNI_OK ) throw Error("can't detach current thread");
}
