#ifndef LISTS_HPP
#define LISTS_HPP

#include "Array.hpp"
#include "Structure.hpp"
#include "Entity.hpp"

#include <vector>
#include <map>

namespace lscrp {

	class Lists {
	private:
		std::vector<Structure*> m_structureList;
		std::map<int, Entity*> m_entities;
		std::vector<Array*> m_arrays;

		void deleteStructures();
		void deleteEntities();
		void deleteArrays();
	public:
		std::vector<Structure*>* structureList();
		std::map<int, Entity*>* entityList();
		std::vector<Array*>* arrayList();
		void addStructure(Structure*);
		void addEntity(Entity*);
		void addArray(Array*);
		void removeEntity(Entity*);
		void removeArray(Array*);
		bool entityExists(int, Amxstring*);
		bool entityExists(int);
		Array* getEntities(int);


		~Lists();
	};
}

#endif // LISTS_HPP

