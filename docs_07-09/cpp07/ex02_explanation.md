# cpp07/ex02: Array

## 1️⃣ Visão Geral

Desenvolver uma **class template `Array<T>`** com alocação dinâmica, operador `[]` para acesso, tratamento de exceções para bounds-checking e método `size()`. É a progressão natural: de function templates para class templates, introduzindo gerenciamento de memória genérico.

---

## 2️⃣ Conceitos-Chave Aprendidos

- **Class Templates**: Parametrizar tipo E tamanho (`template <typename T, int N>`)
- **Orthodox Canonical Form**: Construtor, cópia, atribuição, destrutor
- **Operador Overloading**: `operator[]` para acesso natural
- **Exception Handling**: `throw std::out_of_range()` para erros
- **RAII**: Alocar no construtor, desalocar no destrutor

---

## 3️⃣ Arquitetura

```
Array.hpp
└── template <typename T, int N>
    class Array
    ├── Constructor: T* _array = new T[N]
    ├── Copy constructor (cópia profunda)
    ├── operator= (atribuição com cópia profunda)
    ├── operator[](int index) com bounds-check
    ├── size() const → retorna N
    └── Destructor: delete[] _array
```

**Fluxo**: Criar array genérico → Acessar com `[]` → Exceção se fora dos limites.

---

## 4️⃣ Exemplo Prático Mínimo

```cpp
#ifndef ARRAY_HPP
#define ARRAY_HPP
#include <stdexcept>

template <typename T, int N>
class Array {
private:
    T* _array;

public:
    Array() : _array(new T[N]) {}
    
    Array(const Array& other) : _array(new T[N]) {
        for (int i = 0; i < N; ++i)
            _array[i] = other._array[i];
    }
    
    Array& operator=(const Array& other) {
        if (this != &other) {
            for (int i = 0; i < N; ++i)
                _array[i] = other._array[i];
        }
        return *this;
    }
    
    ~Array() { delete[] _array; }
    
    T& operator[](int i) {
        if (i < 0 || i >= N)
            throw std::out_of_range("Index out of bounds");
        return _array[i];
    }
    
    int size() const { return N; }
};

#endif
```

Uso:
```cpp
Array<int, 5> arr;
arr[0] = 42;
std::cout << arr.size();  // 5

arr[10];  // Throw std::out_of_range
```

---

## 5️⃣ Considerações Importantes

- ❌ **Proibido STL**: Nenhum `vector` - Penalidade: **-42**
- ✅ **Dois Templates**: `typename T` (tipo) + `int N` (tamanho em tempo de compilação)
- ⚠️ **Orthodox Canonical Form Obrigatório**: Sem cópia = memory leak
- 💡 **Tamanho Fixo em Compilação**: `Array<int, 5>` vs `Array<int, 10>` são tipos diferentes
- 🔧 **Bounds Checking**: `operator[]` DEVE validar índice, lançar exceção

---

## 6️⃣ Checklist de Submissão

- [ ] Compila com `-Wall -Wextra -Werror -std=c++98` sem warnings
- [ ] Array works com múltiplos tipos (`int`, `float`, `std::string`)
- [ ] `operator[]` lança `std::out_of_range` para índices inválidos
- [ ] `size()` retorna tamanho correto
- [ ] Cópia profunda funciona (modificar cópia não afeta original)
- [ ] Include guards presentes
- [ ] Sem STL containers
- [ ] Sem memory leaks
- [ ] `main.cpp` testa acesso válido, inválido e cópia

---

**Anterior**: [ex01 - Iter](./ex01_explanation.md)  
**Próximo Módulo**: [cpp08 - STL Containers & Iterators](../cpp08/ex00_explanation.md)
