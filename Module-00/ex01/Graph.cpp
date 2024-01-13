#include "Graph.hpp"

Graph::Graph() : _points(), _lines() {}

Graph::~Graph() {}

Graph::Graph(const Graph &copy) : _points(copy._points), _lines(copy._lines) {}

Graph &Graph::operator=(const Graph &rhs)
{
	_points = rhs._points;
	_lines = rhs._lines;
	return (*this);
}

size_t Graph::size() const
{
	return (_points.size());
}

void Graph::add_point(const Vector2 &point)
{
	_points.push_back(point);
}

void Graph::add_line(const Line &line)
{
	_lines.push_back(line);
}

void Graph::add_line(const Vector2 &p1, const Vector2 &p2)
{
	add_line(Line(p1, p2));
}

void Graph::read_file(const std::string &filename)
{
	std::ifstream input(filename.c_str());
	if (!input.is_open())
		throw std::runtime_error("Couldn't open graph file \"" + filename + "\"");
	float x = 0.f, y = 0.f;
	while (input.peek() != std::ifstream::traits_type::eof())
	{
		input >> x;
		if (!input)
			throw std::invalid_argument("Invalid input file");
		input >> y;
		if (!input)
			throw std::invalid_argument("Invalid input file");
		_points.push_back(Vector2(x, y));
	}
}

// grid numbers are truncated to last digit
// for negative numbers, sign is not displayed
void Graph::show(int xlim_min, int xlim_max, int ylim_min, int ylim_max) const
{
	if (xlim_min >= xlim_max || ylim_min >= ylim_max)
		throw std::invalid_argument("Invalid xlim or ylim for graph");
	point_set visible_set;
	for (point_vector::const_iterator it = _points.begin(); it != _points.end(); ++it)
	{
		const int it_x = static_cast<int>(it->get_x());
		const int it_y = static_cast<int>(it->get_y());
		if (it_x >= xlim_min && it_x <= xlim_max && it_y >= ylim_min && it_y <= ylim_max)
			visible_set.insert(Vector2(it_x, it_y));
	}
	for (line_vector::const_iterator line = _lines.begin(); line != _lines.end(); ++line)
	{
		try
		{
			for (int x = xlim_min; x <= xlim_max; ++x)
			{
				const Vector2 p = Vector2(x, static_cast<int>(line->solve_for_y(x).get_y()));
				if (p.get_x() >= xlim_min && p.get_x() <= xlim_max && p.get_y() >= ylim_min && p.get_y() <= ylim_max)
					visible_set.insert(p);
			}
		}
		catch (const std::logic_error&)
		{
			const int x_value = static_cast<int>(-line->get_offset() / line->get_x_factor());
			if (x_value >= xlim_min && x_value <= xlim_max)
				for (int y = ylim_min; y <= ylim_max; y++)
					visible_set.insert(Vector2(x_value, y));
		}
	}
	for (int y = ylim_max; y >= ylim_min; y--)
	{
		std::cout << '&' << (std::abs(y) % 10);
		for (int x = xlim_min; x <= xlim_max; x++)
			if (visible_set.find(Vector2(x, y)) != visible_set.end())
				std::cout << 'X';
			else
				std::cout << '.';
		std::cout << std::endl;
	}
	std::cout << "& ";
	for (int x = xlim_min; x <= xlim_max; x++)
		std::cout << (std::abs(x) % 10);
	std::cout << std::endl;
}
