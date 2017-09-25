/** @brief fichero de implementacion de la clase conjunto
*/

//Constructores

conjunto::conjunto( ){

}

conjunto::conjunto (const conjunto & d){
   vm = d.vm;
}


// Métodos de búsqueda

pair<conjunto::value_type,bool>  conjunto::find (const string & chr, const unsigned int & pos) const{
   bool encontrado = false;
   mutacion mutfind;
   const_iterator it = cbegin();

   while (it != cend() && !encontrado){
      if ( (*it).getChr()==chr && (*it).getPos()==pos ){
         mutfind = (*it);
         encontrado = true;
      }
      it++;
   }

   const pair<conjunto::value_type,bool> res (mutfind, encontrado);
   return res;

}

pair<conjunto::value_type,bool>  conjunto::find (const string & ID) const{
   bool encontrado = false;
   mutacion mutfind;
   const_iterator it = cbegin();

   while (it != cend() && !encontrado){
      if ( (*it).getID()==ID ){
         mutfind = (*it);
         encontrado = true;
      }
      it++;
   }

   const pair<conjunto::value_type,bool> res (mutfind, encontrado);
   return res;
}


pair<conjunto::value_type,bool>  conjunto::find (const conjunto::value_type & e) const{
   bool encontrado = false;
   mutacion mutfind;
   const_iterator it = cbegin();

   while (it != cend() && !encontrado){
      if ( ((*it).getChr()==e.getChr() && (*it).getPos()==e.getPos()) || ((*it).getID()==e.getID()) ){
         mutfind = (*it);
         encontrado = true;
      }
      it++;
   }

   const pair<conjunto::value_type,bool> res (mutfind, encontrado);
   return res;
}



// cuenta cuantas entradas coinciden con los parámetros dados.
conjunto::size_type conjunto::count (const string & chr, const unsigned int & pos) const{
   size_type cont = 0;
   const_iterator it = cbegin();

   while (it != cend() && cont==0){
      if ((*it).getChr()==chr && (*it).getPos()==pos){
         cont++;
      }
      it++;
   }

   return cont;
}


conjunto::size_type conjunto::count (const string & ID) const{
   size_type cont = 0;
   const_iterator it = cbegin();

   while (it != cend() && cont==0){
      if ((*it).getID()==ID){
         cont++;
         if (cont>1)
            cout<<cont<<" "<<ID<<endl;
      }
      it++;
   }

   return cont;
}


conjunto::size_type conjunto::count (const conjunto::value_type & e) const{
   size_type cont = 0;
   const_iterator it = cbegin();

   while (it != cend() && cont==0){
      if ((*it).getChr()==e.getChr() && (*it).getPos()==e.getPos() && (*it).getID()==e.getID()){
         cont++;
      }
      it++;
   }

   return cont;
}

// Método insert

bool conjunto::insert( const conjunto::value_type & e){
   bool encontrado = false;

   if (empty()){
      vm.push_back(e);
   }else{
      encontrado = find(e).second;

      if (!encontrado){
         vm.insert(lower_bound(e), e);
      }
   }

   return !encontrado;
}


// Metodos de borrado

bool conjunto::erase(const string & chr, const unsigned int & pos){
   bool encontrado = false;
   iterator it = begin();

   while (it != end() && !encontrado){
      if ( (*it).getChr()==chr && (*it).getPos()==pos ){
         vm.erase(it);;
         encontrado = true;
      }
      it++;
   }

   return encontrado;
}

bool conjunto::erase(const string & ID){
   bool encontrado = false;
   iterator it = begin();

   while (it != end() && !encontrado){
      if ( (*it).getID()==ID ){
         vm.erase(it);
         encontrado = true;
      }
      it++;
   }

   return encontrado;
}

bool conjunto::erase(const conjunto::value_type & e){
   return erase(e.getID());
}

void conjunto::clear(){
   vm.clear();
}


// Devuelve el tamaño
conjunto::size_type conjunto::size() const {
   return vm.size();
}

bool conjunto::empty() const{
   return (vm.size()==0);
}


