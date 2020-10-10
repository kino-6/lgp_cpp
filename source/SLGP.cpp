#include "SLGP.h"

SLGP::SLGP(std::string problem_file){
	this->pop.clear();

	// stunb
	this->Nvariables = 9;
	this->NOperators = 4;
	this->NRegisters = 9;
	this->NInputs    = 3;
	this->NConstants = 2;
	this->NIndividuals = 10;

	this->problem = SLGP_Problem(problem_file);

	// gene_generator
	this->mt.seed(42);
	std::uniform_int_distribution<Gene> gene_generator(0x30, 0x30+this->NOperators);
	this->new_gene = gene_generator;
}

Gene SLGP::MakeGene(unsigned int kind_of_genes){
	return (Gene)this->new_gene(this->mt);
}

Individual SLGP::MakeIndividual(unsigned int gene_num){
	Individual one;
	one.gene.resize(gene_num);
	for(unsigned int i=0; i<gene_num; i++){
		one.gene.at(i) = MakeGene(this->Nvariables);
	}
	return one;
}

void SLGP::MakePopulation(unsigned int pop_size){
	this->pop.resize(pop_size);
	for(unsigned int i=0; i<pop_size; i++){
		this->pop.at(i) = MakeIndividual(this->NIndividuals);
	}
}

void SLGP::PrintIndividual(unsigned int idx){
	try{
		std::cout
			<< "Genes = "
			<< std::to_string(this->pop.at(idx).gene.size())
			<< std::endl;

		for(unsigned int i=0; i<this->pop.at(idx).gene.size(); i++){
			std::cout << i << ": " << std::to_string(pop.at(idx).gene.at(i)) + " " << std::ends;
			std::cout << std::endl;
		}

		std::cout
			<< "Fitness = "
			<< std::to_string(this->pop.at(idx).fitness)
			<< std::endl;

	}catch (const char* msg){
		std::cerr << "some_exception: " << msg << std::endl;
	}
}

SLGP::~SLGP(void){
	this->pop.clear();
}