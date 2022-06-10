#include "PredictionTrie.h"

PredictionTrie::PredictionTrie()
{
    _root = new PredictionTrie::PredictionTrieNode;
    _root->count = 0u;
    _root->type = PredictionTrie::PredictionTrieNode::Type::Root;
}

PredictionTrie::~PredictionTrie()
{
    clear(_root->children);
}

void PredictionTrie::clear(std::unordered_map<char, PredictionTrieNode*> unorderedMap)
{
    for (auto& x: unorderedMap)
    {
        clear(x.second->children);
        x.second->children.clear();
    }
}

void PredictionTrie::insert(const std::string& word)
{
    auto* current = _root;

    for (auto letter : word)
    {
        auto foundIt = current->children.find(letter);

        if (foundIt == current->children.end())
        {
            auto [it, _] = current->children.emplace(letter, new PredictionTrieNode);
            foundIt = it;
        }

        current = foundIt->second;
    }

    current->type = PredictionTrie::PredictionTrieNode::Type::Leaf;
    current->count += 1u;
}

PredictionTrie::PredictionTrieNode* PredictionTrie::find(const std::string& word) const
{
    auto* current = _root;
    for (auto letter : word)
    {
        auto foundIt = current->children.find(letter);

        if (foundIt == current->children.end())
        {
            return nullptr;
        }

        current = foundIt->second;
    }

    return current;
}

std::vector<PredictionTrie::MatchedPair> PredictionTrie::allWordsStartedWith(const std::string& wordBegin) const
{
    auto* found = find(wordBegin);
    if (!found)
    {
        return {};
    }

    std::vector<MatchedPair> result;
    collectAllWordsStartedWith(wordBegin, found->children, result);

    return result;
}

void PredictionTrie::collectAllWordsStartedWith(
        const std::string& wordPart, const std::unordered_map<char, PredictionTrieNode*>& letterLayer,
        std::vector<MatchedPair>& result) const
{
    for (auto&& [letter, node] : letterLayer)
    {
        std::string word = wordPart + letter;
        if (node->type == PredictionTrie::PredictionTrieNode::Type::Leaf)
        {
            result.push_back(std::make_tuple(word, node->count));
        }

        collectAllWordsStartedWith(word, node->children, result);
    }
}

std::vector<std::string> PredictionTrie::findBestMatches(const std::string& wordBegin, unsigned count) const
{
    auto allWords = allWordsStartedWith(wordBegin);

    count = allWords.size() < count ? allWords.size() : count;

    std::partial_sort(
            std::begin(allWords),
            allWords.begin() + count,
            std::end(allWords),
            [](const auto& first, const auto& second)
            {
                return std::get<1>(first) > std::get<1>(second);
            }
    );

    std::vector<std::string> result;

    for (int i = 0; i < count; ++i)
    {
        result.push_back(std::get<0>(allWords[i]));
    }

    return result;
}

void PredictionTrie::collectAllNodes(const std::unordered_map<char,
        PredictionTrieNode*>& letterLayer, std::vector<PredictionTrieNode*>& result) const
{
    for (auto& [letter, node] : letterLayer)
    {
        result.emplace_back(node);
        collectAllNodes(node->children, result);
    }
}



