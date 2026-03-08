# cpp08/ex02: MutantStack

## 1️⃣ Visão Geral

Adaptar a **classe `std::stack`** (LIFO container) para suportar **iteradores**, criando uma classe `MutantStack` que combina operações de stack com iteração sobre elementos. Aprende adaptadores STL e como estender containers para usos não convencionais.

---

## 2️⃣ Conceitos-Chave Aprendidos

- **std::stack**: Container adaptador (LIFO - Last In First Out)
- **Herança vs Composição**: Stack usa container interno
- **Iteradores Customizados**: Expor iteradores do container interno
- **Container Adaptador**: `stack` wraps `deque` ou `vector` internamente
- **Polimorfismo**: Mesma interface para iteração

---

## 3️⃣ Arquitetura

```
MutantStack.hpp
└── template <typename T>
    class MutantStack : public std::stack<T>
    ├── Herda de std::stack<T>
    ├── Expõe iterator via c.begin() (acesso a container interno)
    ├── Expõe iterator fim via c.end()
    └── Mantém operações push/pop/top normais
```

**Padrão**: Stack normal + iteradores para acesso linear aos elementos.

---

## 4️⃣ Exemplo Prático Mínimo

```cpp
#ifndef MUTANTSTACK_HPP
#define MUTANTSTACK_HPP
#include <stack>

template <typename T>
class MutantStack : public std::stack<T> {
public:
    typedef typename std::stack<T>::container_type::iterator iterator;
    typedef typename std::stack<T>::container_type::const_iterator const_iterator;
    
    iterator begin() {
        return this->c.begin();
    }
    
    iterator end() {
        return this->c.end();
    }
    
    const_iterator begin() const {
        return this->c.begin();
    }
    
    const_iterator end() const {
        return this->c.end();
    }
};

#endif
```

Uso:
```cpp
MutantStack<int> mstack;
mstack.push(5); mstack.push(17); mstack.push(3);

for (MutantStack<int>::iterator it = mstack.begin(); 
     it != mstack.end(); ++it) {
    std::cout << *it << std::endl;  // Itera: 5, 17, 3
}
```

---

## 5️⃣ Considerações Importantes

- ✅ **std::stack**: Usar como base via `public` herança
- ✅ **Acesso ao Container Interno**: `this->c` para acessar deque/vector
- ⚠️ **Iteradores Typedefs**: Definir `iterator` e `const_iterator` corretamente
- 💡 **Não Quebra Selagens**: Ainda é stack (push/pop funcionam)
- 🔧 **Padrão Estranho Útil**: Permite debug e usos inesperados

---

## 6️⃣ Checklist de Submissão

- [ ] Compila com `-Wall -Wextra -Werror -std=c++98` sem warnings
- [ ] Herda corretamente de `std::stack<T>`
- [ ] `push()`, `pop()`, `top()` funcionam como stack normal
- [ ] `begin()` e `end()` retornam iteradores válidos
- [ ] Iteradores permitem percorrer todos os elementos
- [ ] Iteradores `const` funcionam corretamente
- [ ] Include guards + sem `using namespace std`
- [ ] Sem memory leaks
- [ ] `main.cpp` testa push, pop, iteração em ordem

---

**Anterior**: [ex01 - Span](./ex01_explanation.md)  
**Próximo Módulo**: [cpp09 - STL Advanced](../cpp09/ex00_explanation.md)
