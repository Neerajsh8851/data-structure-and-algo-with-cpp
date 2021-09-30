

#include <iostream>


#include"List.h"
#include <stdlib.h>

int main() {

	Alist<int> data;

	for (int i = 0; i < 50; i++)
		data.add(i);

	std::cout << "ascending order: \n";
	data.start();
	while (data.hasNext())
	{
		std::cout << data.getNext() << ", ";
	}

	std::cout << "\n descending order: \n";
	data.end();
	while (data.hasPrev())
	{
		std::cout << data.getPrev() << ", ";
	}


	data.remove(10);

	std::cout << "\n value at index 10 = " << data.get(10);
	return 0;
}

