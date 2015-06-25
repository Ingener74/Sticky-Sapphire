/*
 * RgbImageViewer.h
 *
 *  Created on: Jul 29, 2014
 *      Author: pavel
 */

#ifndef RGBIMAGEVIEWER_H_
#define RGBIMAGEVIEWER_H_

#include <memory>

#include <jni.h>
#include <android/bitmap.h>

#include "RgbImage.h"

class RgbImageViewer
{
public:
    RgbImageViewer(JNIEnv * jniEnv, jobject object_self);
    virtual ~RgbImageViewer();

    void drawRgbImage(RgbImage);

private:
    JavaVM *jvm = nullptr;

    jobject _object_self;
    jmethodID _method_drawBitmap;
};

#endif /* RGBIMAGEVIEWER_H_ */
