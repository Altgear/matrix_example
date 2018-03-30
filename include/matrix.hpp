#include <iostream>

#ifndef MATRIX_T_TMPL_
#define MATRIX_T_TMPL_

template <typename Type>

class matrix_t
{
  private:
	Type **elements_;
	std::size_t rows_;
	std::size_t collumns_;

  public:
	matrix_t();
	matrix_t(matrix_t const &other);
	matrix_t &operator=(matrix_t const &other);
	~matrix_t();

	std::size_t rows() const;
	std::size_t collumns() const;

	matrix_t operator+(matrix_t const &other) const;
	matrix_t operator-(matrix_t const &other) const;
	matrix_t operator*(matrix_t const &other) const;

	matrix_t &operator-=(matrix_t const &other);
	matrix_t &operator+=(matrix_t const &other);
	matrix_t &operator*=(matrix_t const &other);

	std::istream &read(std::istream &stream);
	std::ostream &write(std::ostream &stream);
};

template <typename Type>
matrix_t<Type>::matrix_t() : elements_{nullptr}, rows_{0}, collumns_{0}
{
}

template <typename Type>
matrix_t<Type>::matrix_t(matrix_t<Type> const &other)
{
	rows_ = other.rows_;
	collumns_ = other.collumns_;
	elements_ = new Type *[rows_];
	for (unsigned int i = 0; i < rows_; ++i)
	{
		elements_[i] = new Type[collumns_];
		for (unsigned int j = 0; j < collumns_; ++j)
		{
			elements_[i][j] = other.elements_[i][j];
		}
	}
}

template <typename Type>
matrix_t<Type> &matrix_t<Type>::operator=(matrix_t<Type> const &other)
{
	if (this != &other)
	{
		if (elements_ != nullptr && rows_ && collumns_)
		{
			for (unsigned int i = 0; i < rows_; ++i)
			{
				delete[] elements_[i];
			}
			delete[] elements_;
		}
		rows_ = other.rows_;
		collumns_ = other.collumns_;
		elements_ = new Type *[rows_];
		for (unsigned int i = 0; i < rows_; ++i)
		{
			elements_[i] = new Type[collumns_];
			for (unsigned int j = 0; j < collumns_; ++j)
			{
				elements_[i][j] = other.elements_[i][j];
			}
		}
	}
	return *this;
}

template <typename Type>
matrix_t<Type>::~matrix_t()
{
	for (unsigned int i = 0; i < rows_; ++i)
	{
		delete[] elements_[i];
	}
	delete[] elements_;
}

template <typename Type>
std::size_t matrix_t<Type>::rows() const
{
	return rows_;
}

template <typename Type>
std::size_t matrix_t<Type>::collumns() const
{
	return collumns_;
}

template <typename Type>
matrix_t<Type> matrix_t<Type>::operator+(matrix_t<Type> const &other) const
{
	matrix_t result;
	if (rows_ == other.rows_ && collumns_ == other.collumns_)
	{
		result.rows_ = rows_;
		result.collumns_ = collumns_;
		result.elements_ = new Type *[rows_];
		for (unsigned int i = 0; i < rows_; i++)
		{
			result.elements_[i] = new Type[collumns_];
			for (unsigned int j = 0; j < collumns_; j++)
			{
				result.elements_[i][j] = elements_[i][j] + other.elements_[i][j];
			}
		}
	}
	return result;
}

template <typename Type>
matrix_t<Type> matrix_t<Type>::operator-(matrix_t<Type> const &other) const
{
	matrix_t result;
	if (rows_ == other.rows_ && collumns_ == other.collumns_)
	{
		result.rows_ = rows_;
		result.collumns_ = collumns_;
		result.elements_ = new Type *[rows_];
		for (unsigned int i = 0; i < rows_; i++)
		{
			result.elements_[i] = new Type[collumns_];
			for (unsigned int j = 0; j < collumns_; j++)
			{
				result.elements_[i][j] = elements_[i][j] - other.elements_[i][j];
			}
		}
	}
	return result;
}

