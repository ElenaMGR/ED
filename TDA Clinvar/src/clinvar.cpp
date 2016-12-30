/** @brief fichero de implementacion de la clase clinvar
*/

#include "clinvar.h"

//******************************** Class Iterator ***********************************************//
const Mutacion & Clinvar::iterator::operator*(){
   return *it;
}

Clinvar::iterator & Clinvar::iterator::operator++(){
   ++it;
   return (*this);
}

Clinvar::iterator Clinvar::iterator::operator++(int){
   Clinvar::iterator aux(*this);
   ++it;
   return aux;
}

Clinvar::iterator & Clinvar::iterator::operator--(){
   --it;
   return (*this);
}

Clinvar::iterator Clinvar::iterator::operator--(int){
   Clinvar::iterator aux(*this);
   --it;
   return aux;
}

bool Clinvar::iterator::operator==(const iterator & itc){
   return (it==itc.it);
}

bool Clinvar::iterator::operator!=(const iterator & itc){
   return (it!=itc.it);
}

Clinvar::iterator & Clinvar::iterator::operator=(const iterator & itc){
   if (this != &itc){
      it = itc.it;
   }
   return *this;
}

//******************************** Fin Class Iterator ********************************************//
//******************************** Class gen_Iterator ********************************************//
const Mutacion & Clinvar::gen_iterator::operator*(){
   return **itlist;
}

Clinvar::gen_iterator & Clinvar::gen_iterator::operator++(){
   itlist++;
   if(itlist==itmap->second.end()){
      itmap++;
      itlist=itmap->second.begin();
      if (itmap==ptrclinvar->gen_map.end()){
         itlist=itmap->second.begin();
      }
   }
   return *this;

}

Clinvar::gen_iterator Clinvar::gen_iterator::operator++(int){
   Clinvar::gen_iterator tmp(*this);
   itlist++;
   if(itlist==itmap->second.end()){
      itmap++;
      itlist=itmap->second.begin();
      if (itmap==ptrclinvar->gen_map.end()){
         itlist=itmap->second.begin();
      }
   }
   return tmp;
}

Clinvar::gen_iterator & Clinvar::gen_iterator::operator--(){
   if(itlist==itmap->second.begin()){
      itmap--;
      itlist=itmap->second.end();
      itlist--;
   }else{
     itlist--;
   }
   return *this;
}

Clinvar::gen_iterator Clinvar::gen_iterator::operator--(int){
   Clinvar::gen_iterator tmp(*this);
   if(itlist==itmap->second.begin()){
      itmap--;
      itlist=itmap->second.end();
      itlist--;
   }else{
     itlist--;
   }
   return tmp;
}

bool Clinvar::gen_iterator::operator==(const gen_iterator & itc){
   return (itlist==itc.itlist && itmap==itc.itmap);
}

bool Clinvar::gen_iterator::operator!=(const gen_iterator & itc){
   return (itlist!=itc.itlist || itmap!=itc.itmap);
}

Clinvar::gen_iterator & Clinvar::gen_iterator::operator=(const gen_iterator & itc){
   if (this != &itc){
      itlist = itc.itlist;
      itmap = itc.itmap;
      ptrclinvar = itc.ptrclinvar;
   }
   return *this;
}
//******************************** Fin Class gen_Iterator *****************************************//
/************************** Métodos relacionados con los iteradores ********************************/
Clinvar::iterator Clinvar::begin(){
   Clinvar::iterator it_aux;
   it_aux.it=mutDB.begin();
   return it_aux;
}

Clinvar::iterator Clinvar::end(){
   Clinvar::iterator it_aux;
   it_aux.it=mutDB.end();
   return it_aux;
}

Clinvar::iterator Clinvar::lower_bound(string cromosoma, unsigned int posicion){
   Clinvar::iterator it_aux;
   Mutacion val;
   val.setChr(cromosoma);
   val.setPos(posicion);
   it_aux.it = mutDB.lower_bound(val);
   return it_aux;
}

Clinvar::iterator Clinvar::upper_bound(string cromosoma, unsigned int posicion){
   Clinvar::iterator it_aux;
   Mutacion val;
   val.setChr(cromosoma);
   val.setPos(posicion);
   it_aux.it = mutDB.upper_bound(val);
   return it_aux;
}

