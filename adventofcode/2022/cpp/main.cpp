#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

int assignment_4_2()
{
	ifstream f("day4.txt");
	int sum = 0;
	while (!f.eof())
	{
		string line;
		f >> line; // x-y,k-z format
		int x, y, k, z;
		char temp;
		istringstream(line) >> x >> temp >> y >> temp >> k >> temp >> z;

		if (x <= k && y >= z || k <= x && z >= y || x <= k && y >= k || x <= z && y >= z)
		{
			sum++;
		}
	}
	return sum;
}

int assignment_4_1()
{
	ifstream f("day4.txt");
	int sum = 0;
	while (!f.eof())
	{
		string line;
		f >> line; // x-y,k-z format
		int x, y, k, z;
		char temp;
		istringstream(line) >> x >> temp >> y >> temp >> k >> temp >> z;

		if (x <= k && y >= z || k <= x && z >= y)
		{
			sum++;
		}
	}
	return sum;
}

int assignment_3_2()
{
	ifstream f("day3.txt");
	int sum = 0;
	while (!f.eof())
	{
		string line1, line2, line3;
		bool found = false;
		f >> line1 >> line2 >> line3;
		for (size_t i = 0; i < line1.size() && !found; i++)
		{
			for (size_t j = 0; j < line2.size() && !found; j++)
			{
				for (size_t k = 0; k < line3.size() && !found; k++)
				{
					if (line1[i] == line2[j] && line1[i] == line3[k])
					{
						sum += isupper(line1[i]) ? line1[i] - 'A' + 27 : line1[i] - 'a' + 1;
						found = true;
					}
				}
			}
		}
	}
	return sum;
}

int assignment_3_1()
{
	ifstream f("day3.txt");
	int sum = 0;
	while (!f.eof())
	{
		string line;
		bool found = false;
		f >> line;
		for (size_t i = 0; i < line.size() / 2 && !found; i++)
		{
			for (size_t j = line.size() / 2; j < line.size() && !found; j++)
			{
				if (line[i] == line[j])
				{
					sum += isupper(line[i]) ? line[i] - 'A' + 27 : line[i] - 'a' + 1;
					found = true;
				}
			}
		}
	}
	return sum;
}

int assignment_2_2()
{
	ifstream f("day2.txt");
	int sum = 0;
	while (!f.eof())
	{
		string left, right;
		f >> left >> right;
		if (left == "A") // Rock
		{
			if (right == "Y") sum += (1 + 3); // Draw
			else if (right == "X") sum += (3 + 0); // Lose
			else if (right == "Z") sum += (2 + 6); // Win
		}
		else if (left == "B") // Paper
		{
			if (right == "Y") sum += (2 + 3);
			else if (right == "X") sum += (1 + 0);
			else if (right == "Z") sum += (3 + 6);
		}
		else if (left == "C") // Scissors
		{
			if (right == "Y") sum += (3 + 3);
			else if (right == "X") sum += (2 + 0);
			else if (right == "Z") sum += (1 + 6);
		}
	}
	return sum;
}

int assignment_2_1()
{
	ifstream f("day2.txt");
	int sum = 0;
	while (!f.eof())
	{
		string left, right;
		f >> left >> right;
		if (left == "A") // Rock
		{
			if (right == "Y") sum += (2 + 6); // Paper 2
			else if (right == "X") sum += (1 + 3); // Rock 1
			else if (right == "Z") sum += (3 + 0); // Scissors 3
		}
		else if (left == "B") // Paper
		{
			if (right == "Y") sum += (2 + 3); // Paper 2
			else if (right == "X") sum += (1 + 0); // Rock 1
			else if (right == "Z") sum += (3 + 6); // Scissors 3
		}
		else if (left == "C") // Scissors
		{
			if (right == "Y") sum += (2 + 0); // Paper 2
			else if (right == "X") sum += (1 + 6); // Rock 1
			else if (right == "Z") sum += (3 + 3); // Scissors 3
		}
	}
	return sum;
}

int assignment_1()
{
	ifstream f("day1.txt");
	int sum = 0;
	int max = 0;
	while (!f.eof())
	{
		int temp = 0;
		f >> temp;
		sum += temp;

		// Here is a cheating with replacing \n\n with \n0 instead 
		if (temp == 0)
		{
			if (sum > max)
			{
				max = sum;
			}
			sum = 0;
		}
	}
	return max;
}

int main()
{
	cout << assignment_1() << endl;
	cout << assignment_2_1() << endl;
	cout << assignment_2_2() << endl;
	cout << assignment_3_1() << endl;
	cout << assignment_3_2() << endl;
	cout << assignment_4_1() << endl;
	cout << assignment_4_2() << endl;
	return 0;
}
