# C++ Modules 07-09: Copilot Instructions

## 📚 Visão Geral do Projeto

Este projeto consiste em 3 módulos C++ que formam uma progressão estruturada na aprendizagem:

- **cpp07**: Introdução a Templates Genéricos
- **cpp08**: STL com Containers e Iteradores
- **cpp09**: STL Avançado com Algoritmos e Múltiplos Containers

Cada módulo contém 3 exercícios incrementais que constroem conhecimento progressivo de forma incremental.

---

## 🔧 Regras Gerais Compartilhadas

### Compilação

```bash
c++ -Wall -Wextra -Werror -std=c++98
```

- **Compilador**: `c++`
- **Flags obrigatórias**: `-Wall -Wextra -Werror`
- **Padrão**: C++98 (não C++11 ou superior)

### Convenções de Nomenclatura

- **Classes**: `UpperCamelCase` (ex: `BrickWall`, `MyClass`)
- **Arquivos de classe**: `ClassName.hpp`, `ClassName.cpp`
- **Diretórios de exercícios**: `ex00`, `ex01`, `ex02`, ..., `exn`
- **Outputs**: Devem terminar com newline (`\n`)

### Formatação de Código

- **Estilo**: Não é imposto, mas deve ser legível
- **Peer-evaluation**: Código que avaliadores não entendem não pode ser avaliado
- **Foco**: Clareza e manutenibilidade acima de tudo

---

## 🚫 Restrições e Proibições Globais

### Padrão C++

- ✅ **Permitido**: C++98
- ❌ **Proibido**: C++11 e derivados, Boost libraries

### Funções Proibidas

- ❌ `*printf()` (printf, fprintf, sprintf, etc.)
- ❌ `*alloc()` (malloc, calloc, realloc)
- ❌ `free()`
- ❌ `using namespace <ns_name>` → Penalidade: `-42`
- ❌ Keyword `friend` → Penalidade: `-42`

**Resultado de violação**: Nota `0` ou `-42`

### STL (Standard Template Library)

- **cpp07**: ❌ Nenhum container da STL (vector, list, map, etc.)
- **cpp07**: ❌ Nenhum algoritmo da STL (requer `#include <algorithm>`)
- **cpp08**: ✅ STL Containers e Iteradores permitidos (obrigatório usar)
- **cpp09**: ✅ STL completo com Algoritmos (obrigatório usar)

**Violação em cpp07**: Penalidade `-42`

### Implementação em Headers

- ✅ **Permitido**: Implementação de function templates em `.hpp`
- ❌ **Proibido**: Implementação de funções normais em headers (exceto templates)
- **Resultado**: Nota `0` no exercício

---

## 📐 Requisitos de Design

### Gestão de Memória

- ❌ **Proibido**: Memory leaks
- ✅ **Usar**: `new` e `delete` corretamente
- ✅ **Padrão**: RAII (Resource Acquisition Is Initialization)

### Orthodox Canonical Form

**Obrigatório para módulos 02-09** (exceto quando explicitamente indicado):

```cpp
class MyClass {
public:
    MyClass();                           // Construtor padrão
    MyClass(const MyClass& other);       // Construtor de cópia
    MyClass& operator=(const MyClass& other); // Operador de atribuição
    ~MyClass();                          // Destrutor
};
```

### Include Guards

```cpp
#ifndef CLASSNAME_HPP
#define CLASSNAME_HPP

// Código da classe

#endif
```

- ✅ **Obrigatório**: Todo arquivo `.hpp` deve ter include guards
- ✅ **Independência**: Headers devem incluir todas suas dependências
- ❌ **Proibido**: Double inclusion
- **Resultado de violação**: Nota `0`

### Makefile

#### Regras obrigatórias:
```makefile
$(NAME)   # Compilar o programa
all       # Padrão, compila $(NAME)
clean     # Remove arquivos objeto (.o)
fclean    # Remove objeto + executável
re        # Limpa e recompila (clean + all)
```

#### Requisitos:
- ✅ Usar `c++` como compilador
- ✅ Incluir flags `-Wall -Wextra -Werror -std=c++98`
- ✅ Evitar relink desnecessário
- ✅ Usar variáveis (NAME, SRCS, OBJS, CXXFLAGS)

