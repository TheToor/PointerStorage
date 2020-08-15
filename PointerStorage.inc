enum {
    INTEGER,
    FLOAT,
    STRING,
    BOOLEAN,
    ARRAY,
    ARRAY_FLOAT
};
/*
    Function createClass
    Return Pointer to class
    Parameter
    String (Name of class)
*/
native createClass(const className[]);
/*
    Function addAttribute
    Return values:
    0: class not found (invalid pointer)
    1: success
    Parameter
    Integer (Pointer to class)
    Integer (Type of attribute)
    String (Name of attribute)
*/
native addAttribute(classPtr, attType, const attrName[]);
/*
    Function attributeExists
    Return values:
    -1: class not found (invalid pointer)
    0: attribute doesn't exist
    1: attribute exists
    Parameter
    Integer (Pointer to class)
    String (Name of attribute)
*/
native attributeExists(classPtr, const attrName[]);
/*
    Function createEntity
    Return values:
    0: class not found (invalid pointer)
    > 0: pointer to entity
    Parameter
    Integer (Pointer to class)
*/
native createEntity(classPtr);
/*
    Function setEntityValue
    Return values:
    -1: entity not found (invalid pointer)
    0: invalid attribute
    1: success
    Parameter
    Integer (Pointer to entity)
    String (Name of attribute)
    Any (Only one value)
*/
native setEntityValue(entityPtr, const attrName[], { _,Float }:...);
/*
    Function getEntityValue
    Return values:
    -2: invalid default value
    -1: entity not found (invalid pointer)
    0: invalid attribute
    1: success
    Parameter
    Integer (Pointer to entity)
    String (Name of attribute)
    Any (Only one value as reference)
*/
native getEntityValue(entityPtr, const attrName[], { _,Float }:...);
/*
    Function cloneEntity
    Return values:
    0: entity not found (invalid pointer)
    > 0: new pointer to entity
    Parameter
    Integer (Pointer to entity)
*/
native cloneEntity(entityPtr);
/*
    Function deleteEntity
    Return values:
    0: fail
    1: success
    Parameter
    Integer (Pointer to entity)
*/
native deleteEntity(entityPtr);
/*
    Function findEntities
    Return values:
    -1: invalid entity pointer
    0: attributes <> values
    > 0: pointer to list
    Parameter
    Integer (Pointer to class)
    Any (arguments and values: key, value, ...)
*/
native findEntities(classPtr, { _,Float }:...);
/*
    Function findEntitiesOr
    Return values:
    -1: invalid entity pointer
    0: attributes <> values
    > 0: pointer to list
    Parameter
    Integer (Pointer to class)
    Any (arguments and values: key, value, ...)
*/
native findEntitiesOr(classPtr, { _,Float }:...);
/*
native findEntitiesPos(clssPtr, const attrName[], Float:x, Float:y, Float:z, Float:range);
    Function findEntitiesOr
    Return values:
    -1: invalid entity pointer
    -2: invalid attributename
    > 0: pointer to list
    Parameter
    Integer (Pointer to class)
    X, Y, Z, Range: Position and Range
*/
native findEntitiesPos(clssPtr, const attrName[], Float:x, Float:y, Float:z, Float:range);
/*
    Function createList
    Return values:
    0: Invalid datatype
    > 0: pointer to list
    Parameter
    Integer (Datatype ? integer)
*/
native createList(type = INTEGER);
/*
    Function addListItem
    Return values:
    -1: Invalid datatype (internal error)
    0: Invalid pointer to list
    1: success
    Parameter
    Integer (Pointer to list)
    Any (values)
*/
native addListItem(listPtr, { _,Float }:...);
/*
    Function listCount
    Return values:
    -1: Invalid pointer to list
    >= 0: number of elements
    Parameter
    Integer (Pointer to list)
*/
native listCount(listPtr);
/*
    Function listValueByIndex
    Return values:
    -2: Index >= number of elements
    -1: Invalid pointer to list
    0: Invalid datatype (internal error)
    1: success
    Parameter
    Integer (Pointer to list)
    Integer: Index of element
    Any: Value as reference
*/
native listValueByIndex(listPtr, index, { _,Float }:...);
/*
    Function setListValueByIndex
    Return values:
    -2: Index >= number of elements
    -1: Invalid pointer to list
    0: Invalid datatype (internal error)
    1: success
    Parameter
    Integer (Pointer to list)
    Integer: Index of element
    Any: Value
*/
native setListValueByIndex(listPtr, index, { _,Float }:...);
/*
    Function clearList
    Return values:
    0: Invalid pointer to list
    1: success
    Parameter
    Integer (Pointer to list)
*/
native clearList(listPtr);
/*
    Function removeListItem
    Return values:
    -1: Invalid pointer to list 
    0: Index >= number of elements
    1: success
    Parameter
    Integer (Pointer to list)
    Integer (Index of element)
*/
native removeListItem(listPtr, index);
/*
    Function combineLists
    Return values:
    0: List can't be found
    > 0: Pointer to new List
    Parameter
    Integer (Pointer to list)
    Integer (Pointer to list)
*/
native combineLists(listPtr, listPtr2);
/*
    Function existsEntityByClass
    Return Types
    1:      Entity exists in class
    0:      Entity do not exists in class or class do not exists
    Parameter:
    Int (Pointer to class)
    Int (Pointer to entity)
*/
native existsEntityByClass(classPtr, entityPtr);
/*
    Function existsEntity
    Return Types
    1:      Entity exists
    0:      Entity do not exists
    Parameter:
    Int (Pointer to entity)
*/
native existsEntity(classPtr);
/*
    Function getEntityList
    Return Types
    0:      class does not exists
    > 0:    Pointer to list of pointers of entities
    Parameter:
    Int (Pointer to class)
*/
native getEntityList(classPtr);