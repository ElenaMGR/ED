/** @brief fichero de implementacion de la clase conjunto
*/

// Constructores
template <typename T, typename CMP>
conjunto<T,CMP>::conjunto( ){

}


template <typename T, typename CMP>
conjunto<T,CMP>::conjunto (const conjunto<T,CMP> & d){
   if(this!=&d){
      vm = d.vm;
      comp = d.comp;
   }
}


// Búsqueda
template <typename T, typename CMP>
typename conjunto<T,CMP>::iterator  conjunto<T,CMP>::find (const value_type & s) {
   bool encontrado = false;
   iterator it;

   if (!empty()){
      iterator principio = begin();
      iterator fin = end()-1;
      while (principio < fin && !encontrado){
         it = ((fin - principio)/2) + principio;
         if( cmp(s,(*it)) ){
            fin = --it;
         }else if ((*it) == s)
            encontrado = true;
         else{
            principio = ++it;
         }
      }
   }

   if (!encontrado)
      it = end();

   return it;
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::const_iterator  conjunto<T,CMP>::find (const value_type & s) const{
   bool encontrado = false;
   const_iterator it;

   iterator principio = cbegin();
   iterator fin = cend();
   while (principio < fin && !encontrado){
      it = ((fin - principio)/2) + principio;
      if( comp(s,(*it)) )
         fin = --it;
      else if ((*it) == s)
         encontrado = true;
      else
         principio = ++it;
   }

   if (!encontrado)
      it = cend();

   return it;
}


// Contador
template <typename T, typename CMP>
typename conjunto<T,CMP>::size_type conjunto<T,CMP>::count (const value_type & e) const{
   size_type cont = 0;
   if (find(e)!=end())
      cont = 1;
   return cont;
}

//Inserción
template <typename T, typename CMP>
pair<typename conjunto<T,CMP>::iterator,bool> conjunto<T,CMP>::insert (const value_type& val){
   bool insertado = false;
   iterator it;

   it = std::lower_bound(vm.begin(),vm.end(),val, comp);
   if (it==vm.end()||!(*it==val)){
      it =vm.insert(it,val);
      insertado = true;
   }
   if (!insertado)
      it=end();

   return pair<iterator,bool>(it,insertado);
}


// borrado
template <typename T, typename CMP>
typename conjunto<T,CMP>::iterator  conjunto<T,CMP>::erase (const iterator position){
   iterator it = vm.erase(position);
   return it;
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::size_type conjunto<T,CMP>::erase (const value_type& val){
   iterator it = find (val);
   size_type cont = 0;
   if (it!=end()){
      vm.erase(it);
      cont ++;
   }
   return cont;
}

template <typename T, typename CMP>
void  conjunto<T,CMP>::clear(){
   vm.clear();
}

// Tamaño
template <typename T, typename CMP>
typename conjunto<T,CMP>::size_type  conjunto<T,CMP>::size() const {
   return vm.size();
}

template <typename T, typename CMP>
bool conjunto<T,CMP>::empty() const{
   return (vm.size()==0);
}

// Operador =
template <typename T, typename CMP>
conjunto<T,CMP> & conjunto<T,CMP>::operator=( const conjunto & org){
   if (this != &org){
      vm=org.vm;
   }

   return *this;
}

// Iteradores
template <typename T, typename CMP>
typename conjunto<T,CMP>::iterator conjunto<T,CMP>::begin (){
   return vm.begin();
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::iterator conjunto<T,CMP>::end (){
   return vm.end();
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::const_iterator conjunto<T,CMP>::cbegin () const{
   return vm.cbegin();
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::const_iterator conjunto<T,CMP>::cend () const{
   return vm.cend();
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::iterator conjunto<T,CMP>::lower_bound (const value_type& val){
   return std::lower_bound(vm.begin(),vm.end(),val, comp);
}


template <typename T, typename CMP>
typename conjunto<T,CMP>::const_iterator conjunto<T,CMP>::lower_bound (const value_type& val) const{
   return std::lower_bound(vm.cbegin(),vm.cend(),val, comp);
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::iterator conjunto<T,CMP>::upper_bound (const value_type& val){
   return std::upper_bound(vm.begin(),vm.end(),val, comp);
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::const_iterator conjunto<T,CMP>::upper_bound (const value_type& val) const{
   return std::upper_bound(vm.cbegin(),vm.cend(),val, comp);
}

// Operador <<
template <typename T, typename CMP>
ostream &  operator << ( ostream & sal, const conjunto<T,CMP> & C){
   typename conjunto<T,CMP>::const_iterator it = C.cbegin();
   while(it != C.cend()){
      sal<<(*it)<<endl;
      ++it;
   }
   return sal;
}

//  Invariante de la representacion
template <typename T, typename CMP>
bool conjunto<T,CMP>::cheq_rep( ) const{
   return true;
}
