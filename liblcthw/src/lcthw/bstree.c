#include <lcthw/dbg.h>
#include <lcthw/bstree.h>
#include <stdlib.h>
#include <lcthw/bstrlib.h>
#include <assert.h>

static int default_compare(void *a, void *b)
{
	 return bstrcmp((bstring)a, (bstring)b);
}


BSTree *BSTree_create(BSTree_compare compare)
{
	 BSTree *map = calloc(1, sizeof(BSTree));
	 check_mem(map);

	 map->compare = compare == NULL ? default_compare : compare;

	 return map;

error:
	 if(map) {
		  BSTree_destroy(map);
	 }
	 return NULL;
}

static int BSTree_destroy_cb(BSTreeNode *node)
{
	 assert(node != NULL && "Cannot destroy NULL node.");
	 
	 free(node);
	 return 0;
}


void BSTree_destroy(BSTree *map)
{
	 if(map) {
		  BSTree_traverse(map, BSTree_destroy_cb);
		  free(map);
	 }
}

static inline BSTreeNode *BSTreeNode_create(BSTreeNode *parent, void *key, void *data)
{
	 assert(key != NULL && "Key cannot be NULL");
	 assert(data != NULL && "Data cannot be NULL.");
	 
	 BSTreeNode *node = calloc(1, sizeof(BSTreeNode));
	 check_mem(node);

	 node->key = key;
	 node->data = data;
	 node-> parent = parent;
	 return node;
	 
error:
	 return NULL;
}


static inline void BSTree_setnode(BSTree *map, BSTreeNode *node, void *key, void *data)
{
	 assert(map != NULL && "Tree cannot be NULL when setting nodes.");
	 assert(node != NULL && "Node to set cannot be NULL.");
	 assert(key != NULL && "Key to set cannot be NULL.");
	 assert(data != NULL && "Data to set cannot be NULL.");
	 
	 int cmp = map->compare(node->key, key);

	 if(cmp <= 0) {
		  if(node->left) {
			   BSTree_setnode(map, node->left, key, data);
		  } else {
			   node->left = BSTreeNode_create(node, key, data);
		  }
	 } else {
		  if(node->right) {
			   BSTree_setnode(map, node->right, key, data);
		  } else {
			   node->right = BSTreeNode_create(node, key, data);
		  }
	 }
}


int BSTree_set(BSTree *map, void *key, void *data)
{
	 assert(map != NULL && "Cannot set NULL tree.");
	 assert(key != NULL && "Key to set cannot be NULL.");
	 assert(data != NULL && "Data to set cannot be NULL.");
	 
	 if(map->root == NULL) {
		  // first so just make it and get out
		  map->root = BSTreeNode_create(NULL, key, data);
		  check_mem(map->root);
	 } else {
		  BSTree_setnode(map, map->root, key, data);
	 }

	 return 0;
error:
	 return -1;
}

static inline BSTreeNode *BSTree_getnode(BSTree *map, BSTreeNode *node, void *key)
{
	 assert(map != NULL && "Tree cannot be NULL when getting nodes.");
	 assert(node != NULL && "Node to get cannot be NULL.");
	 assert(key != NULL && "Key to look for cannot be NULL.");
	 
	 int cmp = map->compare(node->key, key);

	 if(cmp == 0) {
		  return node;
	 } else if(cmp < 0) {
		  if(node->left) {
			   return BSTree_getnode(map, node->left, key);
		  } else {
			   return NULL;
		  }
	 } else {
		  if(node->right) {
			   return BSTree_getnode(map, node->right, key);
		  } else {
			   return NULL;
		  }
	 }
}

void *BSTree_get(BSTree *map, void *key)
{
	 assert(map != NULL && "Tree to obtain cannot be NULL.");
	 assert(key != NULL && "Key to obtain cannot be NULL.");
	 
	 if(map->root == NULL) {
		  return NULL;
	 } else {
		  BSTreeNode *node = BSTree_getnode(map, map->root, key);
		  return node == NULL ? NULL : node->data;
	 }
}

