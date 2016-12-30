#include "mutacion.h"
#include "enfermedad.h"
#include "conjunto.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <functional>


using namespace std;
using namespace std::chrono;
/**
  * @author Elena María Gómez Ríos
*/

/** @brief clase ComparacionPorIDCreciente la cual compara las mutaciones por el id
 *  de forma alfanmérica (tal y como lo hace el string).
*/
class ComparacionPorIDCreciente {
   public:
      /** @brief compara dos mutaciones por id de forma creciente
   	  * @param[in] a: mutacion a comparar.
        * @param[in] b: mutacion a comparar.
   	  * @return Si el ID de a es menor que el ID de b devuelve true, false en caso contrario
   	  * @post no modifica el conjunto.
   	*/
      bool operator()(const mutacion &a, const mutacion &b) {
         return (a.getID() < b.getID()); // devuelve verdadero si el ID de a precede al ID de b
      }
};

/** @brief clase ComparacionPorIDCreciente la cual compara las mutaciones por el id
 *  de forma alfanmérica (tal y como lo hace el string).
*/
class ComparacionPorIDDecreciente {
   public:
      /** @brief compara dos mutaciones por id de forma decreciente
   	  * @param[in] a: mutacion a comparar.
        * @param[in] b: mutacion a comparar.
   	  * @return Si el ID de a es mayor que el ID de b devuelve true, false en caso contrario
   	  * @post no modifica el conjunto.
   	*/
      bool operator()(const mutacion &a, const mutacion &b) {
         return (a.getID() > b.getID()); // devuelve verdadero si el ID de b precede al ID de a
      }
};

/** @brief lee un fichero de mutaciones, linea a linea
	 @param[in] s nombre del fichero
    @param[in,out] cm objeto tipo conjunto sobre el que se almacenan las mutaciones
	 @return true si la lectura ha sido correcta, false en caso contrario
*/

template <typename T, typename CMP>
bool load(conjunto<T,CMP> &  cm, const string & s) {
   ifstream fe;
   string cadena;

   cout << "Abrimos "<< s << endl;
   fe.open(s.c_str(), ifstream::in);
   if (fe.fail()){
      cerr << "Error al abrir el fichero " << s << endl;
   }
   else {
      //leo la cabecera del fichero (líneas que comienzan con #)
      do{
         getline(fe,cadena,'\n');
      }while (cadena.find("#")==0 && !fe.eof());

      //leo la tabla de mutaciones, una línea cada vez
      while ( !fe.eof() ){
         //cout << "leo:: "<< cadena << endl;
         // Invoco el constructor de mutación que recibe una cadena completa, la parsea y crea la mutación.
         mutacion mut(cadena);
         // Insertar mutación en el conjunto
         cm.insert(mut);

         getline(fe,cadena,'\n');
      }
      fe.close();
      return true;
   } // else
   fe.close();
   return false;
}



int main(int argc, char *argv[]){

   //Conjunto de mutacion creciente por cromosoma/posicion
   conjunto<mutacion, less<mutacion> > conjuntoMutacionesCreciente;
   string query_str;

   //Cargar las mutaciones en vectorSNPs
   //load(conjuntoMutaciones, "./data/prueba1.vcf");
   load(conjuntoMutacionesCreciente, "./data/clinvar_20160831.vcf");

   //Imprimir número de elementos almacenados en conjuntoMutaciones
   cout << "Lectura del fichero finalizada. Mutaciones cargadas: "<<conjuntoMutacionesCreciente.size()<<endl;

   //Imprimir las mutaciones en orden creciente por cromosoma/posicion
   cout<<"Mutaciones en orden creciente por cromosoma/posición"<<endl;
   cout<<conjuntoMutacionesCreciente<<endl;

   //Conjunto de mutacion decreciente por cromosoma/posicion
   //Mezclo las mutaciones primero para que tarde menos al insertar
   random_shuffle(conjuntoMutacionesCreciente.begin(),conjuntoMutacionesCreciente.end());

   conjunto<mutacion, greater<mutacion> > conjuntoMutacionesDecreciente;
   conjunto<mutacion, less<mutacion> >:: iterator it =  conjuntoMutacionesCreciente.begin();
   while (it != conjuntoMutacionesCreciente.end()){
      conjuntoMutacionesDecreciente.insert(*it);
      it++;
   }

   //Imprimir las mutaciones en orden decreciente por cromosoma/posicion
   cout<<"Mutaciones en orden decreciente por cromosoma/posición"<<endl;
   cout<<conjuntoMutacionesDecreciente<<endl;

   //Conjunto de enfermedad por orden creciente
   conjunto<enfermedad, less<enfermedad> > conjuntoEnfermedadesCreciente;
   /*conjunto<mutacion, less<mutacion> >:: iterator*/ it =  conjuntoMutacionesCreciente.begin();
   vector<enfermedad> enf;
   while (it != conjuntoMutacionesCreciente.end()){

      enf = ((*it).getEnfermedades());
      for (int i = 0; i< enf.size(); i++){
         conjuntoEnfermedadesCreciente.insert(enf[i]);
      }
      it++;
   }

   //Imprimir las enfermedades en orden creciente por nombre
   cout<<"Enfermedades en orden creciente por nombre"<<endl;
   cout<<conjuntoEnfermedadesCreciente<<endl;

   //Conjunto de enfermedad por orden decreciente
   conjunto<enfermedad, greater<enfermedad> > conjuntoEnfermedadesDecreciente;
   /*conjunto<mutacion, less<mutacion> >:: iterator*/ it =  conjuntoMutacionesDecreciente.begin();
   /*vector<enfermedad> enf;*/
   enf.clear();
   while (it != conjuntoMutacionesCreciente.end()){

      enf = ((*it).getEnfermedades());
      for (int i = 0; i< enf.size(); i++){
         conjuntoEnfermedadesCreciente.insert(enf[i]);
      }
      it++;
   }

   //Imprimir las enfermedades en orden decreciente por nombre
   cout<<"Enfermedades en orden decreciente por nombre"<<endl;
   cout<<conjuntoEnfermedadesDecreciente<<endl;

   //Conjunto de mutacion creciente por id
   conjunto<mutacion, ComparacionPorIDCreciente > conjuntoMutacionesCrecienteID;
   /*conjunto<mutacion, less<mutacion> >:: iterator*/ it =  conjuntoMutacionesCreciente.begin();
   while (it != conjuntoMutacionesCreciente.end()){
      conjuntoMutacionesCrecienteID.insert(*it);
      it++;
   }

   //Imprimir las mutaciones en orden decreciente por cromosoma/posicion
   cout<<"Mutaciones en orden creciente por id"<<endl;
   cout<<conjuntoMutacionesCrecienteID<<endl;


   //Conjunto de mutacion decreciente por id
   conjunto<mutacion, ComparacionPorIDDecreciente > conjuntoMutacionesDecrecienteID;
   /*conjunto<mutacion, less<mutacion> >:: iterator*/ it =  conjuntoMutacionesCreciente.begin();
   while (it != conjuntoMutacionesCreciente.end()){
      conjuntoMutacionesDecrecienteID.insert(*it);
      it++;
   }

   //Imprimir las mutaciones en orden decreciente por cromosoma/posicion
   cout<<"Mutaciones en orden decreciente por id"<<endl;
   cout<<conjuntoMutacionesDecrecienteID<<endl;

   return 0;
}
