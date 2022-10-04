import std;

using std::vector;

long find_a(const vector<int>& changes) {
  return std::accumulate(changes.begin(), changes.end(), 0L);
}

long find_b(const vector<int>& changes) {
  std::unordered_set<long> seen;
  long frequency{0};
  while (true) {
    for (auto change : changes) {
      frequency += change;
      if (seen.contains(frequency)) {
        return frequency;
      }
      seen.insert(frequency);
    }
  }
}

int main() {
  using integer_parser = std::istream_iterator<int>;
  std::vector<int> changes{integer_parser(std::cin), integer_parser()};
  auto a{find_a(changes)};
  auto b{find_b(changes)};
  std::cout << a << " " << b << "\n";
  return 0;
}
