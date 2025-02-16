#pragma once


#include <string>
#include <unordered_map>

namespace Core {

	template<typename Resource>
	class Resource_Manager
	{
	private:
		std::unordered_map<std::string, Resource> m_resources;

		const std::string m_folder;
		const std::string m_extention;

		std::string getFullFilename(const std::string& name)
		{
			return m_folder + name + m_extention;
		}

	public:

		Resource_Manager(const std::string& folder, const std::string& extention)
            : m_folder("res/" + folder + "/")
            , m_extention("." + extention)
        {
        }

        const Resource& get(const std::string& name)
        {
            if (!exists(name)) {
                add(name);
            }

            return m_resources.at(name);
        }

        bool exists(const std::string& name) const
        {
            return m_resources.find(name) != m_resources.end();
        }

        void add(const std::string& name)
        {
            Resource r;

            // if the resource fails to load, then it adds a default "fail"
            // resource
            if (!r.loadFromFile(getFullFilename(name))) {
                Resource fail;
                fail.loadFromFile(m_folder + "_fail_" + m_extention);
                m_resources.insert(std::make_pair(name, fail));
            }
            else {
                m_resources.insert(std::make_pair(name, r));
            }
        }
	};
}