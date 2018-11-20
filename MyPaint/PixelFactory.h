#pragma once
#include "EditFactory.h"
#include "PixelsHC.h"

class PixelsFactory : public EditFactory {
public:
	PixelsHC* create(int depth) { return new PixelsHC(depth); }
}; 
