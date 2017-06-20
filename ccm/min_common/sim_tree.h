#ifndef _TREE_NODE_H
#define _TREE_NODE_H
#include <algorithm>
#include <vector>
template<typename T >
class tree_node
{
public:
	void walk_depth_first() const;
	T& get_node();
	void add_child_node(tree_node* pn);
	void remove_child_node(tree_node* pn);
private:
	T t;
	std::vector<tree_node*> children;
};

template< typename T >
void tree_node<T>::walk_depth_first() const
{

	for ( auto & n: children ) 
	{
		n->walk_depth_first();
	}
}

template< typename T >
T& tree_node<T>::get_node()
{
	return t;
}

template< typename T >
void tree_node<T>::add_child_node(tree_node* pn)
{
	children.push_back(pn);
}

template< typename T >
void tree_node<T>::remove_child_node(tree_node* pn)
{
	remove(children.begin(),children.end(),pn);
}
#endif
