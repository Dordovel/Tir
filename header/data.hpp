#ifndef PROJECT_RESOURCES_HEADER
#define PROJECT_RESOURCES_HEADER

#include <string_view>
#include <string>

class Resources
{
	private:
		std::string _folder;

	public:
		Resources(std::string_view pathToFolder);

		std::string get_resources(std::string_view name);
};

#endif //PROJECT_RESOURCES_HEADER
