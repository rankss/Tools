#ifndef UNIONSET_HPP
#define UNIONSET_HPP

#include <vector>
#include <iostream>

namespace Structures
{
	class UnionSet
	{
	private:
		std::vector<int> set;
		std::vector<int> rank;

		int find(int x)
		{
			try
			{
				return (this->set[x] == x) ? x : this->set[x] = this->find(set[x]);
			}
			catch (const std::exception& e)
			{
				throw e;
			}
		}

	public:
		UnionSet() = delete;
		UnionSet(int n)
		{
			this->set.resize(n);
			this->rank.resize(n, 0);
			for (int i = 0; i < n; i++)
				this->set[i] = i;
		}
		~UnionSet() {}

		int Size() { return (int)set.size(); }

		std::vector<int> Set() { return this->set; }

		int Union(int x, int y)
		{
			int xset = this->find(x), yset = this->find(y);
			if (xset != yset)
			{
				if (this->rank[xset] < this->rank[yset])
					this->set[xset] = yset;
				else if (this->rank[xset] > this->rank[yset])
					this->set[yset] = xset;
				else
					this->set[yset] = xset, this->rank[xset]++;
				return 1;
			}
			return 0;
		}

		int SetCount()
		{
			int count = 0;
			for (int i = 0; i < this->set.size(); i++)
				if (this->set[i] == i)
					count++;
			return count;
		}

		int& operator [](int index)
		{
			try
			{
				return this->set[index];
			}
			catch (const std::exception& e)
			{
				throw e;
			}
		}

		friend std::ostream& operator <<(std::ostream& os, UnionSet& set)
		{
			os << "[ " << set[0];
			for (int i = 1; i < set.Size(); i++)
				os << " " << set[i];
			os << " ]" << std::endl;

			return os;
		}
	};
}

#endif // !UNIONSET_HPP