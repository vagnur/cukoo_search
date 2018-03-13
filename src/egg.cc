#include <egg.hh>

egg::egg(void)
{
	;
}

egg::egg(const int &number_of_parameters, const std::vector<double> lower_bounds, const std::vector<double> upper_bounds)
{
	//Each attribute of the class is initialized and the memory is reserved for each vector.
	this->number_of_parameters = number_of_parameters;
	this->solution.resize(number_of_parameters);
	this->parameters_distributions.resize(number_of_parameters);
	for(int i=0;i<number_of_parameters;i++)
	{
		std::uniform_real_distribution<double> dis(lower_bounds[i], upper_bounds[i]);
		this->parameters_distributions[i] = dis;
	}
}

void egg::generate_solution(const std::function<double(std::vector<double>,int)> fitness)
{
	std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 generator(rd()); //Standard mersenne_twister_engine seeded with rd()
	for(int i=0;i<this->number_of_parameters;i++)
	{
		//For each parameter, a random value is obtained and setted in the i position of the solution vector
		this->solution[i] = this->parameters_distributions[i](generator);
	}
	this->fitness = fitness(this->solution,this->number_of_parameters);
}

void egg::change_egg(std::vector<double> new_egg)
{
	this->solution = new_egg;
}

double egg::get_fitness(void) const
{
	return this->fitness;
}

std::vector<double> egg::get_solution(void) const
{
	return this->solution;
}

//TODO : Eventualy remove
void egg::print_solution(void)
{
	for(int i=0;i<this->number_of_parameters;i++)
	{
		std::cout << this->solution[i] << " ";
	}
}	

egg::~egg(void)
{
	;
}