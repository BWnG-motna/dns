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
	T    const * pData ;
	Node * pPrev ;
	Node * pNext ;

public :
	T    const * GetData() const ;
	Node * GetPrev() const ;
	Node * GetNext() const ;

public :
	void SetData( T const * pDat ) ;
	void SetPrev( Node * pNode ) ;
	void SetNext( Node * pNode ) ;
	
public :
	 Node() ;
	 Node( T const * pDat ) ;
	~Node() ;

} ; // class Node
	

}   // namespace ds

}   // namespace daniel