#ifndef MARKOV_MODEL_H
#define MARKOV_MODEL_H

#include <unordered_map>
#include <vector>
#include <string>

class MarkovModel {
public:
    MarkovModel(int ordre);
    void construire_modele(const std::vector<std::string>& mots);
    std::string generer_texte(int longueur, const std::string& mot_initial = "");

private:
    int ordre_;
    std::unordered_map<std::string, std::vector<std::string>> table_markov_;
    std::string choisir_suivant(const std::vector<std::string>& suivants);
};

#endif // MARKOV_MODEL_H
