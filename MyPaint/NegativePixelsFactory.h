#pragma once
#include "EditFactory.h"
#include "NegativePixels.h"

class NegativePixelsFactory : public EditFactory {
public:
	PixelsHC* create(int depth) { return new NegativePixels(depth); }
};
