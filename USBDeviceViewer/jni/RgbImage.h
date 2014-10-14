/*
 * RgbImage.h
 *
 *  Created on: Jul 29, 2014
 *      Author: pavel
 */

#ifndef RGBIMAGE_H_
#define RGBIMAGE_H_

#include <Common.h>

struct RgbImage
{
	int32_t rows = 0;
	int32_t cols = 0;
	std::vector<uint8_t> buffer;
};

#endif /* RGBIMAGE_H_ */
