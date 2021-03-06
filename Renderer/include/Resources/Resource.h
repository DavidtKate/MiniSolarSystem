#pragma once

namespace re
{
	// Abstract class
	class Resource
	{
	public:

		Resource() = default;
		virtual ~Resource() = default;

		virtual void Load() = 0;
		virtual void Unload() = 0;

		void SetID(size_t a_ID) { m_resourceID = a_ID; };
		size_t GetID() const { return m_resourceID; };

	protected:

		size_t m_resourceID = 0;
	};
}