import std;

using std::vector, std::string, std::stoi, std::exchange;

struct Claim {
  int id;
  int left;
  int top;
  int width;
  int height;

  static Claim from_str(string line) {
    Claim claim;
    line = line.substr(1);
    claim.id = stoi(line.substr(0, line.find(' ')));
    line = line.substr(line.find('@') + 2);
    claim.left = stoi(line.substr(0, line.find(',')));
    line = line.substr(line.find(',') + 1);
    claim.top = stoi(line.substr(0, line.find(':')));
    line = line.substr(line.find(':') + 2);
    claim.width = stoi(line.substr(0, line.find('x')));
    line = line.substr(line.find('x') + 1);
    claim.height = stoi(line);
    return claim;
  }
};

int main() {
  constexpr int max_size{1000};
  vector<Claim> claims;
  string line;
  while (std::getline(std::cin, line)) {
    claims.push_back(Claim::from_str(line));
  }
  vector<int> claim_counts(max_size * max_size, 0);
  for (const auto& claim : claims) {
    for (auto y{claim.top}; y < claim.top + claim.height; ++y) {
      for (auto x{claim.left}; x < claim.left + claim.width; ++x) {
        ++claim_counts[x * max_size + y];
      }
    }
  }
  auto a{std::count_if(claim_counts.begin(), claim_counts.end(),
                       [](auto claim_count) { return claim_count > 1; })};
  auto intact_claim{std::find_if(claims.begin(), claims.end(), [&](const auto& claim) {
    for (auto y{claim.top}; y < claim.top + claim.height; ++y) {
      for (auto x{claim.left}; x < claim.left + claim.width; ++x) {
        if (claim_counts[x * max_size + y] != 1) {
          return false;
        }
      }
    }
    return true;
  })};
  auto b{intact_claim->id};
  std::cout << a << " " << b << "\n";
  return 0;
}
