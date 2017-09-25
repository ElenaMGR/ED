/*
 * mutacion.h
 *
 * Copyright  (C) Juan F. Huete y Carlos Cano
*/
#ifndef __MUTACION_H
#define __MUTACION_H

#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include "enfermedad.h"
//! Clase mutacion, asociada a la definición de una mutación/SNP
/*! mutacion::mutacion, mutacion::setID, mutacion::setChr, mutacion::setPos, mutacion::setRef_alt, mutacion::setGenes,
 * mutacion::setCommon, mutacion::setCaf, mutacion::setEnfermedades, mutacion::setClnsig, mutacion::getID,
 * mutacion::getChr, mutacion::getPos, mutacion::getRef_alt, mutacion::getGenes, mutacion::getCommon,
 * mutacion::getCaf, mutacion::getEnfermedades, mutacion::getClnsig, mutacion::operator=, mutacion::operator==,
 * mutacion::operator<
 * \n Descripción: contiene toda la información asociada a una mutación almacenada en la BD ClinVar-dbSNP
 *
 * @author Elena María Gómez Ríos
*/


class mutacion {
   private:
      // Función de abstracción: FA(m) = m es una mutación concreta ID, chr, pos, ref_alt, genes, common, caf, enfermedades,
      // clnsig
      // Invariante de Representación: IR(m) = (m.pos > 0)
      /** Identificador del SNP/mutación
      */
      string ID;
      /** Identificador del cromosoma
      */
      string chr;
      /** Identificador de la posición dentro del cromosoma
      */
      unsigned int pos;
      /** Base(s) en el genoma de referencia y alternativa(s) posible(s).
       * La primera posición la ocupará el string con la(s) base(s) del genoma de referencia, y, a continuación,
       * aparecerán la(s) base(s) alternativas en el mismo orden que se indica en el fichero
      */
      vector<string> ref_alt;
      /** Gen(es) asociado(s) al SNP
      */
      vector<string> genes;
      /** Indica si el SNP es común en la población
      */
      bool common;
      /** Frecuencia de cada base del SNP en la población.
       * En primer lugar debe indicarse la frecuencia de la base 'ref' (posición 0 de ref-alt), seguida por las
       * frecuencias de las bases alternativas indicadas en 'ref-alt', en el mismo orden.
      */
      vector<float> caf;
      /** Enfermedades asociadas al SNP
      */
      vector<enfermedad> enfermedades;
      /** Relevancia clínica del SNP para cada enfermedad utilizando el código numérico del campo CLNSIG.
       * En caso de que existan varias enfermedades asociadas a la mutación, cada una de ellas puede presentar
       * diferente código CLNSIG, por lo que se deben almacenar en el vector clnsig en el mismo orden que las enfermedades
       * asociadas. En caso de presentarse sólo un código CLNSIG y varias enfermedades, este código se aplica a todas ellas.
      */
      vector<int> clnsig;

   public:
      //Constructores
      /**@brief Constructor de enfermedad por defecto.
   	*/
      mutacion();

      /**@brief Constructor de copia de la clase.
   		@param[in] m mutacion a copiar
   	*/
      mutacion(const mutacion& m);

      /**@brief Constructor parametrizado de la clase.
   		@param[in] str cadena que contiene todos los atributos de la clase
   	*/
      mutacion(const string & str); //para crear objeto mutacion a partir de la cadena que contiene una línea completa
                                    //del fichero de entrada

