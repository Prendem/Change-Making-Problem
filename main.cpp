#include "pch.h" //Comment out if not using VS with precompiled headers
#include <iostream>
#include <vector>

std::vector<int> makeChange(int target, std::vector<int> &denominations)
{
	std::vector<int> mincoins(target), lastcoin(target);

	for (int value{ 1 }; value <= target; ++value)
	{
		for (int dindex{ static_cast<int>(denominations.size()-1) }; dindex >= 0; --dindex)
		{
			if (denominations[dindex] > value && dindex != 0)
				continue;
			
			if (denominations[dindex] > value && dindex == 0)
			{
				mincoins[value - 1] = 0;
				lastcoin[value - 1] = 0;
				break;
			}
			
			if (denominations[dindex] == value)
			{
				mincoins[value - 1] = 1;
				lastcoin[value - 1] = denominations[dindex];
				break;
			}

			if (mincoins[value - 1 - denominations[dindex]] == 0 && dindex != 0)
				continue;
			
			if (mincoins[value - 1 - denominations[dindex]] == 0 && dindex == 0)
			{
				mincoins[value - 1] = 0;
				lastcoin[value - 1] = 0;
				break;
			}

			if (mincoins[value - 1 - denominations[dindex]] != 0)
			{
				mincoins[value - 1] = mincoins[value - 1 - denominations[dindex]] + 1;
				lastcoin[value - 1] = denominations[dindex];
				break;
			}

		}
	}

	if (mincoins[target - 1] == 0)
		return std::vector<int> {0};

	std::vector<int> returnvector(mincoins[target - 1] + 1);
	returnvector[0] = mincoins[target - 1];
	returnvector[mincoins[target - 1]] = lastcoin[target - 1];
	int previousindex{ target - 1 };

	for (int rindex{ mincoins[target - 1] - 1 }; rindex > 0; --rindex)
	{
		returnvector[rindex] = lastcoin[previousindex - lastcoin[previousindex]];
		previousindex = previousindex - lastcoin[previousindex];
	}

	return returnvector;

}

void sort(std::vector<int> &denominations)
{
	for (int index1{ 0 }; index1 < denominations.size() - 1; ++index1)
	{
		for (int index2{ index1 + 1 }; index2 < denominations.size(); ++index2)
		{
			if (denominations[index1] > denominations[index2])
			{
				int temp{ denominations[index1] };
				denominations[index1] = denominations[index2];
				denominations[index2] = temp;
			}
		}
	}
}

std::vector<int> input(int &target)
{
	
	std::cout << "Enter the number of allowed coins: ";
	int arraylength;
	bool lengthvalid{ false };
	while (!lengthvalid)
	{
		std::cin >> arraylength;
		if (std::cin.fail() || arraylength < 1)
		{
			std::cout << "Invalid input, please enter a positive integer: ";
			std::cin.clear();
			std::cin.ignore(32767, '\n');
			continue;
		}
		else
			lengthvalid = true;
		
	}

	std::vector<int> denominations(arraylength);

	for (int index{ 0 }; index < arraylength; ++index)
	{
		std::cout << "Enter coin #" << index + 1 << ": ";
		bool elementvalid{ false };
		while (!elementvalid)
		{
			std::cin >> denominations[index];
			if (std::cin.fail() || denominations[index] < 1)
			{
				std::cout << "Invalid input, please enter a positive integer: ";
				std::cin.clear();
				std::cin.ignore(32767, '\n');
				continue;
			}
			else
				elementvalid = true;
		}
	}

	std::cout << "Enter the ammount desired ammount of money: ";
	bool targetvalid{ false };
	while (!targetvalid)
	{

		std::cin >> target;
		if (std::cin.fail() || target < 1)
		{
			std::cout << "Invalid input, please enter a positive integer: ";
			std::cin.clear();
			std::cin.ignore(32767, '\n');
			continue;
		}
		else
			targetvalid = true;
	}

	return denominations;
}

int main()
{
	int target;
	std::vector<int> denominations{ input(target) };
	sort(denominations);
	std::vector<int> returnvector{ makeChange(target, denominations) };
	if (returnvector[0] == 0)
	{
		std::cout << "The target could not be made with the given coins";
		return 0;
	}

	std::cout << "The minimum number of the given coins required to make " << target << " is " << returnvector[0] << std::endl;
	std::cout << "This is made with the combination ";
	for (int index{ 1 }; index < returnvector.size(); ++index)
	{
		std::cout << returnvector[index] << " ";
	}

	return 0;
}
