#ifndef GRAPH_HPP
# define GRAPH_HPP

# include "Line.hpp"
# include "Vector2.hpp"

# include <cmath>
# include <fstream>
# include <iostream>
# include <set>
# include <vector>

class Graph
{
    public:
        typedef std::vector<Vector2> point_vector;
        typedef std::vector<Line> line_vector;
        typedef std::set<Vector2> point_set;
    private:
        point_vector _points;
        line_vector _lines;
    public:
        Graph();
        ~Graph();
        Graph(const Graph &copy);
        Graph &operator=(const Graph &rhs);
        size_t size() const;
        void add_point(const Vector2 &point);
        void add_line(const Line &line);
        void add_line(const Vector2 &p1, const Vector2 &p2);
        void read_file(const std::string &filename);
        void show(int xlim_min, int xlim_max, int ylim_min, int ylim_max) const;
};

#endif
