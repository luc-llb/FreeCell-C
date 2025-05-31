# 🃏 FreeCell em C

Implementação do jogo **FreeCell** em linguagem **C**, desenvolvida como projeto da disciplina **Estrutura de Dados (ECOP02)**, do curso de **Engenharia da Computação** da **Universidade Federal de Itajubá (UNIFEI)**.

## 📝 Sobre o Jogo

**FreeCell** é um jogo de cartas do estilo paciência, jogado com um baralho padrão de **52 cartas**. O objetivo é organizar as cartas em 4 pilhas (uma para cada naipe) em ordem crescente, começando do **Ás (1)** e seguindo até o **Rei (13)**.

### Regras principais:

* As cartas devem ser movidas respeitando a ordem crescente e alternância de cores nas colunas.
* Existem "células livres" que podem temporariamente armazenar cartas.
* O jogo é vencido ao completar todas as pilhas finais corretamente.

## 📂 Etapas do Projeto

* **Primeira Etapa:**

  * Arquivo: [`FreeCell.c`](./FreeCell.c)
  * Implementação básica do jogo com **3 tipos de jogadas**.

* **Segunda Etapa:**

  * Arquivo: [`Free_Cell2.c`](./Free_Cell2.c)
  * Adição de mais **4 tipos de jogadas**, exigindo mudanças na estrutura e na lógica do código anterior.

## 🧾 Requisitos

Para compilar e executar o projeto, você precisará de:

* Compilador **C** (ex: `gcc`, `clang`)
* Terminal compatível (Linux, macOS ou Windows com suporte a linha de comando)

## ▶️ Como Compilar e Executar

### Usando GCC:

```bash
# Primeira etapa
gcc -o freecell FreeCell.c
./freecell

# Segunda etapa (versão aprimorada)
gcc -o freecell2 Free_Cell2.c
./freecell2
```

## 🧠 Conceitos Aplicados

* Manipulação de listas e pilhas
* Estruturas condicionais e laços
* Lógica de jogos com cartas
* Modularização e organização de código
* Manipulação de strings e estruturas em C

## 🎓 Sobre

Projeto desenvolvido na disciplina **Estrutura de Dados (ECOP02)**, ofertada pela **Universidade Federal de Itajubá (UNIFEI)** para o curso de **Engenharia da Computação**.
