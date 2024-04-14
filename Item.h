#pragma once
class Item
{
public:
	Item(double value, double size);
	Item(const Item& other);
	Item(Item&& other);
	~Item() {};

	Item& operator=(const Item& other);
	Item& operator=(Item&& other);

	friend class KnapsackProblem;

private:
	double value;
	double size;
};

