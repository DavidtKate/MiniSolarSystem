#include "repch.h"
#include "Resources/ResourceManager.h"

namespace re
{
    void ResourceManager::AddResource(resource_ptr a_resource, const std::string& a_resourceName)
    {
        a_resource->SetID(m_resources.size());
        a_resource->Load();

        m_resources.emplace(a_resourceName, std::move(a_resource));
    }
}