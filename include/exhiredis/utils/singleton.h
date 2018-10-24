//
// Created by dguco on 18-10-20.
//

#ifndef EXHIREDIS_SINGLETON_HPP
#define EXHIREDIS_SINGLETON_HPP

#include <memory>
#include <mutex>
using namespace std;

namespace exhiredis
{
	std::mutex g_SingleTonLock;

	template<typename T>
	class CSingleton
	{
	public:
		CSingleton()
		{};
	private:
		CSingleton(const CSingleton &temp) = delete;
		CSingleton &operator=(const CSingleton &temp) = delete;
	private:
		static std::shared_ptr<T> spSingleton;
	public:
		static std::shared_ptr<T> &GetSingletonPtr()
		{
			return spSingleton;
		}

		static std::shared_ptr<T> &CreateInstance()
		{
			std::lock_guard<mutex> lock(g_SingleTonLock);
			if (spSingleton == NULL) {
				spSingleton = std::make_shared<T>( );
			}
			return spSingleton;
		}
	};

}
#endif //EXHIREDIS_SINGLETON_HPP