#ifndef PREDICTIONTRIE_H
#define PREDICTIONTRIE_H

#include <unordered_map>
#include <tuple>
#include <vector>
#include <string>
#include <algorithm>


class PredictionTrie
{
private:
    using MatchedPair = std::tuple<std::string, unsigned int>;
public:

    PredictionTrie();
    ~PredictionTrie();

    PredictionTrie(const PredictionTrie& other) = delete;
    PredictionTrie(PredictionTrie&& other) = delete;

    void insert(const std::string& word);

    std::vector<MatchedPair> allWordsStartedWith(const std::string& wordBegin) const;
    std::vector<std::string> findBestMatches(const std::string& wordBegin, unsigned count) const;

private:
    struct PredictionTrieNode
    {
        enum class Type
        {
            Root,
            Regular,
            Leaf,
        };

        Type type = Type::Regular;
        std::unordered_map<char, PredictionTrieNode*> children;
        unsigned int count = 0;
    };

    PredictionTrieNode* find(const std::string& word) const;

    void collectAllWordsStartedWith(
            const std::string& wordPart,
            const std::unordered_map<char, PredictionTrieNode*>& letterLayer,
            std::vector<MatchedPair>& result) const;

    void collectAllNodes(const std::unordered_map<char,
            PredictionTrieNode*>& letterLayer, std::vector<PredictionTrieNode*>& result) const;

    void clear(std::unordered_map<char, PredictionTrieNode*> unorderedMap);


    PredictionTrieNode* _root;
};


#endif //PREDICTIONTRIE_H
