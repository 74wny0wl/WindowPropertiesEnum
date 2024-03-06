#include "Menu.h"

#include <iostream>

void Menu::showBanner()
{
    std::cout << "WindowPropertiesEnum 1.0.0 by t4wny0wl" << std::endl;
}

void Menu::showUsage()
{
    std::cout << "Usage: \n";
    std::cout << "-w windowName - window name (mandatory)" << std::endl;
}