#pragma once


#include "Common.h"


namespace daniel
{
	
namespace ds
{


template < typename T >
class Node 
{

private :
	T    * pData ;
	Node * pPrev ;
	Node * pNext ;

public :
	T    * GetData() const ;
	Node * GetPrev() const ;
	Node * GetNext() const ;

public :
	void SetData( T    * pDat ) ;
	void SetPrev( Node * pNode ) ;
	void SetNext( Node * pNode ) ;
	
public :
	 Node() ;
	 Node( T * pDat ) ;
	~Node() ;

} ; // class Node
	

}   // namespace ds

}   // namespace daniel