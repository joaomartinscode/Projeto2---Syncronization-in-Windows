# Pseudocódigo do Sistema de Encomendas Multithread

## Thread Principal (Main)

1. Validar argumentos da linha de comandos
2. Inicializar valores de tempo mínimo e máximo
3. Inicializar gerador de números aleatórios
4. Apagar ficheiro de log antigo
5. Abrir ficheiro de log para escrita
6. Abrir ficheiro de encomendas
7. Criar mutexes:
   - Exclusão da lista de encomendas
   - Exclusão dos contadores
   - Exclusão do ficheiro ecrã/log
8. Criar semáforos:
   - Lugares disponíveis na lista
   - Encomendas disponíveis para processamento
9. Criar thread de monitorização
10. Criar N threads de trabalhadores
11. Enquanto existirem encomendas no ficheiro:
    - Ler encomenda
    - Alocar memória para a encomenda
    - Inserir encomenda na lista partilhada
12. Fechar ficheiro de encomendas
13. Sinalizar que não existirão mais encomendas
14. Acordar todas as threads trabalhadoras bloqueadas
15. Esperar que todas as threads trabalhadoras terminem
16. Esperar que a thread de monitorização termine
17. Libertar recursos (threads, mutexes, semáforos, memória)
18. Fechar ficheiro de log
19. Terminar programa

---

## Thread Trabalhadora (Worker)

1. Obter identificador da thread
2. Enquanto verdadeiro:
   - Esperar até existir uma encomenda disponível
   - Entrar em exclusão mútua da lista
   - Se a lista estiver vazia:
     - Sair da exclusão mútua
     - Se o processamento estiver terminado:
       - Sair do ciclo
     - Continuar
   - Remover encomenda da lista
   - Sair da exclusão mútua
   - Atualizar contadores:
     - Incrementar "a processar"
   - Simular processamento:
     - Calcular tempo aleatório
     - Dormir durante esse tempo
   - Entrar em exclusão mútua do ficheiro de log
   - Escrever informação da encomenda processada
   - Sair da exclusão mútua
   - Atualizar contadores:
     - Decrementar "a processar"
     - Incrementar "concluídas"
   - Libertar memória da encomenda
3. Terminar thread

---

## Thread de Monitorização

1. Enquanto verdadeiro:
   - Entrar em exclusão mútua da lista
   - Ler número de encomendas pendentes
   - Sair da exclusão mútua
   - Entrar em exclusão mútua dos contadores
   - Ler número de encomendas:
     - A processar
     - Concluídas
   - Se processamento terminado E
     - Pendentes == 0 E
     - A processar == 0:
       - Mostrar estatísticas finais
       - Sair da exclusão mútua
       - Sair do ciclo
   - Sair da exclusão mútua
   - Mostrar estatísticas no ecrã
   - Esperar 1 segundo
2. Terminar thread