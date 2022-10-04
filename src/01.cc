import std;

int main() {
  using integer_parser = std::istream_iterator<int>;
  std::vector<int> changes{integer_parser(std::cin), integer_parser()};
  auto a{std::accumulate(changes.begin(), changes.end(), 0L)};
  auto b = [&]() -> long {
    std::unordered_set<long> seen;
    long frequency{0};
    while (true) {
      for (auto change : changes) {
        frequency += change;
        if (seen.contains(frequency)) {
          return frequency;
        } else {
          seen.insert(frequency);
        }
      }
    }
  }();
  std::cout << a << " " << b << "\n";
  return 0;
}
