/*
 * UvcImage.cpp
 *
 *  Created on: Jul 16, 2014
 *      Author: ingener
 */

#include <UsbCameraViewer/UvcImage.h>

namespace usbcv
{

UvcImage::UvcImage( int32_t rows, int32_t cols, int32_t bitsPerPixel ) :
        _buffer(rows * cols * bitsPerPixel / 8)
{
}

UvcImage::~UvcImage()
{
}

int32_t UvcImage::getRows() const
{
    return _rows;
}

int32_t UvcImage::getCols() const
{
    return _cols;
}

int32_t UvcImage::getBitsPerPixel() const
{
    return _bitsPerPixel;
}

uint8_t* UvcImage::getData() const
{
    return const_cast<uint8_t*>(&_buffer.front());
}

} /* namespace usbcv */
