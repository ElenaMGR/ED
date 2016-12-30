/*
 * clinvar.h
 *
*/
#ifndef __CLINVAR_H
#define __CLINVAR_H

#include <string>
#include <iostream>
#include <algorithm>
#include <set>
#include <map>
#include <unordered_map>
#include <list>
#include "enfermedad.h"
#include "mutacion.h"
#include <fstream>
#include <queue>
#include <unordered_set>

using namespace std;

/** @brief clase ProbMutaciones la cual determinará cuando una mutación es
   * mas probable que otra
   * @author Elena María Gómez Ríos
*/
class ProbMutaciones {
   public:
      /** @brief compara dos mutaciones por id de forma creciente
   	  * @param[in] a: mutacion a comparar.
        * @param[in] b: mutacion a comparar.
   	  * @return true si a tiene mayor probabilidad que b
   	  * @post no modifica el conjunto.
   	*/
      bool operator()(const Mutacion &a, const Mutacion &b) {
            return (1-a.getCaf()[0] >= 1-b.getCaf()[0]);
      }
};

/** @brief clase Clinvar
  * ! Clinvar::load, Clinvar::insert, Clinvar::erase, Clinvar::find_Mut, Clinvar::find_Enf, Clinvar::getEnfermedades,
  * Clinvar::getMutacionesEnf, Clinvar::getMutacionesGen, Clinvar::topKMutaciones, Clinvar::begin, Clinvar::end,
  * Clinvar::lower_bound, Clinvar::upper_bound, Clinvar::ebegin, Clinvar::eend, Clinvar::gbegin, Clinvar::gend
* @author Elena María Gómez Ríos
*/
class Clinvar{
   public:
      //los siguientes typedef permiten identificar en las cabeceras de los métodos
      //cuando un string se refiere a un ID de gen, mutacion o enfermedad, respectivamente.
      typedef string IDgen;
      typedef string IDmut;
      typedef string IDenf;

//******************************** Class Iterator ***********************************************//

      /* @brief iterador sobre mutaciones en orden creciente de cromosoma/posicion
      */
      class iterator {
         private:
            friend class Clinvar;
            set<Mutacion>::iterator it;
         public:
            const Mutacion & operator*();   //const - no se puede modificar la mutacion y alterar el orden del set
            iterator & operator++();
            iterator operator++(int);
            iterator & operator--();
            iterator operator--(int);
            bool operator==(const iterator & itc);
            bool operator!=(const iterator & itc);
            iterator & operator=(const iterator & itc);
      };

      /* @brief iterador sobre enfermedades
      */
      // Nos vale utilizar el iterador del map
      typedef map<IDenf, Enfermedad>::iterator enfermedad_iterator;

      /* @brief iterador sobre mutaciones considerando el orden creciente del ID del gen
      */
      class gen_iterator {
         private:
            friend class Clinvar;
            map<IDgen, list< set<Mutacion>::iterator> >::iterator itmap;
            list<set<Mutacion>::iterator>::iterator itlist;
            Clinvar *ptrclinvar;
         public:
            const Mutacion & operator*();   //const - no se puede modificar la mutacion y alterar el orden del set
            gen_iterator & operator++();
            gen_iterator operator++(int);
            gen_iterator & operator--();
            gen_iterator operator--(int);
            bool operator==(const gen_iterator & itc);
            bool operator!=(const gen_iterator & itc);
            gen_iterator & operator=(const gen_iterator & itc);

      };

//********************************Fin Class Iterator ***********************************************//


      /** @brief Se encarga de leer los elementos de un fichero dado por el argumento nombreDB, e insertar toda la información
       *  en ClinVar.
       *  @param[in] nombreDB nombre del fichero de la DB
       */
      void load (string nombreDB);

      /** @brief Este método se encarga de insertar una nueva mutación en ClinVar. Esto implica actualizar todas las estructuras
       *  necesarias para mantener la coherencia interna de la representación propuesta.
       *  @param[in] x mutación a insertar en ClinVar
       */
      void insert (const Mutacion & x);

      /** @brief borrar una mutación de la base de datos dado su ID. No sólo borra la mutación del repositorio principal de
       *  datos sino que además se encarga de borrar toda referencia a dicho elemento dentro de él. En el caso de que una
       *  enfermedad estuviese asociada únicamente a la mutación que está siendo eliminada, esta enfermedada también debe
       *  eliminarse de ClinVar.
       *  @param[in] ID ID de la mutación a borrar
       *  @return Devuelve verdadero si el elemento ha sido borrado correctamente, falso en caso contrario.
       */
      bool erase (IDmut ID);

      /** @brief Busca la mutación con identificador ID dentro de ClinVar.
       *  @param[in] ID ID de la mutación a buscar
       *  @return iterador de la posición donde se encuentra la mutación, si no lo encuentra devuelve end()
       */
      iterator find_Mut (IDmut ID);

      /** @brief Busca la enfermedad con identificador ID dentro de ClinVar.
       *  @param[in] ID ID de la enfermedad a buscar.
       *  @return iterador de la posición donde se encuentra la enfermedad, si no lo encuentra devuelve eend()
       */
      enfermedad_iterator find_Enf(IDenf ID);

