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
	int32_t rows;
	int32_t cols;
	std::vector<uint8_t> buffer;
};

#endif /* RGBIMAGE_H_ */
