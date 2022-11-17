#include "Generation.h"

Generation::Generation(vector<int> _v, int _group_size, int _n, double _dispersion)
{

	number_of_generations = _n;

	group_size = _group_size;

	dispersion = _dispersion;

	for (int i = 0; i < _n * _group_size; ++i)
		gen.push_back(_v);
}

void Generation::calculate_generation()
{
	for (int i = 0; i < gen.size(); ++i)
	{
		for (int j = 0; j < input.size(); ++j)
		{
			gen[i].calculate_mistake_for_dots(input, ans);
		}
	}

	sort(gen.begin(), gen.end());

	best_mistake = gen[0].get_mistake();

	return;
}

void Generation::set_input(vector<double> _v)
{
	input = _v;
}

vector<double> Generation::get_input()
{
	return input;
}

void Generation::set_ans(vector<double> _v)
{
	ans = _v;
}

vector<double> Generation::get_ans()
{
	return ans;
}

void Generation::generate_next_generation()
{
	int j = gen.size() - 1;
	for (int i = 0; i < number_of_generations; ++i)
	{
		for (int k = 1; k < group_size; ++k)
		{
			gen[i].mutate(gen[j], dispersion);
			//cout << j << " ";
			--j;
		}
	}

	//cout << endl;
}