#include <nest.hh>

nest::nest(void)
{
	;
}

nest::nest(const int &number_of_eggs, const int &number_of_parameters, const double &pa, const std::vector<double> lower_bounds, const std::vector<double> upper_bounds)
{
	//Each attribute of the class is initialized and the memory is reserved for each vector.
	this->number_of_eggs = number_of_eggs;
	this->number_of_parameters = number_of_parameters;
	//The vector eggs is initialized whit an egg object in each position.
	this->eggs.assign(number_of_eggs, egg(number_of_parameters,lower_bounds,upper_bounds));
	this->pa = pa;
}

void nest::initial_population(const std::function<double(std::vector<double>,int)> fitness)
{
	for(int i=0;i<this->number_of_eggs;i++)
	{
		//Each object of the vector eggs generate a initial solution.
		this->eggs[i].generate_solution(fitness);
	}
}

void nest::	compare_eggs(const double cuckoo_egg_fitness, const std::vector<double> cuckoo_egg)
{
	//The position of the egg in the nest is obtained randomly
	//TRICK : The best egg from this iteration remain unchanged
	int egg_to_compare = std::rand()%this->number_of_eggs;
	while(egg_to_compare==0)
		egg_to_compare = std::rand()%this->number_of_eggs;
	//If the fitness of the cuckoo egg is better than the fitness of the egg to compare,
	//then the cuckoo get use the space in the nest
	if(cuckoo_egg_fitness > this->eggs[egg_to_compare].get_fitness())
	{
		eggs[egg_to_compare].change_egg(cuckoo_egg);
	}
}

/*
TODO : Understand this thing

% In the real world, if a cuckoo's egg is very similar to a host's eggs, then 
% this cuckoo's egg is less likely to be discovered, thus the fitness should 
% be related to the difference in solutions.  Therefore, it is a good idea 
% to do a random walk in a biased way with some random step sizes.  
*/
void nest::discover_eggs(const std::function<double(std::vector<double>,int)> fitness)
{
	//To obtain the first egg to be discovered 
	int first_to_eliminate = this->number_of_eggs-(pa*this->number_of_eggs)-1;
	//From that number until the end of the nest each egg generate a new solution and the old one is destroyed.
	for(int i=first_to_eliminate;i<this->number_of_eggs;i++)
	{
		eggs[i].generate_solution(fitness);
	}
}

void nest::rank_eggs(void)
{
	std::sort(this->eggs.begin(), this->eggs.begin() + this->number_of_eggs,[](egg const &e1, egg const &e2) -> bool{return e1.get_fitness() < e2.get_fitness();});
}

//TODO : Do a better post process
void nest::postprocess(void)
{
	/*
	for(int i=0;i<this->number_of_eggs;i++)
	{
		this->eggs[i].print_solution();
		std::cout << std::endl;
	}
	*/
	double mean=0;
	for(int i=0;i<this->number_of_eggs;i++)
	{
		mean = mean + this->eggs[i].get_fitness();
	}
	mean = mean/this->number_of_eggs;
	std::cout << "Min/Max/Avg Fitness " << "[" << this->eggs[0].get_fitness() << "," << this->eggs[this->number_of_eggs-1].get_fitness() << "," << mean <<"]" << std::endl;
}

std::vector<double> nest::get_egg_solution(const int &i) const
{
	return this->eggs[i].get_solution();
}

nest::~nest(void)
{
	;
}