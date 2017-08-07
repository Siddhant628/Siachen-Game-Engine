# Siachen Game Engine

Siachen is a **cross-platform, data driven game engine in C++ 11** I worked on as an individual project through a semester at [FIEA, University of Central Florida](https://fiea.ucf.edu/).

## Features
- Custom replacements for STL containers such as **linked list**, **hashmap** and **vector**.
- Implemented a custom **RTTI** to move up and down the inheritance tree.
- Support for an **XML parser** which uses **chain of responsibility** pattern to parse XML data as a scrpiting language. Implemented various parser helpers to parse primitives, actions, events, tables, entities, sectors and worlds.
- Implemented **factory pattern** to support creating of objects through XML files in order to use it as a configuration language.
- Support for an **asynchronous event system** which can deliver and queue events asynchronously. It is based on the **observer** design pattern.

## Architecture
- Implemented **Datum**, a runtime polymorphic container which is similar to the STL vector. However, unlike a vector, its type is defined at run time and it can store values of certain user-defined types.
- Implemented **Scope**, which is the second piece of the data subsystem which forms a dynamic hierarchical database. Scopes are tables which store name-value pairs with datum objects as the values. (Scope and datum are a recursive pair where datums can contain other scopes / tables)
- Implemented **Attributed Scope**, which provide support to scopes to represent something concrete. Attributed scopes have their own attributes (key-value pairs) which could be either associated with the members of their instances or specific data associated with some key within their table.
- Implemented **Entity**, a wrapper for an attributed table whose table gets populated at compile time based on the known information.
- Implemented **Sector**, a class which segments the world into various chunks called sectors. A sector essentially is an attributed scope which manages certain entities in isolation from another set of entities in another sector.
- Implemented **World**, the scope which contains all other scopes, i.e. the parent scope within which the entire simulation is contained.
- Implemented **Action**, attributed scopes which affect the state of the scopes containing them (when their update method is called). Implemented various actions which affect their associated scopes in specific ways.
