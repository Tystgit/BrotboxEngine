#pragma once

#include "DataType.h"
#include "List.h"
#include "UtilMath.h"
#include "UniquePointer.h"
#include "UtilTest.h"

namespace bbe
{
	namespace INTERNAL
	{
		class GeneralPurposeAllocatorFreeChunk
		{
		public:
			byte* m_addr;
			size_t m_size;

			GeneralPurposeAllocatorFreeChunk(byte* addr, size_t size)
				: m_addr(addr), m_size(size)
			{
				//do nothing
			}

			bool touches(const GeneralPurposeAllocatorFreeChunk& other) const
			{
				//UNTESTED
				if (m_addr + m_size == other.m_addr)
				{
					return true;
				}
				if (other.m_addr + other.m_size == m_addr)
				{
					return true;
				}

				return false;
			}

			bool operator>(const GeneralPurposeAllocatorFreeChunk& other) const
			{
				return m_addr > other.m_addr;
			}

			bool operator>=(const GeneralPurposeAllocatorFreeChunk& other) const
			{
				return m_addr >= other.m_addr;
			}

			bool operator<(const GeneralPurposeAllocatorFreeChunk& other) const
			{
				return m_addr < other.m_addr;
			}

			bool operator<=(const GeneralPurposeAllocatorFreeChunk& other) const
			{
				return m_addr <= other.m_addr;
			}

			bool operator==(const GeneralPurposeAllocatorFreeChunk& other) const
			{
				return m_addr == other.m_addr;
			}

			template <typename T, typename... arguments>
			T* allocateObject(size_t amountOfObjects = 1, arguments&&... args)
			{
				//UNTESTED
				static_assert(alignof(T) <= 128, "Max alignment of 128 was exceeded");
				byte* allocationLocation = (byte*)nextMultiple(alignof(T), ((size_t)m_addr) + 1);
				size_t amountOfBytes = amountOfObjects * sizeof(T);
				byte* newAddr = allocationLocation + amountOfBytes;
				if (newAddr <= m_addr + m_size)
				{
					byte offset = (byte)(allocationLocation - m_addr);
					allocationLocation[-1] = offset;
					T* returnPointer = reinterpret_cast<T*>(allocationLocation);
					m_size -= newAddr - m_addr;
					m_addr = newAddr;
					for (size_t i = 0; i < amountOfObjects; i++)
					{
						T* object = bbe::addressOf(returnPointer[i]);
						new (object) T(std::forward<arguments>(args)...);
					}
					return returnPointer;
				}
				else
				{
					return nullptr;
				}
			}
		};
	}
	

	class GeneralPurposeAllocator
	{
		//TODO use parent allocator
		//TODO defragmentation
	public:
		template<typename T>
		class GeneralPurposeAllocatorDestroyer
		{
		private:
			GeneralPurposeAllocator* m_pa;
			size_t m_size;
		public:
			GeneralPurposeAllocatorDestroyer(GeneralPurposeAllocator *pa, size_t size)
				: m_pa(pa), m_size(size)
			{
				//do nothing
			}

			void destroy(void* data)
			{
				m_pa->deallocateObjects(reinterpret_cast<T*>(data), m_size);
			}
		};
	private:
		static const size_t GENERAL_PURPOSE_ALLOCATOR_DEFAULT_SIZE = 1024;
		byte* m_data;
		size_t m_size;

		List<INTERNAL::GeneralPurposeAllocatorFreeChunk, true> m_freeChunks;

	public:
		explicit GeneralPurposeAllocator(size_t size = GENERAL_PURPOSE_ALLOCATOR_DEFAULT_SIZE)
			: m_size(size)
		{
			//UNTESTED
			m_data = new byte[m_size];
			m_freeChunks.pushBack(INTERNAL::GeneralPurposeAllocatorFreeChunk(m_data, m_size));
		}

