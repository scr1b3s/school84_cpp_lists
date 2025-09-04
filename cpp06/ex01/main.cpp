#include "Serializer.hpp"
#include "Data.hpp"
#include <iostream>
#include <iomanip>

int main()
{
	std::cout << "=== SERIALIZATION/DESERIALIZATION TESTS ===" << std::endl;

	// Test 1: Basic serialization and deserialization
	std::cout << "\n--- Test 1: Basic round-trip conversion ---" << std::endl;
	
	Data originalData(42, "Test Object", 3.14159, true);
	std::cout << "Original data: ";
	originalData.print();
	
	Data* originalPtr = &originalData;
	std::cout << "Original pointer address: " << originalPtr << std::endl;
	
	// Serialize the pointer
	uintptr_t serialized = Serializer::serialize(originalPtr);
	std::cout << "Serialized value: 0x" << std::hex << serialized << std::dec << std::endl;
	
	// Deserialize back to pointer
	Data* deserializedPtr = Serializer::deserialize(serialized);
	std::cout << "Deserialized pointer address: " << deserializedPtr << std::endl;
	
	// Verify they are the same
	std::cout << "Pointers are equal: " << (originalPtr == deserializedPtr ? "YES" : "NO") << std::endl;
	std::cout << "Data content matches: " << (*originalPtr == *deserializedPtr ? "YES" : "NO") << std::endl;
	
	std::cout << "Deserialized data: ";
	deserializedPtr->print();

	// Test 2: Multiple objects serialization
	std::cout << "\n--- Test 2: Multiple objects ---" << std::endl;
	
	Data data1(1, "First", 1.11, true);
	Data data2(2, "Second", 2.22, false);
	Data data3(3, "Third", 3.33, true);
	
	Data* ptrs[] = {&data1, &data2, &data3};
	uintptr_t serializedPtrs[3];
	
	// Serialize all pointers
	for (int i = 0; i < 3; i++)
	{
		serializedPtrs[i] = Serializer::serialize(ptrs[i]);
		std::cout << "Object " << i + 1 << " - Original: " << ptrs[i] 
				  << ", Serialized: 0x" << std::hex << serializedPtrs[i] << std::dec << std::endl;
	}
	
	// Deserialize and verify
	std::cout << "\nDeserialization verification:" << std::endl;
	for (int i = 0; i < 3; i++)
	{
		Data* deserializedPtr = Serializer::deserialize(serializedPtrs[i]);
		std::cout << "Object " << i + 1 << " - Deserialized: " << deserializedPtr 
				  << ", Match: " << (ptrs[i] == deserializedPtr ? "YES" : "NO") << std::endl;
		std::cout << "  ";
		deserializedPtr->print();
	}

	// Test 3: Dynamic allocation
	std::cout << "\n--- Test 3: Dynamic allocation ---" << std::endl;
	
	Data* dynamicData = new Data(99, "Dynamic Object", 99.99, false);
	std::cout << "Dynamic data created at: " << dynamicData << std::endl;
	dynamicData->print();
	
	uintptr_t serializedDynamic = Serializer::serialize(dynamicData);
	Data* deserializedDynamic = Serializer::deserialize(serializedDynamic);
	
	std::cout << "Serialized dynamic data: 0x" << std::hex << serializedDynamic << std::dec << std::endl;
	std::cout << "Deserialized dynamic data at: " << deserializedDynamic << std::endl;
	std::cout << "Dynamic pointers match: " << (dynamicData == deserializedDynamic ? "YES" : "NO") << std::endl;
	
	std::cout << "Deserialized dynamic data: ";
	deserializedDynamic->print();
	
	// Clean up
	delete dynamicData;  // Note: deserializedDynamic points to same memory

	// Test 4: Null pointer handling
	std::cout << "\n--- Test 4: Null pointer handling ---" << std::endl;
	
	Data* nullPtr = NULL;
	uintptr_t serializedNull = Serializer::serialize(nullPtr);
	Data* deserializedNull = Serializer::deserialize(serializedNull);
	
	std::cout << "Original null pointer: " << nullPtr << std::endl;
	std::cout << "Serialized null: 0x" << std::hex << serializedNull << std::dec << std::endl;
	std::cout << "Deserialized null: " << deserializedNull << std::endl;
	std::cout << "Null pointers match: " << (nullPtr == deserializedNull ? "YES" : "NO") << std::endl;

	// Test 5: Address arithmetic demonstration
	std::cout << "\n--- Test 5: Address arithmetic ---" << std::endl;
	
	Data array[3] = {
		Data(1, "Array1", 1.0, true),
		Data(2, "Array2", 2.0, false), 
		Data(3, "Array3", 3.0, true)
	};
	
	for (int i = 0; i < 3; i++)
	{
		Data* ptr = &array[i];
		uintptr_t serialized = Serializer::serialize(ptr);
		Data* deserialized = Serializer::deserialize(serialized);
		
		std::cout << "Array[" << i << "] - Original: " << ptr 
				  << ", Deserialized: " << deserialized 
				  << ", Match: " << (ptr == deserialized ? "YES" : "NO") << std::endl;
	}

	// Test 6: Size and alignment information
	std::cout << "\n--- Test 6: Type information ---" << std::endl;
	
	std::cout << "sizeof(Data): " << sizeof(Data) << " bytes" << std::endl;
	std::cout << "sizeof(Data*): " << sizeof(Data*) << " bytes" << std::endl;
	std::cout << "sizeof(uintptr_t): " << sizeof(uintptr_t) << " bytes" << std::endl;
	std::cout << "Data alignment: " << __alignof__(Data) << " bytes" << std::endl;

	std::cout << "\n=== ALL TESTS COMPLETED ===" << std::endl;
	return 0;
}
