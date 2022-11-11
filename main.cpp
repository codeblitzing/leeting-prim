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

template <typename Q>
auto pop(Q&q) {
  auto result = q.top();
  q.pop();
  return result;
}

int prim1();

typedef array<int,2> Point;

int mhat_dist(Point const & pt1, Point const & pt2)
{
  auto [x1,y1] = pt1;
  auto [x2,y2] = pt2;

  auto dist = abs(x1-x2) + abs(y1-y2);
  return dist;
}


// 1584 - Min cost to connect all points (Prim)
// points = [[0,0],[2,2],[3,10],[5,2],[7,0]]
// 0->   0->0:0   (0->1:4)   0->2:13     0->3:7    0->4:7             4     = 4
// 1->   1->0:4    1->1:0   (1->2:9)    (1->3:3)   1->4:7             +9 +3 = 16
// 2->   2->0:13   2->1:9    2->2:0      2->3:10   2->4:14
// 3->   3->0:7    3->1:3    3->2:10     3->3:0   (3->4:4)            +4    = 20
// 4->   4->0:7    4->1:7    4->2:14     4->3:4    4->4:0
//
// cost = 20

int main()
{
  vector<Point> points = {{0,0},{2,2},{3,10},{5,2},{7,0}};
  print("points", points);
  auto N = points.size();

  for (int i = 0; i < N; ++i) {
    cout << i << "->";
    for (int j = 0; j < N; ++j) {
      cout << "   " << i << "->" << j << ":" << mhat_dist(points[i], points[j]);
    }
    cout << endl;
  }

  set<int> visited, un_visited;

  // Put others in unvisited
  int curr_node = 1;
  visited.insert(curr_node);
  for (int i = 0; i < N; ++i) {
    if (i != curr_node) {
      un_visited.insert(i);
    }
  }

  // TODO: build min-heap
  auto cmp = [](array<int,2> const & a, array<int,2> const & b) -> bool {
    return a[0] > b[0];
  };

  // Visit each node breadth-first
  vector<array<int, 2> > d0 = {{0,curr_node}};
  priority_queue min_heap(d0.begin(), d0.end(), cmp);
  print_queue("min_heap", min_heap);

  int total_cost = 0;
  while (visited.size() < N) {

    // Add edges to all the others
    auto const & curr = points[curr_node];
    for (auto other_node: un_visited) {
      auto const & other = points[other_node];
      auto dist = mhat_dist(curr, other);
      min_heap.push({dist, other_node});
    }

    // Pull out of min-heap until find an unvisited node
    for (;;) {
      auto [cost, dest] = pop(min_heap);
      if (visited.contains(dest)) {
        continue;
      }

      // This is the lowest-cost edge to add
      cout << "adding: " << dest << " (" << cost << ")" << endl;
      total_cost += cost;
      curr_node = dest;
      break;
    }

    // Move curr_node from unvisited to visited
    un_visited.erase(curr_node);
    visited.insert(curr_node);
  }

  cout << "Total cost: " << total_cost << endl;


//  prim1();

  return 0;
}

int prim1()
{
  vector<array<int, 2> > points = {{0,0},{2,2},{3,10},{5,2},{7,0}};
  print("points", points);
  auto N = points.size();

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
    //adj[i] = vector<array<int,2> >(N);
    auto [xi, yi] = (*ii);

    int j = 0;
    for (auto /*const &*/ jj = points.begin(); jj != points.end(); ++jj, ++j) {
      auto [xj, yj] = *jj;
      auto cost = abs(xi - xj) + abs(yi - yj);
      adj[i].push_back({cost, j});
    }
  }

  // start with a point, add all adjacencies for that point...
  // pull top out of pq (will be lowest-cost edge), discard if we have already visited that dest...
  // add cost to total
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

