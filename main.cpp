#include <iostream>
#include <vector>
#include <string>
#include "text_processing.h"
#include "markov_model.h"

int main() {
    std::string nom_fichier = "text_source.txt"; // Nom du fichier texte source
    int ordre = 2; // Ordre du modèle de Markov

    // Chargement et traitement du texte
    std::vector<std::string> mots = charger_et_traiter_texte(nom_fichier);

    // Construction du modèle de Markov
    MarkovModel modele(ordre);
    modele.construire_modele(mots);

    // Génération du texte
    int longueur_texte = 10; // Nombre de mots à générer
    std::string mot_initial;
    std::cout << "Souhaitez-vous spécifier un mot initial ? (oui/non) ";
    std::string reponse;
    std::cin >> reponse;

    if (reponse == "oui") {
        std::cout << "Entrez le mot initial : ";
        std::cin >> mot_initial;
    }

    std::string texte_genere = modele.generer_texte(longueur_texte, mot_initial);

    // Affichage du texte généré
    std::cout << texte_genere << std::endl;

    return 0;
}
