#include <iostream>
#include "text_processing.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>

std::vector<std::string> charger_et_traiter_texte(const std::string& nom_fichier) {
    std::ifstream fichier(nom_fichier);
    std::string ligne, mot, texte;
    std::vector<std::string> mots;

    if (fichier.is_open()) {
        while (std::getline(fichier, ligne)) {
            texte += ligne + " ";
        }
        fichier.close();
    } else {
        std::cerr << "Erreur : Impossible d'ouvrir le fichier " << nom_fichier << std::endl;
        return mots;
    }

    // Conversion en minuscules
    std::transform(texte.begin(), texte.end(), texte.begin(), ::tolower);

    // Segmentation en mots en gérant la ponctuation interne
    std::istringstream iss(texte);
    while (iss >> mot) {
        // Suppression des ponctuations en début et fin de mot
        while (!mot.empty() && std::ispunct(mot.front())) {
            mot.erase(0, 1);
        }
        while (!mot.empty() && std::ispunct(mot.back())) {
            mot.pop_back();
        }
        if (!mot.empty()) {
            mots.push_back(mot);
        }
    }

    return mots;
}
