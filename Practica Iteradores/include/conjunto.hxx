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
   typename conjunto<T,CMP>::iterator it;
	it=this->begin();
	bool encontrado=false;
	while(it!=this->end() && !encontrado){
		if(*(it.it)==s){
			encontrado=true;
		}
		else{
			it++;
		}
	}
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
   typename conjunto<T,CMP>::iterator sal;
   sal.it=vm.begin();
   sal.elvector = &vm;
   return sal;
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::iterator conjunto<T,CMP>::end (){
   typename conjunto<T,CMP>::iterator sal;
   sal.it=vm.end();
   sal.elvector = &vm;
   return sal;
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::const_iterator conjunto<T,CMP>::cbegin () const{
   typename conjunto<T,CMP>::iterator sal;
   sal.it=vm.cbegin();
   sal.elvector = &vm;
   return sal;
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::const_iterator conjunto<T,CMP>::cend () const{
   typename conjunto<T,CMP>::iterator sal;
   sal.it=vm.cend();
   sal.elvector = &vm;
   return sal;
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::secure_iterator conjunto<T,CMP>::sbegin (){
   typename conjunto<T,CMP>::iterator sal;
   sal.it=vm.begin();
   sal.elvector = &vm;
   return sal;
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::const_secure_iterator conjunto<T,CMP>::csbegin( ) const{
   typename conjunto<T,CMP>::iterator sal;
   sal.it=vm.cbegin();
   sal.elvector = &vm;
   return sal;
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


//---------------Class iterator----------------------------

template <typename T, typename CMP>
conjunto<T,CMP>::iterator::iterator(){

}

template <typename T, typename CMP>
conjunto<T,CMP>::iterator::iterator(const iterator &  x){
   this->it=x.it;
   this->elvector=x.elvector;
}

template <typename T, typename CMP>
conjunto<T,CMP>::iterator::iterator(const secure_iterator &  x){
   this->it=x.it;
   this->elvector=x.elvector;
}

template <typename T, typename CMP>
const T & conjunto<T,CMP>::iterator::operator*(){
   return *it;
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::iterator & conjunto<T,CMP>::iterator::operator++(){
   it++;
   return (*this);
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::iterator conjunto<T,CMP>::iterator::operator++(int i){
   typename conjunto<T,CMP>::iterator tmp(*this);
   it++;
   return tmp;
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::iterator & conjunto<T,CMP>::iterator::operator--(){
   this->it--;
   return (*this);
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::iterator conjunto<T,CMP>::iterator::operator--(int i){
   typename conjunto<T,CMP>::iterator tmp(*this);
   it--;
   return tmp;
}

template <typename T, typename CMP>
bool conjunto<T,CMP>::iterator::operator==(const iterator & x) const{
   return (it==x.it);
}

template <typename T, typename CMP>
bool conjunto<T,CMP>::iterator::operator!=(const iterator & x) const{
   return (it!=x.it);
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::iterator & conjunto<T,CMP>::iterator::operator=(const iterator & x){
   it = x.it;
   elvector = x.elvector;
   return (*this);
}

//---------------FIN Class iterator----------------------------

//---------------Class const_iterator----------------------------

template <typename T, typename CMP>
conjunto<T,CMP>::const_iterator::const_iterator(){

}

template <typename T, typename CMP>
conjunto<T,CMP>::const_iterator::const_iterator(const const_iterator &  x){
   this->it=x.it;
   this->elvector=x.elvector;
}

template <typename T, typename CMP>
conjunto<T,CMP>::const_iterator::const_iterator(const const_secure_iterator &  x){
   this->it=x.it;
   this->elvector=x.elvector;
}

template <typename T, typename CMP>
const T & conjunto<T,CMP>::const_iterator::operator*(){
   return *it;
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::const_iterator & conjunto<T,CMP>::const_iterator::operator++(){
   this->it++;
   return *this;
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::const_iterator conjunto<T,CMP>::const_iterator::operator++(int i){
   typename conjunto<T,CMP>::const_iterator tmp(*this);
   it++;
   return tmp;
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::const_iterator & conjunto<T,CMP>::const_iterator::operator--(){
   this->it--;
   return *this;
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::const_iterator conjunto<T,CMP>::const_iterator::operator--(int i){
   typename conjunto<T,CMP>::const_iterator tmp(*this);
   it--;
   return tmp;
}

template <typename T, typename CMP>
bool conjunto<T,CMP>::const_iterator::operator==(const const_iterator & x) const{
   return (it==x.it);
}

template <typename T, typename CMP>
bool conjunto<T,CMP>::const_iterator::operator!=(const const_iterator & x) const{
   return (it!=x.it);
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::const_iterator & conjunto<T,CMP>::const_iterator::operator=(const const_iterator & x){
   it = x.it;
   elvector = x.elvector;
   return (*this);
}

//---------------FIN Class const_iterator----------------------------

//---------------Class secure_iterator----------------------------

template <typename T, typename CMP>
conjunto<T,CMP>::secure_iterator::secure_iterator(){

}

template <typename T, typename CMP>
conjunto<T,CMP>::secure_iterator::secure_iterator(const secure_iterator &  x){
   this->it=x.it;
   this->elvector=x.elvector;
}


template <typename T, typename CMP>
const T & conjunto<T,CMP>::secure_iterator::operator*(){
   return *elvector;
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::secure_iterator & conjunto<T,CMP>::secure_iterator::operator++(){
   this->it++;
   return *this;
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::secure_iterator conjunto<T,CMP>::secure_iterator::operator++(int i){
   typename conjunto<T,CMP>::secure_iterator tmp(*this);
   it++;
   return tmp;
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::secure_iterator & conjunto<T,CMP>::secure_iterator::operator--(){
   this->it--;
   return *this;
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::secure_iterator conjunto<T,CMP>::secure_iterator::operator--(int i){
   typename conjunto<T,CMP>::secure_iterator tmp(*this);
   it--;
   return tmp;
}

template <typename T, typename CMP>
bool conjunto<T,CMP>::secure_iterator::operator==(const secure_iterator & x) const{
   return (it==x.it);
}

template <typename T, typename CMP>
bool conjunto<T,CMP>::secure_iterator::operator!=(const secure_iterator & x) const{
   return (it!=x.it);
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::secure_iterator & conjunto<T,CMP>::secure_iterator::operator=(const secure_iterator & x){
   it = x.it;
   elvector = x.elvector;
}

//---------------FIN Class secure_iterator----------------------------

//---------------Class const_secure_iterator----------------------------

template <typename T, typename CMP>
conjunto<T,CMP>::const_secure_iterator::const_secure_iterator(){

}

template <typename T, typename CMP>
conjunto<T,CMP>::const_secure_iterator::const_secure_iterator(const const_secure_iterator &  x){
   this->it=x.it;
   this->elvector=x.elvector;
}


template <typename T, typename CMP>
const T & conjunto<T,CMP>::const_secure_iterator::operator*(){
   return *elvector;
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::const_secure_iterator & conjunto<T,CMP>::const_secure_iterator::operator++(){
   this->it++;
   return *this;
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::const_secure_iterator conjunto<T,CMP>::const_secure_iterator::operator++(int i){
   typename conjunto<T,CMP>::const_secure_iterator tmp(*this);
   it++;
   return tmp;
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::const_secure_iterator & conjunto<T,CMP>::const_secure_iterator::operator--(){
   this->it--;
   return *this;
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::const_secure_iterator conjunto<T,CMP>::const_secure_iterator::operator--(int i){
   typename conjunto<T,CMP>::const_secure_iterator tmp(*this);
   it--;
   return tmp;
}

template <typename T, typename CMP>
bool conjunto<T,CMP>::const_secure_iterator::operator==(const const_secure_iterator & x) const{
   return (it==x.it);
}

template <typename T, typename CMP>
bool conjunto<T,CMP>::const_secure_iterator::operator!=(const const_secure_iterator & x) const{
   return (it!=x.it);
}

template <typename T, typename CMP>
typename conjunto<T,CMP>::const_secure_iterator & conjunto<T,CMP>::const_secure_iterator::operator=(const const_secure_iterator & x){
   it = x.it;
   elvector = x.elvector;
}

//---------------FIN Class const_secure_iterator----------------------------

//---------------Class impar_iterator----------------------------

template <typename T, class CMP>
conjunto<T, CMP>::impar_iterator::impar_iterator(){

}

template <typename T, class CMP>
conjunto<T, CMP>::impar_iterator::impar_iterator(const typename conjunto<T,CMP>::impar_iterator &  x){
	this->it=x.it;
	this->elvector=x.elvector;
}

template <typename T, class CMP>
const typename conjunto<T,CMP>::value_type &
			 conjunto<T, CMP>::impar_iterator::operator*()
{
	return *it;
}

template <typename T, class CMP>
typename conjunto<T,CMP>::impar_iterator & conjunto<T,CMP>::impar_iterator::operator++(){
	bool impar=false;
	if(it<(*elvector).end()){
		++it;
	}
	while(it!=(*elvector).end() && !impar){
		if((*it).getPos()%2==0){
			++it;
		}
		else{
			impar=true;
		}
	}
	return (*this);
}

template <typename T, class CMP>
typename conjunto<T,CMP>::impar_iterator
	 conjunto<T,CMP>::impar_iterator::operator++(int i){
	typename conjunto<T,CMP>::impar_iterator aux(*this);
	it++;
	return aux;
}

template <typename T, class CMP>
typename conjunto<T,CMP>::impar_iterator & conjunto<T,CMP>::impar_iterator::operator--(){
	bool impar=false;
	if(it>(*elvector).begin()){
		--it;
	}
	while(it!=(*elvector).begin() && !impar){
		if((*it).getPos()%2==0){
			--it;
		}
		else{
			impar=true;
		}
	}
	return (*this);
}

template <typename T, class CMP>
typename conjunto<T,CMP>::impar_iterator  conjunto<T,CMP>::impar_iterator::operator--(int i){
	typename conjunto<T,CMP>::impar_iterator aux(*this);
	it--;
	return aux;
}

template <typename T, class CMP>
bool conjunto<T,CMP>::impar_iterator::operator==(const typename conjunto<T,CMP>::impar_iterator & x) const {
	return this->it==x.it;
}



template <typename T, class CMP>
bool conjunto<T,CMP>::impar_iterator::operator!=(const typename conjunto<T,CMP>::impar_iterator & x) const {
	return this->it!=x.it;
}

template <typename T, class CMP>
typename conjunto<T,CMP>::impar_iterator & conjunto<T,CMP>::impar_iterator::operator=(const typename conjunto<T,CMP>::impar_iterator & x){
	this->it=x.it;
	this->elvector=x.elvector;
	return (*this);
}

//---------------FIN Class impar_iterator----------------------------

//---------------Class const_impar_iterator----------------------------

template <typename T, class CMP>
conjunto<T, CMP>::const_impar_iterator::const_impar_iterator(){

}

template <typename T, class CMP>
conjunto<T, CMP>::const_impar_iterator::const_impar_iterator(const typename conjunto<T,CMP>::const_impar_iterator &  x){
	this->it=x.it;
	this->elvector=x.elvector;
}

template <typename T, class CMP>
const typename conjunto<T,CMP>::value_type & conjunto<T, CMP>::const_impar_iterator::operator*(){
	return *it;
}

template <typename T, class CMP>
typename conjunto<T,CMP>::const_impar_iterator & conjunto<T,CMP>::const_impar_iterator::operator++(){
	bool impar=false;
	if(it<(*elvector).end()){
		++it;
	}
	while(it!=(*elvector).end() && !impar){
		if((*it).getPos()%2==0){
			++it;
		}
		else{
			impar=true;
		}
	}
	return (*this);
}

template <typename T, class CMP>
typename conjunto<T,CMP>::const_impar_iterator
	 conjunto<T,CMP>::const_impar_iterator::operator++(int i){
	typename conjunto<T,CMP>::const_impar_iterator aux(*this);
	it++;
	return aux;
}

template <typename T, class CMP>
typename conjunto<T,CMP>::const_impar_iterator & conjunto<T,CMP>::const_impar_iterator::operator--(){
	bool impar=false;
	if(it>(*elvector).begin()){
		--it;
	}
	while(it!=(*elvector).begin() && !impar){
		if((*it).getPos()%2==0){
			--it;
		}
		else{
			impar=true;
		}
	}
	return (*this);
}

template <typename T, class CMP>
typename conjunto<T,CMP>::const_impar_iterator  conjunto<T,CMP>::const_impar_iterator::operator--(int i){
	typename conjunto<T,CMP>::const_impar_iterator aux(*this);
	it--;
	return aux;
}

template <typename T, class CMP>
bool conjunto<T,CMP>::const_impar_iterator::operator==(const typename conjunto<T,CMP>::const_impar_iterator & x) const {
	return this->it==x.it;
}



template <typename T, class CMP>
bool conjunto<T,CMP>::const_impar_iterator::operator!=(const typename conjunto<T,CMP>::const_impar_iterator & x) const {
	return this->it!=x.it;
}

template <typename T, class CMP>
typename conjunto<T,CMP>::const_impar_iterator & conjunto<T,CMP>::const_impar_iterator::operator=(const typename conjunto<T,CMP>::const_impar_iterator & x){
	this->it=x.it;
	this->elvector=x.elvector;
	return (*this);
}

//---------------FIN Class impar_iterator----------------------------