static inline BSTree_traverse_nodes(BSTreeNode *node, BSTree_traverse_cb traverse_cb)
{
	 assert(node != NULL && "Node during traversal cannot be NULL.");
	 int rc = 0;

	 if(node->left) {
		  rc = BSTree_traverse_nodes(node->left, traverse_cb);
		  if(rc != 0)  return rc;
	 }

	 if(node->right) {
		  rc = BSTree_traverse_nodes(node->right, traverse_cb);
		  if(rc != 0) return rc;
	 }

	 return traverse_cb(node);
}

int BSTree_traverse(BSTree *map, BSTree_traverse_cb traverse_cb)
{
	 assert(map != NULL && "Tree to traverse cannot be NULL");
	 
	 if(map->root) {
		  return BSTree_traverse_nodes(map->root, traverse_cb);
	 }

	 return 0;
}

static inline BSTreeNode *BSTree_find_min(BSTreeNode *node)
{
	 assert(node != NULL && "Cannot find minimum of NULL node!");
	 
	 while(node->left) {
		  node = node->left;
	 }

	 return node;
}

static inline void BSTree_replace_node_in_parent(BSTree *map, BSTreeNode *node, BSTreeNode *new_value)
{
	 assert(node != NULL && "Node cannot be NULL.");
	 assert(map != NULL && "Tree cannot be NULL");
	 
	 if(node->parent) {
		  if(node == node->parent->left) {
			   node->parent->left = new_value;
		  } else {
			   node->parent->right = new_value;
		  }
	 } else {
		  // this is the root so gotta change it
		  map->root = new_value;
	 }

	 if(new_value) {
		  new_value->parent = node->parent;
	 }
}

static inline void BSTree_swap(BSTreeNode *a, BSTreeNode *b)
{
	 assert(a != NULL && "First node should not be NULL for swap");
	 assert(b != NULL && "Second node shouldn ot be NULL for swap");
	 
	 void *temp = NULL;
	 temp = b->key; b->key = a->key; a->key = temp;
	 temp = b->data; b->data = a->data; a->data = temp;
}

static inline BSTreeNode *BSTree_node_delete(BSTree *map, BSTreeNode *node, void *key)
{
	 assert(map != NULL && "Tree should never be NULL when deleting node");
	 assert(node != NULL && "Current node should never be NULL");
	 
	 int cmp= map->compare(node->key, key);

	 if(cmp < 0) {
		  if(node->left) {
			   return BSTree_node_delete(map, node->left, key);
		  } else {
			   // not found
			   return NULL;
		  }
	 } else if(cmp > 0) {
		  if(node->right) {
			   return BSTree_node_delete(map, node->right, key);
		  } else {
			   // not found
			   return NULL;
		  }
	 } else {
		  if(node->left && node->right) {
			   //swap this node for the smallest node that is bigger than us
			   BSTreeNode *successor = BSTree_find_min(node->right);
			   BSTree_swap(successor, node);

			   // this leaves the old successor with possibly a right child
			   // so replace it with that right child
			   BSTree_replace_node_in_parent(map, successor, successor->right);

			   // finally it's swapped, so return successor instead of node
			   return successor;
		  } else if(node->left) {
			   BSTree_replace_node_in_parent(map, node, node->left);
		  } else if(node->right) {
			   BSTree_replace_node_in_parent(map, node, node->right);
		  } else {
			   BSTree_replace_node_in_parent(map, node, NULL);
		  }

		  return node;
	 }
}

void *BSTree_delete(BSTree *map, void *key)
{
	 assert(map != NULL && "Cannot delete already deleted map.");
	 assert(key != NULL && "Key needs to point to non-NULL value.");
	 
	 void *data = NULL;
	 
	 if(map->root) {
		  BSTreeNode *node = BSTree_node_delete(map, map->root, key);

		  if(node) {
			   data = node->data;
			   free(node);
		  }
	 }

	 return data;
}
