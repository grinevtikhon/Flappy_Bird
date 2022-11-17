#include "Network.h"

double fun(double x)
{
	return 1.0f / (1 + pow(2.7182818284, -x));
}

Network::Network(vector<int> _v)
{
	ans.resize(_v.back());

	value.resize(_v.size());
	for (int i = 0; i < _v.size(); ++i)
		value[i].resize(_v[i], 0);

	bias.resize(_v.size());
	for (int i = 0; i < bias.size(); ++i)
		bias[i].resize(_v[i], 0);

	w.resize(_v.size() - 1);
	for (int i = 0; i < w.size(); ++i)
	{
		w[i].resize(_v[i]);
		for (int j = 0; j < w[i].size(); ++j)
			w[i][j].resize(_v[i + 1]);
	}

	generateRandomBias();
	generateRandomW();
}

void Network::generateRandomW()
{
	for (int i = 0; i < w.size(); ++i)
		for (int j = 0; j < w[i].size(); ++j)
			for (int k = 0; k < w[i][j].size(); ++k)
				w[i][j][k] = rand() % 5 - 2;

	return;
}
void Network::generateRandomBias()
{
	for (int i = 0; i < bias.size(); ++i)
		for (int j = 0; j < bias[i].size(); ++j)
			bias[i][j] = rand() % 10 - 5;

	return;
}

void Network::calculate_neuron(int& _x, int& _y)
{
	value[_x][_y] = 0;
	for (int i = 0; i < value[_x - 1].size(); ++i) {
		value[_x][_y] += value[_x - 1][i] * w[_x - 1][i][_y];
	}
	value[_x][_y] += bias[_x][_y];

	if (_x != value.size() - 1)
		value[_x][_y] = fun((value[_x][_y]));


	return;
}

void Network::calculate_line(int _x)
{
	for (int i = 0; i < value[_x].size(); ++i)
		calculate_neuron(_x, i);

	return;
}

void Network::calculate_network()
{
	for (int i = 1; i < value.size(); ++i)
		calculate_line(i);

	return;
}

void Network::setInput(vector<double> _v)
{
	value[0] = _v;

	return;
}

void Network::setAnswer(vector<double> _v)
{
	if (_v.size() != ans.size())
	{
		cout << "ALARM vvedino ne norm ans!! \n";
		return;
	}
	for (int i = 0; i < _v.size(); ++i)
		ans[i] = _v[i];

	return;
}

vector<double> Network::getAnswer()
{
	return value.back();
}

void Network::calculate_mistake()
{
	//mistake = 0;

	for (int i = 0; i < ans.size(); ++i)
		mistake += pow(value.back()[i] - ans[i], 2);

	return;
}

void Network::clear_mistake()
{
	mistake = 0;

	return;
}

void Network::set_mistake(double _mistake)
{
	mistake = _mistake;
}

double Network::get_mistake()
{
	return mistake;
}

bool Network::operator<(Network& _n)
{
	return get_mistake() < _n.get_mistake();
}

bool Network::operator<=(Network& _n)
{
	return get_mistake() <= _n.get_mistake();
}

bool Network::operator==(Network& _n)
{
	return get_mistake() == _n.get_mistake();
}

bool Network::operator>(Network& _n)
{
	return get_mistake() > _n.get_mistake();
}

bool Network::operator>=(Network& _n)
{
	return get_mistake() >= _n.get_mistake();
}

void Network::mutate(Network& _n, double _dispersion)
{
	for (int i = 0; i < _n.w.size(); ++i)
		for (int j = 0; j < _n.w[i].size(); ++j)
			for (int k = 0; k < _n.w[i][j].size(); ++k)
			{
				double buf = (rand() % 4000 - 2000.0) / 1000.0;
				if (abs(buf) > 1)
				{
					_n.w[i][j][k] = w[i][j][k] / (buf / 2 * _dispersion);
				}
				else {
					_n.w[i][j][k] = w[i][j][k] * buf * _dispersion;
				}
			}


	for (int i = 0; i < _n.bias.size(); ++i)
		for (int j = 0; j < _n.bias[i].size(); ++j)
		{
			double buf = (rand() % 4000 - 2000.0) / 1000.0;
			if (abs(buf) > 1)
			{
				_n.bias[i][j] = bias[i][j] / (buf / 2 * _dispersion);
			}
			else {
				_n.bias[i][j] = bias[i][j] * buf * _dispersion;
			}
		}

	return;
}

double Network::fuction(vector<double> _x)
{
	setInput(_x);
	calculate_network();
	return getAnswer()[0];
}

void Network::calculate_mistake_for_dots(vector<double> _dot, vector<double> _ans)
{
	clear_mistake();

	for (int i = 0; i < _dot.size(); ++i)
	{
		setAnswer({ _ans[i] });
		setInput({ _dot[i] });
		calculate_network();
		calculate_mistake();
	}

	return;
}
