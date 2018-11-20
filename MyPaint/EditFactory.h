#pragma once

#include "PixelsHC.h"

class EditFactory {
public:
	virtual PixelsHC* create(int) = 0;
};