Clinvar::enfermedad_iterator Clinvar::ebegin(){
   return EnfDB.begin();
}

Clinvar::enfermedad_iterator Clinvar::eend(){
   return EnfDB.end();
}

Clinvar::gen_iterator Clinvar::gbegin(){
   Clinvar::gen_iterator it_aux;
   it_aux.itmap = gen_map.begin();
   it_aux.itlist = it_aux.itmap->second.begin();
   it_aux.ptrclinvar = &(*this);
   return it_aux;
}

Clinvar::gen_iterator Clinvar::gend(){
   Clinvar::gen_iterator it_aux;
   it_aux.itmap = gen_map.end();
   it_aux.itlist = it_aux.itmap->second.begin();
   it_aux.ptrclinvar = &(*this);
   return it_aux;
}

/***************************************************************************************************/


void Clinvar::load (string nombreDB){
   ifstream fe;
   string cadena;

   cout << "Abrimos "<< nombreDB << endl;
   fe.open(nombreDB.c_str(), ifstream::in);
   if (fe.fail()){
     cerr << "Error al abrir el fichero " << nombreDB << endl;
   }
   else {
      //leo la cabecera del fichero (líneas que comienzan con #)
      do{
        getline(fe,cadena,'\n');
      }while (cadena.find('#')!=string::npos && !fe.eof());

      //leo la tabla de mutaciones, una línea cada vez
      while ( !fe.eof() ){
          //cout << "leo:: "<< cadena << endl;
          // Invoco el constructor de mutación que recibe una cadena completa, la parsea y crea la mutación.
          Mutacion mut = Mutacion(cadena);
          //cout << mut<< endl;
          // Insertar mutación en el conjunto
          insert(mut);

          getline(fe,cadena,'\n');
      }
      fe.close();
    } // else
    fe.close();
}

void Clinvar::insert (const Mutacion & x){
   pair<set<Mutacion>::iterator,bool> it;
   //Inserto en la BD mutaciones
   it = mutDB.insert(x);
   if (it.second){
      //Inserto el puntero que asocia IDmutacion con mutación
      IDm_map.insert(pair<IDmut,set<Mutacion>::iterator> (x.getID(),it.first));
      vector<Enfermedad> enf = x.getEnfermedades();
      for (Enfermedad e:enf){
         // Inserto la Base de datos de enfermedades
         EnfDB.insert(pair<IDenf,Enfermedad> (e.getID(),e) );
         //Inserto el puntero que asocia enfermedad con mutaciones
         IDenf_map.insert(pair<IDenf,set<Mutacion>::iterator> (e.getID(),it.first));
      }
      vector<string> genes = x.getGenes();
      list< set<Mutacion>::iterator> lista;
      for (int i=0; i<genes.size(); i++){
         //Busco el gen
         lista = gen_map[genes[i]];
         //Inserto el puntero que asocia genes con mutaciones
         lista.push_back(it.first);
         gen_map[genes[i]]=lista;
      }
   }

}

bool Clinvar::erase (IDmut ID){
   bool borrado=false;
   pair<multimap<IDenf,set<Mutacion>::iterator>::iterator, multimap<IDenf,set<Mutacion>::iterator>::iterator> res;
   vector<Enfermedad> enf;
   int cont;
   vector<string> genes;

   unordered_map<IDmut,set<Mutacion>::iterator>::iterator it = IDm_map.find(ID);

   if (it!=IDm_map.end()){
      set<Mutacion>::iterator itm = (*it).second;
      Mutacion mut = *itm;

      enf = getEnfermedades(mut);
      for(Enfermedad e: enf){
         cont=IDenf_map.count(e.getID());
         if (cont==1){
            //Elimino BD Enfermedad
            EnfDB.erase(e.getID());
            //Elimino el puntero que asocia enfermedades con mutaciones
            IDenf_map.erase(e.getID());
            borrado=true;
         }else if (cont>1){
            //Elimino el puntero que asocia enfermedades con mutaciones
            res = IDenf_map.equal_range(e.getID());
            for (multimap<IDenf,set<Mutacion>::iterator>::iterator it=res.first; it!=res.second; ++it){
               if ((*(it->second)).getID()==ID){
                  //Elimino el puntero que asocia enfermedades con mutaciones
                  IDenf_map.erase(e.getID());
                  borrado=true;
               }
            }
         }
      }

      //Elmino los punteros que asocian genes con mutación
      genes = mut.getGenes();
      for (int i=0; i<genes.size(); i++){
         map<IDgen, list< set<Mutacion>::iterator> >::iterator it = gen_map.find(genes[i]);
         (it->second).remove(itm);
      }


      //Elimino el puntero que asocia IDmutacion con mutación
      IDm_map.erase(ID);
      //Elimino la BD mutaciones
      mutDB.erase(itm);
   }

   return borrado;
}



