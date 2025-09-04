#include "Data.hpp"

Data::Data() : id(0), name(""), value(0.0), active(false)
{
}

Data::Data(int id, const std::string& name, double value, bool active)
	: id(id), name(name), value(value), active(active)
{
}

void Data::print() const
{
	std::cout << "Data { id: " << id 
			  << ", name: \"" << name 
			  << "\", value: " << value 
			  << ", active: " << (active ? "true" : "false") 
			  << " }" << std::endl;
}

bool Data::operator==(const Data& other) const
{
	return (id == other.id && 
			name == other.name && 
			value == other.value && 
			active == other.active);
}
