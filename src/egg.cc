#include <egg.hh>

egg::egg(void)
{
	;
}

egg::egg(const int &number_of_parameters, const std::vector<double> min, const std::vector<double> max)
{
	//Each attribute of the class is initialized and the memory is reserved for each vector.
	this->number_of_parameters = number_of_parameters;
	this->solution.resize(number_of_parameters);
	std::uniform_real_distribution<double> parameter_selector(0.0,1.0);
	this->parameter_selector = parameter_selector;
	this->min = min;
	this->max = max;
}

void egg::generate_solution(const std::function<double(std::vector<double>,int,std::vector<double>,std::vector<double>)> fitness)
{
	std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 generator(rd()); //Standard mersenne_twister_engine seeded with rd()
	for(int i=0;i<this->number_of_parameters;i++)
	{
		//For each parameter, a random value is obtained and setted in the i position of the solution vector
		this->solution[i] = this->parameter_selector(generator);
	}
	this->fitness = fitness(this->solution,this->number_of_parameters,this->min,this->max);
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