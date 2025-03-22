#ifndef LIB_H
#define LIB_H

#include<vector>
#include<string>

/**
 * Define los posibles resultados de cada letra de un intento legal.
 * Ver documentación de `evaluar_intento` para más detalles.
 */
enum class EstadoLetra { LugarCorrecto, LugarIncorrecto, NoPresente };

/**
 * Toma el nombre de un archivo que contiene una palabra por línea y devuelve un
 * vector de strings con todas las palabras tal como están en el archivo.
 */
std::vector<std::string> cargar_listado(const std::string & nombre_archivo);

/**
 * Toma un intento, una palabra secreta y un listado de palabras e indica si el
 * intento es legal o no. Un intento es legal si tiene la misma longitud que la
 * palabra secreta y si es una palabra reconocida en el listado de palabras.
 */
bool intento_valido(const std::string &  intento, const std::string &  palabra_secreta, const std::vector<std::string> &listado);

/**
 * Toma un intento y una palabra secreta, y devuelve un vector con la respuesta
 * para cada una de las letras del intento.
 *
 * Una letra del intento puede estar en...
 *   - LugarCorrecto, si la palabra secreta tiene esa misma letra en esa posición
 *   - LugarIncorrecto, si la palabra secreta contiene esa letra pero en otra posición
 *   - NoPresente, si la palabra secreta no contiene esa letra.
 */
std::vector<EstadoLetra> evaluar_intento(const std::string &  intento, const std::string &  palabra_secreta);

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
std::string respuesta_en_string(const std::vector<EstadoLetra> & respuesta);

#endif
