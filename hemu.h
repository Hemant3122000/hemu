#pragma once
#include <iostream>
#include <initializer_list>

//Namespace hemu
namespace hemu
{
	//Tensor class for storing dynamically allocated tensor which have elements of generic type
	//T is type of elements and N is Number of dimensions
	template<typename T>
	class Tensor
	{
		//private data members for hemu::Tensor
	private:
		//Number of dimensions
		size_t N;
		//pointer to store shape of Tensor(on heap)
		size_t* shape;

		//pointer to store hemu::Tensor elements(on heap)
		T* data;
	public:
		//returns number of elements of Tensor
		size_t numel() const
		{
			size_t n = 1;
			for (size_t i = 0; i < this->N; i++)
				n *= *(shape + i);
			return n;
		}

		//default constructor for Tensor
		Tensor() = delete;

		//constructor with parameters for Tensor
		Tensor(std::initializer_list<size_t> shape)
		{
			this->N = shape.size();
			this->shape = new size_t[this->N]{};
			std::copy(shape.begin(), shape.end(), this->shape);
			this->data = new T[this->numel()]{};
		}

		//constructor using shape pointer and Number of dimensions
		Tensor(size_t* shape_ptr,size_t N)
		{
			this->N = N;
			this->shape = new size_t[this->N]{};
			std::copy_n(shape_ptr, this->N, this->shape);
			this->data = new T[this->numel()]{};
		}
		//copy constructor
		Tensor(const Tensor& src)
		{
			this->N = src.N;
			this->shape = new size_t[src.N]{};
			std::copy_n(src.shape, src.N, this->shape);
			this->data = new T[src.numel()]{};
			std::copy_n(src.data, src.numel(), this->data);
		}

		//move constructor
		Tensor(const Tensor&& src)
		{
			this->N = src.N;
			this->shape = new size_t[src.N]{};
			std::copy_n(src.shape, src.N, this->shape);
			this->data = new T[src.numel()]{};
			std::copy_n(src.data, src.numel(), this->data);
			src.~Tensor();
		}

		//destructor
		~Tensor()
		{
			delete[] this->data;
			this->data = nullptr;
			delete[] this->shape;
			this->shape = nullptr;
		}

		//method to get pointer at indexed location
		T* ptrat(std::initializer_list<size_t> index)
		{
			size_t n = 0;
			size_t n1 = 1;
			for (int i = 0; i < index.size(); i++)
			{
				n1 = *(index.begin() + i);
				for (int j = 0; j < (this->N - i - 1); j++)
				{
					n1 *= *(this->shape + 1 + i + j);
				}
				n += n1;
			}
			return this->data + n;
		}

		//at method to access individual elements
		T& at(std::initializer_list<size_t> index)
		{
			return *(this->ptrat(index));
		}
		//= overload to assign values to underlying flat array using initializer_list
		void operator=(std::initializer_list<T> data)
		{
			std::copy(data.begin(), data.end(), this->data);
		}

		//= overload to assign values to underlying flat array using data pointer
		void operator=( T* data_ptr)
		{
			std::copy_n(data_ptr, this->numel(), this->data);
		}
	};
}
