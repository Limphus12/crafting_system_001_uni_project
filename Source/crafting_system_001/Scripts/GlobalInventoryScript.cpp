#include "GlobalInventoryScript.h"

GlobalInventoryScript::GlobalInventoryScript()
{
	void PlusTestResource();
	{
		GlobalInventoryScript::TestResourceCount++;
	}

	void MinusTestResource();
	{
		GlobalInventoryScript::TestResourceCount--;
	}
}