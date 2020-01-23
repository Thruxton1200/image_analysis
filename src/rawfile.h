#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <fstream>
#include <numeric>
#include <cmath>

// ----- template functions ----- //
template <typename T> void write_rawfile(std::string fname, std::vector<T>& image);
template <typename T> void read_rawfile (std::string fname, std::vector<T>& image);

// ----- template functions ---- //
template <typename T> void write_rawfile(std::string fname, std::vector<T>& image)
{
    std::ofstream ofs(fname.c_str()); 
    if (!ofs) std::cerr << "Failed to open " << fname << std::endl;
    else { ofs.write(reinterpret_cast<char*>(&image[0]), sizeof(T) * image.size()); }
}

template <typename T> void read_rawfile (std::string fname, std::vector<T>& image)
{
    std::ifstream ifs(fname.c_str());
    if (!ifs) std::cerr << "Failed to open " << fname << std::endl;
    else { ifs.read(reinterpret_cast<char*>(&image[0]), sizeof(T) * image.size()); }
}
