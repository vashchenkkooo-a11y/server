#include "TokenGenerator.h"
#include <boost/uuid/random_generator.hpp> //даёт готовый генератор UUID
#include <boost/uuid/uuid_io.hpp> //возможность превратить UUID в строку

std::string TokenGenerator::generate()
{
    boost::uuids::random_generator generator;
    boost::uuids::uuid id = generator();
    return boost::uuids::to_string(id);
}