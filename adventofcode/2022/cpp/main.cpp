#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>
#include <list>
using namespace std;

int assignment_8_2()
{
	struct Node
	{
		int heigh = 0;
		bool visible = false;
	};

	vector<vector<Node>> map;
	ifstream f("day8.txt");
	string s;

	int row = 0;

	while (!f.eof())
	{
		f >> s;
		map.push_back(vector<Node>());
		for (char c : s)
		{
			map[row].push_back({ static_cast<int>(c) - '0', false });
		}
		row++;
	}

	int max = 0;
	int field_size = map.size();

	for (int i = 1; i < field_size - 1; i++)
	{
		for (int j = 1; j < field_size - 1; j++)
		{
			int current_heigh = map[i][j].heigh;
			// Go UP
			int up = 0;
			for(int k = i - 1; k >= 0; k--)
			{
				up++;
				if (map[k][j].heigh >= current_heigh)
				{
					break;
				}
			}
			
			// Go DOWN
			int down = 0;
			for (int k = i + 1; k < field_size; k++)
			{
				down++;
				if (map[k][j].heigh >= current_heigh)
				{
					break;
				}
			}

			// Go LEFT
			int left = 0;
			for (int k = j - 1; k >= 0; k--)
			{
				left++;
				if (map[i][k].heigh >= current_heigh)
				{
					break;
				}
			}

			// Go RIGHT
			int right = 0;
			for (int k = j + 1; k < field_size; k++)
			{
				right++;
				if (map[i][k].heigh >= current_heigh)
				{
					break;
				}
			}

			if (up * down * left * right > max)
			{
				max = up * down * left * right;
			}
		}
	}

	return max;
}

int assignment_8_1()
{
	struct Node
	{
		int heigh = 0;
		bool visible = false;
	};

	vector<vector<Node>> map;
	ifstream f("day8.txt");
	string s;

	int row = 0;

	while (!f.eof())
	{
		f >> s;
		map.push_back(vector<Node>());
		for (char c : s)
		{
			map[row].push_back({ static_cast<int>(c) - '0', false });
		}
		row++;
	}

	int field_size = map.size();
	int visible_num = 4 * field_size - 4;

	for (int i = 1; i < field_size - 1; i++)
	{
		int current_heigh = map[i][0].heigh;
		for (int j = 1; j < field_size - 1; j++)
		{
			if (map[i][j].heigh > current_heigh)
			{
				if (!map[i][j].visible)
				{
					visible_num++;
					map[i][j].visible = true;
				}
				current_heigh = map[i][j].heigh;
			}

			if (current_heigh == 9)
			{
				break;
			}
		}
	}

	for (int i = 1; i < field_size - 1; i++)
	{
		int current_heigh = map[0][i].heigh;
		for (int j = 1; j < field_size - 1; j++)
		{
			if (map[j][i].heigh > current_heigh)
			{
				if (!map[j][i].visible)
				{
					visible_num++;
					map[j][i].visible = true;
				}
				current_heigh = map[j][i].heigh;
			}

			if (current_heigh == 9)
			{
				break;
			}
		}
	}

	for (int i = 1; i < field_size - 1; i++)
	{
		int current_heigh = map[i][field_size - 1].heigh;
		for (int j = field_size - 2; j > 0; j--)
		{
			if (map[i][j].heigh > current_heigh)
			{
				if (!map[i][j].visible)
				{
					visible_num++;
					map[i][j].visible = true;
				}
				current_heigh = map[i][j].heigh;
			}

			if (current_heigh == 9)
			{
				break;
			}
		}
	}

	for (int i = 1; i < field_size - 1; i++)
	{
		int current_heigh = map[field_size - 1][i].heigh;
		for (int j = field_size - 2; j > 0; j--)
		{
			if (map[j][i].heigh > current_heigh)
			{
				if (!map[j][i].visible)
				{
					visible_num++;
					map[j][i].visible = true;
				}
				current_heigh = map[j][i].heigh;
			}

			if (current_heigh == 9)
			{
				break;
			}
		}
	}

	return visible_num;
}

// Assignment 7

struct Node
{
	enum class Type
	{
		DIR = 0,
		FILE = 1
	};

	int size;
	Type type;
	string name;
	Node* parent;
	list<Node> child;
};

int calculate_size(Node* current)
{
	for (auto& node : current->child)
	{
		if (node.type == Node::Type::DIR)
		{
			current->size += calculate_size(&node);
		}
		else
		{
			current->size += node.size;
		}
	}
	return current->size;
}

