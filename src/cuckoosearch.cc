#include <iostream>
#include <unistd.h>
#include <cuckoo.hh>
#include <nest.hh>
#include <vector>
#include <fstream>

double fitness(std::vector<double> cuckoo_egg,int number_of_parameters, std::vector<double> min, std::vector<double> max);

int main(int argc, char** argv)
{ 
	//Parameters for the algorithm
	//	char c = Used for the getopt options
	//	int number_of_parameters = Number of parameters of the problem
	//	int number_of_eggs = Number of eggs (solutions) to use
	//	int max_generation = Maximun number of generations before the algoritm ends
	//	int t = The actual generation
	//	int ouput = How often feedback is given to the user (e.g in wich generation)
	//	double beta = Used in the Levy Flight
	//	double pa = Fraction of worse nests to destroy
	//	double stop_criterion = Stop criterion for the algorithm (minium fitness to get)
	//	vector expected = Expected values (e.g real values)
	//	vector upper_bounds : Each position of the vector contains the upper bound of the i parameter.
	//	vector lower_bounds : Each position of the vector contains the lower bound of the i parameter.
	char c;
	int number_of_parameters=0,number_of_eggs=0,max_generation=0,t=0,ouput=10;	
	double beta=0.0,pa=0.0,stop_criterion=0.0;
	extern char *optarg;
	while((c=getopt(argc,argv,"p:n:g:b:f:o:s:"))!=-1)
	{
		switch (c)
		{
			case 'p':
				number_of_parameters = std::stoi(optarg);
				break;
			case 'n':
				number_of_eggs = std::stoi(optarg);
				break;
			case 'g':
				max_generation = std::stoi(optarg);
				break;
			case 'b':
				beta = std::stod(optarg);
				break;
			case 'f':
				pa = std::stod(optarg);
				break;
			case 'o':
				ouput = std::stoi(optarg);
				break;
			case 's':
				stop_criterion = std::stod(optarg);
				break;
		}
	}
	//Parameters verification
	if(number_of_parameters==0)
	{
		std::cout << "Mandatory parameter -p (number of parameters) needed" << std::endl;
		return -1;
	}
	if(number_of_eggs==0)
	{
		std::cout << "Mandatory parameter -n (number of eggs) needed" << std::endl;
		return -1;
	}
	if(max_generation==0)
	{
		std::cout << "Mandatory parameter -g (max number of iterations) needed" << std::endl;
		return -1;
	}
	if(beta==0)
	{
		std::cout << "Mandatory parameter -b (beta) needed" << std::endl;
		return -1;
	}
	if(pa==0)
	{
		std::cout << "Mandatory parameter -f (fraction of worse nests to destroy) needed" << std::endl;
		return -1;
	}
	if(stop_criterion==0.0)
	{
		std::cout << "Mandatory parameter -s (stop criterion) needed" << std::endl;
		return -1;
	}
	//This vector alocates the cuckoo eggs in each generation
	std::vector<std::vector<double> > cuckoo_eggs(number_of_eggs);

	//Min and max for each parameter
	std::vector<double> min(number_of_parameters);
	std::vector<double> max(number_of_parameters);

	//File read
	std::ifstream input;
	input.open("input.data",std::ifstream::in);
	for(int i=0;i<number_of_parameters;i++)
	{
		input >> min[i];
	}
	for(int i=0;i<number_of_parameters;i++)
	{
		input >> max[i];
	}
	input.close();

	//Initialization of the cukoo and the nest class
	cuckoo cko(beta,number_of_parameters);
	nest nst(number_of_eggs,number_of_parameters,pa,min,max);

	//CUCKOO SEARCH ALGORITHM

	//Generate initial population of hosts
	nst.initial_population(fitness);

	while(t<max_generation)
	{
		//Get a cuckoo egg for each egg in the nest
		for(int i=0;i<number_of_eggs;i++)
		{
			cuckoo_eggs[i] = cko.get_cuckoo(nst.get_egg_solution(i),0.01);
		}
		//The cuckoo eggs are compared and replaces if necesary
		for(int i=0;i<number_of_eggs;i++)
		{
			nst.compare_eggs(fitness(cuckoo_eggs[i],number_of_parameters,min,max),cuckoo_eggs[i]);
		}
		//A fraction (pa) of worse nests are abandoned and rebuild (new solutions)
		nst.discover_eggs(fitness);
		//Rank the solutions (the best one is in the first position of the vector)
		nst.rank_eggs();
		t++;
		//Feedback
		if(t%ouput==0)
		{
			nst.postprocess();
		}
		if(nst.get_best_fitness() < stop_criterion)
			break;
	}
	//Display of the best solution
	std::cout << "Best egg (solution) at generation " << t << std::endl;
	for(int i=0;i<number_of_parameters;i++)
	{
		std::cout << (nst.get_egg_solution(0)[i]*(max[i]-min[i]))+min[i] << " ";
	}
	std::cout << "With Fitness: " << nst.get_best_fitness() << std::endl;
	return 0;
}

//Example of fitness
//In this case, the algorithm needs to guess the sequence [0,1,2,3,4]
double fitness(std::vector<double> solution, int number_of_parameters, std::vector<double> min, std::vector<double> max)
{
	double fitness=0,value,unormal_value;
	//In this case wee use the Mean squared error
	for(unsigned int i=0;i<solution.size();i++)
	{
		//See that, since the algorithm searchs in a [0,1] space,
		//is necesary to adjust the values in the search space
		unormal_value = (solution[i]*(max[i]-min[i]))+min[i];
		value = i - unormal_value;
		fitness = fitness + pow(value,2);
	}
	return fitness/number_of_parameters;
}