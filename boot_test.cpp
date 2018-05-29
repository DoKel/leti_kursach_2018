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
	seq1.insert(1);
	seq1.insert(2);
	seq1.insert(2);
	seq1.insert(3);
	seq1.insert(4);
	//seq1.getRandomSequence(10, randGen<6>());
	for(auto& el: seq1){
		std::cout << el << "\t";
	}
	std::cout << std::endl;

	Sequence<int> seq2;
	seq2.getRandomSequence(7, randGen<6>());
	//for(auto& el: seq2){
		//std::cout << el << "\t";
	//}
	std::cout << std::endl;

	auto seq_res = Sequence<int>::erase(seq1, 1, 2);
	seq_res.insert(5);


	for(auto& el: seq_res){
		std::cout << el << "\t";
	}
	std::cout << std::endl;
}
