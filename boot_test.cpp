#include <iostream>
#include "Sequence.cpp"

template<size_t power>
struct randGen{
	int operator()() const{
		return rand()%power;
	}
};

int main() {
	Sequence<int> seq1;
	seq1.getRandomSequence(3, randGen<6>());
	for(auto& el: seq1){
		std::cout << el << "\t";
	}
	std::cout << std::endl;

	Sequence<int> seq2;
	seq2.getRandomSequence(3, randGen<6>());
	for(auto& el: seq2){
		std::cout << el << "\t";
	}
	std::cout << std::endl;

	auto seq_res = Sequence<int>::merge(seq1, seq2);

	for(auto& el: seq_res){
		std::cout << el << "\t";
	}
	std::cout << std::endl;
}
