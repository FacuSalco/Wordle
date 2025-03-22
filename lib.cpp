#include "lib.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

vector<string> cargar_listado(const string &nombre_archivo)
{
    vector<string> listado;
    ifstream inputFile(nombre_archivo);

    if (!inputFile.good())
    {
        cout << "No se pudo abrir el archivo " << nombre_archivo << endl;
        exit(EXIT_FAILURE);
    }
    string line;
    while (getline(inputFile, line))
    {
        listado.push_back(line);
    }
    inputFile.close();

    if (listado.empty())
    {
        cout << "El archivo " << nombre_archivo << " está vacío." << endl;
        exit(EXIT_FAILURE);
    }

    return listado;
}

/**
 * Toma un intento, una palabra secreta y un listado de palabras e indica si el
 * intento es legal o no. Un intento es legal si tiene la misma longitud que la
 * palabra secreta y si es una palabra reconocida en el listado de palabras.
 */

bool intento_valido(const string &intento, const string &palabra_secreta, const vector<string> &listado)
{
    bool sameLength = intento.size() == palabra_secreta.size();

    bool isValidWord = false;
    for (const string &word : listado)
    {
        if (word == intento)
        {
            isValidWord = true;
            break;
        }
    }

    if (sameLength && isValidWord)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/**
 * Toma un intento y una palabra secreta, y devuelve un vector con la respuesta
 * para cada una de las letras del intento.
 *
 * Una letra del intento puede estar en...
 *   - LugarCorrecto, si la palabra secreta tiene esa misma letra en esa posición
 *   - LugarIncorrecto, si la palabra secreta contiene esa letra pero en otra posición
 *   - NoPresente, si la palabra secreta no contiene esa letra.
 */

vector<EstadoLetra> evaluar_intento(const string &intento, const string &palabra_secreta)
{
    vector<EstadoLetra> feedback = {};
    int i = 0;
    while (i < intento.size())
    {
        if (intento[i] == palabra_secreta[i])
        {
            feedback.push_back(EstadoLetra::LugarCorrecto);
            i++;
            continue;
        }
        else
        {
            int j = 0;
            bool found = false;
            while (j < intento.size())
            {
                if (intento[i] == palabra_secreta[j])
                {
                    feedback.push_back(EstadoLetra::LugarIncorrecto);
                    found = true;
                    break;
                }
                j++;
            }
            if (!found)
            {
                feedback.push_back(EstadoLetra::NoPresente);
            }
        }
        i++;
    }
    cout << endl;
    return feedback;
}

/**
 * Toma el resultado de *evaluar_intento* y devuelve un string que se puede
 * imprimir por pantalla para indicar esa respuesta al usuario.
 *
 * Formato esperado:
 *   - LugarCorrecto se muestra con el caracter "+"
 *   - LugarIncorrecto se muestra con el caracter "-"
 *   - NoPresente se muestra con el caracter "X".

 * Por ejemplo, si el vector en entrada es el siguiente...
 *   {LugarIncorrecto, NoPresente, NoPresente, LugarCorrecto, LugarIncorrecto}

 * ... se espera que el string de salida sea "-XX+ -".
 * */

string respuesta_en_string(const vector<EstadoLetra> &respuesta)
{
    string answer = "";
    int i = 0;
    while (i < respuesta.size())
    {
        if (respuesta[i] == EstadoLetra::LugarCorrecto)
        {
            answer.append("+");
        }
        else if (respuesta[i] == EstadoLetra::LugarIncorrecto)
        {
            answer.append("-");
        }
        else if (respuesta[i] == EstadoLetra::NoPresente)
        {
            answer.append("X");
        }

        i++;
    }

    return answer;
}
