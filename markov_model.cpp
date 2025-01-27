#include <iostream>
#include "markov_model.h"
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <iterator>

MarkovModel::MarkovModel(int ordre) : ordre_(ordre) {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

void MarkovModel::construire_modele(const std::vector<std::string>& mots) {
    if (mots.size() < static_cast<size_t>(ordre_)) {
        std::cerr << "Erreur : Le texte source est trop court pour l'ordre spécifié." << std::endl;
        return;
    }

    for (size_t i = 0; i <= mots.size() - ordre_; ++i) {
        std::ostringstream oss;
        for (int j = 0; j < ordre_; ++j) {
            if (j > 0) oss << ' ';
            oss << mots[i + j];
        }
        std::string cle = oss.str();
        std::string suivant = (i + ordre_ < mots.size()) ? mots[i + ordre_] : "";
        table_markov_[cle].push_back(suivant);
    }
}

std::string MarkovModel::generer_texte(int longueur, const std::string& mot_initial) {
    if (table_markov_.empty()) {
        std::cerr << "Erreur : Le modèle de Markov n'a pas été construit." << std::endl;
        return "";
    }

    std::string cle;

    // Si un mot initial est fourni et existe dans le modèle
    if (!mot_initial.empty()) {
        for (const auto& pair : table_markov_) {
            if (pair.first.find(mot_initial) == 0) {
                cle = pair.first;
                break;
            }
        }
        if (cle.empty()) {
            std::cerr << "Mot initial introuvable dans le modèle. Utilisation d'une clé aléatoire." << std::endl;
        }
    }

    // Si aucune clé initiale n'est trouvée, choisir une clé de départ aléatoire
    if (cle.empty()) {
        auto it = table_markov_.begin();
        std::advance(it, std::rand() % table_markov_.size());
        cle = it->first;
    }

    std::vector<std::string> mots_genere;
    mots_genere.push_back(cle);

    for (int i = 1; i < longueur; ++i) {
        auto it_cle = table_markov_.find(cle);
        if (it_cle == table_markov_.end()) break;

        const std::vector<std::string>& successeurs = it_cle->second;
        std::string suivant = successeurs[std::rand() % successeurs.size()];

        mots_genere.push_back(suivant);
        cle = cle.substr(cle.find(' ') + 1) + " " + suivant;
    }

    std::ostringstream texte_genere;
    for (const auto& mot : mots_genere) {
        texte_genere << mot << ' ';
    }

    return texte_genere.str();
}