		~GeneralPurposeAllocator()
		{
			if (m_freeChunks.getLength() != 1)
			{
				debugBreak();
			}
			if (m_freeChunks[0].m_addr != m_data)
			{
				debugBreak();
			}
			if (m_freeChunks[0].m_size != m_size)
			{
				debugBreak();
			}
			if (m_data != nullptr)
			{
				delete[] m_data;
				m_data = nullptr;
			}
		}

		GeneralPurposeAllocator(const GeneralPurposeAllocator& other) = delete;
		GeneralPurposeAllocator(GeneralPurposeAllocator&& other) = delete;
		GeneralPurposeAllocator& operator=(const GeneralPurposeAllocator& other) = delete;
		GeneralPurposeAllocator& operator=(GeneralPurposeAllocator&& other) = delete;

		template <typename T, typename... arguments>
		T* allocateObjects(size_t amountOfObjects = 1, arguments&&... args)
		{
			//UNTESTED
			static_assert(alignof(T) <= 128, "Max alignment of 128 was exceeded");
			for (size_t i = 0; i < m_freeChunks.getLength(); i++)
			{
				T* data = m_freeChunks[i].allocateObject<T>(amountOfObjects, std::forward<arguments>(args)...);
				if (data != nullptr)
				{
					return data;
				}
			}

			//TODO add further error handling
			return nullptr;
		}

		template <typename T, typename... arguments>
		T* allocateObject(arguments&&... args)
		{
			//UNTESTED
			return allocateObjects<T>(1, std::forward<arguments>(args)...);
		}

		template <typename T, typename... arguments>
		UniquePointer<T, GeneralPurposeAllocatorDestroyer<T>> allocateObjectsUniquePointer(size_t amountOfObjects = 1, arguments&&... args)
		{
			T* pointer = allocateObjects<T>(amountOfObjects, std::forward<arguments>(args)...);
			return UniquePointer<T, GeneralPurposeAllocatorDestroyer<T>>(pointer, GeneralPurposeAllocatorDestroyer<T>(this, amountOfObjects));
		}

		template <typename T, typename... arguments>
		UniquePointer<T, GeneralPurposeAllocatorDestroyer<T>> allocateObjectUniquePointer(arguments&&... args)
		{
			return allocateObjectsUniquePointer<T>(1, std::forward<arguments>(args)...);
		}

		template<typename T>
		void deallocateObjects(T* dataPointer, size_t amountOfObjects = 1)
		{
			//UNTESTED
			for (size_t i = 0; i < amountOfObjects; i++)
			{
				bbe::addressOf(dataPointer[i])->~T();
			}

			byte* bytePointer = reinterpret_cast<byte*>(dataPointer);
			size_t amountOfBytes = sizeof(T) * amountOfObjects;
			byte offset = bytePointer[-1];

			//TODO add this to the freeChunks list
			INTERNAL::GeneralPurposeAllocatorFreeChunk gpafc(bytePointer - offset, amountOfBytes + offset);

			INTERNAL::GeneralPurposeAllocatorFreeChunk* p_gpafc = &gpafc;
			INTERNAL::GeneralPurposeAllocatorFreeChunk* left;
			bool didTouchLeft = false;
			bool didMerge = false;
			INTERNAL::GeneralPurposeAllocatorFreeChunk* right;

			m_freeChunks.getNeighbors(*p_gpafc, left, right);
			if (left != nullptr)
			{
				if (left->touches(*p_gpafc))
				{
					left->m_size += p_gpafc->m_size;
					didTouchLeft = true;
					p_gpafc = left;
					didMerge = true;
				}
			}
			if (right != nullptr)
			{
				if (right->touches(*p_gpafc))
				{
					if (didTouchLeft)
					{
						p_gpafc->m_size += right->m_size;
						m_freeChunks.removeSingle(*right);
					}
					else
					{
						right->m_size += p_gpafc->m_size;
						right->m_addr = p_gpafc->m_addr;
					}
					didMerge = true;
				}
			}

			if (!didMerge)
			{
				m_freeChunks.pushBack(gpafc);
			}
		}
	};
}