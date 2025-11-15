#include <iostream>
#include <string>
#include <cmath> // Pour std::round ou autres si besoin, mais math simple suffit

using namespace std;

/*******************************************
 * Complétez le programme à partir d'ici.
 *******************************************/

class Souris
{
public:
    // Constructeurs (poids, couleur, age=0, esperance_vie=36)
    Souris(double p, string c, int a = 0, int ev = 36)
        : poids(p), couleur(c), age(a), esperance_vie(ev), clonee(false)
    {
        cout << "Une nouvelle souris !" << endl; //
    }

    // Constructeur de copie
    Souris(const Souris& autre)
        : poids(autre.poids), couleur(autre.couleur), age(autre.age), clonee(true)
    {
        // La nouvelle esperance de vie est les 4/5 de l'originale
        esperance_vie = (int)round(autre.esperance_vie * 4.0 / 5.0);
        
        cout << "Clonage d'une souris !" << endl; //
    }

    // Destructeur
    ~Souris()
    {
        cout << "Fin d'une souris..." << endl; //
    }

    // Méthode d'affichage
    void afficher() const
    {
        cout << "Une souris " << couleur;
        
        // Afficher ", clonee," uniquement si clonee est vrai
        if (clonee) {
            cout << ", clonee,";
        }
        
        cout << " de " << age << " mois et pesant " << poids << " grammes" << endl; //
    }

    // Méthode vieillir
    void vieillir()
    {
        age += 1; //
        
        // Si clonée et age > (esperance_vie / 2), devient verte
        if (clonee && (age > esperance_vie / 2)) {
            couleur = "verte";
        }
    }

    // Méthode evolue
    void evolue()
    {
        while (age < esperance_vie) {
            vieillir();
        }
    }

private:
    double poids;
    string couleur;
    int age;
    int esperance_vie;
    bool clonee;
};

/*******************************************
 * Ne rien modifier après cette ligne.
 *******************************************/
