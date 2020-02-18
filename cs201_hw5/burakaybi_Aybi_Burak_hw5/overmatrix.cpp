//BURAK AYBI 20712
#include<iostream>
#include "matrix.h"

using namespace std;

Matrix::Matrix()
{
	  rowNum = 0;
	  columnNum = 0;
	  init=NULL;
}


Matrix::Matrix(int r, int c, int in) //Constructor with rowNum, columnNum, init parameters
{

	if(r<=0 || c<=0)
	{
		rowNum=0;
		columnNum=0;
		init=NULL;
	}
	else
	{
	rowNum=r;
	columnNum=c;
	init = new int* [rowNum]; 
		for (int i = 0; i<rowNum; i++) 
			init[i] = new int[columnNum];
	
		for(int i = 0; i < rowNum; i++)
		{
			init[i]=new int [columnNum];
			for(int j = 0; j < columnNum; j++)
	     {
		          init[i][j] = in;
			}
		}
	
	}
		
}

int Matrix::getRowNumber()const
{
	return rowNum;
}

int Matrix::getColumnNumber()const
{
	return columnNum;
}

int Matrix::getElementAt(int r, int c)const
{
	return init[r][c];
}

void Matrix::setElementAt(int r, int c, int value)
{
	 init[r][c]=value;
}




Matrix::Matrix(const Matrix &matrix)  // copy constructor
{ 
	
	rowNum=matrix.getRowNumber(); 
	columnNum=matrix.getColumnNumber();
	init=new int*[rowNum];
	for (int i = 0; i < rowNum; i++)
    {
		init[i]=new int [columnNum];
		for(int j=0; j<columnNum; j++)
			init[i][j] = matrix.init[i][j];
		
    }
	

}

Matrix::~Matrix() //destructor
{
	if(rowNum!=0)
	{
		for(int i =0;i<rowNum;i++)
			delete [] init[i]; 
	
		delete [] init;
	}
	init=NULL;
	rowNum=0;
	columnNum=0;
}

void Matrix::print() //print function in main.cpp
{
	for(int i=0; i<rowNum; i++)
	{
		
		for(int j=0; j<columnNum; j++)
		{
			cout<<init[i][j];
			cout<<" ";
		}
		cout<<endl;
	}
}
 Matrix Matrix::operator +(const Matrix& matrix) //overloading operator +
    {
        
		Matrix new_Matrix(matrix.getRowNumber(), matrix.getColumnNumber(),0);
		for(int i = 0; i < rowNum; i++)
        {
			for(int j = 0; j < columnNum; j++)
            {
				new_Matrix.init[i][j] = this->init[i][j] + matrix.init[i][j];
            }
        }
		return new_Matrix;
    }

Matrix Matrix::operator=(const Matrix &matrix)  // overloading operator =
{
	//I delete matrix 
			
	if(rowNum!=0)
	{
		for(int i =0;i<rowNum;i++)
			delete [] init[i]; 
	
		delete [] init;
	}
	init=NULL;
	rowNum=0;
	columnNum=0;
	//then creating matrix which is new and give values to matrix
	rowNum=matrix.getRowNumber();
	columnNum=matrix.getColumnNumber();
	init=new int*[rowNum];
	for(int i=0; i<rowNum;i++)
	{
		init[i]=new int[columnNum];
		for(int j=0; j<columnNum;j++)
			init[i][j]=matrix.getElementAt(i,j);
	}
	return *this;
}
   


Matrix Matrix::operator -(const Matrix& matrix) //overloading operator -
    {
		Matrix new_matrix(matrix.getRowNumber(), matrix.getColumnNumber(),0);
		for(int i = 0; i < rowNum; i++)
        {
			for(int j = 0; j < columnNum; j++)
            {
				new_matrix.init[i][j] = init[i][j] - matrix.init[i][j];
            }
        }
        return new_matrix;
    }

 bool Matrix::operator ==(const Matrix &matrix) //overloading operator ==
    {
			for(int i = 0; i < matrix.getRowNumber(); i++)
			{
				for(int j = 0; j < matrix.getColumnNumber(); j++)
				{
					if(init[i][j] != matrix.init[i][j])
					    return false;
					else 
						break;
				}
			}
		return true;
    }

Matrix Matrix::operator!() //overloading operator !(transpose)
	{
		Matrix matrix(rowNum, columnNum,0);
		for(int i = 0; i < matrix.getRowNumber(); i++)
        {
			for(int j = 0; j < matrix.getColumnNumber(); j++)
            {
                matrix.init[j][i] =init[i][j];
            }
        }
        return matrix;
    }

