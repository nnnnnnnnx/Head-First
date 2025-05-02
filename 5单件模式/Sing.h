#pragma once
#include <iostream>
#include <memory>
#include <mutex>
//单件模式确保一个类只有一个实例，并提供一个全局的访问点。
class ChocolateBoiler {
private:
	bool empty;
	bool boiled;
	static std::unique_ptr<ChocolateBoiler> instance;
	static std::once_flag initFlag;
private:
	ChocolateBoiler() {
		empty = true;
		boiled = false;
	}
public:
	static ChocolateBoiler* getInstance()
	{
		if (instance == nullptr) {
			call_once(initFlag, [&]() {
				instance = std::make_unique<ChocolateBoiler>();
				//instance.reset(new ChocolateBoiler());
				}
			);
		}
		return instance.get();
	}
	void fill() {
		if (isEmpty()) {
			empty = false;
			boiled = true;
		}
	}
	void drain() {
		if (!isEmpty() && !isBoiled()) {
			empty = true;
		}
	}
	void boil() {
		if (!isEmpty() && !isBoiled()) {
			boiled = true;
		}
	}
	bool isEmpty() {
		return empty;
	}
	bool isBoiled() {
		return boiled;
	}

};

std::unique_ptr<ChocolateBoiler> ChocolateBoiler::instance;
std::once_flag ChocolateBoiler::initFlag;

/*
class ChocolateBoiler {
private:
	static ChocolateBoiler* instance;
	static std::mutex mtx;

	ChocolateBoiler() {}

public:
	static ChocolateBoiler* getInstance() {
		std::lock_guard<std::mutex> lock(mtx);
		if (instance == nullptr) {
			instance = new ChocolateBoiler();
		}
		return instance;
	}

	ChocolateBoiler(const ChocolateBoiler&) = delete;
	ChocolateBoiler& operator=(const ChocolateBoiler&) = delete;
};

ChocolateBoiler* ChocolateBoiler::instance = nullptr;
std::mutex ChocolateBoiler::mtx;
*/


/*
class Singleton {
private:
	Singleton();
public:
	static Singleton& getInstance() {
		static Singleton instance;
		return instance;
	}
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;
};
*/

/*
class Singleton {
private:
	Singleton() {}
	~Singleton() {}

	static Singleton* instance;
	static std::once_flag initFlag;

public:
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;

	static Singleton* getInstance() {
		std::call_once(initFlag, []() {
			instance = new Singleton();
			});
		return instance;
	}

	static void destroyInstance() {
		delete instance;
		instance = nullptr;
	}
};

Singleton* Singleton::instance = nullptr;
std::once_flag Singleton::initFlag;
*/

/*
class Singleton {
private:
	Singleton() {}
	static std::unique_ptr<Singleton> instance;
	static std::once_flag initFlag;

public:
	static Singleton* getInstance() {
		std::call_once(initFlag, []() {
			instance.reset(new Singleton());
		});
		return instance.get();
	}
};

std::unique_ptr<Singleton> Singleton::instance;
std::once_flag Singleton::initFlag;
*/