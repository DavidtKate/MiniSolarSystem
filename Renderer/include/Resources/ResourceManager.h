#pragma once
#include "Resources/Resource.h"

namespace re
{
	// Functor to unload resources when unique_ptr's are deleted
	struct FreeResource
	{
		void operator()(re::Resource* a_resource)
		{
			a_resource->Unload();
			delete a_resource;
		}
	};

	typedef std::unique_ptr<Resource, FreeResource> resource_ptr;

	// Singleton class
	class ResourceManager
	{
	public:

		static ResourceManager& GetInstance()
		{
			static ResourceManager s_resourceManager;
			return s_resourceManager;
		}

		void AddResource(resource_ptr a_resource, const std::string& a_resourceName);

		template<typename T>
		T& GetResource(const std::string& a_resourceName) const
		{
			return dynamic_cast<T&>(*m_resources.find(a_resourceName)->second);
		}

		size_t GetSize() const { return m_resources.size(); }
		void FreeResources() { m_resources.clear(); }

	private:

		ResourceManager() = default;
		~ResourceManager() = default;

		std::unordered_map<std::string, resource_ptr> m_resources;
	};
}