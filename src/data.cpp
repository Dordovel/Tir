#include "../header/data.hpp"
#include <filesystem>

Resources::Resources(std::string_view pathToFolder): _folder(pathToFolder){}

std::string Resources::get_resources(std::string_view name)
{
	namespace fs = std::filesystem;

	std::filesystem::path p(this->_folder);
	for(auto&& file : fs::recursive_directory_iterator(p))
    {
	    if(file.is_regular_file())
        {
	        if(file.path().stem() == name)
	            return file.path();
        }
    }

    return "";
}
