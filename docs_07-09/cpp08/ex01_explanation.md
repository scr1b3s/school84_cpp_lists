# cpp08/ex01: Span

## 1️⃣ Visão Geral

Implementar uma **classe `Span`** que armazena até N inteiros e fornece operações para encontrar a menor e maior "span" (distância entre dois números). Aprende a combinar STL containers (`vector`), algoritmos (`sort`, `adjacent_find`, `min_element`) e processamento em escala (10,000+ números).

---

## 2️⃣ Conceitos-Chave Aprendidos

- **std::vector**: Container dinâmico para armazenar múltiplos inteiros
- **std::sort()**: Ordena elementos para otimizar busca
- **std::adjacent_find()**: Encontra ainda primeiro par adjacente
- **std::min_element()**: Encontra menor elemento
- **Iteradores de Range**: `addNumbers(begin, end)` para adicionar em lote
- **Exception Handling**: Exceções próprias para estados inválidos

---

## 3️⃣ Arquitetura

```
Span.hpp / Span.cpp
└── class Span
    ├── Constructor(unsigned int N) → capacity = N
    ├── addNumber(int num) → push para vector (throw se cheio)
    ├── shortestSpan() → ordena, adjacent_find, retorna distância
    ├── longestSpan() → ordena, min/max_element, retorna distância
    └── addNumbers(Iterator begin, Iterator end) → adiciona range
```

**Fluxo**: Adicionar números → Ordena internamente → Calcula spans.

---

## 4️⃣ Exemplo Prático Mínimo

```cpp
#include "Span.hpp"

class SpanException : public std::exception {
public:
    virtual const char* what() const throw() { 
        return "Span exception"; 
    }
};

class Span {
private:
    std::vector<int> _nums;
    unsigned int _n;
public:
    Span(unsigned int n) : _n(n) {}
    
    void addNumber(int num) {
        if (_nums.size() >= _n)
            throw SpanException();
        _nums.push_back(num);
    }
    
    int shortestSpan() {
        if (_nums.size() < 2)
            throw SpanException();
        std::vector<int> sorted(_nums);
        std::sort(sorted.begin(), sorted.end());
        int minSpan = INT_MAX;
        for (size_t i = 0; i < sorted.size() - 1; ++i) {
            minSpan = std::min(minSpan, sorted[i+1] - sorted[i]);
        }
        return minSpan;
    }
    
    int longestSpan() {
        if (_nums.size() < 2)
            throw SpanException();
        return *std::max_element(_nums.begin(), _nums.end()) -
               *std::min_element(_nums.begin(), _nums.end());
    }
};
```

---

## 5️⃣ Considerações Importantes

- ✅ **std::vector** deve ser usado internamente
- ✅ **Algoritmos STL**: `sort`, `adjacent_find`, `min/max_element`
- ⚠️ **Exception Handling**: Exceções próprias ou `std::exception`
- 💡 **Escala**: Testar com 10,000+ números
- 🔧 **addNumbers()**: Permite adicionar intervalo de iterator para intervalo

---

## 6️⃣ Checklist de Submissão

- [ ] Compila com `-Wall -Wextra -Werror -std=c++98` sem warnings
- [ ] `addNumber()` throws quando container cheio
- [ ] `shortestSpan()` retorna distância correta entre números mais próximos
- [ ] `longestSpan()` retorna diferença entre maior e menor
- [ ] `addNumbers(it, it)` funciona com iteradores
- [ ] Testes com 5 números + 10,000 números funcionam
- [ ] Include guards + Orthodox Canonical Form
- [ ] Sem memory leaks
- [ ] Exemplo do subject gera saída exata

---

**Anterior**: [ex00 - Easy find](./ex00_explanation.md)  
**Próximo**: [ex02 - MutantStack](./ex02_explanation.md)
