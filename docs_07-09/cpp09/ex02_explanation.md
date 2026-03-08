# cpp09/ex02: PmergeMe

## 1️⃣ Visão Geral

Implementar o **algoritmo Ford-Johnson** (merge-insert sort) e compará-lo usando **dois containers diferentes** (`std::vector` e `std::list`). Aprende a encapsular algoritmos, medir performance, e entender trade-offs entre containers. Containers: `std::vector` + `std::list` *(não reutilizáveis em ex00/ex01)*.

---

## 2️⃣ Conceitos-Chave Aprendidos

- **Ford-Johnson Sort**: Algoritmo híbrido (insertion sort + merge sort)
- **std::vector vs std::list**: Acesso O(1) vs inserção O(1)
- **Medição de Performance**: `std::clock()` ou `gettimeofday()`
- **Templating de Algoritmos**: Mesma lógica para containers diferentes
- **Otimização Prática**: Quando usar qual container
- **Validação de Sorting**: Verificar se resultado está ordenado

---

## 3️⃣ Arquitetura

```
PmergeMe [números]
├── 1. Parse argumentos (números positivos inteiros)
├── 2. Copy em std::vector e std::list
├── 3. Para cada container:
│   ├── Medir tempo antes
│   ├── Aplicar Ford-Johnson sort
│   └── Medir tempo depois
├── 4. Validar: ambos ordenados identicamente
└── 5. Output: "Before:", sorted arrays, timing
```

**Fluxo**: Parse → Duplicate → Sort ambos → Measure → Compare.

---

## 4️⃣ Exemplo Prático Mínimo

```cpp
#include <vector>
#include <list>
#include <iostream>
#include <ctime>

template <typename T>
void mergeInsertSort(T& container) {
    // Ford-Johnson: Divide em pares, compara, insere em ordem
    // Implementação simplificada (real usa mais lógica)
    
    // Para vector: usar std::sort
    if (sizeof(container) == sizeof(std::vector<int>))
        std::sort(container.begin(), container.end());
}

int main(int ac, char **av) {
    if (ac < 2) return 1;
    
    std::vector<int> vec;
    std::list<int> lst;
    
    for (int i = 1; i < ac; ++i) {
        int num = std::atoi(av[i]);
        if (num < 0) {
            std::cerr << "Error: negative number" << std::endl;
            return 1;
        }
        vec.push_back(num);
        lst.push_back(num);
    }
    
    std::cout << "Before: ";
    for (size_t i = 0; i < vec.size(); ++i)
        std::cout << vec[i] << " ";
    std::cout << std::endl;
    
    clock_t start = std::clock();
    mergeInsertSort(vec);
    clock_t vecEnd = std::clock();
    
    clock_t lstStart = std::clock();
    mergeInsertSort(lst);
    clock_t lstEnd = std::clock();
    
    std::cout << "After: ";
    for (std::vector<int>::iterator it = vec.begin(); 
         it != vec.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;
    
    std::cout << "Time to process " << vec.size() 
              << " elements with std::vector: " 
              << (double)(vecEnd - start) / CLOCKS_PER_SEC 
              << "us" << std::endl;
    
    std::cout << "Time to process " << vec.size() 
              << " elements with std::list: " 
              << (double)(lstEnd - lstStart) / CLOCKS_PER_SEC 
              << "us" << std::endl;
    
    return 0;
}
```

---

## 5️⃣ Considerações Importantes

- ✅ **Dois Containers Obrigatórios**: `std::vector` + `std::list` (ou alternativas)
- ✅ **Ford-Johnson Algoritmo**: Padrão específico de sorting
- ⚠️ **Validação de Números**: Apenas positivos, sem duplicatas (subject specifica)
- 💡 **Performance Realis**: `std::vector` geralmente mais rápido para sorting (acesso)
- 🔧 **Containers Únicos**: Não reutilizar `std::map` (ex00) ou `std::stack` (ex01)

---

## 6️⃣ Checklist de Submissão

- [ ] Compila com `-Wall -Wextra -Werror -std=c++98` sem warnings
- [ ] Executável chamado `PmergeMe`
- [ ] Aceita números como argumentos
- [ ] Valida: números positivos, sem negativos ou inválidos
- [ ] Implementa Ford-Johnson sort (não trivial/std::sort simples)
- [ ] Usa `std::vector` para um container
- [ ] Usa `std::list` para outro container
- [ ] Ambos ordenados corretamente no final
- [ ] Mede e exibe tempo para cada container
- [ ] Output mostra: Before, After, Time vector, Time list
- [ ] Include guards + sem `using namespace std`
- [ ] Sem memory leaks

---

**Anterior**: [ex01 - RPN](./ex01_explanation.md)  
**Módulo Completo**: [cpp09 - STL Advanced](./ex00_explanation.md)
