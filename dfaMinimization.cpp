#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <unordered_set>
#include <queue>
#include <unordered_map>
#include <string>

struct dfaGraph {
  std::vector<std::map<char, size_t>> transitionList;
  std::vector<char> alphabets;
  size_t finalState{};
  size_t initialState{};
  size_t countOfStates() const { return transitionList.capacity(); }
  size_t delta(size_t precedingState, char alphabet) const { 
      return transitionList[precedingState].find(alphabet)->second;
  }
  void reserveMemory() {
    size_t countOfStates{};
    std::cout << "Enter no. of states in DFA: ";
    std::cin >> countOfStates;
    transitionList.reserve(countOfStates);
  }
};

bool equivalent(const std::pair<size_t, size_t>& state, const std::unordered_set<size_t>& equivalentSet,
                const dfaGraph& dfa) {
  for (auto alphabet : dfa.alphabets) {
    size_t deltaOfFirst = dfa.delta(state.first, alphabet);
    size_t deltaOfSecond = dfa.delta(state.second, alphabet);
    if (deltaOfFirst != deltaOfSecond) {
      if ((equivalentSet.find(deltaOfFirst) == equivalentSet.end()) ||
            (equivalentSet.find(deltaOfSecond) == equivalentSet.end()))
        return false;
    }
  }
   return true;
}

bool bothSetAreEquivalent(const std::vector<std::unordered_set<size_t>>& equivalence, 
    const std::vector<std::unordered_set<size_t>>& precedingEquivalence) {
  if (equivalence.size() != precedingEquivalence.size()) return false;
  for (size_t i = 0; i < equivalence.size(); i++) {
    if (equivalence[i] != precedingEquivalence[i]) return false;
  }
  return true;
}

std::vector<std::unordered_set<size_t>> nextEquivalence(const dfaGraph& dfa,
    const std::vector <std::unordered_set<size_t>>&
    precedingEquivalence) {
  std::vector<std::unordered_set<size_t>> equivalentSet;
  for (auto& stateTuple : precedingEquivalence) {
    size_t pos = equivalentSet.size();
    for (auto& state : stateTuple) {
      if (equivalentSet.size() == pos) {
        equivalentSet.push_back(std::unordered_set<size_t>{state});
      } else {
        for (size_t i = pos; i < equivalentSet.size(); i++) {
          size_t s = *((equivalentSet[i]).begin());
          if (equivalent(std::make_pair(s, state), stateTuple, dfa)) {
            equivalentSet[i].insert(state);
            break;
          }
          if (equivalentSet.size() == (pos + 1))
            equivalentSet.push_back(std::unordered_set<size_t>{state});
        }
      }
    }
  }

  if (precedingEquivalence == equivalentSet)
    return equivalentSet;
  else
    return nextEquivalence(dfa, std::move(equivalentSet));
}

std::unordered_map<size_t, size_t> stateToEquivalenceMap(
    const dfaGraph& dfa,
    const std::vector<std::unordered_set<size_t>>& equivalentSet) {
  std::unordered_map<size_t, size_t> map;
  for (size_t state = 0; state < dfa.countOfStates(); state++) {
    for (size_t i = 0; i < equivalentSet.size(); i++) {
      if (equivalentSet[i].find(state) != equivalentSet[i].end()) {
        map.insert({state, i});
        break;
      }
    }     
  }
  return map;
}

std::string equivalenceToString(const std::unordered_set<size_t>& equivalence) {
  std::string s = "{";
  for (auto state : equivalence) s += "q" + std::to_string(state) + ",";
  s[s.size() - 1] = '}';
  return s;
}

void printDfaFromEquivalentSet(
    const dfaGraph& dfa,
    const std::vector<std::unordered_set<size_t>>& equivalentSet) {
  std::unordered_map<size_t, size_t> map =
      stateToEquivalenceMap(dfa, equivalentSet);
  std::cout << "\n\nState";
  for (auto alphabet : dfa.alphabets) std::cout << "\t\t" << alphabet;
  for (size_t i = 0; i < equivalentSet.size(); i++) {
    std::cout << '\n' << equivalenceToString(equivalentSet[i]);
    for (auto& alphabet : dfa.alphabets) {
      size_t precedingState = *(equivalentSet[i].begin());
      size_t succeedingState = dfa.delta(precedingState, alphabet);
      std::cout << "\t\t" << equivalenceToString(equivalentSet[map.find(succeedingState)->second]);
    }
  }
  std::cout << "\n\nStarting State : "
            << equivalenceToString(
                   equivalentSet[map.find(dfa.initialState)->second]);
  std::cout << "\nFinal State : "
            << equivalenceToString(
                   equivalentSet[map.find(dfa.finalState)->second]);
}

std::unordered_set<size_t> reachableNonFinalStates(const dfaGraph& dfa) {
  std::unordered_set<size_t> reachableNonFinalStates{};
  std::vector<bool> reachableLookUpTable(dfa.countOfStates(), false);  // vector of bool has different behaviour
  std::queue<size_t> Queue;
  Queue.push(dfa.initialState);
  while (!Queue.empty()) {
    reachableLookUpTable[Queue.front()] = true;
    for (auto alphabet : dfa.alphabets) {
      size_t succeedingState = dfa.delta(Queue.front(), alphabet);
      if (!reachableLookUpTable[succeedingState]) Queue.push(succeedingState);
    }
    Queue.pop();
  }

  for (size_t state = 0; state < dfa.countOfStates(); state++) {
    if (state == dfa.finalState) continue;
    reachableNonFinalStates.insert(state);
  }
  return reachableNonFinalStates;
}

std::vector<char> seperateAlternateChar(const std::string& str) {
  std::vector<char> char_set{};
  for (size_t i = 0; i < str.size(); i = i + 2) char_set.push_back(str[i]);
  return char_set;
}

std::vector<char> askAlphabets() { 
  std::string str;
  std::vector<char> alphabets;
  std::cout << "Enter alphabets: ";
  std::cin >> str;
  alphabets = seperateAlternateChar(str);
  return alphabets;
}

size_t askFinalState() { 
  size_t finalState;
  std::cout << "Enter accepting state : ";
  std::cin >> finalState;
  return finalState;
}

int main() {
  dfaGraph dfa;
  dfa.reserveMemory();
  dfa.alphabets = askAlphabets();
  dfa.finalState = askFinalState();
  for (size_t state = 0; state < dfa.countOfStates(); state++) {
    std::map<char, size_t> transitionMap;
    for (auto alphabet : dfa.alphabets) {
      size_t transitionState{};
      std::cout << "delta(q" << state << "," << alphabet << ") = ";
      std::cin >> transitionState;
      transitionMap.insert({alphabet, transitionState});
    }
    dfa.transitionList.push_back(std::move(transitionMap));
  }
  auto reachableStatesSet = reachableNonFinalStates(dfa);
  std::vector<std::unordered_set<size_t>> equivalenceSet(2);
  equivalenceSet.push_back(std::move(reachableStatesSet));
  equivalenceSet.push_back(std::unordered_set<size_t>{dfa.finalState});
  auto finalEquivalence = nextEquivalence(dfa, equivalenceSet);
  printDfaFromEquivalentSet(dfa, finalEquivalence);
}
