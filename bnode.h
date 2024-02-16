/***********************************************************************
 * Header:
 *    BINARY NODE
 * Summary:
 *    One node in a binary tree (and the functions to support them).
 *      __      __     _______        __
 *     /  |    /  |   |  _____|   _  / /
 *     `| |    `| |   | |____    (_)/ /
 *      | |     | |   '_.____''.   / / _
 *     _| |_   _| |_  | \____) |  / / (_)
 *    |_____| |_____|  \______.' /_/
 *
 *    This will contain the class definition of:
 *        BNode         : A class representing a BNode
 *    Additionally, it will contain a few functions working on Node
 * Author
 *       Andre Regino & Marco Varela
 ************************************************************************/

#pragma once

#include <iostream>  // for OFSTREAM
#include <cassert>

/*****************************************************************
 * BNODE
 * A single node in a binary tree.  Note that the node does not know
 * anything about the properties of the tree so no validation can be done.
 *****************************************************************/
template <class T>
class BNode
{
public:
   // 
   // Construct
   //
   BNode(): pLeft(nullptr), pRight(nullptr), pParent(nullptr), data(T())
   {
   
   }
   BNode(const T &  t): pLeft(nullptr), pRight(nullptr), pParent(nullptr), data(t)
   {
      
   }
   BNode(T && t) : pLeft(nullptr), pRight(nullptr), pParent(nullptr), data(std::move(t))
   {
      
   }

   //
   // Data
   //
   BNode <T> * pLeft;
   BNode <T> * pRight;
   BNode <T> * pParent;
   T data;
};

/*******************************************************************
 * SIZE BTREE
 * Return the size of a b-tree under the current node
 *******************************************************************/
template <class T>
inline size_t size(const BNode <T> * p)
{
   // Check if we just passed a leaf
   if (p == nullptr)
      return 0;
   
   else
      
      // Use recurssion and add current node
      return size(p->pLeft) + size(p->pRight) + 1 ;
}


/******************************************************
 * ADD LEFT
 * Add a node to the left of the current node
 ******************************************************/
template <class T>
inline void addLeft(BNode <T> * pNode, BNode <T> * pAdd)
{
   // Connect parent to child
   pNode->pLeft = pAdd;
   
   // Connect child to parent
   pAdd->pParent = pNode;
}

/******************************************************
 * ADD RIGHT
 * Add a node to the right of the current node
 ******************************************************/
template <class T>
inline void addRight (BNode <T> * pNode, BNode <T> * pAdd)
{
   // Connect parent to child
   pNode->pRight = pAdd;
   
   // Connect child to parent
   pAdd->pParent = pNode;
}

/******************************************************
 * ADD LEFT
 * Add a node to the left of the current node
 ******************************************************/
template <class T>
inline void addLeft (BNode <T> * pNode, const T & t) 
{
   // Create node to add
   BNode<T> * pAdd = new BNode<T> (t);
   
   // Connect node to parent
   pAdd->pParent = pNode;
   
   // Connect parent to child
   pNode->pLeft = pAdd;
}

template <class T>
inline void addLeft(BNode <T>* pNode, T && t)
{
   // Create node to add
   BNode<T> * pAdd = new BNode<T> (std::move(t));
   
   // Connect node to parent
   pAdd->pParent = pNode;
   
   // Connect parent to child
   pNode->pLeft = pAdd;
}

/******************************************************
 * ADD RIGHT
 * Add a node to the right of the current node
 ******************************************************/
template <class T>
void addRight (BNode <T> * pNode, const T & t)
{
   // Create node to add
   BNode<T> * pAdd = new BNode<T> (t);
   
   // Connect node to parent
   pAdd->pParent = pNode;
   
   // Connect parent to child
   pNode->pRight = pAdd;
}

template <class T>
void addRight(BNode <T>* pNode, T && t)
{
   // Create node to add
   BNode<T> * pAdd = new BNode<T> (std::move(t));
   
   // Connect node to parent
   pAdd->pParent = pNode;
   
   // Connect parent to child
   pNode->pRight = pAdd;
}

/*****************************************************
 * DELETE BINARY TREE
 * Delete all the nodes below pThis including pThis
 * using postfix traverse: LRV
 ****************************************************/
template <class T>
void clear(BNode <T> * & pThis)
{
   if (pThis == nullptr)
      return;
   
   // Left
   clear(pThis->pLeft);

   // Right
   clear(pThis->pRight);
   
   // Visit
   delete pThis;
   pThis = nullptr;
   
   return;
   
}

/***********************************************
 * SWAP
 * Swap the list from LHS to RHS
 *   COST   : O(1)
 **********************************************/
template <class T>
inline void swap(BNode <T>*& pLHS, BNode <T>*& pRHS)
{
   std::swap(pLHS, pRHS);
}

/**********************************************
 * COPY BINARY TREE
 * Copy pSrc->pRight to pDest->pRight and
 * pSrc->pLeft onto pDest->pLeft
 *********************************************/
template <class T>
BNode <T> * copy(const BNode <T> * pSrc) 
{
   if (pSrc == nullptr)
      return nullptr;
   
   // Visit
   BNode<T> * destination = new BNode<T> (pSrc->data);
   
   // Left
   destination->pLeft = copy(pSrc->pLeft);
   if (destination->pLeft != nullptr)
      
      // Add left's address to parent
      destination->pLeft->pParent = destination;
   
   // Right
   destination->pRight = copy(pSrc->pRight);
   if (destination->pRight != nullptr)
      
      // Add right's address to parent
      destination->pRight->pParent = destination;
   
   return destination;
}

/**********************************************
 * assign
 * copy the values from pSrc onto pDest preserving
 * as many of the nodes as possible.
 *********************************************/
template <class T>
void assign(BNode <T> * & pDest, const BNode <T>* pSrc)
{
   if (pSrc == nullptr)
      clear(pDest);
    
   
   else if (pDest == nullptr && pSrc != nullptr)
   {
      // Visit
      pDest = new BNode<T>(pSrc->data);
      
      // Right
      assign(pDest->pRight, pSrc->pRight);
      if (pDest->pRight != nullptr)
         
         // Add left's address to parent
         pDest->pRight->pParent = pDest;
      
      // Left
      assign(pDest->pLeft, pSrc->pLeft);
      if (pDest->pLeft != nullptr)
         
         // Add left's address to parent
         pDest->pLeft->pParent = pDest;
      
   }
   else if (pDest != nullptr && pSrc != nullptr )
   {
      // Visit
      pDest->data = pSrc->data;
      
      // Right
      assign(pDest->pRight, pSrc->pRight);
      if (pDest->pRight != nullptr)
         
         // Add left's address to parent
         pDest->pRight->pParent = pDest;
      
      // Left
      assign(pDest->pLeft, pSrc->pLeft);
      if (pDest->pLeft != nullptr)
         
         // Add left's address to parent
         pDest->pLeft->pParent = pDest;
   }
   
   return;
}
