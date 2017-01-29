/**
 * @file Nmer.h
 * @brief TDA Nmer
 *   Representa un conjunto de Nmer subsecuencias de tamaño 1 hasta N que se pueden obtener a partir de una cadena
 *   de ADN
 * @author Elena María Gómez Ríos
 */

#ifndef __NMER_H
#define __NMER_H

#include "ktree.h"
#include <set>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;
/** @brief clase OrdenCre la ordena en orden creciente por la frecuencia
*/
class OrdenCre {
  public:
     /** @brief compara dos subcadenas por la frecuencia de forma creciente
       * @param[in] n: pair a comparar.
       * @param[in] n2: pair a comparar.
       * @return true si n tiene menor frecuencia que n2
       * @post no modifica el conjunto.
      */
      bool operator()(const pair<string,int> & n ,const pair<string,int> & n2) {
          return (n.second <= n2.second);
      }
};
/** @brief clase OrdenDecre la ordena en orden creciente por la frecuencia
*/
class OrdenDecre {
  public:
     /** @brief compara dos subcadenas por la frecuencia de forma decreciente
       * @param[in] n: pair a comparar.
       * @param[in] n2: pair a comparar.
       * @return true si n tiene mayor frecuencia que n2
       * @post no modifica el conjunto.
      */
      bool operator()(const pair<string,int> & n ,const pair<string,int> & n2) {
          return (n.second >= n2.second);
      }
};

class Nmer {
   public:
     typedef unsigned int size_type;

     /** @brief Constructor primitivo .
         Crea un Nmer de longitud maxima 0, con el valor ('-',0) en la raíz
     */
     Nmer();

     /** @brief Constructor .
         Crea un Nmer igual al Nmer pasado
     */
     Nmer(const Nmer & a);

     /** @brief lectura fichero serializado
      * @param nombre_fichero fichero serializado con extension .srl
      *
      * Genera a partir del fichero el ktree que contiene todos los kmers asociados a una cadena de ADN
      *
      * La cadena original viene descrita en el fichero serializado
      */
     bool loadSerialized(const string & nombre_fichero);

     /** @brief lectura fichero
      * @param nombre_fichero fichero con extension .txt
      *
      * Genera a partir del fichero el ktree que contiene todos los kmers asociados a una cadena de ADN
      *
      * La cadena original viene descrita en el fichero
      */
     bool loadFichero(const string & nombre_fichero);


     /** @brief Imprime los Nmers
      * @todo Debemos de implementar este método de forma que nos garantizemos que se imprimen todos los Nmers.
      */
      void list_Nmer() const;


     /** @brief Máxima longitud de los Nmers almacenados
      */
      unsigned int length()const;


     /** @brief Número de Nmers almacenados
      */
      size_type size() const;

      /** @brief operador de asignacion
      */
      Nmer & operator=(const Nmer & a);

      /** @brief Devuelve el Nmer (subarbol) asociado a un prefijo. Por ejemplo, si adn es
        * "ACT", devuelve el Nmer que representa todas las subcadenas que empiezan por "ACT" (ACT*)
      */
      Nmer Prefix(string adn);

      /** @brief Se devuelve un Nmer donde para cada nodo (representa una
        * secuencia) se computa la suma de las frecuencias en *this y en referencia
      */
      Nmer Union(const Nmer reference);

      /** @brief Devuelve true si la cadena adn está representada en el árbol.
      */
      bool containsString(const string adn) const;

      /** @brief Devuelve true si cada nodo de *this está también representado en reference, es decir,
        * si todas las secuencias representadas en el árbol de *this están también incluidas en reference.
        * False en otro caso.
      */
      bool included(const Nmer reference) const;

      /** @brief Construir Nme a partir de cadena de ADN
      */
      void sequenceADN(unsigned int tama, const string & adn);

      /** @brief devuelve la lista de todas las subcadenas (no prefijo) que aparecen menos de threshold
        * veces en el Nmer ordenadas en orden creciente de frecuencia
        */
      set<pair<string,int>,OrdenCre > rareNmer(int threshold);

      /** @brief Devuelve la lista de las cadenas de longitud mayor posible (no prefijo) que aparecen más
        * de threshold veces en el Nmer, ordenadas en orden decreciente de frecuencia
      */
      set<pair<string,int>,OrdenDecre > commonNmer(int threshold);

      /** @brief Devuelve el conjunto de Nmers de longitud exacta l.
      */
      set<pair<string,int>, OrdenCre > level(int l);

      /** @brief Distancia entre dos Nmer
      */
      float Distance(const Nmer & x);

      /** @brief Recorrido en preorden del arbol, mostrando el Nmer
      */
      void recorrido_preorden (ktree<pair<char,int>,4>::const_node n, string & contenido) const;

      /** @brief Recorre dos árboles y hace la unión de ambos
      */
      void recorridoUnion(Nmer arbol2, ktree<pair<char,int>,4>::node nodoArbol1, ktree<pair<char,int>,4>::node nodoArbol2);

      bool recorridoInclude(ktree<pair<char,int>,4>::const_node nodoThis, ktree<pair<char,int>,4>::const_node nodoRef) const;

      void recorridoRareNmer(ktree<pair<char,int>,4>::const_node nodo, int threshold,set<pair<string,int>,OrdenCre> &resultado, string & subcadena);

      void recorridoCommonNmer(ktree<pair<char,int>,4>::const_node nodo, int threshold,set<pair<string,int>,OrdenDecre> &resultado, string & subcadena);

      void recorridoLevel(ktree<pair<char,int>,4>::const_node nodo, int level,set<pair<string,int>,OrdenCre> &resultado, string & subcadena);
   private:
     ktree<pair<char,int>,4> el_Nmer; // subsecuencias
     unsigned int max_long; // Mayor longitud de la cadena representada, esto es, el nivel máximo del árbol

     /** @brief Inserta la cadena en el arbol
     */
     void insertar_cadena(const string & cadena);

     /** @brief Functor para convertir un string en un pair<char,int>
      * se utiliza en loadSerialized
      */
     class String2Base {
      public:
       pair<char,int> operator()( const string & cad) {
   	    pair<char,int> salida;
   	    salida.first = cad[0];
   	    salida.second = std::stoi(cad.substr(1));
   	    return salida;
       }
     };

      /** @brief Functor para convertir un pair<char,int> en un string
       * Necesario para serializar un Nmer.
      */
     class Base2String {
      public:
        string operator()( const pair<char,int> & x) {
          string salida = string(1,x.first) + " " +std::to_string(x.second);
          return salida;
        }
     };

};

ostream& operator<<(ostream & s, const pair<char,int> & par);

#endif
