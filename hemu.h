#pragma once
#include <iostream>
#include <initializer_list>

//Namespace hemu
namespace hemu
{
	//Tensor class for storing dynamically allocated tensor which have elements of generic type
	//T is type of elements and N is Number of dimensions
	template<typename T, size_t N>
	class Tensor
	{
		//private data members for hemu::Tensor
	private:
		//pointer to store shape of Tensor(on heap)
		size_t* shape;

		//pointer to store hemu::Tensor elements(on heap)
		int* data;
	public:
		//returns number of elements of Tensor
		size_t numel() const
		{
			size_t n = 1;
			for (size_t i = 0; i < N; i++)
				n *= *(shape + i);
			return n;
		}

		//returns shape of Tensor
		const size_t* GetShape() const
		{
			return this->shape;
		}

		//default constructor for Tensor
		Tensor()
		{
			this->shape = new size_t[N]{};
			this->data = new T[this->numel()]{};
		}

		//constructor with parameters for Tensor
		Tensor(std::initializer_list<size_t> shape)
		{
			this->shape = new size_t[N]{};
			std::copy(shape.begin(), shape.end(), this->shape);
			this->data = new T[this->numel()]{};
			
		}

		//copy constructor
		Tensor(const Tensor& src)
		{
			this->shape = new size_t[N]{};
			std::copy_n(src.shape, N, src.shape);
			this->data = new T[src.numel()]{};
			std::copy_n(src.data, src.numel(), this->data);
		}

		//destructor
		~Tensor()
		{
			delete[] this->data;
			this->data = nullptr;
			delete[] this->shape;
			this->shape = nullptr;
		}
		//[] for accessing elements of tensor
		/*auto& operator[](size_t index)
		{
			static size_t count = 0;
			static size_t temp = 0;
			std::vector<size_t> s = this->shape;
			for (size_t i = 0; i <= count; i++)
				s[i] = 1;
			size_t n = 1;
			for (size_t i : s)
				n *= i;

			n += temp;
			temp = n;
			Tensor<T, N - 1> dst;
			std::copy(this->data[temp+1], this->data[n], dst.data[0]);
			std::copy(this->shape[count + 1], this->shape.end(), dst.shape[0]);
			return dst;
		}*/

		void operator=(std::initializer_list<int> data)
		{
			std::copy(data.begin(), data.end(), this->data);
		}
	};
}