Clinvar::iterator Clinvar::find_Mut (IDmut ID){
   unordered_map<IDmut,set<Mutacion>::iterator>::iterator aux;
   aux = IDm_map.find(ID);
   Clinvar::iterator itaux;
   if (aux==IDm_map.end())
      return end();
   else
      itaux.it = (*aux).second;
   return itaux;
}

Clinvar::enfermedad_iterator Clinvar::find_Enf(IDenf ID){
   Clinvar::enfermedad_iterator aux;
   aux = EnfDB.find(ID);
   if (aux==EnfDB.end())
      return eend();
   else
      return aux;
}

vector<Enfermedad> Clinvar::getEnfermedades(Mutacion & mut){
   Clinvar::iterator it = find_Mut(mut.getID());
   vector<Enfermedad> enf;
   if (it != end())
      enf =(*it).getEnfermedades();
   return enf;
}

list<Clinvar::IDenf> Clinvar::getEnfermedades(string keyword){
   list<Clinvar::IDenf> lista;
   Clinvar::enfermedad_iterator it = ebegin();
   while (it != eend()){
      if (((*it).second).nameContains(keyword))
         lista.push_back((*it).second.getID());
      it++;
   }

   return lista;
}

set<Clinvar::IDmut> Clinvar::getMutacionesEnf (IDenf ID){
   set<Clinvar::IDmut> mut;
   pair<multimap<IDenf,set<Mutacion>::iterator>::iterator, multimap<IDenf,set<Mutacion>::iterator>::iterator> res;
   res = IDenf_map.equal_range(ID);
   for (multimap<IDenf,set<Mutacion>::iterator>::iterator it=res.first; it!=res.second; ++it){
      mut.insert((*(it->second)).getID());
   }

   return mut;
}

set<Clinvar::IDmut> Clinvar::getMutacionesGen (IDgen ID){
   set<Clinvar::IDmut> mut;
   map<IDgen, list< set<Mutacion>::iterator> >::iterator it = gen_map.find(ID);
   list< set<Mutacion>::iterator>::iterator lit = it->second.begin();
   while (lit!= it->second.end()){
      mut.insert((*(*lit)).getID());
      lit++;
   }

   return mut;
}

set<Mutacion,ProbMutaciones> Clinvar::topKMutaciones (int k, string keyword){
   /*En primer lugar, debemos determinar cuando una enfermedad está relacionada con el string 'keyword' y, para cada una
   de las enfermedades obtenidas, determinar las mutaciones asociadas.*/
   list<Clinvar::IDenf> listaIDEnfermedades = getEnfermedades(keyword);
   set<Clinvar::IDmut> listaIDMutaciones;
   set<Clinvar::IDmut> listaAux;
   set<Mutacion,ProbMutaciones> listaMutaciones;
   priority_queue<Mutacion,vector<Mutacion>,ProbMutaciones> mypq;
   Mutacion mut;
   IDenf ID;

   list<Clinvar::IDenf>::iterator it = listaIDEnfermedades.begin();
   while(it != listaIDEnfermedades.end()){
      ID = *it;
      listaAux = getMutacionesEnf(ID);
      listaIDMutaciones.insert(listaAux.begin(),listaAux.end());
      it++;
   }

   //Guardo las mutaciones
   set<Clinvar::IDmut>::iterator aux = listaIDMutaciones.begin();
   while (aux != listaIDMutaciones.end()){
      mut=*(find_Mut(*aux));
      if (mypq.size()<k)
         mypq.push(mut);
      else{
         if (1-(mypq.top().getCaf()[0]) < 1-(mut.getCaf()[0])){
            mypq.pop();
            mypq.push(mut);
         }
      }
      aux++;
   }
   while(!mypq.empty()){
      listaMutaciones.insert(mypq.top());
      mypq.pop();
   }


   return listaMutaciones;
}
