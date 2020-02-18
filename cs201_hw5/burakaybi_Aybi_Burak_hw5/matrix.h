#include<iostream>

class Matrix {
	private: 
		int rowNum, columnNum;
		int ** init;
    public:
		 
		Matrix::Matrix();
		Matrix(int r, int c, int in);
		Matrix(const Matrix &matrix);
		~Matrix();
		int getElementAt(int r, int c)const;
		void setElementAt(int r, int c, int value);
		int getRowNumber()const;
		int getColumnNumber()const;
		void print();
		Matrix operator +(const Matrix& matrix);
		Matrix operator -(const Matrix& matrix);
		Matrix operator =(const Matrix&);
		bool operator ==(const Matrix& matrix);
		Matrix operator!();
};

		