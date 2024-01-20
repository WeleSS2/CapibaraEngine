#pragma once
#include <iostream>
#include <mutex>

namespace CEngine {
    namespace DPatterns {
        
        template <typename T>
        class Singleton
        {
        public:
            static T* getInstance()
            {
                std::call_once(onceFlag_, []()
                { 
                    instance_ = new T(); 
                } 
                );

                return instance_;
            }

        protected:
            Singleton() {}

        private:
            static T* instance_;
            static std::once_flag onceFlag_;

            Singleton(const Singleton&) = delete;
            Singleton& operator=(const Singleton&) = delete;
        };

        template <typename T>
        T* Singleton<T>::instance_ = nullptr;

        template <typename T>
        std::once_flag Singleton<T>::onceFlag_;
    }
}