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
   Nmer salida;
   ktree<pair<char,int>,4>::node n(el_Nmer.root());
   for(unsigned int i=0; i<adn.size(); i++){
      if(adn[i]=='A'){
         n=n.k_child(0);
      }
      if(adn[i]=='G'){
         n=n.k_child(1);
      }
      if(adn[i]=='C'){
         n=n.k_child(2);
      }
      if(adn[i]=='T'){
         n=n.k_child(3);
      }
      if(n.null()){
         i=adn.size();
      }
   }

   if(!n.null()){
      salida.el_Nmer.assing(el_Nmer, n);
   }

   return (salida);
}

/*
void Nmer::sequenceADN(unsigned int tama, const string & adn){

}

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
