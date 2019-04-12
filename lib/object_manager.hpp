#ifndef __OBJECT_MANAGER_H__
#define __OBJECT_MANAGER_H__

#include <iostream>
#include <vector>
#include <string>

template <class ObjectType>
class ObjectManager{
	private:
		std::vector<ObjectType> Items;
	public:
		unsigned long int size(void){return Items.size();}
		ObjectType *Get(int i){return &Items[i];}
		void DeleteById(std::string pId){

			int indexToDelete = -1;
			for (int i = 0; i < Items.size(); ++i)
			{
				if(Items[i].getId() == pId){
					indexToDelete = i;
					break;
				}
			}
			
			if(indexToDelete >= 0 && indexToDelete < Items.size()){
				Items.erase(Items.begin() + indexToDelete);
			}

		}
		std::vector<std::string> Find(std::string pSearchId){

			std::vector<std::string> returnValue;
	
			for (int i = 0; i < Items.size(); ++i)
			{
				if(Items[i].getId().find(pSearchId) != std::string::npos){
					returnValue.push_back(Items[i].getId());
				}
			}

			return returnValue;

		}
		ObjectType* Get(std::string pId){
	
			ObjectType *returnValue = NULL;
            
			for (int i = 0; i < Items.size(); ++i)
			{
				if(Items[i].getId() == pId){
					returnValue = &Items[i];
					break;
				}
			}
			return returnValue;

		}
		void Add(ObjectType pObject){
			Items.push_back(pObject);
		}
		ObjectType *Add(std::string pId){

			ObjectType itemObject(pId);
			
			Items.push_back(itemObject);
			
			unsigned long int lastItem = Items.size() - 1;
			
			//if(lastItem >= 0)
				return &Items[lastItem];
			
			//return NULL;

		}
		ObjectManager(){

		}
		~ObjectManager(){

		}
};

/*********************************************************/
/*********IMPLEMENTACION DE LA CLASE CON PUNTEROS*********/
/*********************************************************/

template <class ObjectType>
class ObjectManager<ObjectType *>{
	private:
		std::vector<ObjectType *> Items;
	public:
		int size(void){return Items.size();}
		ObjectType *Get(int i){return Items[i];}
		void DeleteById(std::string pId){
			int indexToDelete = -1;
			for (int i = 0; i < Items.size(); ++i)
			{
				if(Items[i]->getId() == pId){
					indexToDelete = i;
					break;
				}
			}
			if(indexToDelete >= 0 && indexToDelete < Items.size()){
				Items.erase(Items.begin() + indexToDelete);
			}
		}
		std::vector<std::string> Find(std::string pSearchId){

			std::vector<std::string> returnValue;
			for (int i = 0; i < Items.size(); ++i)
			{
				if(Items[i]->getId().find(pSearchId) != std::string::npos){
					returnValue.push_back(Items[i]->getId());
				}
			}
			return returnValue;

		}
		ObjectType* Get(std::string pId){

			ObjectType *returnValue = NULL;
            
			for (int i = 0; i < Items.size(); ++i)
			{
				if(Items[i]->getId() == pId){
					returnValue = Items[i];
					break;
				}
			}
			return returnValue;

		}
		void Add(ObjectType *pObject){
			Items.push_back(pObject);
		}
		ObjectManager(){

		}
		~ObjectManager(){

		}
};

#endif
