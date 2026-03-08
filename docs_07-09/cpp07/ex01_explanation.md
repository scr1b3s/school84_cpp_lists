# cpp07/ex01: Iter

## 1️⃣ Visão Geral

Implementar uma **function template `iter`** que aplica uma função a cada elemento de um array (padrão similar a `map` ou `forEach` em linguagens funcionais). Aprende a combinar templates com ponteiros de função/functores, base para algoritmos STL que virão em cpp08.

---

## 2️⃣ Conceitos-Chave Aprendidos

- **Ponteiros de Função**: Passar função como argumento (`void (*func)(T&)`)
- **Templates com Múltiplos Parâmetros**: `T` para tipo, tamanho de array, função
- **Callbacks**: Padrão de invocar função fornecida pelo usuário
- **Generalização de Iteração**: Abstrair o loop repetitivo

---

## 3️⃣ Arquitetura

```
iter.hpp
└── template <typename T, typename Func>
    void iter(T* array, int length, Func func)
    ├── Recebe array, tamanho e função
    ├── Loop for (int i = 0; i < length; ++i)
    └── Chama func(array[i]) para cada elemento
```

**Padrão**: Função aplicadora genérica + callback customizado.

---

## 4️⃣ Exemplo Prático Mínimo

```cpp
#ifndef ITER_HPP
#define ITER_HPP
#include <iostream>

template <typename T, typename Func>
void iter(T* array, int length, Func func) {
    for (int i = 0; i < length; ++i) {
        func(array[i]);
    }
}

// Funções callback utilitárias
template <typename T>
void print(const T& x) {
    std::cout << x << std::endl;
}

#endif
```

Uso:
```cpp
int arr[] = {1, 2, 3, 4, 5};
iter(arr, 5, print<int>);  // Imprime cada elemento

// Ou com classe template
class Square {
public:
    void operator()(int& x) const { x = x * x; }
};

int nums[] = {1, 2, 3};
iter(nums, 3, Square());  // Eleva ao quadrado
```

---

## 5️⃣ Considerações Importantes

- ❌ **Proibido STL**: Nenhum `vector`, `algorithm` - Penalidade: **-42**
- ✅ **Ponteiros de Função**: `T*` para array, `Func func` para callback
- ⚠️ **Template sobre Função**: Compilador deduz tipo da função automaticamente
- 💡 **Uso com Classes Função**: Classes com `operator()` funcionam como callbacks
- 🔧 **Ordem de Parâmetros**: Array, tamanho, DEPOIS a função (mais natural)

---

## 6️⃣ Checklist de Submissão

- [ ] Compila com `-Wall -Wextra -Werror -std=c++98` sem warnings
- [ ] `iter()` funciona com arrays de tipos diferentes (`int`, `double`, `std::string`)
- [ ] Callbacks funcionam: funções template + classes com `operator()`
- [ ] Include guards presentes
- [ ] Sem STL containers ou algoritmos
- [ ] Sem memory leaks
- [ ] `main.cpp` demonstra múltiplas callbacks em diferentes tipos

---

**Anterior**: [ex00 - Start with a few functions](./ex00_explanation.md)  
**Próximo**: [ex02 - Array](./ex02_explanation.md)
