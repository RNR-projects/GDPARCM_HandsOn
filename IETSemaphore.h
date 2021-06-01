#pragma once
#include <semaphore> 

class IETSemaphore
{
public:
	IETSemaphore(int available);
	~IETSemaphore();

	void acquire() const;
	void acquire(int permits) const;
	void release() const;
	void release(int permits) const;

private:
	const static int Global_Max_Permit = 50;
	typedef std::counting_semaphore<Global_Max_Permit> Semaphore;
	Semaphore* semaphore;
};