// Operador =
conjunto & conjunto::operator=( const conjunto & org){
   if (this != &org){
      vm=org.vm;
   }

   return *this;
}


//Iteradores
conjunto::iterator conjunto::begin (){
   iterator it;
   it = (vm.empty())?vm.end():vm.begin();
   return it;
}

conjunto::iterator conjunto::end (){
   return vm.end();
}

conjunto::const_iterator conjunto::cbegin () const{
   const_iterator it;
   it = (vm.empty())?vm.cend():vm.cbegin();
   return it;
}

conjunto::const_iterator conjunto::cend () const{
   return vm.cend();
}

conjunto::const_iterator conjunto::lower_bound (const string & chr, const unsigned int & pos) const{
   value_type e;
   e.setChr(chr);
   e.setPos(pos);

   return lower_bound(e);
}

conjunto::const_iterator conjunto::lower_bound (const conjunto::value_type & e) const{
   const_iterator it = cbegin();
   bool encontrado = false;

   while(it != cend() && !encontrado){
      if ((*it)<e )
         it++;
      else
         encontrado = true;
   }

   return it;
}

conjunto::const_iterator conjunto::upper_bound (const string & chr, const unsigned int & pos) const{
   value_type e;
   e.setChr(chr);
   e.setPos(pos);

   return upper_bound(e);
}

conjunto::const_iterator conjunto::upper_bound (const conjunto::value_type & e) const{
   const_iterator it = lower_bound(e);
   while (it != cend() && *it == e){
      it++;
   }

   return it;
}

//Chequea el invariante de representación
bool conjunto::cheq_rep( ) const{
   bool correcto=true;
   for (int i=0; i<vm.size() && correcto; i++){
      if (vm[i].getPos() < 1)
         correcto=false;

      if (!(vm[i].getChr()=="1" || vm[i].getChr()=="2" || vm[i].getChr()=="3" || vm[i].getChr()=="4" || vm[i].getChr()=="5"
      || vm[i].getChr()=="6" || vm[i].getChr()=="7" || vm[i].getChr()=="8" || vm[i].getChr()=="9" || vm[i].getChr()=="10"
      || vm[i].getChr()=="11" || vm[i].getChr()=="12" || vm[i].getChr()=="13" || vm[i].getChr()=="14" || vm[i].getChr()=="15"
      || vm[i].getChr()=="16" || vm[i].getChr()=="17" || vm[i].getChr()=="18" || vm[i].getChr()=="19" || vm[i].getChr()=="20"
      || vm[i].getChr()=="21" || vm[i].getChr()=="22" || vm[i].getChr()=="X" || vm[i].getChr()=="Y" || vm[i].getChr()=="MT"))
         correcto = false;
   }

   for (int i=0; i<vm.size()-1 && correcto; i++){
      if (vm[i].getChr() == vm[i+1].getChr()){
         if (vm[i].getPos() >= vm[i+1].getPos())
            correcto = false;
      }

      if ( vm[i].getChr() != vm[i+1].getChr()){
         int chrcomp;
         int mchrcomp;
         try {
            chrcomp = stoi(vm[i].getChr());
            mchrcomp = stoi(vm[i+1].getChr());
         }
         catch (const std::invalid_argument& ia) {
            if (vm[i].getChr()=="X"){
               chrcomp=23;
            }else if (vm[i].getChr()=="Y"){
               chrcomp=24;
            }
            else if (vm[i].getChr()=="MT"){
               chrcomp=25;
            }
            if (vm[i+1].getChr()=="X"){
               mchrcomp=23;
            }else if (vm[i+1].getChr()=="Y"){
               mchrcomp=24;
            }
            else if (vm[i+1].getChr()=="MT"){
               mchrcomp=25;
            }
         }

         if (chrcomp >= mchrcomp)
            correcto=false;
      }
   }

   return correcto;
}

ostream &  operator << ( ostream & sal, const conjunto & C){
   conjunto::const_iterator it = C.cbegin();
   while(it != C.cend()){
      sal<<*it<<endl;
      it++;
   }
}
