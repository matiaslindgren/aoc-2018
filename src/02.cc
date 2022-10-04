import std;

using std::vector, std::string;

int find_a(const vector<string>& lines) {
  std::array<int, 'z' - 'a' + 1> freq;
  auto contains = [&](int count) -> bool {
    return std::find(freq.begin(), freq.end(), count) != freq.end();
  };
  int two_count{0};
  int three_count{0};
  for (const auto& line : lines) {
    freq.fill(0);
    for (auto ch : line) {
      ++freq[ch - 'a'];
    }
    two_count += contains(2);
    three_count += contains(3);
  }
  return two_count * three_count;
}

string intersect_chars(const string& s1, const string& s2) {
  string result;
  auto char1{s1.begin()};
  auto char2{s2.begin()};
  while (char1 != s1.end() && char2 != s2.end()) {
    if (*char1 == *char2) {
      result.push_back(*char1);
    }
    ++char1;
    ++char2;
  }
  return result;
}

string find_b(const vector<string>& lines) {
  for (auto line1{lines.begin()}; line1 != lines.end(); ++line1) {
    for (auto line2{lines.begin()}; line2 != line1; ++line2) {
      auto result{intersect_chars(*line1, *line2)};
      if (result.size() == line1->size() - 1) {
        return result;
      }
    }
  }
  return {};
}

int main() {
  using line_parser = std::istream_iterator<string>;
  vector<string> lines{line_parser(std::cin), line_parser()};
  auto a{find_a(lines)};
  auto b{find_b(lines)};
  std::cout << a << " " << b << "\n";
  return 0;
}
