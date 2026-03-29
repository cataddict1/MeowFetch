#include <iostream>
#include <fstream>
#include <string>

static std::string cat = " /\\_/\\ \n( O.o )\n/     \\\n"; // cat ascii

int main(){
    std::ifstream file("/etc/os-release"); // get the OS name
    std::string osname;
    if(!file){ // checks if opening /etc/os-release failed
        std::cout << "Could not find OS name!\n";
        file.close();
        return 1;
    }
    //file >> osname;
    std::getline(file, osname);
    file.close();

    std::cout << cat << '\n'; // print the ascii cat
    osname.erase(0, 6); // erase the " NAME="" "
    osname.erase(10, 10);
    std::cout << "OS: " << osname << '\n';

    
    return 0;
}