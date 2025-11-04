[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/7RAFczHS)
# Project 4 - HashTable

Project description can be found [in the repo](Project4_HashTable.pdf)

Place your complexity analysis below.

---

Time complexity:
Since O is the worst case, they should all have a time complexity of n. 
Insert: If there was a collision for every single insert, it would be O(n) as it would have to deal with every collision in sequence.
Remove: If there was a collision every time it check the key, up until all keys were checked, it would be be O(n).
Contains: Same as remove, if it had a collision with every check, it would be O(n).
Get: If it had to iterate through every key having a collision to finish the method, it would result in O(n).
operator[]: Copies the same logic as Get, so O(n).
