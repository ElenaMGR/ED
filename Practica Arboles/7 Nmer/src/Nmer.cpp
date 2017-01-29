#include "Nmer.h"

#include <fstream>

//template<typename T, int K>
//extern void recorrido_preorden(typename ktree<T,K>::const_node n);

Nmer::Nmer() {
  max_long = 0;
  el_Nmer = ktree<pair<char,int>,4>(pair<char,int>('-',0));
}

Nmer::Nmer(const Nmer & a) {
   max_long = a.max_long;
   el_Nmer = a.el_Nmer;
}

bool Nmer::loadSerialized(const string & fichero) {
   string cadena;
   ifstream fe;
   pair<char,int> nulo('x',-1);
   Nmer::String2Base stb;

   fe.open(fichero.c_str(), ifstream::in);
   if (fe.fail()){
      cerr << "Error al abrir el fichero " << fichero << endl;
   }
   else {
      //leo la cabecera del fichero (líneas que comienzan con #)
      do{
         getline(fe,cadena,'\n');
      } while (cadena.find("#")==0 && !fe.eof());
      // leemos Nmer_length
      max_long = std::stoi(cadena);
      // leemos cadena serializada
      getline(fe,cadena,'\n');
      el_Nmer.deserialize(cadena,nulo,';',stb);
      fe.close();
      return true;
   } // else
   fe.close();
   return false;
}

void Nmer::list_Nmer() const {
   // implmenentar el recorrido en preorden para el ktree de forma que nos devuelva los Nmers completos y no
   // sólo el nodo.
   //recorrido_preorden<pair<char,int>,4>(el_Nmer.root());
   string listado = "";
   recorrido_preorden(el_Nmer.root(),listado);
}

unsigned int Nmer::length() const {
   return max_long;
}

Nmer::size_type Nmer::size() const{
   return el_Nmer.size()-1;
}

Nmer & Nmer::operator=(const Nmer & a){
   if (this != &a){
      this->max_long=a.max_long;
      this->el_Nmer=a.el_Nmer;
   }
   return (*this);
}

Nmer Nmer::Prefix(string adn){
   Nmer resultado;
   Nmer subarbol;
   ktree<pair<char,int>,4>::node n(el_Nmer.root());
   ktree<pair<char,int>,4>::node n2(resultado.el_Nmer.root());
   pair<char,int> etiqueta;
   int hijo;

   for(unsigned int i=0; i<adn.size(); i++){
      switch (adn[i]) {
         case 'A': n = n.k_child(0); hijo=0; break;
         case 'G': n = n.k_child(1); hijo=1; break;
         case 'C': n = n.k_child(2); hijo=2; break;
         case 'T': n = n.k_child(3); hijo=3; break;
      }

      etiqueta.first=adn[i];
      etiqueta.second=(*n).second;
      resultado.el_Nmer.insert_k_child(n2,hijo,etiqueta);
      n2 = n2.k_child(hijo);

      if(n.null()){
         i=adn.size();
      }
   }

   if(!n.null()){
      subarbol.el_Nmer.assing(el_Nmer, n);
   }

   resultado.el_Nmer.insert_k_child(n2.parent(),hijo,subarbol.el_Nmer);

   return resultado;
}

Nmer Nmer::Union(const Nmer reference){
   Nmer resultado(*this);
   Nmer referencia(reference);
   resultado.recorridoUnion(referencia, resultado.el_Nmer.root(), referencia.el_Nmer.root());
   return resultado;
}

bool Nmer::containsString(const string adn) const{
   bool esta=false;
   ktree<pair<char,int>,4>::const_node n(el_Nmer.root());

   for(unsigned int i=0; i<adn.size(); i++){
      switch (adn[i]) {
         case 'A': n = n.k_child(0); break;
         case 'G': n = n.k_child(1); break;
         case 'C': n = n.k_child(2); break;
         case 'T': n = n.k_child(3); break;
      }

      if(n.null()){
         i=adn.size();
      }
   }

   if(!n.null()){
      esta=true;
   }

   return esta;
}


bool Nmer::included(const Nmer reference) const{
   return recorridoInclude(el_Nmer.root(), reference.el_Nmer.root());
}


void Nmer::sequenceADN(unsigned int tama, const string & adn){
   //Inicializamos el árbol poniendo la etiqueta (’-’,0) en el nodo raíz
   //Para cada uno de las posiciones, i, de la cadena
   //Obtenemos un substring de tamaño tama que empiece en adn[i];
   //insertar_cadena(subcadena);
}
/*
set<pair<string,int>,OrdenCre > Nmer::rareNmer(int threshold){

}

set<pair<string,int>,ordenDecre > Nmer::commonNmer(int threshold){

}

set<pair<string,int>, ordenCrec > Nmer::level(int l){

}

float Nmer::Distance(const Nmer & x){

}
*/

ostream&   operator<<(ostream & s, const pair<char,int> & par){
  s << par.first << " " << par.second;
  return s;
}


void Nmer::recorrido_preorden (ktree<pair<char,int>,4>::const_node n, string & contenido) const{
   if (!n.null()){
      contenido.push_back((*n).first);
      cout << "( " << contenido <<" "<< (*n).second <<" );"<<endl;
      if (contenido.back()=='-'){
         contenido.pop_back();
      }
      typename ktree<pair<char,int>,4>::const_node::child_iterator ini = n.begin();
      typename ktree<pair<char,int>,4>::const_node::child_iterator fin = n.end();
      while (ini!=fin){
         recorrido_preorden(*ini, contenido);
         ++ini;
      }
      contenido.pop_back();
   }
}

void Nmer::recorridoUnion(Nmer arbol2, ktree<pair<char,int>,4>::node nodoArbol1, ktree<pair<char,int>,4>::node nodoArbol2) {
   Nmer subarbol;
   for(int i=0; i<4; i++){

      if (!nodoArbol2.k_child(i).null()){
         if (!nodoArbol1.k_child(i).null()){
            //Si el nodo hijo i no es nulo en ninguno de los 2 árboles
            (*nodoArbol1.k_child(i)).second += (*nodoArbol2.k_child(i)).second;
            recorridoUnion(arbol2, nodoArbol1.k_child(i), nodoArbol2.k_child(i));
         }
         else {
            //Si el nodo hijo i del segundo árbol no es nulo, pero el del árbol1 si
            //Copio el subarbol del arbol 2 en arbol1
            subarbol.el_Nmer.assing(arbol2.el_Nmer, nodoArbol2.k_child(i));
            el_Nmer.insert_k_child(nodoArbol1,i,subarbol.el_Nmer);
         }
      }
   }
}


bool Nmer::recorridoInclude(ktree<pair<char,int>,4>::const_node nodoThis, ktree<pair<char,int>,4>::const_node nodoRef) const {
   for(int i=0; i<4; i++){
      if (!nodoThis.k_child(i).null()){
         if (!nodoRef.k_child(i).null()){
            return recorridoInclude(nodoThis.k_child(i), nodoRef.k_child(i));
         }
         else {
            return false;
         }
      }
   }
   return true;
}

void Nmer::insertar_cadena(const string & cadena){

}
