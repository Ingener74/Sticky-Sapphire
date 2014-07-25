/*
 * UvcImage.h
 *
 *  Created on: Jul 16, 2014
 *      Author: ingener
 */

#ifndef UVCIMAGE_H_
#define UVCIMAGE_H_

#include <UsbCameraViewer/Common.h>

namespace usbcv
{

class UvcImage
{
public:
    UvcImage( int32_t rows = 0, int32_t cols = 0, int32_t bitsPerPixel = 24 );
    virtual ~UvcImage();

    int32_t getRows() const;
    int32_t getCols() const;
    int32_t getBitsPerPixel() const;
    uint8_t* getData() const;

private:
    int32_t _rows = 0, _cols = 0, _bitsPerPixel = 24;
    std::vector<uint8_t> _buffer;
};

} /* namespace usbcv */

#endif /* UVCIMAGE_H_ */