      /** @brief Devuelve un vector con todas las enfermedades asociadas a una mutación en la base de datos clinvar.
       *  @param[in] mut mutación sobre la que buscar las enfermedades.
       *  @return vector con todas las enfermedades asociadas a la mutación mut
       */
      vector<Enfermedad> getEnfermedades(Mutacion & mut);

      /** @brief Devuelve una lista de los identificadores de enfermedad que contienen la palabra keyword como parte del nombre
       *  de la enfermedad. Utilizar enfermedad.nameContains() para programar este método
       *  @param[in] keyword palabra a buscar como parte de nombre de las enfermedades
       *  @return lista de identificadores de enfermedad que contienen la palabra keyword
       */
      list<IDenf> getEnfermedades(string keyword);

      /** @brief Devuelve un conjunto ordenado (en orden creciente de IDmut) de todas las mutaciones que se encuentran aso-
       *  ciadas a la enfermedad con identificador ID. Si no tuviese ninguna enfermedad asociada, devuelve el conjunto
       *  vacío.
       *  @param[in] ID Identificador de la enfermedad.
       *  @return devuelve el conjunto de identificadores ordenados de mutación asociados a la enfermedad.
       */
      set<IDmut> getMutacionesEnf (IDenf ID);

      /** @brief Devuelve un conjunto ordenado (en orden creciente de IDmut) de todas las mutaciones que se encuentran aso-
       *  ciadas a los genes con identificador ID. Si no tuviese ninguna enfermedad asociada, devuelve el conjunto
       *  vacío.
       *  @param[in] ID Identificador del gen.
       *  @return devuelve el conjunto de identificadores ordenados de mutación asociados al gen.
       */
      set<IDmut> getMutacionesGen (IDgen ID);


      /** @brief Dado un string 'keyword', el sistema recupera todas las enfermedades cuyo nombre contiene keyword, y
       *  devuelve un set ordenado de mutaciones, en orden decreciente de probabilidad, con las k mutaciones más frecuentes
       *  en la población asociadas con esas enfermedades.
       *  @param[in] k número de mutaciones que queremos conseguir.
       *  @param[in] keyword palabra que queremos buscar.
       *  @return devuelve un set ordenado de mutaciones, en orden decreciente de probabilidad, con las k mutaciones
       *  más frecuentes en la población asociadas con esas enfermedades
      */
      set<Mutacion,ProbMutaciones> topKMutaciones (int k, string keyword);

      /* Métodos relacionados con los iteradores */
      /** @brief Devuelve el iterador correspondiente a la primera mutación según el criterio de ordenación de
        * cada tipo de elemento.
        * @return iterator correspondiente a la primera mutación
      */
      iterator begin();

      /** @brief Devuelve el iterador que apunta al elemento siguiente al último elemento de mutación
        * @return Devuelve el iterador que apunta al elemento siguiente al último elemento de mutación
      */
      iterator end();

      /** @brief Método que permiten hacer la búsqueda por rango considerando el par de valores cromosoma/posición.
        * @param[in] posicion parámetro por el que se compara la mutación
        * @param[in] cromosoma parámetro por el que se compara la mutación
        * @return devuelve el iterador que apunta a la primera mutación que es mayor o igual a los parámetros dados
        * en la entrada
      */
      iterator lower_bound(string cromosoma, unsigned int posicion);

      /** @brief Método que permiten hacer la búsqueda por rango considerando el par de valores cromosoma/posición.
        * @param[in] posicion parámetro por el que se compara la mutación
        * @param[in] cromosoma parámetro por el que se compara la mutación
        * @return devuelve el iterador que apunta a la primera mutación que es estrictamente mayor a los parámetros dados
        * en la entrada
      */
      iterator upper_bound(string cromosoma, unsigned int posicion);

      /** @brief Devuelve el iterador correspondiente a la primera enfermedad según el criterio de ordenación de
        * cada tipo de elemento.
        * @return iterator correspondiente a la primera enfermedad
      */
      enfermedad_iterator ebegin();

      /** @brief Devuelve el iterador que apunta al elemento siguiente al último elemento de enfermedad
        * @return Devuelve el iterador que apunta al elemento siguiente al último elemento de enfermedad
      */
      enfermedad_iterator eend();

      /** @brief Devuelve el iterador correspondiente a la primera gen según el criterio de ordenación de
        * cada tipo de elemento.
        * @return iterator correspondiente al primer gen
      */
      gen_iterator gbegin();

      /** @brief Devuelve el iterador que apunta al elemento siguiente al último elemento de gen
        * @return Devuelve el iterador que apunta al elemento siguiente al último elemento de gen
      */
      gen_iterator gend();

   private:
      friend class iterator;
      friend class gen_iterator;

      /** Base de datos que contiene toda la información asociada a una mutacion
      */
      set<Mutacion> mutDB;

      /** Asocia IDmutacion con mutación
      */
      unordered_map<IDmut,set<Mutacion>::iterator> IDm_map;

      /** Asocia genes con mutaciones
      */
      map<IDgen, list< set<Mutacion>::iterator> > gen_map;

      /** Base de datos de enfermedades
      */
      map<IDenf,Enfermedad> EnfDB;

      /** Asocia enfermedad con mutaciones
      */
      multimap<IDenf,set<Mutacion>::iterator> IDenf_map;

};


#endif
