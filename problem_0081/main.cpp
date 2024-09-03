#include "timer.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>

#include <boost/config.hpp>

#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/property_map/property_map.hpp>

using matrix_t = std::vector<std::vector<unsigned long> >;

void read_matrix(const std::string &filename, matrix_t &matrix) {
  std::ifstream input_file_stream(filename);
  for (std::string line; std::getline(input_file_stream, line); ) {
    std::istringstream line_stream(line);
    matrix.push_back({});
    for (std::string number; std::getline(line_stream, number, ','); ) {
      matrix.back().emplace_back(std::stoul(number));
    }
  }
}

long dijkstra(matrix_t &matrix) {
  using graph_t = boost::adjacency_list<boost::vecS, boost::vecS,
                  boost::directedS, boost::no_property,
                  boost::property<boost::edge_weight_t, unsigned long> >;
  using vertex_descriptor_t = boost::graph_traits<graph_t>::vertex_descriptor;
  using edge_t = std::pair<unsigned long, unsigned long>;
  using predecessors_t = std::vector<vertex_descriptor_t>;
  using distances_t = std::vector<unsigned long>;

  const unsigned long rows = matrix.size();
  const unsigned long cols = matrix.front().size();
  std::vector<edge_t> edges;
  std::vector<unsigned long> weights;
  for (std::size_t row = 0; row < rows; ++row) {
    for (std::size_t col = 0; col < cols; ++col) {
      if (row < rows - 1) {
        edges.emplace_back(cols * row + col, cols * (row + 1) + col);
        weights.emplace_back(matrix[row + 1][col]);
      }

      if (col < cols - 1) {
        edges.emplace_back(cols * row + col, cols * row + col + 1);
        weights.emplace_back(matrix[row][col + 1]);
      }
    }
  }

  graph_t graph(std::begin(edges), std::end(edges), std::begin(weights),
                rows * cols);
  predecessors_t predecessors(boost::num_vertices(graph));
  distances_t distances(boost::num_vertices(graph));
  vertex_descriptor_t source = boost::vertex(0, graph);

  boost::dijkstra_shortest_paths(graph, source,
    boost::predecessor_map(predecessors.data()).distance_map(distances.data()));

  return distances[rows * cols - 1] + matrix[0][0];
}

int main () {

  const std::string filename = "matrix.txt";
  matrix_t matrix;
  long result;

  {
    timer Timer;

    read_matrix(filename, matrix);
    result = dijkstra(matrix);
  }

  std::cout << "Result: " << result << "\n";
}
