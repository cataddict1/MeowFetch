#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <cstring>
#include <cpuid.h>

static std::string cat = " /\\_/\\ \n( O.o )\n/     \\\n"; // cat ascii

std::string get_cpu_name() {
    std::array<unsigned int, 4> cpui;
    char brand[0x40];
    memset(brand, 0, sizeof(brand));

    for (unsigned int i = 0; i < 3; ++i) {
        __cpuid(0x80000002 + i, cpui[0], cpui[1], cpui[2], cpui[3]);
        memcpy(brand + i*16, cpui.data(), sizeof(cpui));
    }
    return std::string(brand);
}


int main(){
    std::ifstream get_osname("/etc/os-release"); // get the OS name
    std::string osname;
    if(!get_osname){ // checks if opening /etc/os-release failed
        std::cout << "Could not find OS name!\n";
        get_osname.close();
        return 1;
    }
    // file >> osname;
    std::getline(get_osname, osname);
    get_osname.close();
    osname.erase(0, 6); // erase the " NAME="" "
    osname.erase(10, 10);

    // get the kernel version
    std::ifstream read_kernel_ver("/proc/sys/kernel/osrelease");
    std::string kernelversion;
    if (!read_kernel_ver) {
        std::cout << "Could not find kernel version!\n";
        read_kernel_ver.close();
        return 1;
    }

    std::getline(read_kernel_ver, kernelversion);
    read_kernel_ver.close();

    // get the cpu name - this part doesn't work
    /*
    std::ifstream get_cpu("/proc/cpuinfo");
    std::string cpu_string;
    if (!get_cpu) {
        std::cout << "Could not get CPU name!\n";
        get_cpu.close();
        return 1;
    }
    int count_newline = 0;
    int pos = 0;
    char ch = cpu_string[pos];
    std::string cpu;
    std::string appending_string;
    while (std::getline(get_cpu, cpu_string)) {
        pos++;
        if (ch == '\n') {
            count_newline++;
        }
        else if (count_newline == 4) {
            for (char i; i !=':';) {
                i = ch;
                pos++;
            }
            pos++;

            for (char x; x !='\n';) {
                appending_string = ch;
                cpu.append(appending_string);
            }
            break;
        }
    }
    get_cpu.close();
    */


    // get hostname
    std::ifstream get_hostname("/etc/hostname");
    std::string hostname;
    if (!get_hostname) {
        std::cout << "Could not get hostname!\n";
        get_hostname.close();
        return 1;
    }
    std::getline(get_hostname, hostname);
    get_hostname.close();

    // the visual part
    std::cout << cat << '\n'; // print the ascii cat
    // print info
    std::cout << std::flush;
    system(R"(echo -n $(whoami) )");
    std::cout << '@' << hostname << "\n-----------------------";
    std::cout << "\nOS: " << osname << ' ' << std::flush;
    system(R"(uname -m)");
    std::cout << "Kernel: " << kernelversion << "\n";
    std::cout << "Shell: " << std::flush;
    system(R"(echo $SHELL)");
    std::cout << "CPU: " << get_cpu_name() << "\n";
    std::cout << "GPU:" << std::flush;
    system(R"(lspci | grep -i 'vga\|3d\|2d' | cut -d: -f3-)");

    
    return 0;
}
