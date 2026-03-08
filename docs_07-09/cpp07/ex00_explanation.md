# cpp07/ex00: Start with a few functions

## 1️⃣ Visão Geral

Implementar 3 **function templates genéricos** (`swap`, `min`, `max`) que funcionam com qualquer tipo de dado compatível com operadores de comparação. Este é o primeiro contato com templates em C++, fundamental para entender como reutilizar código sem sacrificar type safety.

---

## 2️⃣ Conceitos-Chave Aprendidos

- **Templates Genéricos**: Usar `T` como placeholder para qualquer tipo
- **Instanciação Implícita**: Compilador cria versões específicas automaticamente
- **Type Safety em Tempo de Compilação**: Erros de tipo detectados antes da execução
- **Reusabilidade sem STL**: Mesmo padrão usado em containers como `vector<T>`

---

## 3️⃣ Arquitetura

Todos os templates em um header único:

```
whatever.hpp
├── template <typename T> void swap(T& a, T& b)
│   └── Troca valores de dois elementos
│
├── template <typename T> T min(const T& a, const T& b)
│   └── Retorna menor dos dois (ou primeiro se iguais)
│
└── template <typename T> T max(const T& a, const T& b)
    └── Retorna maior dos dois (ou primeiro se iguais)
```

**Fluxo**: Função `main()` chama templates com diferentes tipos (int, float, string) → Compilador instancia automaticamente.

---

## 4️⃣ Exemplo Prático Mínimo

```cpp
#ifndef WHATEVER_HPP
#define WHATEVER_HPP

template <typename T>
void swap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

template <typename T>
T min(const T& a, const T& b) {
    return (a < b) ? a : b;
}

template <typename T>
T max(const T& a, const T& b) {
    return (a > b) ? a : b;
}

#endif
```

Uso:
```cpp
int x = 5, y = 10;
swap(x, y);  // Compilador cria swap<int>(int&, int&)

std::string a = "hello", b = "world";
std::string smaller = min(a, b);  // Compilador cria min<string>(const string&, const string&)
```

---

## 5️⃣ Considerações Importantes

- ❌ **Proibido STL**: Nenhum `vector`, `list`, `algorithm` - Penalidade: **-42**
- ✅ **Templates em .hpp**: Implementação DEVE estar no header (compilador precisa)
- ⚠️ **Include Guards Obrigatórios**: `#ifndef WHATEVER_HPP` evita double inclusion
- 💡 **Sem `using namespace std`**: Colocar `std::` explicitamente
- 🔧 **Operadores Necessários**: Se usar `<`, função precisa suportar (ou será erro de compilação)

---

## 6️⃣ Checklist de Submissão

- [ ] Compila com `-Wall -Wextra -Werror -std=c++98` sem warnings
- [ ] Templates funcionam com múltiplos tipos: `int`, `float`, `char`, `std::string`
- [ ] Include guards presentes em `whatever.hpp`
- [ ] Sem `using namespace std` ou `friend` keyword
- [ ] Sem nenhum STL container ou algoritmo
- [ ] Sem memory leaks
- [ ] `main.cpp` demonstra os 3 templates com vários tipos

---

**Próximo**: [ex01 - Iter](./ex01_explanation.md)
