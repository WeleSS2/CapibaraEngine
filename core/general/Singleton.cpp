#include "Singleton.hpp"

template <typename T>
static T* CEngine::DPatterns::Singleton<T>::getInstance()
{
    std::call_once(onceFlag_, []()
    { 
        instance_ = new T(); 
    } 
    );
    
    return instance_;
};

template <typename T>
T* CEngine::DPatterns::Singleton<T>::instance_ = nullptr;

template <typename T>
std::once_flag CEngine::DPatterns::Singleton<T>::onceFlag_;