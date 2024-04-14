#include "Item.h"
#include <stdexcept>
#include "invalidItemSizeException.h"
#include "invalidItemValueException.h"

Item::Item(double value, double size) : value(value), size(size)
{
	if (value < 0) {
		throw invalidItemValueException("Invalid item value!");
	}
	if (size <= 0) {
		throw invalidItemSizeException("Invalid item size!");
	}
}

Item::Item(const Item& other) : value(other.value), size(other.size) {}


Item::Item(Item&& other) : value(other.value), size(other.size) {}


Item& Item::operator=(const Item& other)
{
	if (this == &other) {
		return *this;
	}

	value = other.value;
	size = other.size;

	return *this;
}

Item& Item::operator=(Item&& other)
{
	value = other.value;
	size = other.size;

	return *this;
}
