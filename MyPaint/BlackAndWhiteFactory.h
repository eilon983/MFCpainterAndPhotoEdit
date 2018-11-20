#pragma once
#include "EditFactory.h"
#include "BlackAndWhite.h"

class BlackAndWhiteFactory : public EditFactory {
public:
	PixelsHC* create(int depth) { return new BlackAndWhite(depth); }
};
