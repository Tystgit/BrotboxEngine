#pragma once

#include "PoolAllocator.h"
#include <iostream>
#include "UtilTest.h"
#include "CPUWatch.h"

namespace bbe {
	namespace test {
		void poolAllocatorPrintAllocationSpeed() {
			double totalTimeAlloc = 0;
			double totalTimeDealloc = 0;
			int runs = 0;

			while (true) {
				constexpr size_t amountOfPersons = 1000000;
				PoolAllocator<Person> personAllocator(sizeof(Person) * amountOfPersons);
				Person* arr[amountOfPersons];

				CPUWatch swAllocate;
				for (size_t i = 0; i < amountOfPersons; i++) {
					arr[i] = personAllocator.allocate();
					//arr[i] = new Person();
				}
				totalTimeAlloc += swAllocate.getTimeExpiredSeconds();

				CPUWatch swDeallocate;
				for (size_t i = 0; i < amountOfPersons; i++) {
					personAllocator.deallocate(arr[i]);
					//delete arr[i];
				}
				totalTimeDealloc += swDeallocate.getTimeExpiredSeconds();

				
				runs++;
				std::cout << "avg Alloc Time:   " << (totalTimeAlloc / runs) << std::endl;		//0.0864
				std::cout << "avg Dealloc Time: " << (totalTimeDealloc / runs) << std::endl;	//0.03469
				std::cout << std::endl;
			}
			
		}
	}
}