# cpp09/ex01: Reverse Polish Notation (RPN)

## 1️⃣ Visão Geral

Implementar uma **calculadora RPN** que processa expressões em notação polonesa reversa (operandos primeiro, depois operador). Exemplo: `3 4 +` = 7 (em vez de `3 + 4`). Usa **`std::stack`** para processar operandos e operações. Container: `std::stack` *(não reutilizável em ex00/ex02)*.

---

## 2️⃣ Conceitos-Chave Aprendidos

- **std::stack**: Estrutura LIFO para operandos
- **Parsing Tokenizado**: Split string por espaços, identificar números vs operadores
- **Operações Matemáticas**: Aplicar operador aos dois últimos operandos
- **Error Handling**: Stack underflow, divisão por zero, expressão inválida
- **Algoritmo de Avaliação RPN**: Padrão clássico de compiladores

---

## 3️⃣ Arquitetura

```
RPN [expressão]
├── 1. Parse tokens (split por espaço)
├── 2. Para cada token:
│   ├── Se número (0-9): push para stack
│   ├── Se operador (+, -, *, /):
│   │   ├── Pop dois operandos (b, depois a)
│   │   ├── Calcular a OP b
│   │   └── Push resultado
│   └── Senão: erro
├── 3. Stack deve ter exatamente 1 elemento no final
└── 4. Output resultado
```

**Fluxo**: Tokens → Process RPN → Stack → Result.

---

## 4️⃣ Exemplo Prático Mínimo

```cpp
#include <stack>
#include <iostream>
#include <sstream>
#include <cstdlib>

int main(int ac, char **av) {
    if (ac != 2) return 1;
    
    std::stack<double> stack;
    std::istringstream iss(av[1]);
    std::string token;
    
    while (iss >> token) {
        if (token == "+" || token == "-" || 
            token == "*" || token == "/") {
            
            if (stack.size() < 2) {
                std::cerr << "Error" << std::endl;
                return 1;
            }
            
            double b = stack.top(); stack.pop();
            double a = stack.top(); stack.pop();
            double result = 0;
            
            if (token == "+") result = a + b;
            else if (token == "-") result = a - b;
            else if (token == "*") result = a * b;
            else if (token == "/") {
                if (b == 0) {
                    std::cerr << "Error: division by zero" << std::endl;
                    return 1;
                }
                result = a / b;
            }
            
            stack.push(result);
        } else {
            char* endptr;
            double num = std::strtod(token.c_str(), &endptr);
            if (*endptr != '\0') {
                std::cerr << "Error" << std::endl;
                return 1;
            }
            stack.push(num);
        }
    }
    
    if (stack.size() != 1) {
        std::cerr << "Error" << std::endl;
        return 1;
    }
    
    std::cout << stack.top() << std::endl;
    return 0;
}
```

---

## 5️⃣ Considerações Importantes

- ✅ **std::stack Obrigatório**: Para gerenciar operandos
- ✅ **Números < 10**: Entrada sempre 0-9, não multi-dígitos
- ⚠️ **Validações**: Stack underflow, division by zero, token inválido
- 💡 **Números Floating-Point**: Resultado pode ser decimal
- 🔧 **Container Único**: `std::stack` não pode ser usado em ex00/ex02

---

## 6️⃣ Checklist de Submissão

- [ ] Compila com `-Wall -Wextra -Werror -std=c++98` sem warnings
- [ ] Executável chamado `RPN`
- [ ] Aceita expressão RPN como argumento (1 string entre aspas)
- [ ] Parseia tokens corretamente (números e operadores)
- [ ] Processa `+`, `-`, `*`, `/` corretamente
- [ ] Valida: stack underflow, divisão por zero, token inválido
- [ ] Resultado final exato quando válido
- [ ] Mensagem de erro apropriada em caso inválido
- [ ] Include guards + sem `using namespace std`
- [ ] Sem memory leaks

---

**Anterior**: [ex00 - Bitcoin Exchange](./ex00_explanation.md)  
**Próximo**: [ex02 - PmergeMe](./ex02_explanation.md)
