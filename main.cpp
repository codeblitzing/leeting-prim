#include <iostream>
#include "bits/stdc++.h"
using namespace std;

template<typename T>
void print(std::string_view name, vector<T> const& q) {
  std::cout << name << ": \t";
  for (auto const& v : q) {
//    std::cout << v << ' ';
    for (auto const &n : v) {
      std::cout << n << ' ';
    }
    std::cout << ", ";
  }
  std::cout << '\n';
}

template<typename Q>
void print_queue(std::string_view name, Q q) {
  // NB: q is passed by value because there is no way to traverse
  // priority_queue's content without erasing the queue.
  std::cout << name << ": \t";
  for (; !q.empty(); q.pop()) {
    for (auto const &v: q.top()) {
      std::cout << v << ' ';
    }
    std::cout << ", ";
  }
  std::cout << '\n';
}

// 1584 - Min cost to connect all points (Prim)
// points = [[0,0],[2,2],[3,10],[5,2],[7,0]]
// cost = 20

int main()
{
  vector<vector<int> > points = {{0,0},{2,2},{3,10},{5,2},{7,0}};
  print("points", points);

  vector<vector<int> > d0 = {{0,0}};
  print("d0", d0);

  auto cmp = [](vector<int> const & a, vector<int> const & b) -> bool {
    return a[0] < b[0];
  };
  priority_queue minQ(d0.begin(), d0.end(), cmp);
  print_queue("minQ", minQ);

  // ================
  // TODO: need visited list

  // Build adjacency list:   (src#): 0 -> [ [cost, dest#], [cost, dest#], ...]
  vector<vector<vector<int> > > adj(points.size());
//  for (auto & ipt: points) {
//    for (auto &jpt: points)
//  }

  int i = 0;
  for (auto /*const &*/ ii = points.begin(); ii != points.end(); ++ii, ++i) {
    int j = 0;
    auto [xi, yi] = (*ii);
    for (auto const & jj = ii+1; jj != points.end(); ++jj, ++j) {
      auto [xj, yj] = *jj;
      auto cost = abs(xi - xj) + abs(yi - yj);
      adj[i].push_back({cost, });
    }

  }

  // TODO: this isnt the right data - must compute manhattan dist between each point
  minQ.push({2, 2});

  // TODO: start with a point, add all adjacencies for that point...
  //       pull top out of pq (will be lowest-cost edge), discard if we have already visited that dest...
  //       add cost to total

  int iiiii=10;

  return 0;
}

