/*
 * RgbImageViewer.h
 *
 *  Created on: Jul 29, 2014
 *      Author: pavel
 */

#ifndef RGBIMAGEVIEWER_H_
#define RGBIMAGEVIEWER_H_

#include <Common.h>
#include <RgbImage.h>

class RgbImageViewer
{
public:
	using Ptr = std::shared_ptr<RgbImageViewer>;

	RgbImageViewer( JNIEnv * jniEnv, jobject object_self );
	virtual ~RgbImageViewer();

	void drawRgbImage( RgbImage );

private:
	jobject _object_self;
	jmethodID _method_drawBitmap;
};

#endif /* RGBIMAGEVIEWER_H_ */
