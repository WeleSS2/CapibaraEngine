#pragma once
#include <iostream>
#include <mutex>

namespace CEngine {
    namespace DPatterns {
        
        template <typename T>
        class Singleton
        {
        public:
            static T* getInstance();

        protected:
            Singleton() {}

        private:
            static T* instance_;
            static std::once_flag onceFlag_;

            Singleton(const Singleton&) = delete;
            Singleton& operator=(const Singleton&) = delete;
        };
    }
}