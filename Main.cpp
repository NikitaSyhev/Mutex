#include <iostream>
#include <mutex>
#include <string>
#include <thread>

// Mutex - помогает синхронихировать потоки. Ѕлокирует проход потока через строчку.
//Mutex, deadlock, recursive mutex

//Recursive Mutex - можно испоьзовать всегда, но он дороже дл¤ быстродействи¤ ( как и всегда можно использовать - 
// shared_ptr но иногда используем unique_ptr

//deadlock - блокировка обеих потоков
class Logger {
public:


	//race_conditon
	void log(const std::string& message) {

		std::lock_guard<std::mutex> lock(_mutex);
		std::scoped_lock s_lock{ _mutex, _secondMutex };
		std::cout << "[" << counter << "]" << std::endl;
		counter++;

	}

	/*void successMessage() {
		std::lock_guard<std::recursive_mutex> lock(_mutex);
		std::cout << "succes Message" << std::endl;
	}*/


	void someFunc() {
		std::lock_guard<std::mutex> lock(_mutex);
		std::cout << "Some text" << std::endl;
		std::lock_guard <std::mutex> lock2(_secondMutex);

	}
private:
	int counter = 0;
	std::mutex _mutex;
	std::mutex _secondMutex;
};




//main thread - главный поток не рекомендуется блокировать так как виснит вся программа
int main() {
	Logger logger;
	logger.log("Hello");
	logger.log("Info message");
	std::cout << "Hello world\n";

	std::thread t1 = std::thread([&logger]() { // создали 1 поток т1
		std::string threadName = "t1"; // лямбда которая создает строку
		for (size_t i = 0; i < 100; i++) {
			logger.log(threadName + " doing" + std::to_string(i) + " iteration of work");
		}
		});

	std::thread t2 = std::thread([&logger]() {// создали второй поток t2
		std::string threadName = "t2";
		for (size_t i = 0; i < 100; i++) {
			logger.log(threadName + " doing" + std::to_string(i) + " iteration of work");
		}
		});


	t1.join(); t2.join();








	std::optional<int> val = std::nullopt;
	std::cout << val.value() << std::endl;

}