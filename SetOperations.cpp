#ifndef SET_OPS_CPP
#define SET_OPS_CPP

#include <unordered_set>
#include <list>
#include <algorithm>

template<class T>
Sequence<T> Sequence<T>::operator|(const Sequence<T>& other) const{
	return Sequence<T>::concat(*this, other);
}

template<class T>
Sequence<T> Sequence<T>::operator&(const Sequence<T>& other) const{
	Sequence<T> result;


	std::list<Sequence::customPair> difference;
	std::set_symmetric_difference(this->set.begin(), this->set.end(), other.set.begin(), other.set.end(),
						std::inserter(difference, difference.end()), ComparePairsByFirst<Sequence<T>::customPair>());
	std::unordered_set<T> difference_hashtable;
	for(auto& el : difference){
		difference_hashtable.insert(el.first);
	}

	std::set_intersection(this->set.begin(), this->set.end(), other.set.begin(), other.set.end(),
						std::inserter(result.set, result.set.end()), ComparePairsByFirst<Sequence<T>::customPair>());

	result.seq = this->seq;
	for(auto it = result.seq.begin(); it != result.seq.end(); ){
		auto search = difference_hashtable.find((*it)->first);
		if(search != difference_hashtable.end()){
			it = result.seq.erase(it);
		}else{
			++it;
		}
	}

	return result;
}

template<class T>
Sequence<T> Sequence<T>::operator^(const Sequence<T>& other) const{
	Sequence<T> result;

	std::list<Sequence::customPair> difference;
	std::set_intersection(this->set.begin(), this->set.end(), other.set.begin(), other.set.end(),
						std::inserter(difference, difference.end()), ComparePairsByFirst<Sequence<T>::customPair>());
	std::unordered_set<T> difference_hashtable;
	for(auto& el : difference){
		difference_hashtable.insert(el.first);
	}

	std::set_symmetric_difference(this->set.begin(), this->set.end(), other.set.begin(), other.set.end(),
						std::inserter(result.set, result.set.end()), ComparePairsByFirst<Sequence<T>::customPair>());

	result.seq.insert(result.seq.end(), this->seq.begin(), this->seq.end());
	result.seq.insert(result.seq.end(), other.seq.begin(), other.seq.end());
	for(auto it = result.seq.begin(); it != result.seq.end(); ){
		auto search = difference_hashtable.find((*it)->first);
		if(search != difference_hashtable.end()){
			it = result.seq.erase(it);
		}else{
			++it;
		}
	}
	std::cout << std::endl;

	return result;
}

template<class T>
Sequence<T> Sequence<T>::operator/(const Sequence<T>& other) const{
	Sequence<T> result;

	std::unordered_set<T> difference_hashtable;
	for(auto& el : other){
		difference_hashtable.insert(el);
	}

	std::set_difference(this->set.begin(), this->set.end(), other.set.begin(), other.set.end(),
						std::inserter(result.set, result.set.end()), ComparePairsByFirst<Sequence<T>::customPair>());

	result.seq = this->seq;
	for(auto it = result.seq.begin(); it != result.seq.end(); ){
		auto search = difference_hashtable.find((*it)->first);
		if(search != difference_hashtable.end()){
			it = result.seq.erase(it);
		}else{
			++it;
		}
	}

	return result;
}

#endif
