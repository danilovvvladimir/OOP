#pragma once
#include <string>
using HexColor = uint32_t;


class IShape
{
public:
	virtual double GetArea() const = 0;
	virtual double GetPerimeter() const = 0;
	virtual std::string ToString() const = 0;
	virtual HexColor GetOutlineColor() const = 0;
};