int assignment_7_1_find_answer(Node* current)
{
	int answer = current->size > 100000 ? 0 : current->size;
	for (auto& node : current->child)
	{
		if (node.type == Node::Type::DIR)
		{
			answer += assignment_7_1_find_answer(&node);
		}
	}
	return answer;
}

// Need to find the smallest directory with that can be deleted to free enough space
int assignment_7_2_find_answer(Node* current, int needed_size, int smallest_directory_size)
{
	if (current->size >= needed_size && current->size < smallest_directory_size)
	{
		smallest_directory_size = current->size;
	}

	for (auto& node : current->child)
	{
		if (node.type == Node::Type::DIR)
		{
			smallest_directory_size = assignment_7_2_find_answer(&node, needed_size, smallest_directory_size);
		}
	}

	return smallest_directory_size;
}

int assignment_7(bool mode_7_2 = false)
{
	ifstream f("day7.txt");

	Node root{ 0, Node::Type::DIR, "/", nullptr };
	Node* current = &root;

	string s;

	while (!f.eof())
	{
		f >> s;

		if (s == "$")
		{
			continue;
		}
		else if (s == "ls")
		{
			while (!f.eof())
			{
				f >> s;
				if (s == "dir")
				{
					f >> s;
					current->child.push_back({ 0, Node::Type::DIR, s, current });
				}
				else if (s == "$")
				{
					break;
				}
				else if (!f.eof())
				{
					int size = stoi(s);
					f >> s;
					current->child.push_back({ size, Node::Type::FILE, s, current });
				}
			}
		}
		else if (s == "cd")
		{
			f >> s;
			if (s == "..")
			{
				if (current->parent != nullptr)
				{
					current = current->parent;
				}
			}
			else
			{
				for (Node& child : current->child)
				{
					if (child.name == s)
					{
						current = &child;
						break;
					}
				}
			}
		}
	}

	calculate_size(&root);
	int ans = mode_7_2 ? assignment_7_2_find_answer(&root, 30000000 - (70000000 - root.size), 70000000) : assignment_7_1_find_answer(&root);
	return ans;
}

int assignment_6(const int N)
{
	ifstream f("day6.txt");
	int num = 0;

	list<char> lst;

	while (!f.eof())
	{
		char c;
		f >> c;
		for (list<char>::iterator it = lst.begin(); it != lst.end(); ++it)
		{
			if (*it == c)
			{
				lst.erase(lst.begin(), it);
				lst.erase(it);
				break;
			}
		}
		lst.push_back(c);

		num++;
		if (lst.size() == N)
		{
			return num;
		}
	}

	return num;
}

int assignment_5(bool mode_5_2 = false)
{
	ifstream f("day5.txt");
	int sum = 0;

	vector<stack<char>> container;
	vector<stack<char>> temp;
	temp.resize(10);
	container.resize(10);

	while (!f.eof())
	{
		string line;
		getline(f, line);
		int index = 0;

		if (line.find("1   2   3   4   5   6   7   8   9") != string::npos)
		{
			getline(f, line);
			break;
		}

		for (int i = 0; i < line.size(); i++)
		{
			if (line[i] == '[')
			{
				temp[index].push(line[i + 1]);
				index++;
			}
			else if (line[i] == ' ')
			{
				if (i < line.size())
				{
					if (line[i + 1] == ' ')
					{
						i += 3;
						index++;
					}
				}
			}
		}
	}

	for (int i = 0; i < temp.size(); i++)
	{
		while (temp[i].size() > 0)
		{
			container[i].push(temp[i].top());
			temp[i].pop();
		}
	}

	while (!f.eof())
	{
		string temp;
		int count = 0;
		int from = 0;
		int to = 0;

		string line;
		getline(f, line);
		istringstream(line) >> temp >> count >> temp >> from >> temp >> to;

		// match 0..8 iteration
		from--;
		to--;

		if (mode_5_2)
		{
			stack<char> stack_to_rearrange;
			while (count > 0)
			{
				stack_to_rearrange.push(container[from].top());
				container[from].pop();
				count--;
			}

			while (stack_to_rearrange.size() > 0)
			{
				container[to].push(stack_to_rearrange.top());
				stack_to_rearrange.pop();
			}
		}
		else
		{
			while (count > 0)
			{
				container[to].push(container[from].top());
				container[from].pop();
				count--;
			}
		}
	}
	
	return sum;
}

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
	cout << assignment_5() << endl; // 5_1
	cout << assignment_5(true) << endl; // 5_2
	cout << assignment_6(4) << endl;
	cout << assignment_6(14) << endl;
	cout << assignment_7() << endl; // 7_1
	cout << assignment_7(true) << endl; // 7_2
	cout << assignment_8_1() << endl;
	cout << assignment_8_2() << endl;

	return 0;
}