#### Exemplo mínimo:
```makefile
NAME = program
SRCS = main.cpp ClassName.cpp
OBJS = $(SRCS:.cpp=.o)
CXXFLAGS = -Wall -Wextra -Werror -std=c++98
CXX = c++

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
```

---

## 📦 Especificidades por Módulo

### cpp07: C++ Templates

**Objetivo**: Aprender templates genéricos

**Características**:
- 3 exercícios: function templates e class templates
- ❌ STL proibido
- ✅ Templates em `.hpp`
- Foco: Genericidade e Type Safety

**Requisitos Específicos**:
- Funções template devem aceitar qualquer tipo compatível
- Class templates com múltiplas especializações
- Entender instantiação implícita do compilador

**Documentação**: `/docs/cpp07/ex00.md`, `ex01.md`, `ex02.md`

---

### cpp08: Templated Containers, Iterators, Algorithms

**Objetivo**: Aprender STL (containers, iteradores)

**Características**:
- 3 exercícios usando STL containers
- ✅ STL obrigatório quando apropriado
- ✅ Containers e Iteradores
- ❌ Algoritmos ainda não (relativo)

**Requisitos Específicos**:
- Usar containers quando apropriado (vector, list, map, etc.)
- Trabalhar com iteradores
- Entender lazy evaluation e template specialization

**Documentação**: `/docs/cpp08/ex00.md`, `ex01.md`, `ex02.md`

---

### cpp09: STL

**Objetivo**: Aprender STL completo com Algoritmos

**Características**:
- 3 exercícios usando múltiplos containers
- ✅ STL completamente obrigatório
- ✅ Algorithms (require `#include <algorithm>`)
- ⚠️ Cada container só pode ser usado UMA VEZ no módulo

**Requisitos Específicos**:
- Mínimo 1 container por exercício
- Exercício 02 requer 2 containers
- Uso obrigatório de algoritmos STL
- Não reutilizar containers já usados

**Documentação**: `/docs/cpp09/ex00.md`, `ex01.md`, `ex02.md`

---

## 📖 Referência Rápida de Headers

### Permitidos (Padrão C++98)

```cpp
#include <iostream>   // Input/Output
#include <fstream>    // File I/O
#include <sstream>    // String streams
#include <string>     // std::string
#include <cmath>      // Math functions
#include <cstdlib>    // General utilities
#include <cstring>    // C string utilities
#include <cctype>     // Character classification
#include <limits>     // Numeric limits
#include <exception>  // Exception handling
#include <stdexcept>  // Standard exceptions
```

### Permitidos em cpp08-09 (STL)

```cpp
#include <vector>     // Dynamic array
#include <list>       // Linked list
#include <map>        // Key-value pairs
#include <set>        // Unique elements
#include <queue>      // FIFO container
#include <stack>      // LIFO container
#include <deque>      // Double-ended queue
#include <algorithm>  // STL algorithms
#include <iterator>   // Iterator utilities
#include <functional> // Function objects
```

---

## 🗂️ Estrutura do Projeto

```
/cpp/
├── copilot-instructions.md          (este arquivo)
├── tasks/                           (Task lists por módulo)
│   ├── TEMPLATE.md                  (Template reutilizável)
│   ├── HOW_TO_USE.md                (Instruções de uso)
│   ├── cpp07_tasks.md               (Tasks do cpp07)
│   ├── cpp08_tasks.md               (Tasks do cpp08)
│   └── cpp09_tasks.md               (Tasks do cpp09)
├── docs/                            (Documentação técnica)
│   ├── cpp07/
│   │   ├── ex00.md
│   │   ├── ex01.md
│   │   └── ex02.md
│   ├── cpp08/
│   │   ├── ex00.md
│   │   ├── ex01.md
│   │   └── ex02.md
│   └── cpp09/
│       ├── ex00.md
│       ├── ex01.md
│       └── ex02.md
├── resources/                       (PDFs dos módulos)
│   ├── cpp07/
│   │   └── en.subject.pdf
│   ├── cpp08/
│   │   └── en.subject.pdf
│   └── cpp09/
│       └── en.subject.pdf
├── cpp07/                           (Código do módulo)
│   ├── ex00/
│   │   ├── Makefile
│   │   ├── main.cpp
│   │   └── [arquivos adicionais]
│   ├── ex01/
│   │   ├── Makefile
│   │   ├── main.cpp
│   │   └── [arquivos adicionais]
│   └── ex02/
│       ├── Makefile
│       ├── main.cpp
│       └── [arquivos adicionais]
├── cpp08/                           (Código do módulo)
│   ├── ex00/ ... ex02/
├── cpp09/                           (Código do módulo)
│   ├── ex00/ ... ex02/
```