template <typename Type>
matrix_t<Type> matrix_t<Type>::operator*(matrix_t<Type> const &other) const
{
	matrix_t result;
	if (collumns_ == other.rows_)
	{
		result.rows_ = rows_;
		result.collumns_ = other.collumns_;
		result.elements_ = new Type *[rows_];
		for (unsigned int i = 0; i < rows_; i++)
		{
			result.elements_[i] = new Type[other.collumns_];
			for (unsigned int j = 0; j < other.collumns_; j++)
			{
				std::size_t sum = 0;
				for (unsigned int k = 0; k < collumns_; k++)
				{
					sum += elements_[i][k] * other.elements_[k][j];
				}
				result.elements_[i][j] = sum;
			}
		}
	}
	return result;
}

template <typename Type>
matrix_t<Type> &matrix_t<Type>::operator-=(matrix_t<Type> const &other)
{
	if (rows_ == other.rows_ && collumns_ == other.collumns_)
	{
		for (unsigned int i = 0; i < rows_; i++)
		{
			for (unsigned int j = 0; j < collumns_; j++)
			{
				elements_[i][j] -= other.elements_[i][j];
			}
		}
	}
	return *this;
}

template <typename Type>
matrix_t<Type> &matrix_t<Type>::operator+=(matrix_t<Type> const &other)
{
	if (rows_ == other.rows_ && collumns_ == other.collumns_)
	{
		for (unsigned int i = 0; i < rows_; i++)
		{
			for (unsigned int j = 0; j < collumns_; j++)
			{
				elements_[i][j] += other.elements_[i][j];
			}
		}
	}
	return *this;
}

template <typename Type>
matrix_t<Type> &matrix_t<Type>::operator*=(matrix_t<Type> const &other)
{
	Type **result;
	if (collumns_ == other.rows_)
	{
		result = new Type *[rows_];
		for (unsigned int i = 0; i < rows_; i++)
		{
			result[i] = new Type[other.collumns_];
			for (unsigned int j = 0; j < other.collumns_; j++)
			{
				std::size_t sum = 0;
				for (unsigned int k = 0; k < collumns_; k++)
				{
					sum += elements_[i][k] * other.elements_[k][j];
				}
				result[i][j] = sum;
			}
		}
		for (std::size_t i = 0; i < rows_; ++i)
		{
			delete[] elements_[i];
		}
		delete[] elements_;
		elements_ = nullptr;

		elements_ = result;
		collumns_ = other.collumns_;
	}
	return *this;
}

template <typename Type>
std::istream &matrix_t<Type>::read(std::istream &stream)
{
	std::size_t rows;
	std::size_t collumns;
	char symbol;

	bool success = true;
	if (stream >> rows && stream >> symbol && symbol == ',' && stream >> collumns)
	{
		Type **elements = new Type *[rows];
		for (std::size_t i = 0; success && i < rows; ++i)
		{
			elements[i] = new Type[collumns];
			for (std::size_t j = 0; j < collumns; ++j)
			{
				if (!(stream >> elements[i][j]))
				{
					success = false;
					break;
				}
			}
		}

		if (success)
		{
			for (std::size_t i = 0; i < rows_; ++i)
			{
				delete[] elements_[i];
			}
			delete[] elements_;

			rows_ = rows;
			collumns_ = collumns;
			elements_ = elements;
		}
		else
		{
			for (std::size_t i = 0; i < rows; ++i)
			{
				delete[] elements[i];
			}
			delete[] elements;
		}
	}
	else
	{
		success = false;
	}

	if (!success)
	{
		stream.setstate(std::ios_base::failbit);
	}

	return stream;
}

template <typename Type>
std::ostream &matrix_t<Type>::write(std::ostream &stream) const
{
	stream << rows_ << ", " << collumns_;
	for (std::size_t i = 0; i < rows_; ++i)
	{
		stream << '\n';
		for (std::size_t j = 0; j < collumns_; ++j)
		{
			stream << elements_[i][j];
			if (j != collumns_ - 1)
			{
				stream << ' ';
			}
		}
	}
	if (collumns_ != rows_)
		stream << '\n';
	return stream;
}
#endif //MATRIX_T_TMPL_