#ifndef CONTAINER_ATOMICCONTAINER_H_
#define CONTAINER_ATOMICCONTAINER_H_

#include <string>
#include <list>
#include <semaphore.h>
#include <memory>

#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/msg.h>
#include <stdexcept>

namespace core
{
template<class T>
class AtomicContainer
{
	public:
		AtomicContainer(int lockId)
				: _cmdList(std::list<T>())
		{
			if (sem_init(&_semaphore, 0, 1)) //visible to other threads, value = 1
				throw std::runtime_error("Cannot acquire semaphore");
		}

		virtual ~AtomicContainer()
		{
			sem_destroy(&_semaphore);
		}

		void pushBack(T item)
		{
			sem_wait(&_semaphore);

			_cmdList.push_back(item);

			sem_post(&_semaphore);
		}

		T popFirst()
		{
			sem_wait(&_semaphore);

			if (_cmdList.empty())
				throw std::runtime_error("Container is empty");

			T tmp = _cmdList.front();
			_cmdList.pop_front();

			sem_post(&_semaphore);

			return tmp;
		}

		bool empty()
		{
			return _cmdList.empty();
		}

	private:
		std::list<T> _cmdList;
		sem_t _semaphore;
};

}

#endif /* CONTAINER_ATOMICCONTAINER_H_ */
