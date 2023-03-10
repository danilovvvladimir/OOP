#pragma once
#include "ICanvas.h"
using HexColor = uint32_t;

class ICanvasDrawable
{
public:
	virtual void Draw(ICanvas& canvas) = 0;
};