# cpp09/ex00: Bitcoin Exchange

## 1️⃣ Visão Geral

Programa que lê histórico de preços de Bitcoin em arquivo CSV e calcula valores em datas específicas usando interpolação (data anterior mais próxima se data exata não existe). É a primeira aplicação "real" de STL, usando **`std::map`** para indexar preços por data com lookup rápido. Container: `std::map` *(não reutilizável em ex01-ex02)*.

---

## 2️⃣ Conceitos-Chave Aprendidos

- **std::map<K, V>**: Dicionário ordenado por chave (data) → valor (preço)
- **std::map::lower_bound()**: Encontra data anterior mais próxima
- **Parsing de CSV**: Ler linhas, splitar por `,`, validar formato
- **Validação de Entrada**: Data válida (YYYY-MM-DD), valor (0-1000)
- **Error Handling**: Mensagens claras para entrada inválida
- **Lógica de Interpolação**: Se data not found, usar maior data < solicitada

---

## 3️⃣ Arquitetura

```
btc [arquivo_input.txt]
├── 1. Carregar data.csv em std::map<std::string, float>
│   └── Validar e ignorar erros de leitura
├── 2. Ler arquivo_input linha por linha
│   ├── Parse formato: "date | value"
│   ├── Validar: data (YYYY-MM-DD) e valor (0-1000)
│   ├── lower_bound(data) na map
│   └── Calcular: valor × taxa de câmbio
└── 3. Output ou erro
```

**Fluxo**: Load CSV → Validate input → Lookup map → Calculate → Output.

---

## 4️⃣ Exemplo Prático Mínimo

```cpp
std::map<std::string, float> db;

// Carregar CSV
std::ifstream csvFile("data.csv");
std::string line;
while (std::getline(csvFile, line)) {
    size_t pos = line.find(',');
    std::string date = line.substr(0, pos);
    float rate = std::strtof(line.c_str() + pos + 1, NULL);
    db[date] = rate;
}

// Processar entrada
std::ifstream inputFile(argv[1]);
while (std::getline(inputFile, line)) {
    size_t pos = line.find(" | ");
    std::string date = line.substr(0, pos);
    float value = std::strtof(line.c_str() + pos + 3, NULL);
    
    // Validar
    if (value < 0 || value > 1000) {
        std::cout << "Error: too large a number." << std::endl;
        continue;
    }
    
    // Buscar taxa
    std::map<std::string, float>::iterator it = db.lower_bound(date);
    if (it == db.begin() && it->first != date)
        continue;  // Data anterior a primeiro registro
    if (it->first != date)
        --it;
    
    std::cout << date << " => " << value << " = " 
              << (value * it->second) << std::endl;
}
```

---

## 5️⃣ Considerações Importantes

- ✅ **std::map Obrigatório**: Para lookup O(log n) eficiente
- ✅ **CSV Fixed**: `data.csv` sempre em formato `date,rate`
- ⚠️ **Validação Rigorosa**: Data format, valor range, arquivo missing
- 💡 **lower_bound**: Retorna iterator para first element ≥ key
- 🔧 **Container Único**: `std::map` não pode ser usado em ex01/ex02

---

## 6️⃣ Checklist de Submissão

- [ ] Compila com `-Wall -Wextra -Werror -std=c++98` sem warnings
- [ ] Executável chamado `btc`
- [ ] Lê `data.csv` corretamente
- [ ] Lê arquivo de entrada via argumento (erro se missing/inválido)
- [ ] Valida data (YYYY-MM-DD) e valor (0-1000, ≥0)
- [ ] Usa `lower_bound()` para encontrar data anterior
- [ ] Output exato: `date => value = result`
- [ ] Mensagens de erro apropriadas
- [ ] Include guards + Orthodox Canonical Form
- [ ] Sem memory leaks

---

**Anterior (cpp08)**: [cpp08/ex02 - MutantStack](../cpp08/ex02_explanation.md)  
**Próximo**: [ex01 - RPN](./ex01_explanation.md)
