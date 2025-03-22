#include <iostream>
#include "lib.h"

using namespace std;

int main()
{

    // CARGAR LISTADO DE PALABRAS
    string filePath;
    cout << "Ruta al listado de palabras: ";
    cin >> filePath;
    vector<string> wordsList = cargar_listado(filePath);

    // ELEGIR PALABRA SECRETA
    srand(time(0));
    string secretWord = wordsList[rand() % wordsList.size()];
    cout << "La palabra secreta es: " << secretWord << endl;
    cout << "La palabra secreta tiene " << secretWord.length() << " letras." << endl;

    // INTENTOS
    int attempts = 5;
    string inputWord;
    cout << "Te quedan " << attempts << " intentos" << endl;
    while (attempts > 0)
    {        
        cin >> inputWord;
        if (intento_valido(inputWord, secretWord, wordsList) == false)
        {
            cout << "Intento inválido. Ingrese una palabra valida." << endl;
            continue;
        }
        if (inputWord == secretWord)
        {
            cout << "¡Correcto!" << endl;
            break;
        }
        string result = respuesta_en_string(evaluar_intento(inputWord, secretWord));
        cout << result << endl;
        cout << "Te quedan " << attempts << " intentos" << endl;
        attempts--;
    }
    if (attempts == 0)
    {
        cout << "Perdiste, no te quedan más intentos. La palabra era: " << secretWord << endl;
    }

    return 0;
}