---

## 📝 Como Usar Este Projeto

### Para Desenvolvedores

1. **Ler este arquivo** para entender as regras globais
2. **Consultar `/tasks/cpp0X_tasks.md`** para rastrear progresso
3. **Implementar código** em `cpp0X/exXX/`
4. **Consultar `/docs/cpp0X/exXX.md`** para referência técnica
5. **Validar** com Makefile e testes em `main.cpp`

### Para Próximas Iterações

1. **Ler `/tasks/TEMPLATE.md`** para entender a estrutura
2. **Consultar `/tasks/HOW_TO_USE.md`** para instruções
3. **Criar `/tasks/cpp0X_tasks.md`** baseado no template
4. **Seguir as 5 fases** de desenvolvimento
5. **Atualizar documentação** em `/docs/cpp0X/`

---

## 🔗 Links Rápidos

### Documentação por Módulo
- [cpp07 - Templates](./docs/cpp07/)
- [cpp08 - Containers & Iterators](./docs/cpp08/)
- [cpp09 - STL Algorithms](./docs/cpp09/)

### System de Tasks
- [Task Template](./tasks/TEMPLATE.md)
- [Como Usar Tasks](./tasks/HOW_TO_USE.md)

### Recursos
- [cpp07 Subject](./resources/cpp07/en.subject.pdf)
- [cpp08 Subject](./resources/cpp08/en.subject.pdf)
- [cpp09 Subject](./resources/cpp09/en.subject.pdf)

---

## �️ Utilitários e Scripts

### Converter PDF para Markdown

Para facilitar a leitura de PDFs pelo modelo, todos os PDFs são convertidos automaticamente para Markdown:

```bash
python3 .github/scripts/pdf_to_md.py <pdf_path>
```

**Exemplos de uso:**

```bash
python3 .github/scripts/pdf_to_md.py resources/cpp07/en.subject.pdf
python3 .github/scripts/pdf_to_md.py resources/cpp08/en.subject.pdf
python3 .github/scripts/pdf_to_md.py resources/cpp09/en.subject.pdf
```

Isso cria arquivos `.md` no mesmo diretório:
- `resources/cpp07/en.subject.md`
- `resources/cpp08/en.subject.md`
- `resources/cpp09/en.subject.md`

**Características:**
- ✅ O script verifica se o `.md` já existe (não sobrescreve)
- ✅ Extrai texto puro do PDF mantendo estrutura
- ✅ Arquivo de texto fácil de buscar e processar
- ✅ Idempotente (seguro rodar múltiplas vezes)

**Como o modelo usa:**
```python
# Ao precisar ler um PDF, o modelo automaticamente:
if not exists("resources/cpp07/en.subject.md"):
    run("python3 .github/scripts/pdf_to_md.py resources/cpp07/en.subject.pdf")
# Depois lê o .md (muito mais eficiente que processar PDF diretamente)
```

---

## 💡 Dicas Importantes

- **Compile frequentemente**: Use Makefile para validar a cada mudança
- **Leia os PDFs completamente**: As guidelines podem conter requisitos não óbvios
- **Teste com main.cpp**: Cada exercício deve demonstrar claramente seus requisitos
- **Evite memory leaks**: Use ferramentas como `valgrind` para validar
- **Include guards sempre**: Previne problemas de double inclusion
- **Templates em headers**: Única exceção para código em `.hpp`
- **Use PDFs como Markdown**: Converta PDFs para `.md` para melhor manipulação

---

**Última atualização**: 7 de Março de 2026
