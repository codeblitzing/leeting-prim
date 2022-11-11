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
  vector<array<int, 2> > points = {{0,0},{2,2},{3,10},{5,2},{7,0}};
  print("points", points);
  auto N = points.size();

//  vector<vector<int> > d0 = {{0,0}};
  vector<array<int, 2> > d0 = {{0,0}};
  print("d0", d0);

  auto cmp = [](array<int,2> const & a, array<int,2> const & b) -> bool {
    return a[0] > b[0];
  };
  priority_queue minQ(d0.begin(), d0.end(), cmp);
  print_queue("minQ", minQ);

  // ================
  // TODO: need visited list
  set<int> visited;

  // Build adjacency list:   (src#): 0 -> [ [cost, dest#], [cost, dest#], ...]
  vector<vector<array<int,2> > > adj(N);

  int i = 0;
  for (auto /*const &*/ ii = points.begin(); ii != points.end(); ++ii, ++i) {
//    adj[i] = vector<array<int,2> >(N);
    auto [xi, yi] = (*ii);

    int j = 0;
    for (auto /*const &*/ jj = points.begin(); jj != points.end(); ++jj, ++j) {
      auto [xj, yj] = *jj;
      auto cost = abs(xi - xj) + abs(yi - yj);
      adj[i].push_back({cost, j});
    }
  }

//  // TODO: this isnt the right data - must compute manhattan dist between each point
//  minQ.push({2, 2});

  // TODO: start with a point, add all adjacencies for that point...
  //       pull top out of pq (will be lowest-cost edge), discard if we have already visited that dest...
  //       add cost to total
  int totalCost = 0;
  int node = 0;
  visited.insert(0);

  while (visited.size() < N) {
    // Add all nodes that are adj to `node` to the min-heap
    i = 0;
    for (auto const & ii : adj[node]) {
      auto const &[cost, dest] = ii;
      i += 1;
      if (!visited.contains(dest)) {
        minQ.push({cost, dest});
      }
    }

    // Pull items out of heap until we have a dest that we havent visited, yet.
    for (;;) {
      auto [cost, dest] = minQ.top();
      minQ.pop();
      if (visited.contains(dest)) {
        continue;
      }

      // New dest
      totalCost += cost;
      visited.insert(dest);

      break;
    }
  }

  int iiiii=10;

  return 0;
}

