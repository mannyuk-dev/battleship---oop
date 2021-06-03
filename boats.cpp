#include "headers/adaship.h"

#include <iostream>
#include <string>

Boats::Boats(){
    //constructor function

};

void Boats::initboats(std::string configpath)
{
}

void Boats::addboat(std::string name, std::string len, std::string color)
{
    //Add boat data
    _boats.push_back({name,
                      std::stoi(len),
                      color});
}

std::vector<boat> Boats::getboats()
{
    // returns all boats
    return _boats;
}