      // Modificadores
      /** @brief Establece el identificador del SNP/mutación.
   		 @param[in] id nombre de el identificador del SNP/mutación.
   	*/
      void setID(const string & id);
      /** @brief Establece el identificador del cromosoma.
   		 @param[in] chr nombre de el identificador del cromosoma.
   	*/
      void setChr(const string & chr);
      /** @brief Establece el identificador de la posición dentro del cromosoma.
          @param[in] pos nombre de el identificador de la posición dentro del cromosoma.
      */
      void setPos(const unsigned int & pos);
      /** @brief Establece la(s) base(s) en el genoma de referencia y alternativa(s) posible(s).
          @param[in] ref_alt base(s) en el genoma de referencia y alternativa(s) posible(s).
      */
      void setRef_alt(const std::vector<string> & ref_alt);
      /** @brief Establece los gen(es) asociado(s) al SNP.
          @param[in] genes gen(es) asociado(s) al SNP.
      */
      void setGenes (const std::vector<string> & genes);
      /** @brief Establece el indicador de si el SNP es común en la población.
          @param[in] common indicador de si el SNP es común en la población.
      */
      void setCommon (const bool & common);
      /** @brief Establece la frecuencia de cada base del SNP en la población.
          @param[in] caf frecuencia de cada base del SNP en la población.
      */
      void setCaf (const std::vector<float> & caf);
      /** @brief Establece las enfermedades asociadas al SNP.
          @param[in] enfermedades enfermedades asociadas al SNP.
      */
      void setEnfermedades (const std::vector<enfermedad> & enfermedades);
      /** @brief Establece la relevancia clínica del SNP para cada enfermedad.
          @param[in] clnsig relevancia clínica del SNP para cada enfermedad.
      */
      void setClnsig (const std::vector<int> & clnsig);

      // Consultores
      /** @brief Obtiene el identificador del SNP/mutación.
   		 @return identificador del SNP/mutación.
   	*/
      string getID( ) const;
      /** @brief Obtiene identificador del cromosoma.
   		 @return identificador del cromosoma.
   	*/
      string getChr( ) const;
      /** @brief Obtiene el identificador de la posición dentro del cromosoma.
   		 @return identificador de la posición dentro del cromosoma.
   	*/
      unsigned int getPos( ) const;
      /** @brief Obtiene la(s) base(s) en el genoma de referencia y alternativa(s) posible(s).
   		 @return la(s) base(s) en el genoma de referencia y alternativa(s) posible(s).
   	*/
      const vector<string> & getRef_alt () const;
      /** @brief Obtiene los gen(es) asociado(s) al SNP.
   		 @return los gen(es) asociado(s) al SNP.
   	*/
      const vector<string> & getGenes () const;
      /** @brief Obtiene el indicador de si el SNP es común en la población.
   		 @return el indicador de si el SNP es común en la población.
   	*/
      bool getCommon () const;
      /** @brief Obtiene la frecuencia de cada base del SNP en la población.
   		 @return la frecuencia de cada base del SNP en la población.
   	*/
      const vector<float> & getCaf () const;
      /** @brief Obtiene las enfermedades asociadas al SNP.
   		 @return las enfermedades asociadas al SNP.
   	*/
      const vector<enfermedad> & getEnfermedades () const;
      /** @brief Obtiene la relevancia clínica del SNP para cada enfermedad.
   		 @return la relevancia clínica del SNP para cada enfermedad.
   	*/
      const vector<int> & getClnsig () const;


      /** @brief operador de asignación
   		 @param[in] m mutación a copiar.
          @return copia de la mutación.
   	*/
      mutacion & operator=(const mutacion & m);
      /** @brief Compara si son iguales dos mutaciones.
          @param[in] m mutación a comparar.
          @return Devuelve true si son iguales y false si no lo son.
      */
      bool operator==(const mutacion & m) const;
      /** @brief Compara si una mutacion es mayor que otra, comparando por por Chr y pos.
   		 @param[in] e enfermedad a comparar.
   		 @return Devuelve true si e es mayor que el que lo llama. False en otro caso.
   	*/
      bool operator<(const mutacion & m) const;      //El orden viene determinado por Chr y pos.
                                                   //El primer criterio es el número de cromosoma. El orden para el
                                                   //número de cromosoma se rige por "1"<"2"<"3"<...<"22"<"X"<"Y"<"MT".
                                                   //Dos mutaciones del mismo cromosoma deben ordenarse según su posición,
                                                   //de menor posición a mayor (orden natural de enteros).

};

/** @brief Imprime mutación con todos sus campos.
    @param[in] os flujo.
    @param[in] m mutación a mostrar.
    @return La mutación por salida estandar.
*/
ostream& operator<< ( ostream& os , const mutacion& m);   //Imprimir TODOS los campos del objeto mutación.


#include "mutacion.hxx"
#endif
