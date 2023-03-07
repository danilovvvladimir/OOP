#pragma once
#include <string>
using HexColor = uint32_t;
// mb using area = double?

const HexColor DEFAULT_HEX_FILL_COLOR = 0xffffff;
const HexColor DEFAULT_HEX_OUTPUT_COLOR = 0;

class IShape
{
public:
	virtual double GetArea() const = 0;
	virtual double GetPerimeter() const = 0;
	virtual std::string ToString() const = 0;
	virtual HexColor GetOutlineColor() const = 0;
};