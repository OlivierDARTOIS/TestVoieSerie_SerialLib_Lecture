// Exemple d'utilisation de la voie série avec serialib
// Ecriture sur un une voie série
// O. Dartois - Janvier 2021

#include <iostream>
#include <string>
#include <thread>

#include "serialib.h"

int main()
{

    // Instanciation d'un objet de la classe serialib
    serialib serial;

    // Nom du port COM à ouvrir
    const std::string portCOM("COM4");

    // Ouverture du port série à la vitesse spécifié
    char erreur = serial.Open(portCOM.c_str(), 115200);

    // Si pb à l'ouverture du port série, on sort avec un message
    if (erreur != 1) {
        std::cout << "Ouverture du port serie KO !" << std::endl;
        return 0;
    }
    
    std::cout << "Ouverture du port serie OK" << std::endl;

    // Réception des caractères sur la voie série
    erreur = 0;
    do {
            char caracRecu;
            // Lecture d'un caractère sur le port série avec un "timeout"  de 2s
            erreur = serial.ReadChar(&caracRecu, 2000);
            // Erreur de réception sur le port série
            if (erreur < 0) {
                std::cout << "Erreur réception" << std::endl;
                break;
            }
            // Réception d'un caractère
            else if (erreur == 1)
                std::cout << caracRecu << std::endl;
            // Fin du temps imparti pour la réception d'un caractère
            else if (erreur == 0)
                std::cout << "Reception timeout" << std::endl;
    } while (erreur != 0);

    // Fermeture du port série
    serial.Close();

    return 0;
}
