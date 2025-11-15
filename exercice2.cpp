#include <iostream>
#include <string>
#include <vector>
#include <algorithm> // Pour std::find_if ou autres

using namespace std;

/*******************************************
 * Complétez le programme à partir d'ici.
 *******************************************/

// Déclarations anticipées
class Auteur;
class Oeuvre;
class Exemplaire;
class Bibliotheque;

// --- Classe Auteur --- [cite: 87]
class Auteur
{
public:
    // Constructeur [cite: 88]
    Auteur(string n, bool p = false) : nom(n), prix(p) {}

    // Méthodes d'accès
    string getNom() const { return nom; } // [cite: 89]
    bool getPrix() const { return prix; } // [cite: 90]

private:
    string nom;
    bool prix; // Indication s'il a été primé (awarded)
};

// --- Classe Oeuvre --- [cite: 91]
class Oeuvre
{
public:
    // Constructeur [cite: 92]
    Oeuvre(string t, const Auteur& a, string l)
        : titre(t), auteur(a), langue(l) {}
    
    // Destructeur [cite: 102]
    ~Oeuvre()
    {
        cout << "L'oeuvre \"" << titre << ", " << auteur.getNom()
             << ", en " << langue << "\" n'est plus disponible." << endl; // [cite: 103]
    }

    // Interdiction de la copie [cite: 104]
    Oeuvre(const Oeuvre&) = delete;
    Oeuvre& operator=(const Oeuvre&) = delete;

    // Méthodes d'accès
    string getTitre() const { return titre; } // [cite: 93]
    const Auteur& getAuteur() const { return auteur; } // [cite: 94]
    string getLangue() const { return langue; } // [cite: 95]

    // Méthode d'affichage [cite: 96]
    void affiche() const
    {
        cout << titre << ", " << auteur.getNom() << ", en " << langue; // [cite: 98]
    }

private:
    string titre;
    const Auteur& auteur; // Référence constante à l'auteur [cite: 91]
    string langue;
};

// --- Classe Exemplaire --- [cite: 106]
class Exemplaire
{
public:
    // Constructeur [cite: 109]
    Exemplaire(const Oeuvre& o) : oeuvre(o)
    {
        cout << "Nouvel exemplaire de: "; // [cite: 110]
        oeuvre.affiche();
        cout << endl; // [cite: 111]
    }

    // Constructeur de copie [cite: 112]
    Exemplaire(const Exemplaire& autre) : oeuvre(autre.oeuvre)
    {
        cout << "Copie d'un exemplaire de: "; // [cite: 113]
        oeuvre.affiche();
        cout << endl; // [cite: 114]
    }
    
    // Destructeur [cite: 115]
    ~Exemplaire()
    {
        cout << "Un exemplaire de \""; // [cite: 116]
        oeuvre.affiche();
        cout << "\" a été jeté" << endl; // [cite: 117]
    }

    // Méthodes d'accès
    const Oeuvre& getOeuvre() const { return oeuvre; } // [cite: 118]

    // Méthode d'affichage [cite: 119]
    void affiche() const
    {
        cout << "Exemplaire de: "; // [cite: 120]
        oeuvre.affiche();
        // Pas de End Of Line [cite: 120]
    }

private:
    const Oeuvre& oeuvre; // Référence constante à l'œuvre [cite: 107]
};

// --- Classe Bibliotheque --- [cite: 121]
class Bibliotheque
{
public:
    // Constructeur [cite: 124]
    Bibliotheque(string n) : nom(n)
    {
        cout << "La bibliothèque " << nom << " est ouverte!" << endl; // [cite: 126]
    }

    // Destructeur [cite: 141]
    ~Bibliotheque()
    {
        cout << "La bibliothèque " << nom << " ferme ses portes," << endl; // [cite: 142]
        cout << "et détruit ses exemplaires :" << endl; // [cite: 143]
        
        // Libération de la mémoire des exemplaires [cite: 144]
        for (Exemplaire* e : exemplaires) {
            delete e;
        }
    }

    // Méthode d'accès
    string getNom() const { return nom; } // [cite: 127]

    // Méthode stocker [cite: 128]
    void stocker(const Oeuvre& oeuvre, int n = 1)
    {
        for (int i = 0; i < n; ++i) {
            // Construction dynamique et ajout à la fin du vecteur [cite: 130, 132]
            exemplaires.push_back(new Exemplaire(oeuvre));
        }
    }

    // Méthode lister_exemplaires [cite: 133]
    void lister_exemplaires(const string& langue = "") const
    {
        if (langue.empty()) {
            // Afficher tous les exemplaires [cite: 134]
            cout << "La bibliothèque " << nom << " offre les exemplaires suivants :" << endl; // Format d'exemple
        } else {
            // Afficher les exemplaires d'une langue spécifique [cite: 133]
            cout << "Les exemplaires en " << langue << " sont :" << endl; // Format d'exemple
        }
        
        for (const Exemplaire* e : exemplaires) {
            if (langue.empty() || (e->getOeuvre().getLangue() == langue)) {
                e->affiche(); // [cite: 135]
                cout << endl; // Séparés par End of Lines [cite: 136]
            }
        }
    }

    // Méthode compter_exemplaires [cite: 137]
    int compter_exemplaires(const Oeuvre& oeuvre) const
    {
        int count = 0;
        for (const Exemplaire* e : exemplaires) {
            // Comparer l'œuvre par ses caractéristiques (titre, auteur, langue)
            // Bien que l'Oeuvre ne soit pas copiable, on peut comparer les références
            const Oeuvre& o_ref = e->getOeuvre();
            if ((o_ref.getTitre() == oeuvre.getTitre()) &&
                (o_ref.getAuteur().getNom() == oeuvre.getAuteur().getNom()) &&
                (o_ref.getLangue() == oeuvre.getLangue())) {
                count++;
            }
        }
        return count;
    }

    // Méthode afficher_Auteur [cite: 138]
    void afficher_Auteur(bool prix = false) const
    {
        if (prix) {
            cout << "Les auteurs à succès sont :" << endl; // Format d'exemple
        } else {
             // Affichage sans filtre prix
        }

        for (const Exemplaire* e : exemplaires) {
            const Auteur& a = e->getOeuvre().getAuteur();
            
            // Si le filtre prix est désactivé (prix == false) OU
            // Si le filtre prix est activé (prix == true) ET l'auteur est primé
            if (!prix || a.getPrix()) { // [cite: 139]
                cout << a.getNom() << endl; // [cite: 140]
            }
        }
    }

private:
    string nom;
    vector<Exemplaire*> exemplaires; // Vecteur de pointeurs vers des Exemplaire [cite: 122]
};

/*******************************************
 * Ne rien modifier après cette ligne.
 *******************************************/
