# cpp08/ex00: Easy find

## 1️⃣ Visão Geral

Implementar uma **function template `easyfind`** que busca a primeira ocorrência de um inteiro em um container STL genérico de inteiros. É o primeiro exercício de cpp08, marcando a transição: STL agora é **obrigatório**. Aprende a trabalhar com iteradores e algoritmos básicos.

---

## 2️⃣ Conceitos-Chave Aprendidos

- **STL Containers Genéricos**: `vector<int>`, `list<int>`, `deque<int>`, etc.
- **Iteradores**: Abstração sobre "apontador" para elemento
- **std::find()**: Algoritmo STL para busca linear
- **Exceções STL**: Lançar exceção quando valor não encontrado
- **Polimorfismo via Templates**: Mesma função para containers diferentes

---

## 3️⃣ Arquitetura

```
easyfind.hpp
└── template <typename T>
    typename T::iterator easyfind(T& container, int value)
    ├── Usa std::find(container.begin(), container.end(), value)
    ├── Se encontrado → retorna iterator
    └── Se não encontrado → throw std::exception
```

**Padrão**: Algoritmo agnóstico do container, itera genericamentecom iteradores.

---

## 4️⃣ Exemplo Prático Mínimo

```cpp
#ifndef EASYFIND_HPP
#define EASYFIND_HPP
#include <algorithm>
#include <stdexcept>

template <typename T>
typename T::iterator easyfind(T& container, int value) {
    typename T::iterator it = std::find(container.begin(), 
                                        container.end(), 
                                        value);
    if (it == container.end())
        throw std::exception();
    return it;
}

#endif
```

Uso:
```cpp
std::vector<int> v;
v.push_back(1); v.push_back(2); v.push_back(3);

std::vector<int>::iterator result = easyfind(v, 2);
std::cout << *result;  // 2

easyfind(v, 42);  // throw std::exception
```

---

## 5️⃣ Considerações Importantes

- ✅ **STL Obrigatório**: Usar `std::find()` para busca
- ✅ **Containers Suportados**: `vector`, `list`, `deque` - todos funcionam
- ⚠️ **Tipo Iterator**: `typename T::iterator` é a assinatura correta
- 💡 **Exception vs Error**: Lançar exceção é seguro, não retornar código de erro
- 🔧 **Genérico**: Mesma função para `vector` vs `list` vs `deque`

---

## 6️⃣ Checklist de Submissão

- [ ] Compila com `-Wall -Wextra -Werror -std=c++98` sem warnings
- [ ] Funciona com `std::vector<int>`, `std::list<int>`, `std::deque<int>`
- [ ] Retorna iterator válido quando valor encontrado
- [ ] Lança exceção quando valor NÃO encontrado
- [ ] Include guards presentes
- [ ] Sem `using namespace std`
- [ ] Sem memory leaks
- [ ] `main.cpp` testa múltiplos containers e casos de erro

---

**Anterior (cpp07)**: [cpp07/ex02 - Array](../cpp07/ex02_explanation.md)  
**Próximo**: [ex01 - Span](./ex01_explanation.md)
