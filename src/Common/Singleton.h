#ifndef SINGLETON_H
#define SINGLETON_H

#include <QMutex>

template <typename T>

class Singleton
{
public:
    static T* Instance() {

        static QMutex mutex;
        mutex.lock();

        if (instance == nullptr) {
            instance = new T();
        }
        mutex.unlock();

        return instance;
    }

    virtual ~Singleton() {

        static QMutex mutex;
        mutex.lock();

        if(instance != nullptr) {
            delete instance;
            instance = nullptr;
        }
        mutex.unlock();
    }

private:
    static T* instance;
};

template<typename T>

T* Singleton<T>::instance = nullptr;

#endif // SINGLETON_H
