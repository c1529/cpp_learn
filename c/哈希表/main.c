#include "Hashmap.h"

int main() {
	HashMap* map = hashmap_create();

	hashmap_put(map, "liu qiang dong", "zhang ze tian");
	hashmap_put(map, "libai", "qing lian jian ge");
	hashmap_put(map, "lu ming fei", "lu ming ze");
	hashmap_put(map, "libai", "wang zhao jun");

	V value1 = hashmap_get(map, "liu qiang dong");
	V value2 = hashmap_get(map, "liu qiang");
	hashmap_put(map, "liu qiang dong", "JD");
	hashmap_delete(map, "liu qiang dong");

	return 0;
}
